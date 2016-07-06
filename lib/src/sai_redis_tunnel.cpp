#include "sai_redis.h"

/**
 * Routine Description:
 *    @brief Create tunnel
 *
 * Arguments:
 *    @param[out] tunnel_id - tunnel id
 *    @param[in] attr_count - number of attributes
 *    @param[in] attr_list - array of attributes
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 *
 * Note: IP address expected in Network Byte Order.
 */
sai_status_t  redis_create_tunnel(
    _Out_ sai_object_id_t* tunnel_id,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t *attr_list)
{
    SWSS_LOG_ENTER();

    sai_status_t status = redis_generic_create(
            SAI_OBJECT_TYPE_TUNNEL,
            tunnel_id,
            attr_count,
            attr_list);

    return status;
}

/**
 *  @brief tunnel table methods, retrieved via sai_api_query()
 */
const sai_tunnel_api_t redis_tunnel_api = {
    redis_create_tunnel,
};