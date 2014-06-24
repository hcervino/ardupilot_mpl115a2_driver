/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-


// AVR LibC Includes
#include <inttypes.h>

#include <AP_Common.h>
#include <AP_Math.h> // ArduPilot Mega Vector/Matrix math Library

#include <AP_Baro.h>
#include "AP_Baro_MPL115A2.h"
#include <AP_HAL.h>

extern const AP_HAL::HAL& hal;

// Public Methods //////////////////////////////////////////////////////////////
bool AP_Baro_MPL115A2::init()
{
	//Code
	return true;
}


// Read the sensor. This is a state machine
// acumulate a new sensor reading
void AP_Baro_MPL115A2::accumulate(void)
{
	//Code
}


// Read the sensor using accumulated data
uint8_t AP_Baro_MPL115A2::read()
{
	//Code
	return 1;
}

float AP_Baro_MPL115A2::get_pressure() {
    return Press;
}


float AP_Baro_MPL115A2::get_temperature() {
    return Temp;
}

// Gets both at once and saves a little time
void AP_Baro_MPL115A2::getPT(float *P, float *T)
{
	//Code
}


// Private functions: /////////////////////////////////////////////////////////

// Gets the factory-set coefficients for this particular sensor
void AP_Baro_MPL115A2::readCoefficients()
{
	//Code
}
