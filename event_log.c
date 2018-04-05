#include "event_log.h"

/* System */
#define SYSTEM_BOOT_EVT																"Boot"
#define EXSYSTEM_TERNAL_SIGNAL_EVT										"External signal"
/* Bluetooth LE Connection */
#define	LE_CONNECTION_OPEN_EVT 												"Opened"
#define LE_CONNECTION_CLOSED_EVT											"Closed"
#define LE_CONNECTION_UPDATE_EVT											"Parameters Updated"
#define LE_CONNECTION_RSSI														"RSSI"
/* Gatt Server */
#define GATT_SERVER_CHARACTERISTIC_STATUS							"Characteristic Status"
#define GATT_SERVER_ATT_VALUE													"Attribute Value"
#define GATT_SERVER_READ_REQUEST											"Read Request"
/* DTM */
#define TEST_DTM_COMPLETED														"DTM Completed"

#define COMMANDS_NOT_ADDED														"Command not added"
#define NO_INFO																				""

void log_events(struct gecko_cmd_packet* evt){
  /* Handle events */
  switch (BGLIB_MSG_ID(evt->header)) {
#if (SYSTEM == 1)
#undef EVT_CATEGORY
#define EVT_CATEGORY	"[SYSTEM]: "
    case gecko_evt_system_boot_id:
    	EVT_LOG_C(SYSTEM_BOOT_EVT, NO_INFO);
    	LOGN();
    	EVT_LOG_V(SYSTEM_BOOT_EVT, "Major = 0x%04x, Minor = 0x%04x, Patch = 0x%04x, Build = %ld, Bootloader = 0x%08x, Hw = 0x%04x, Hash = 0x%08x", \
    			evt->data.evt_system_boot.major, \
    			evt->data.evt_system_boot.minor, \
					evt->data.evt_system_boot.patch, \
					evt->data.evt_system_boot.build, \
					evt->data.evt_system_boot.bootloader, \
					evt->data.evt_system_boot.hw, \
					evt->data.evt_system_boot.hash);
    	LOGN();
      break;

    case gecko_evt_system_external_signal_id:
    	EVT_LOG_I(EXSYSTEM_TERNAL_SIGNAL_EVT, "External signals = 0x%08X", \
    			evt->data.evt_system_external_signal.extsignals);
    	LOGN();
    	break;
#endif

#if (LE_CONNECTION == 1)
#undef EVT_CATEGORY
#define EVT_CATEGORY	"[LE_CONNECTION]: "
    case gecko_evt_le_connection_opened_id:
    	EVT_LOG_C(LE_CONNECTION_OPEN_EVT, "Connection Handle = 0x%02x", \
    			evt->data.evt_le_connection_opened.connection);
    	LOGN();
    	EVT_LOG_I(LE_CONNECTION_OPEN_EVT, "Peer address = ");
    	UINT8_ARRAY_DUMP(evt->data.evt_le_connection_opened.address.addr, 6);
    	LOGN();
    	EVT_LOG_V(LE_CONNECTION_OPEN_EVT, "Role = %s, Bonding handle = %d, advertiser = %d", \
    			evt->data.evt_le_connection_opened.master==1?"Master":"Slave",	\
    			evt->data.evt_le_connection_opened.bonding, \
					evt->data.evt_le_connection_opened.advertiser);
    	LOGN();
    	break;
    case gecko_evt_le_connection_closed_id:
    	EVT_LOG_C(LE_CONNECTION_CLOSED_EVT, "Handle = 0x%02x, Reason = ", \
    	    			evt->data.evt_le_connection_closed.connection);
    	error_checking(evt->data.evt_le_connection_closed.reason, 1);
    	LOGN();
      break;
    case gecko_evt_le_connection_parameters_id:
    	// Why float can't be printed while "print float" has been checked????
    	EVT_LOG_I(LE_CONNECTION_UPDATE_EVT, "Connection Handle = 0x%02x, Interval = %d*1.25ms, Latency = %d, Timeout = %dms", \
    	    	    			evt->data.evt_le_connection_parameters.connection, \
											evt->data.evt_le_connection_parameters.interval, \
											evt->data.evt_le_connection_parameters.latency, \
											evt->data.evt_le_connection_parameters.timeout*10);
    	/* TODO: There are still 2 parameters may need to be handled */
    	LOGN();
    	break;
    case gecko_evt_le_connection_rssi_id:
    	// Status parameter???
    	EVT_LOG_I(LE_CONNECTION_RSSI, "Handle = 0x%02x, Rssi = %ddBm", \
    			evt->data.evt_le_connection_rssi.connection, \
					evt->data.evt_le_connection_rssi.rssi);
    	LOGN();
    	break;
    case gecko_evt_le_connection_phy_status_id:
    	break;
#endif


#if (GATT_SERVER == 1)
#undef EVT_CATEGORY
#define EVT_CATEGORY	"[GATT_SERVER]: "
    case gecko_evt_gatt_server_characteristic_status_id:
    	EVT_LOG_I(GATT_SERVER_CHARACTERISTIC_STATUS, "Connection Handle = 0x%02x, Characteristic = 0x%04x, Type = %s, Value = 0x%04x", \
    			evt->data.evt_gatt_server_characteristic_status.connection, \
					evt->data.evt_gatt_server_characteristic_status.characteristic, \
					evt->data.evt_gatt_server_characteristic_status.status_flags ==1?"Gatt server client config":"Confirmation", \
					evt->data.evt_gatt_server_characteristic_status.client_config_flags);
    	LOGN();
    	break;
    case gecko_evt_gatt_server_attribute_value_id:
    	EVT_LOG_I(GATT_SERVER_ATT_VALUE, "Connection Handle = 0x%02x, Attribute = 0x%04x, Op_Code = 0x%02x, Offset = 0x%04x, Value = ", \
    	    evt->data.evt_gatt_server_attribute_value.connection, \
    			evt->data.evt_gatt_server_attribute_value.attribute, \
    			evt->data.evt_gatt_server_attribute_value.att_opcode, \
    			evt->data.evt_gatt_server_attribute_value.offset);
    	UINT8_ARRAY_DUMP(evt->data.evt_gatt_server_attribute_value.value.data, evt->data.evt_gatt_server_attribute_value.value.len);
    	LOGN();
    	break;
    case gecko_evt_gatt_server_execute_write_completed_id:
    	break;
    case gecko_evt_gatt_server_user_read_request_id:
    	EVT_LOG_I(GATT_SERVER_READ_REQUEST, "Connection Handle = 0x%02x, Characteristic = 0x%04x, Op_Code = 0x%02x, Offset = 0x%04x", \
    	    evt->data.evt_gatt_server_user_read_request.connection, \
    	    evt->data.evt_gatt_server_user_read_request.characteristic, \
    	    evt->data.evt_gatt_server_user_read_request.att_opcode, \
    	    evt->data.evt_gatt_server_user_read_request.offset);
    	LOGN();
    	break;
    case gecko_evt_gatt_server_user_write_request_id:
    	EVT_LOG_I(GATT_SERVER_ATT_VALUE, "Connection Handle = 0x%02x, Characteristic = 0x%04x, Op_Code = 0x%02x, Offset = 0x%04x, Value = ", \
    	    evt->data.evt_gatt_server_user_write_request.connection, \
    	    evt->data.evt_gatt_server_user_write_request.characteristic, \
    	    evt->data.evt_gatt_server_user_write_request.att_opcode, \
    	    evt->data.evt_gatt_server_user_write_request.offset);
    	UINT8_ARRAY_DUMP(evt->data.evt_gatt_server_user_write_request.value.data, evt->data.evt_gatt_server_user_write_request.value.len);
    	LOGN();
    	break;
#endif

#if (HARDWARE == 1)
#undef EVT_CATEGORY
#define EVT_CATEGORY	"[HARDWARE]: "
//    case gecko_evt_hardware_soft_timer_id:
    	// TODO
//    	break;
#endif

#if (TEST == 1)
#undef EVT_CATEGORY
#define EVT_CATEGORY	"[TEST]: "
    case gecko_evt_test_dtm_completed_id:
    	EVT_LOG_I(TEST_DTM_COMPLETED, "Result = ");
    	error_checking(evt->data.evt_test_dtm_completed.result, 1);
    	LOGN();
    	EVT_LOG_I(TEST_DTM_COMPLETED, "Number of Packets = %d", \
    			evt->data.evt_test_dtm_completed.number_of_packets);
    	LOGN();
    	break;
#endif

    default:
    	EVT_LOG_V(COMMANDS_NOT_ADDED, "Header = 0x%08x", BGLIB_MSG_ID(evt->header));
    	LOGN();
      break;
  }
}
