#include<zephyr/kernel.h>
#include<zephyr/sys/printk.h>
#include<zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS   500

int main(void)
{   
    const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
    const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);
    const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET(DT_ALIAS(button0), gpios);

    if(!device_is_ready(led0.port))
    {
        printk("Error: LED0 not ready\n");
        return -1;
    }

    if(!device_is_ready(led1.port))
    {
        printk("Error: LED1 not ready\n");
        return -1;
    }

    if(!device_is_ready(button0.port))
    {
        printk("Error: Button0 not ready\n");
        return -1;
    }

    gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&button0, GPIO_INPUT);

    while(1) {
        int val = gpio_pin_get_dt(&button0);
        if(val == 1)
        {
            gpio_pin_toggle_dt(&led0);
            gpio_pin_toggle_dt(&led1);
            printk("STM32-Nucleo-F401 Button pressed - GPIO Toggled\n");
            k_msleep(SLEEP_TIME_MS);
        }
    }

    return 0;
}