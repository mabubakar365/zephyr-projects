#include<zephyr/kernel.h>
#include<zephyr/sys/printk.h>
#include<zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS   500

int main(void)
{
    const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);

    if(!device_is_ready(led.port))
    {
        return -1;
    }

    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    while(1) {
        gpio_pin_toggle_dt(&led);
        printk("STM32-Nucleo-F401 GPIO Toggled\n");
        k_msleep(SLEEP_TIME_MS);
    }

    return 0;
}