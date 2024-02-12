// bt_test.c - Simple test program for bluetooth-stdio

#include <stdio.h>
#include <stdio_bt.h>
#include <pico/cyw43_arch.h>

int main (void)
    {
    // Configure
    
    stdio_init_all();
    cyw43_arch_init ();
    stdio_bt_init ();
    stdio_set_driver_enabled (&stdio_bt, true);

    // Wait for connection
    
    int iLED = 0;
	while (true)
        {
        iLED ^= 1;
        cyw43_arch_gpio_put (CYW43_WL_GPIO_LED_PIN, iLED);
        if ( stdio_bt_connected() ) break;
		sleep_ms(1000);
        }
    cyw43_arch_gpio_put (CYW43_WL_GPIO_LED_PIN, 0);

    // Echo input lines

    static char s[512];
    char *ps;
    while (true)
        {
        ps = s;
        while (true)
            {
            *ps = getchar ();
            if ((*ps == '\r') || (*ps == '\n'))
                {
                *ps == '\0';
                break;
                }
            ++ps;
            }
        printf ("%s\n", s);
        }
    }
