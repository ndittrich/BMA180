#ifndef BMA180_H
#define BMA180_H

#include <stdint.h>

#define TRUE 1
#define FALSE 0

#define BMA180_DEBUG  1
#if (BMA180_DEBUG == 1)
# define DEBUG_OUT printf
#else
#define DEBUG_OUT (...)
#endif


#define BMA180_I2C_ADDR		0x40
#define BMA180_CHIP_IP		0x03

// Reg Addresses
#define BMA180_CHIPID_ADDR 	0x00
#define BMA180_CHIPVERSION	0x01
#define BMA180_ACC_X_LSB	0x02
#define BMA180_ACC_X_MSB	0x03
#define BMA180_ACC_Y_LSB	0x04
#define BMA180_ACC_Y_MSB        0x05
#define BMA180_ACC_Z_LSB        0x06
#define BMA180_ACC_Z_MSB        0x07
#define BMA180_TEMPREG	        0x08
#define BMA180_STATUSREG1       0x09
#define BMA180_STATUSREG2       0x0A
#define BMA180_STATUSREG3       0x0B
#define BMA180_STATUSREG4       0x0C
#define BMA180_CTRLREG0	        0x0D
#define BMA180_CTRLREG1         0x0E
#define BMA180_CTRLREG2         0x0F
#define BMA180_CTRLREG3		0x21
#define BMA180_CTRLREG4		0x22
#define BMA180_RESETREG         0x10
#define BMA180_BW_TCS		0x20
#define BMA180_HY		0x23
#define BMA180_RANGEREG         0x35
#define BMA180_MODE_CONFIG      0x30

//Commands
#define BMA180_EN_REG_WRITE	0x10
#define BMA180_SOFT_RESET	0xB6

//Working range
#define BMA180_RANGE_1G         0x00
#define BMA180_RANGE_1_5G       0x01
#define BMA180_RANGE_2G         0x02
#define BMA180_RANGE_3G         0x03
#define BMA180_RANGE_4G         0x04
#define BMA180_RANGE_8G         0x05
#define BMA180_RANGE_16G        0x06

// Bandwidth
// Lowpass
#define BMA180_BW_10HZ          0x00
#define BMA180_BW_20HZ          0x01
#define BMA180_BW_40HZ          0x02
#define BMA180_BW_75HZ          0x03
#define BMA180_BW_150HZ         0x04
#define BMA180_BW_300HZ         0x05
#define BMA180_BW_600HZ         0x06
#define BMA180_BW_1200HZ        0x07
// Highpass
#define BMA180_BW_1HZ           0x08
//Bandpass
#define BMA180_BW_02_300HZ      0x09

// Mode-selection
#define BMA180_MODE_LOWNOISE    0x00
#define BMA180_MODE_LOWP        0x03

// Init the I2C-Interface and reset the chip
int BMA180_init(uint8_t mode);
// Perform soft_reset and reread Trim-Registers
void BMA180_soft_reset(void);
void BMA180_set_mode(uint8_t mode);
void BMA180_set_range(uint8_t range);
void BMA180_set_bandwidth(uint8_t bw);
void BMA180_set_EE_w(uint8_t enable);
double BMA180_get_temp(void);
double BMA180_get_raw_ACCx(void);
double BMA180_get_raw_ACCy(void);
double BMA180_get_raw_ACCz(void);

void dump_registers(uint8_t start, uint8_t end);
void write8(uint8_t addr, uint8_t data);
uint8_t read8(uint8_t addr);
void modify_reg(uint8_t reg, uint8_t clearbits, uint8_t setbits);


#endif //BMP085_H
