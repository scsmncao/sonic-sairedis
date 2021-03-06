#include "sai_redis.h"
#include <thread>

#include "selectableevent.h"

// if we will not get response in 60 seconds when
// notify syncd to compile new state or to switch
// to compiled state, then there is something wrong
#define NOTIFY_SYNCD_TIMEOUT (60*1000)

#define NOTIFY_SAI_INIT_VIEW    "SAI_INIT_VIEW"
#define NOTIFY_SAI_APPLY_VIEW   "SAI_APPLY_VIEW"

sai_switch_notification_t redis_switch_notifications;

bool g_switchInitialized = false;
volatile bool g_run = false;

std::shared_ptr<std::thread> notification_thread;

// this event is used to nice end notifications thread
swss::SelectableEvent g_redisNotificationTrheadEvent;

void ntf_thread()
{
    SWSS_LOG_ENTER();

    swss::Select s;

    s.addSelectable(g_redisNotifications);
    s.addSelectable(&g_redisNotificationTrheadEvent);

    while (g_run)
    {
        swss::Selectable *sel;

        int fd;

        int result = s.select(&sel, &fd);

        if (sel == &g_redisNotificationTrheadEvent)
        {
            // user requested shutdown_switch
            break;
        }

        if (result == swss::Select::OBJECT)
        {
            swss::KeyOpFieldsValuesTuple kco;

            std::string op;
            std::string data;
            std::vector<swss::FieldValueTuple> values;

            g_redisNotifications->pop(op, data, values);

            SWSS_LOG_DEBUG("notification: op = %s, data = %s", op.c_str(), data.c_str());

            handle_notification(op, data, values);
        }
    }
}

sai_status_t notify_syncd(const std::string &op)
{
    SWSS_LOG_ENTER();

    std::vector<swss::FieldValueTuple> entry;

    g_notifySyncdProducer->send(op, "", entry);

    swss::Select s;

    s.addSelectable(g_notifySyncdConsumer);

    SWSS_LOG_DEBUG("wait for response after: %s", op.c_str());

    swss::Selectable *sel;

    int fd;

    int result = s.select(&sel, &fd, NOTIFY_SYNCD_TIMEOUT);

    if (result == swss::Select::OBJECT)
    {
        swss::KeyOpFieldsValuesTuple kco;

        std::string op;
        std::string data;
        std::vector<swss::FieldValueTuple> values;

        g_notifySyncdConsumer->pop(op, data, values);

        const std::string &strStatus = op;

        sai_status_t status;

        int index = 0;
        sai_deserialize_primitive(strStatus, index, status);

        SWSS_LOG_INFO("%s status: %d", op.c_str(), status);

        return status;
    }

    SWSS_LOG_ERROR("%s get response failed, result: %d", op.c_str(), result);

    return SAI_STATUS_FAILURE;
}

/**
* Routine Description:
*   SDK initialization. After the call the capability attributes should be
*   ready for retrieval via sai_get_switch_attribute().
*
* Arguments:
*   @param[in] profile_id - Handle for the switch profile.
*   @param[in] switch_hardware_id - Switch hardware ID to open
*   @param[in] firmware_path_name - Vendor specific path name of the firmware
*                                   to load
*   @param[in] switch_notifications - switch notification table
* Return Values:
*   @return SAI_STATUS_SUCCESS on success
*           Failure status code on error
*/
sai_status_t redis_initialize_switch(
    _In_ sai_switch_profile_id_t profile_id,
    _In_reads_z_(SAI_MAX_HARDWARE_ID_LEN) char* switch_hardware_id,
    _In_reads_opt_z_(SAI_MAX_FIRMWARE_PATH_NAME_LEN) char* firmware_path_name,
    _In_ sai_switch_notification_t* switch_notifications)
{
    std::lock_guard<std::mutex> lock(g_mutex);

    SWSS_LOG_ENTER();

    if (firmware_path_name == NULL)
    {
        SWSS_LOG_ERROR("firmware path name is NULL");

        return SAI_STATUS_FAILURE;
    }

    std::string op = std::string(firmware_path_name);

    SWSS_LOG_INFO("operation: '%s'", op.c_str());

    if (op == NOTIFY_SAI_INIT_VIEW || op == NOTIFY_SAI_APPLY_VIEW)
    {
        sai_status_t status = notify_syncd(op);

        if (status == SAI_STATUS_SUCCESS)
        {
            SWSS_LOG_NOTICE("sending %s to syncd succeeded", op.c_str());

            if (g_switchInitialized)
            {
                return status;
            }

            // proceed with proper initialization
        }
        else
        {
            SWSS_LOG_ERROR("sending %s to syncd failed: %d", op.c_str(), status);

            return status;
        }
    }
    else
    {
        SWSS_LOG_WARN("unknown operation: '%s'", op.c_str());
    }

    if (g_switchInitialized)
    {
        SWSS_LOG_ERROR("switch is already initialized");

        return SAI_STATUS_FAILURE;
    }

    g_switchInitialized = true;

    if (switch_notifications != NULL)
    {
        memcpy(&redis_switch_notifications,
               switch_notifications,
               sizeof(sai_switch_notification_t));
    }
    else
    {
        memset(&redis_switch_notifications, 0, sizeof(sai_switch_notification_t));
    }

    g_run = true;

    SWSS_LOG_DEBUG("creating notification thread");

    notification_thread = std::make_shared<std::thread>(std::thread(ntf_thread));

    return SAI_STATUS_SUCCESS;
}

