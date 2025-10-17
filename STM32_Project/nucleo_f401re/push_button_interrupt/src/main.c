#include<zephyr/kernel.h>
#include<zephyr/sys/printk.h>
#include<zephyr/drivers/gpio.h>
#include<zephyr/devicetree.h>
#include<zephyr/device.h>

#define SLEEP_TIME_MS   500

const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);
const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET(DT_ALIAS(button0), gpios);

static struct gpio_callback button_cb_data;

void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t port)
{
    gpio_pin_toggle_dt(&led0);
    gpio_pin_toggle_dt(&led1);
    printk("STM32-Nucleo-F401 Button pressed - GPIO Toggled\n");
}

int main(void)
{   
    int ret; 

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

    gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
    
    ret = gpio_pin_configure_dt(&button0, GPIO_INPUT);
    if(ret != 0)
    {
        printk("Error %d: Failed to configure the interrup\n", ret);
        return -1;
    }

    ret = gpio_pin_interrupt_configure_dt(&button0, GPIO_INT_EDGE_TO_ACTIVE);
    if(ret != 0)
    {
        printk("Error %d: Failed to configure the interrup\n", ret);
        return -1;
    }

    gpio_init_callback(&button_cb_data, button_pressed, BIT(button0.pin));
    gpio_add_callback(button0.port, &button_cb_data);

    printk("Button 0 Interrupt example started\n");

    while(1) {

        k_msleep(SLEEP_TIME_MS);
    }

    return 0;
}