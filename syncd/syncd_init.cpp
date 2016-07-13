#include "syncd.h"

create_fn           common_create[SAI_OBJECT_TYPE_MAX];
remove_fn           common_remove[SAI_OBJECT_TYPE_MAX];
set_attribute_fn    common_set_attribute[SAI_OBJECT_TYPE_MAX];
get_attribute_fn    common_get_attribute[SAI_OBJECT_TYPE_MAX];

sai_acl_api_t                *sai_acl_api;
sai_buffer_api_t             *sai_buffer_api;
sai_fdb_api_t                *sai_fdb_api;
sai_hash_api_t               *sai_hash_api;
sai_hostif_api_t             *sai_hostif_api;
sai_lag_api_t                *sai_lag_api;
sai_mirror_api_t             *sai_mirror_api;
sai_neighbor_api_t           *sai_neighbor_api;
sai_next_hop_api_t           *sai_next_hop_api;
sai_next_hop_group_api_t     *sai_next_hop_group_api;
sai_policer_api_t            *sai_policer_api;
sai_port_api_t               *sai_port_api;
sai_qos_map_api_t            *sai_qos_map_api;
sai_queue_api_t              *sai_queue_api;
sai_route_api_t              *sai_route_api;
sai_router_interface_api_t   *sai_router_interface_api;
sai_samplepacket_api_t       *sai_samplepacket_api;
sai_scheduler_api_t          *sai_scheduler_api;
sai_scheduler_group_api_t    *sai_scheduler_group_api;
sai_stp_api_t                *sai_stp_api;
sai_switch_api_t             *sai_switch_api;
sai_tunnel_api_t             *sai_tunnel_api;
sai_udf_api_t                *sai_udf_api;
sai_virtual_router_api_t     *sai_router_api;
sai_vlan_api_t               *sai_vlan_api;
sai_wred_api_t               *sai_wred_api;

