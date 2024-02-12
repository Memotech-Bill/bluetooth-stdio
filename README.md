# STDIO over Bluetooth for Pico_W C SDK

This repositioy implements a driver to provide STDIO
(__printf__, __scanf__, etc.) over Bluetooth. With it
you can use a Bluetooth serial console on your phone or
tablet to interact with your Pico_W project without any
physical connection. Convenient if the Pico is embedded
in a project.

It should be noted that the Pico SDK documentation states
(section 8.61.1) that:

> the API for adding additional input output devices is not
> yet considered stable

The code is based heavily on the "spp_counter" example
from the BlueKitchen BTStack.

To enable Bluetooth access, include the following near
the start of your program:

````
#include "stdio_bt.h"

    stdio_init_all();
    cyw43_arch_init ();
    stdio_bt_init ();
    stdio_set_driver_enabled (&stdio_bt, true);
````

Your CMakeLists.txt file will need to include something like:

````
    add_subdirectory (/path/to/bluetooth_stdio stdio_bt)
    target_compile_definitions(bbcbasic PUBLIC
      -DBT_NAME="Pico"
      -DPICO_FLASH_BANK_TOTAL_SIZE=0x2000           # = 2 * FLASH_SECTOR_SIZE
      -DPICO_FLASH_BANK_STORAGE_OFFSET=0x1FE000     # = PICO_FLASH_SIZE_BYTES - PICO_FLASH_BANK_TOTAL_SIZE
      )
    target_link_libraries(${PROJECT_NAME}
        bluetooth_stdio
        pico_cyw43_arch_none
        )
````

__BT_NAME__ defines the name that will be given to the Bluetooth
service when you search for a connection.

Alternately, to have your software specify the name given to the Bluetooth service, start your program with:

````
#include "stdio_bt.h"

    stdio_init_all();
    cyw43_arch_init ();
    if ( !stdio_bt_init_name ("Your_Service_Name") )
        panic ("Failed to initialise service name\n");
    stdio_set_driver_enabled (&stdio_bt, true);
````

The Bluetooth code uses 128 KB of flash memory to save
paired connections. The __PICO_FLASH_BANK_*__ defines specify
the location used for this. By default this is located at the
top of flash memory (as per the above example). If you are
using some of the flash memory to store a filesystem, then
you will have to ensure that the two do not overlap. It is
not currently clear how to configure to use another storage
medium (such as SD card) to store this data.

If using WiFi as well as Bluetooth, then replace
__pico_cyw43_arch_none__ appropriately.

The __test__ folder contains a simple test program.
Build this in the standard fashion

````
cd bluetooth-stdio/test
mkdir test
cd test
cmake ..
make
````

Then copy the resulting __bt_test.uf2__ onto a Pico W.
Connect a Bluetooth serial terminal to the resulting
__Pico__ device. Lines typed into the terminal will
be echoed back.

Note that the test program is not protected against
very long (>511 characters) input lines.

