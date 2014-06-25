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
	// Read factory coefficient values (this only needs to be done once)
	readCoefficients();
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

// Gets the floating-point pressure level in kPa
float AP_Baro_MPL115A2::get_pressure() {     
  float pressureComp,centigrade;

  getPT(&pressureComp, &centigrade);
  return pressureComp;    
}

// Gets the floating-point temperature in Centigrade
float AP_Baro_MPL115A2::get_temperature() {    
  float pressureComp, centigrade;

  getPT(&pressureComp, &centigrade);
  return centigrade;
}


// Private functions: /////////////////////////////////////////////////////////

// Gets the factory-set coefficients for this particular sensor
void AP_Baro_MPL115A2::readCoefficients()
{
	uint8_t buff[8];
	
	int16_t a0coeff;
	int16_t b1coeff;
	int16_t b2coeff;
	int16_t c12coeff;
	
	/*	
    // get pointer to i2c bus semaphore
    AP_HAL::Semaphore* i2c_sem = hal.i2c->get_semaphore();

    // take i2c bus sempahore
    if (!i2c_sem->take(HAL_SEMAPHORE_BLOCK_FOREVER))
        return false;
        
        
    // We read the calibration data registers
    if (hal.i2c->readRegisters(MPL115A2_ADDRESS, MPL115A2_REGISTER_A0_COEFF_MSB, 8, buff) != 0) {
        healthy = false;
        i2c_sem->give();
        return false;
    }
	*/

	// We read the calibration data registers
	hal.i2c->readRegisters(MPL115A2_ADDRESS, MPL115A2_REGISTER_A0_COEFF_MSB, 8, buff);
	
	a0coeff = (( (uint8_t) buff[0] << 8) | buff[1]);
	b1coeff = (( (uint8_t) buff[2] << 8) | buff[3]);
	b2coeff = (( (uint8_t) buff[4] << 8) | buff[5]);
	c12coeff = (( (uint8_t) (buff[6] << 8) | buff[7])) >> 2;
	
	_mpl115a2_a0 = (float)a0coeff / 8;
	_mpl115a2_b1 = (float)b1coeff / 8192;
	_mpl115a2_b2 = (float)b2coeff / 16384;
	_mpl115a2_c12 = (float)c12coeff;
	_mpl115a2_c12 /= 4194304.0;
	
	/*	
	healthy = true;
    i2c_sem->give();
	return true;
	*/	  
	  
}

// Gets both at once and saves a little time
void AP_Baro_MPL115A2::getPT(float *P, float *T)
{
	uint16_t pressure, temp;
	float pressureComp;
	uint8_t buff[4];
           
	// Get raw pressure and temperature settings	
	hal.i2c->writeRegister(MPL115A2_ADDRESS, MPL115A2_REGISTER_STARTCONVERSION, 0x00);
	
	// Wait a bit for the conversion to complete (3ms max)
	delay(5);

	hal.i2c->readRegisters(MPL115A2_ADDRESS, MPL115A2_REGISTER_PRESSURE_MSB, 4, buff);

	//Wire.requestFrom(MPL115A2_ADDRESS, 4);
	pressure = (( (uint16_t) buff[0] << 8) | buff[1]) >> 6;
	temp = (( (uint16_t) buff[2] << 8) | buff[3]) >> 6;

	// See datasheet p.6 for evaluation sequence
	pressureComp = _mpl115a2_a0 + (_mpl115a2_b1 + _mpl115a2_c12 * temp ) * pressure + _mpl115a2_b2 * temp;

	// Return pressure and temperature as floating point values
	*P = ((65.0F / 1023.0F) * pressureComp) + 50.0F; // kPa
	*T = ((float) temp - 498.0F) / -5.35F +25.0F; // C
}