void initialize_common_api_pointers()
{
    SWSS_LOG_ENTER();

    common_create[SAI_OBJECT_TYPE_NULL] = NULL;
    common_create[SAI_OBJECT_TYPE_PORT] = NULL;
    common_create[SAI_OBJECT_TYPE_LAG] = (sai_lag_api) ? sai_lag_api->create_lag : NULL;
    common_create[SAI_OBJECT_TYPE_VIRTUAL_ROUTER] = (sai_router_api) ? sai_router_api->create_virtual_router : NULL;
    common_create[SAI_OBJECT_TYPE_NEXT_HOP] = (sai_next_hop_api) ? sai_next_hop_api->create_next_hop : NULL;
    common_create[SAI_OBJECT_TYPE_NEXT_HOP_GROUP] = (sai_next_hop_group_api) ? sai_next_hop_group_api->create_next_hop_group : NULL;
    common_create[SAI_OBJECT_TYPE_ROUTER_INTERFACE] = (sai_router_interface_api) ? sai_router_interface_api->create_router_interface : NULL;
    common_create[SAI_OBJECT_TYPE_ACL_TABLE] = (sai_acl_api) ? sai_acl_api->create_acl_table : NULL;
    common_create[SAI_OBJECT_TYPE_ACL_ENTRY] = (sai_acl_api) ? sai_acl_api->create_acl_entry : NULL;
    common_create[SAI_OBJECT_TYPE_ACL_COUNTER] = (sai_acl_api) ? sai_acl_api->create_acl_counter : NULL;
    common_create[SAI_OBJECT_TYPE_HOST_INTERFACE] = (sai_hostif_api) ? sai_hostif_api->create_hostif : NULL;
    common_create[SAI_OBJECT_TYPE_TRAP_GROUP] = (sai_hostif_api) ? sai_hostif_api->create_hostif_trap_group : NULL;
    common_create[SAI_OBJECT_TYPE_ACL_TABLE_GROUP] = NULL;
    common_create[SAI_OBJECT_TYPE_POLICER] = (sai_policer_api) ? sai_policer_api->create_policer : NULL;
    common_create[SAI_OBJECT_TYPE_WRED] = (sai_wred_api) ? sai_wred_api->create_wred_profile : NULL;
    common_create[SAI_OBJECT_TYPE_QOS_MAPS] = (sai_qos_map_api) ? sai_qos_map_api->create_qos_map : NULL;
    common_create[SAI_OBJECT_TYPE_QUEUE] = NULL;
    common_create[SAI_OBJECT_TYPE_SCHEDULER] = (sai_scheduler_api) ? sai_scheduler_api->create_scheduler_profile : NULL;
    common_create[SAI_OBJECT_TYPE_SCHEDULER_GROUP] = (sai_scheduler_group_api) ? sai_scheduler_group_api->create_scheduler_group : NULL;
    common_create[SAI_OBJECT_TYPE_BUFFER_POOL] = (sai_buffer_api) ? sai_buffer_api->create_buffer_pool : NULL;
    common_create[SAI_OBJECT_TYPE_BUFFER_PROFILE] = (sai_buffer_api) ? sai_buffer_api->create_buffer_profile : NULL;
    common_create[SAI_OBJECT_TYPE_PRIORITY_GROUP] = NULL;
    common_create[SAI_OBJECT_TYPE_LAG_MEMBER] = (sai_lag_api) ? sai_lag_api->create_lag_member : NULL;
    common_create[SAI_OBJECT_TYPE_VLAN_MEMBER] = (sai_vlan_api) ? sai_vlan_api->create_vlan_member : NULL;
    common_create[SAI_OBJECT_TYPE_TUNNEL] = (sai_tunnel_api) ? sai_tunnel_api->create_tunnel : NULL;
    common_create[SAI_OBJECT_TYPE_TUNNEL_TABLE_ENTRY] = (sai_tunnel_api) ? sai_tunnel_api->create_tunnel_term_table_entry : NULL;
    common_create[SAI_OBJECT_TYPE_FDB] =  NULL;
    common_create[SAI_OBJECT_TYPE_SWITCH] = NULL;
    common_create[SAI_OBJECT_TYPE_TRAP] = NULL;
    common_create[SAI_OBJECT_TYPE_TRAP_USER_DEF] = NULL;
    common_create[SAI_OBJECT_TYPE_NEIGHBOR] = NULL;
    common_create[SAI_OBJECT_TYPE_ROUTE] = NULL;
    common_create[SAI_OBJECT_TYPE_VLAN] = NULL;

    common_remove[SAI_OBJECT_TYPE_NULL] = NULL;
    common_remove[SAI_OBJECT_TYPE_PORT] = NULL;
    common_remove[SAI_OBJECT_TYPE_LAG] = (sai_lag_api) ? sai_lag_api->remove_lag : NULL;
    common_remove[SAI_OBJECT_TYPE_VIRTUAL_ROUTER] = (sai_router_api) ? sai_router_api->remove_virtual_router : NULL;
    common_remove[SAI_OBJECT_TYPE_NEXT_HOP] = (sai_next_hop_api) ? sai_next_hop_api->remove_next_hop : NULL;
    common_remove[SAI_OBJECT_TYPE_NEXT_HOP_GROUP] = (sai_next_hop_group_api) ? sai_next_hop_group_api->remove_next_hop_group : NULL;
    common_remove[SAI_OBJECT_TYPE_ROUTER_INTERFACE] = (sai_router_interface_api) ? sai_router_interface_api->remove_router_interface : NULL;
    common_remove[SAI_OBJECT_TYPE_ACL_TABLE] = (sai_acl_api) ? sai_acl_api->delete_acl_table : NULL;
    common_remove[SAI_OBJECT_TYPE_ACL_ENTRY] = (sai_acl_api) ? sai_acl_api->delete_acl_entry : NULL;
    common_remove[SAI_OBJECT_TYPE_ACL_COUNTER] = (sai_acl_api) ? sai_acl_api->delete_acl_counter : NULL;
    common_remove[SAI_OBJECT_TYPE_HOST_INTERFACE] = (sai_hostif_api) ? sai_hostif_api->remove_hostif : NULL;
    common_remove[SAI_OBJECT_TYPE_TRAP_GROUP] = (sai_hostif_api) ? sai_hostif_api->remove_hostif_trap_group : NULL;
    common_remove[SAI_OBJECT_TYPE_ACL_TABLE_GROUP] = NULL;
    common_remove[SAI_OBJECT_TYPE_POLICER] = (sai_policer_api) ? sai_policer_api->remove_policer : NULL;
    common_remove[SAI_OBJECT_TYPE_WRED] = (sai_wred_api) ? sai_wred_api->remove_wred_profile : NULL;
    common_remove[SAI_OBJECT_TYPE_QOS_MAPS] = (sai_qos_map_api) ? sai_qos_map_api->remove_qos_map : NULL;
    common_remove[SAI_OBJECT_TYPE_QUEUE] = NULL;
    common_remove[SAI_OBJECT_TYPE_SCHEDULER] = (sai_scheduler_api) ? sai_scheduler_api->remove_scheduler_profile : NULL;
    common_remove[SAI_OBJECT_TYPE_SCHEDULER_GROUP] = (sai_scheduler_group_api) ? sai_scheduler_group_api->remove_scheduler_group : NULL;
    common_remove[SAI_OBJECT_TYPE_BUFFER_POOL] = (sai_buffer_api) ? sai_buffer_api->remove_buffer_pool : NULL;
    common_remove[SAI_OBJECT_TYPE_BUFFER_PROFILE] = (sai_buffer_api) ? sai_buffer_api->remove_buffer_profile : NULL;
    common_remove[SAI_OBJECT_TYPE_PRIORITY_GROUP] = NULL;
    common_remove[SAI_OBJECT_TYPE_LAG_MEMBER] = (sai_lag_api) ? sai_lag_api->remove_lag_member : NULL;
    common_remove[SAI_OBJECT_TYPE_VLAN_MEMBER] = (sai_vlan_api) ? sai_vlan_api->remove_vlan_member : NULL;
    common_remove[SAI_OBJECT_TYPE_TUNNEL] = (sai_tunnel_api) ? sai_tunnel_api->remove_tunnel : NULL;
    common_remove[SAI_OBJECT_TYPE_TUNNEL_TABLE_ENTRY] = (sai_tunnel_api) ? sai_tunnel_api->remove_tunnel_term_table_entry : NULL;
    common_remove[SAI_OBJECT_TYPE_FDB] =  NULL;
    common_remove[SAI_OBJECT_TYPE_SWITCH] = NULL;
    common_remove[SAI_OBJECT_TYPE_TRAP] = NULL;
    common_remove[SAI_OBJECT_TYPE_TRAP_USER_DEF] = NULL;
    common_remove[SAI_OBJECT_TYPE_NEIGHBOR] = NULL;
    common_remove[SAI_OBJECT_TYPE_ROUTE] = NULL;
    common_remove[SAI_OBJECT_TYPE_VLAN] = NULL;

    common_set_attribute[SAI_OBJECT_TYPE_NULL] = NULL;
    common_set_attribute[SAI_OBJECT_TYPE_PORT] = (sai_port_api) ? sai_port_api->set_port_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_LAG] = (sai_lag_api) ? sai_lag_api->set_lag_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_VIRTUAL_ROUTER] = (sai_router_api) ? sai_router_api->set_virtual_router_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_NEXT_HOP] = (sai_next_hop_api) ? sai_next_hop_api->set_next_hop_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_NEXT_HOP_GROUP] = (sai_next_hop_group_api) ? sai_next_hop_group_api->set_next_hop_group_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_ROUTER_INTERFACE] = (sai_router_interface_api) ? sai_router_interface_api->set_router_interface_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_ACL_TABLE] = (sai_acl_api) ? sai_acl_api->set_acl_table_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_ACL_ENTRY] = (sai_acl_api) ? sai_acl_api->set_acl_entry_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_ACL_COUNTER] = (sai_acl_api) ? sai_acl_api->set_acl_counter_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_HOST_INTERFACE] = (sai_hostif_api) ? sai_hostif_api->set_hostif_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_TRAP_GROUP] = (sai_hostif_api) ? sai_hostif_api->set_trap_group_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_ACL_TABLE_GROUP] = NULL;
    common_set_attribute[SAI_OBJECT_TYPE_POLICER] = (sai_policer_api) ? sai_policer_api->set_policer_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_WRED] = (sai_wred_api) ? sai_wred_api->set_wred_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_QOS_MAPS] = (sai_qos_map_api) ? sai_qos_map_api->set_qos_map_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_QUEUE] = (sai_queue_api) ? sai_queue_api->set_queue_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_SCHEDULER] = (sai_scheduler_api) ? sai_scheduler_api->set_scheduler_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_SCHEDULER_GROUP] = (sai_scheduler_group_api) ? sai_scheduler_group_api->set_scheduler_group_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_BUFFER_POOL] = (sai_buffer_api) ? sai_buffer_api->set_buffer_pool_attr : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_BUFFER_PROFILE] = (sai_buffer_api) ? sai_buffer_api->set_buffer_profile_attr : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_PRIORITY_GROUP] = (sai_buffer_api) ? sai_buffer_api->set_ingress_priority_group_attr : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_LAG_MEMBER] = (sai_lag_api) ? sai_lag_api->set_lag_member_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_VLAN_MEMBER] = (sai_vlan_api) ? sai_vlan_api->set_vlan_member_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_TUNNEL] = (sai_tunnel_api) ? sai_tunnel_api->set_tunnel_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_TUNNEL_TABLE_ENTRY] = (sai_tunnel_api) ? sai_tunnel_api->set_tunnel_term_table_entry_attribute : NULL;
    common_set_attribute[SAI_OBJECT_TYPE_FDB] =  NULL;
    common_set_attribute[SAI_OBJECT_TYPE_SWITCH] = NULL;
    common_set_attribute[SAI_OBJECT_TYPE_TRAP] = NULL;
    common_set_attribute[SAI_OBJECT_TYPE_TRAP_USER_DEF] = NULL;
    common_set_attribute[SAI_OBJECT_TYPE_NEIGHBOR] = NULL;
    common_set_attribute[SAI_OBJECT_TYPE_ROUTE] = NULL;
    common_set_attribute[SAI_OBJECT_TYPE_VLAN] = NULL;

    common_get_attribute[SAI_OBJECT_TYPE_NULL] = NULL;
    common_get_attribute[SAI_OBJECT_TYPE_PORT] = (sai_port_api) ? sai_port_api->get_port_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_LAG] = (sai_lag_api) ? sai_lag_api->get_lag_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_VIRTUAL_ROUTER] = (sai_router_api) ? sai_router_api->get_virtual_router_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_NEXT_HOP] = (sai_next_hop_api) ? sai_next_hop_api->get_next_hop_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_NEXT_HOP_GROUP] = (sai_next_hop_group_api) ? sai_next_hop_group_api->get_next_hop_group_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_ROUTER_INTERFACE] = (sai_router_interface_api) ? sai_router_interface_api->get_router_interface_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_ACL_TABLE] = (sai_acl_api) ? sai_acl_api->get_acl_table_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_ACL_ENTRY] = (sai_acl_api) ? sai_acl_api->get_acl_entry_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_ACL_COUNTER] = (sai_acl_api) ? sai_acl_api->get_acl_counter_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_HOST_INTERFACE] = (sai_hostif_api) ? sai_hostif_api->get_hostif_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_TRAP_GROUP] = (sai_hostif_api) ? sai_hostif_api->get_trap_group_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_ACL_TABLE_GROUP] = NULL;
    common_get_attribute[SAI_OBJECT_TYPE_POLICER] = (sai_policer_api) ? sai_policer_api->get_policer_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_WRED] = (sai_wred_api) ? sai_wred_api->get_wred_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_QOS_MAPS] = (sai_qos_map_api) ? sai_qos_map_api->get_qos_map_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_QUEUE] = (sai_queue_api) ? sai_queue_api->get_queue_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_SCHEDULER] = (sai_scheduler_api) ? sai_scheduler_api->get_scheduler_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_SCHEDULER_GROUP] = (sai_scheduler_group_api) ? sai_scheduler_group_api->get_scheduler_group_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_BUFFER_POOL] = (sai_buffer_api) ? sai_buffer_api->get_buffer_pool_attr : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_BUFFER_PROFILE] = (sai_buffer_api) ? sai_buffer_api->get_buffer_profile_attr : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_PRIORITY_GROUP] = (sai_buffer_api) ? sai_buffer_api->get_ingress_priority_group_attr : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_LAG_MEMBER] = (sai_lag_api) ? sai_lag_api->get_lag_member_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_VLAN_MEMBER] = (sai_vlan_api) ? sai_vlan_api->get_vlan_member_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_TUNNEL] = (sai_tunnel_api) ? sai_tunnel_api->get_tunnel_attribute : NULL;;
    common_get_attribute[SAI_OBJECT_TYPE_TUNNEL_TABLE_ENTRY] = (sai_tunnel_api) ? sai_tunnel_api->get_tunnel_term_table_entry_attribute : NULL;
    common_get_attribute[SAI_OBJECT_TYPE_FDB] =  NULL;
    common_get_attribute[SAI_OBJECT_TYPE_SWITCH] = NULL;
    common_get_attribute[SAI_OBJECT_TYPE_TRAP] = NULL;
    common_get_attribute[SAI_OBJECT_TYPE_TRAP_USER_DEF] = NULL;
    common_get_attribute[SAI_OBJECT_TYPE_NEIGHBOR] = NULL;
    common_get_attribute[SAI_OBJECT_TYPE_ROUTE] = NULL;
    common_get_attribute[SAI_OBJECT_TYPE_VLAN] = NULL;
}

