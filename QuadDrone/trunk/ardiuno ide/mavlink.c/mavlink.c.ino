#include <mavlink.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  mavlink_system_t mavlink_system;

  mavlink_system.sysid = 20;
  mavlink_system.compid = MAV_COMP_ID_IMU;

  uint8_t system_type = MAV_TYPE_FIXED_WING;
  uint8_t autopilot_type = MAV_AUTOPILOT_GENERIC;

  uint8_t system_mode = MAV_MODE_PREFLIGHT;
  uint8_t custom_mode = 0;
  uint8_t system_state = MAV_STATE_STANDBY;

  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  //mavlink_msg_heartbeat_pack(mavlink_system.sysid, mavlink_system.compid, &msg, system_type, autopilot_type, system_mode, custom_mode, system_state);

 // uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);

  // TODO send message
 mavlink_msg_heartbeat_send(MAVLINK_COMM_0, system_type, autopilot_type, system_mode, custom_mode, system_state);
}
