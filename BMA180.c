#include <stdint.h>
#include <unistd.h>
#include "mraa.h"
#include "BMA180.h"


// Global Variables
mraa_i2c_context i2c;
int ee_w;

int BMA180_init(uint8_t mode) {
  i2c = mraa_i2c_init(0);
  mraa_i2c_address(i2c,BMA180_I2C_ADDR);
  if (read8(BMA180_CHIPID_ADDR) != BMA180_CHIP_IP) {
    DEBUG_OUT("[BMA180]:Can not find Chip!\n");
    return -1;
  }
  ee_w = 0;
  // Perform Soft reset
  BMA180_soft_reset();
  if (read8(BMA180_CHIPID_ADDR) != BMA180_CHIP_IP) {
    DEBUG_OUT("[BMA180]:Can not find Chip after soft reset!\n");
    return -1;
  }
  DEBUG_OUT("[BMA180]:Found BMA180 with version:0x%x\n",read8(BMA180_CHIPVERSION));
  //enable writing to registers
  modify_reg(BMA180_CTRLREG0,1,0);
  BMA180_set_EE_w(TRUE);
  modify_reg(BMA180_CTRLREG0,1,0);
  BMA180_set_mode(BMA180_MODE_LOWNOISE);
  BMA180_set_range(BMA180_RANGE_1G);
  BMA180_set_bandwidth(BMA180_BW_1200HZ);
  return 1;
}
   
void BMA180_soft_reset(void) {
  DEBUG_OUT("[BMA180]: Performing soft reset\n");
  write8(BMA180_RESETREG,BMA180_SOFT_RESET);                                                          
  usleep(5000);      
}

void BMA180_set_mode(uint8_t mode) {
  if(ee_w == 0) {
    BMA180_set_EE_w(TRUE);
  }
  modify_reg(BMA180_MODE_CONFIG,(0x3),(mode & 0x3));
  DEBUG_OUT("[BMA180]:Set mode to: %u\n",mode);
}

void BMA180_set_EE_w(uint8_t enable)  {
  write8(BMA180_CTRLREG0,BMA180_EN_REG_WRITE);
  ee_w =1;
}

void BMA180_set_bandwidth(uint8_t bw) {
  if(ee_w == 0) {
    BMA180_set_EE_w(TRUE);
  }
  modify_reg(BMA180_BW_TCS,0xf0,(bw <<4));
  DEBUG_OUT("[BMA180]:Set Bandwith to %u\n",bw);
}

void BMA180_set_range(uint8_t range) {
  if(ee_w == 0) {
    BMA180_set_EE_w(TRUE);
  }
  modify_reg(BMA180_RANGEREG,0xe,((range&0x7) <<1));
  DEBUG_OUT("[BMA180]:Set range to %u",range);
}

double BMA180_get_temp(void) {
  int8_t rawT = read8(BMA180_TEMPREG);
  double temp = rawT+25.0;
  DEBUG_OUT("[BMA180];Read raw Temp=%2.3f\n",temp);
  return temp;
}

double BMA180_get_raw_ACCx(void) {
  uint8_t MSB = read8(BMA180_ACC_X_MSB);
  uint8_t LSB = (read8(BMA180_ACC_X_LSB) & 0xfc)>>2;
  double accx = (MSB <<6) | LSB;
  DEBUG_OUT("[BMA180]:Read raw ACCx=%2.3f\n",accx);
  return accx;
}

double BMA180_get_raw_ACCy(void) {
  uint8_t MSB = read8(BMA180_ACC_Y_MSB);
  uint8_t LSB = (read8(BMA180_ACC_Y_LSB) & 0xfc)>>2;
  double accy = (MSB <<6) | LSB;
  DEBUG_OUT("[BMA180]:Read raw ACCy=%2.3f\n",accy);
  return accy;
}

double BMA180_get_raw_ACCz(void) {
  uint8_t MSB = read8(BMA180_ACC_Z_MSB);
  uint8_t LSB = (read8(BMA180_ACC_Z_LSB) & 0xfc)>>2;
  double accz = (MSB <<6) | LSB;
  DEBUG_OUT("[BMA180]:Read raw ACCz=%2.3f\n",accz);
  return accz;
}

uint8_t read8(uint8_t addr) {
  return mraa_i2c_read_byte_data(i2c,addr);
}

void write8(uint8_t addr, uint8_t data) {
  mraa_i2c_write_byte_data(i2c,data,addr);
}

void dump_registers(uint8_t start, uint8_t end) {
  int i = 0;
  printf("[BMA180]: Register dump\n");
  for(i = start; i <= end; i++) {
    printf("Addr:0x%x val=0x%x\n",i,read8(i));
  }
}

void modify_reg(uint8_t reg, uint8_t clearbits, uint8_t setbits) {
  uint8_t val = read8(reg);
  val &= ~clearbits;
  val |= setbits;
  write8(reg, val);
}