void populate_sai_apis()
{
    SWSS_LOG_ENTER();

    sai_api_query(SAI_API_ACL, (void**)&sai_acl_api);
    sai_api_query(SAI_API_BUFFERS, (void**)&sai_buffer_api);
    sai_api_query(SAI_API_FDB, (void**)&sai_fdb_api);
    sai_api_query(SAI_API_HASH, (void**)&sai_hash_api);
    sai_api_query(SAI_API_HOST_INTERFACE, (void**)&sai_hostif_api);
    sai_api_query(SAI_API_LAG, (void**)&sai_lag_api);
    sai_api_query(SAI_API_MIRROR, (void**)&sai_mirror_api);
    sai_api_query(SAI_API_NEIGHBOR, (void**)&sai_neighbor_api);
    sai_api_query(SAI_API_NEXT_HOP, (void**)&sai_next_hop_api);
    sai_api_query(SAI_API_NEXT_HOP_GROUP, (void**)&sai_next_hop_group_api);
    sai_api_query(SAI_API_POLICER, (void**)&sai_policer_api);
    sai_api_query(SAI_API_PORT, (void**)&sai_port_api);
    sai_api_query(SAI_API_QOS_MAPS, (void**)&sai_qos_map_api);
    sai_api_query(SAI_API_QUEUE, (void**)&sai_queue_api);
    sai_api_query(SAI_API_ROUTE, (void**)&sai_route_api);
    sai_api_query(SAI_API_ROUTER_INTERFACE, (void**)&sai_router_interface_api);
    sai_api_query(SAI_API_SAMPLEPACKET, (void**)&sai_samplepacket_api);
    sai_api_query(SAI_API_SCHEDULER, (void**)&sai_scheduler_api);
    sai_api_query(SAI_API_SCHEDULER_GROUP, (void**)&sai_scheduler_group_api);
    sai_api_query(SAI_API_STP, (void**)&sai_stp_api);
    sai_api_query(SAI_API_SWITCH, (void**)&sai_switch_api);
    sai_api_query(SAI_API_TUNNEL, (void**)&sai_tunnel_api);
    sai_api_query(SAI_API_UDF, (void**)&sai_udf_api);
    sai_api_query(SAI_API_VIRTUAL_ROUTER, (void**)&sai_router_api);
    sai_api_query(SAI_API_VLAN, (void**)&sai_vlan_api);
    sai_api_query(SAI_API_WRED, (void**)&sai_wred_api);

    // set log levels

    sai_log_set(SAI_API_ACL, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_BUFFERS, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_FDB, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_HASH, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_HOST_INTERFACE, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_LAG, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_MIRROR, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_NEIGHBOR, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_NEXT_HOP, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_NEXT_HOP_GROUP, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_POLICER, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_PORT, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_QOS_MAPS, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_QUEUE, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_ROUTE, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_ROUTER_INTERFACE, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_SAMPLEPACKET, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_SCHEDULER, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_SCHEDULER_GROUP, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_STP, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_SWITCH, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_TUNNEL, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_UDF, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_VIRTUAL_ROUTER, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_VLAN, SAI_LOG_NOTICE);
    sai_log_set(SAI_API_WRED, SAI_LOG_NOTICE);
}