/**
 * Routine Description:
 *   @brief Release all resources associated with currently opened switch
 *
 * Arguments:
 *   @param[in] warm_restart_hint - hint that indicates controlled warm restart.
 *                            Since warm restart can be caused by crash
 *                            (therefore there are no guarantees for this call),
 *                            this hint is really a performance optimization.
 *
 * Return Values:
 *   None
 */
void  redis_shutdown_switch(
    _In_ bool warm_restart_hint)
{
    std::lock_guard<std::mutex> lock(g_mutex);

    SWSS_LOG_ENTER();

    if (!g_switchInitialized)
    {
        SWSS_LOG_ERROR("not initialized");

        return;
    }

    g_run = false;

    // notify thread that it should end
    g_redisNotificationTrheadEvent.notify();

    notification_thread->join();

    g_switchInitialized = false;

    memset(&redis_switch_notifications, 0, sizeof(sai_switch_notification_t));
}

/**
 * Routine Description:
 *   SDK connect. This API connects library to the initialized SDK.
 *   After the call the capability attributes should be ready for retrieval
 *   via sai_get_switch_attribute().
 *
 * Arguments:
 *   @param[in] profile_id - Handle for the switch profile.
 *   @param[in] switch_hardware_id - Switch hardware ID to open
 *   @param[in] switch_notifications - switch notification table
 * Return Values:
 *   @return SAI_STATUS_SUCCESS on success
 *           Failure status code on error
 */
sai_status_t redis_connect_switch(
    _In_ sai_switch_profile_id_t profile_id,
    _In_reads_z_(SAI_MAX_HARDWARE_ID_LEN) char* switch_hardware_id,
    _In_ sai_switch_notification_t* switch_notifications)
{
    std::lock_guard<std::mutex> lock(g_mutex);

    SWSS_LOG_ENTER();

    SWSS_LOG_ERROR("not implemented");

    return SAI_STATUS_NOT_IMPLEMENTED;
}

/**
 * Routine Description:
 *   @brief Disconnect this SAI library from the SDK.
 *
 * Arguments:
 *   None
 * Return Values:
 *   None
 */
void redis_disconnect_switch(void)
{
    std::lock_guard<std::mutex> lock(g_mutex);

    SWSS_LOG_ENTER();

    SWSS_LOG_ERROR("not implemented");
}

/**
 * Routine Description:
 *    @brief Set switch attribute value
 *
 * Arguments:
 *    @param[in] attr - switch attribute
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t  redis_set_switch_attribute(
    _In_ const sai_attribute_t *attr)
{
    SWSS_LOG_ENTER();

    sai_status_t status = redis_generic_set(
            SAI_OBJECT_TYPE_SWITCH,
            (sai_object_id_t)0, // dummy sai_object_id_t for switch
            attr);

    return status;
}

/**
 * Routine Description:
 *    @brief Get switch attribute value
 *
 * Arguments:
 *    @param[in] attr_count - number of switch attributes
 *    @param[inout] attr_list - array of switch attributes
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t  redis_get_switch_attribute(
    _In_ sai_uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_list)
{
    SWSS_LOG_ENTER();

    sai_status_t status = redis_generic_get(
            SAI_OBJECT_TYPE_SWITCH,
            (sai_object_id_t)0,
            attr_count,
            attr_list);

    return status;
}

/**
 * @brief Switch method table retrieved with sai_api_query()
 */
const sai_switch_api_t redis_switch_api = {
    redis_initialize_switch,
    redis_shutdown_switch,
    redis_connect_switch,
    redis_disconnect_switch,
    redis_set_switch_attribute,
    redis_get_switch_attribute,
};
