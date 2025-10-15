#include<zephyr/kernel.h>
#include<zephyr/sys/printk.h>

int main(void)
{
    while(1) {
        printk("Hello Zephyr World! STM32-Nucleo-F401\n");
        k_msleep(1000);
    }

    return 0;
}