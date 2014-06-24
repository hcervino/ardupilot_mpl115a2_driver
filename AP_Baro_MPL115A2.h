/**************************************************************************/
/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

/*=========================================================================
I2C ADDRESS/BITS
-----------------------------------------------------------------------*/
#define MPL115A2_ADDRESS (0x60) // 1100000
/*=========================================================================*/

/*=========================================================================
REGISTERS
-----------------------------------------------------------------------*/
#define MPL115A2_REGISTER_PRESSURE_MSB (0x00)
#define MPL115A2_REGISTER_PRESSURE_LSB (0x01)
#define MPL115A2_REGISTER_TEMP_MSB (0x02)
#define MPL115A2_REGISTER_TEMP_LSB (0x03)
#define MPL115A2_REGISTER_A0_COEFF_MSB (0x04)
#define MPL115A2_REGISTER_A0_COEFF_LSB (0x05)
#define MPL115A2_REGISTER_B1_COEFF_MSB (0x06)
#define MPL115A2_REGISTER_B1_COEFF_LSB (0x07)
#define MPL115A2_REGISTER_B2_COEFF_MSB (0x08)
#define MPL115A2_REGISTER_B2_COEFF_LSB (0x09)
#define MPL115A2_REGISTER_C12_COEFF_MSB (0x0A)
#define MPL115A2_REGISTER_C12_COEFF_LSB (0x0B)
#define MPL115A2_REGISTER_STARTCONVERSION (0x12)
/*=========================================================================*/

#ifndef __AP_BARO__MPL115A2_H__
#define __AP_BARO__MPL115A2_H__

#include "AP_Baro.h"

class AP_BARO_MPL115A2 : public AP_Baro
{
 public:
 
	  AP_BARO_MPL115A2();		//Constructor
	  
	  
	  /* AP_Baro public interface: */  
	  bool 		init();						// void begin(void);
	  uint8_t 	read();
	  void 			accumulate(void);
	  float 	getPressure();
	  float 	getTemperature();
	  void 		getPT(float *P, float *T);    
    
  

 private:
	  float 	_mpl115a2_a0;
	  float 	_mpl115a2_b1;
	  float 	_mpl115a2_b2;
	  float 	_mpl115a2_c12;

	  void 		readCoefficients();
};

#endif // __AP_BARO_MPL115A2_H__
