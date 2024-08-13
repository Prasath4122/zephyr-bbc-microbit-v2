#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define GPIO_PIN_NO  2  //GPIO Pin number ("https://tech.microbit.org/hardware/edgeconnector/")
#define GPIO_SET_HIGH 1 
#define GPIO_SET_LOW 0

int main(void)
{
  int conf; 
  const struct device *gpio;
  
  gpio = DEVICE_DT_GET(DT_NODELABEL(gpio0)); //"get_device_binding" updated in 2.6 update refer ("https://www.youtube.com/watch?v=sWaxQyIgEBY")
  if (!device_is_ready(gpio)) {
    printk("Error acquiring GPIO 0 interface\n"); // If condition is used for debugging purpose 
    return -1;
  }
  
  conf = gpio_pin_configure(gpio, GPIO_PIN_NO, GPIO_OUTPUT);
  if (conf < 0) {
    printk("failed to configure gpio pin %d: %d\n",GPIO_PIN_NO, conf);  // If condition is used for debugging purpose
    return -1;
  }

  while(1) {
    gpio_pin_set(gpio, GPIO_PIN_NO, GPIO_SET_HIGH); // Setting a Pin as High (ON)
    k_msleep(500); 
    gpio_pin_set(gpio, GPIO_PIN_NO, GPIO_SET_LOW); // Setting a pin as Low (OFF)
    k_msleep(500);
  }

  return 0;

}
