#include <stdint.h>

#include "quad.h"
#include "mavlink.h"

quad::quad( void )
{
	/* initialize values */
	this.heartbeat_msg = false;
}

uint8_t quad::init( void )
{
	/* TODO : initialize items in the order we want them */
	/* initialize pins 
			init gps, compass, etc	(zero them)   					 */
	
	this.heartbeat_msg = false;
	
	return 0;
}

void quad::start_heartbeat( void )
{
	this.heartbeat_msg = true;
}

void quad::stop_heartbeat( void )
{
	this.heartbeat_msg = false;
}

/* consider passing in arguments for the variables.
   and define them in quad.h or somewhere relavent */
void quad::send_heartbeat( void )
{
	mavlink_heartbeat_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	
	uint32_t custom_mode;
	uint8_t type = MAV_TYPE_QUADROTOR;
	uint8_t autopilot = MAV_AUTOPILOT_GENERIC;
	uint8_t base_mode = MAV_MODE_FLAG_TEST_ENABLED;
	//uint8_t system_status = MAV_STATE_UNINIT;
	//uint8_t mavlink_version = MAVLINK_WIRE_PROTOCOL_VERSION;
	uint16_t = len;
	
	mavlink_msg_heartbeat_pack(32, 200, &msg, type, autopilot, base_mode, system_status, mavlink_version);
	len = mavlink_msg_to_send_buffer(buf, &msg);
	uart0_send(buf, len); 
}