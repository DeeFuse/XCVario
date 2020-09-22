/*
 * Switch.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: iltis
 *
 *      Example:
 *      sw = Switch();
 *      sw.begin( GPIO_NUM_1 );
 *      if( sw.state() )
 *         ESP_LOGI(FNAME,"Open");
 *
 */

#include "esp32-hal.h"
#include "driver/gpio.h"
#include "Switch.h"
#include <logdef.h>
#include "Setup.h"


Switch::Switch() {
	_sw = GPIO_NUM_0;
}

Switch::~Switch() {
}

void Switch::begin( gpio_num_t sw ){
	_sw = sw;
	gpio_set_direction(_sw, GPIO_MODE_INPUT);
	gpio_set_pull_mode(_sw, GPIO_PULLDOWN_ONLY);
}


bool Switch::isClosed() {
	gpio_set_pull_mode(_sw, GPIO_PULLUP_ONLY);
	if( hardware_revision.get() >= 1 )
		delay(10);  // 100 nF against pullup
	else
		delay(100); // 1uF against pullup
	int level = gpio_get_level(_sw );
	gpio_set_pull_mode(_sw, GPIO_PULLDOWN_ONLY);
	if( level )
		return false;
	else
		return true;
// 	gpio_set_pull_mode(_sw, GPIO_PULLDOWN_ONLY);

}
bool Switch::isOpen() {
   return( !isClosed() );
}



