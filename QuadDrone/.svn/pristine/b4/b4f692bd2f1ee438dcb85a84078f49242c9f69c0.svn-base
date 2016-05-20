
#include "mavlink.h" /* consider moving this only to quad.h and getting rid of it here */
#include "quad.h"

typedef quad quad_t;

int main()
{
	quad_t drone;
	
	/* initialize drone */
	/* 1. initialize motors */
	drone.init();
	/* drone.start_heartbeat(); */ /* Possibly getting rid of this */
	for(;;) {
		drone.send_heartbeat();
		delay(1000);
	}
	
	return 0;
}