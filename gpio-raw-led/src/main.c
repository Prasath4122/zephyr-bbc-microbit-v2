#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

//Reference in bbc_microbit_v2 SoC nRF52833 ("https://infocenter.nordicsemi.com/pdf/nRF52833_OPS_v0.7.pdf")

#define GPIO_P0_DIR 0x50000514 //ref.in GPIO direction register address in (Page no.139)
#define GPIO_P0_OUT 0X50000504 //ref.in Output register Address in (Page no.139,140)
#define P0_2 2 //LED Connected Port and its Specific pin("https://tech.microbit.org/hardware/schematic/#v2-pinmap")

int main(void)
{
  uint32_t *dir_reg_value = (uint32_t *)GPIO_P0_DIR;
  uint32_t *write_reg_value = (uint32_t *)GPIO_P0_OUT;

  *dir_reg_value = *dir_reg_value | (1 << P0_2);     //To change the Direction register value for the the mentioned Pin  
  *write_reg_value = *write_reg_value | (1 << P0_2); //To chamge the Output register value for mentioned Pin
    
  while(1) {
    *write_reg_value = *write_reg_value | 0x01 << P0_2; //Turn ON the LED 
    k_msleep(500);
    *write_reg_value = *write_reg_value & (~0x01 << P0_2); //Turn OFF the LED
    k_msleep(500);
  }
}
