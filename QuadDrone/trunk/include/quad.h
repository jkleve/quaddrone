#ifndef QUAD_H
# define QUAD_H

# include <stdint.h>

class quad {
	private:
		bool heartbeat_msg;
	public:
		quad( void );
		uint8_t init( void );		
		void start_heartbeat( void );
		void stop_heartbeat( void );
		void send_heartbeat( void );
};

#endif