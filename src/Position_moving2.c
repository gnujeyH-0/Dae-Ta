/* RaspberryPi 4 for Automotive IoT Kit
* File  : i2c_exp_led.c
* TITLE : GPIO LED control based on I2c Expander 
* Auth  : mkdev.co.kr / makeutil.tistory.com
* Ment  : This program code may not be used for commercial purposes. 
*         The author's information cannot be changed at the time of redistribution.
*/// Define the header & constants
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/i2c-dev.h>
//#include "./aiot_hardware.h"

//#define I2C_ADAPTOR "/dev/i2c-1"
int Position_moving(){
    int led_fd;
    int retv;
    char i2c_reg;
    //char led_data=0;
    char temp_values[2]={0,};
    char values[2]={0,};
    // Open I2C device node (adapter)
    led_fd = open("/dev/i2c-1",O_RDWR);
    if(led_fd < 3) {
        printf("Device node open error!!!: %s", "/dev/i2c-1");
        return -1;
    }
    retv=ioctl(led_fd, I2C_SLAVE,0x20);
    // Specify I2C device address you want to communicate (select slave device)
    if(retv!=0) {
        printf("Ioctl Error!\n");
        return -1;
    }
    read(led_fd,temp_values,8);
    // Send command byte to configure "Configuration Port 1"
    i2c_reg = 0x07;
    values[0] = i2c_reg; // GPIO Register -TCA9535 Data Sheet 23p
    values[1] = 0x00; // Setting Value
    printf("%d\n",values[1]);
    printf("%d\n",temp_values[1]);
    write(led_fd,values, 2);
    // command byte to select "Output Port 1" control register
    i2c_reg = 0x03;
    values[0] = i2c_reg;

    int i=0;
    while(true){
        i++;
        printf("LEDDDDDDD\n");
        printf("LED ON\n");
        // Turn off 8 LEDs before starting
        values[1] = temp_values[1];
        write(led_fd,values,2);
        read(led_fd,temp_values,8);
        //puts(values);
        values[1]= 0xFE&temp_values[1];

        printf("%d\n",temp_values[1]);
        printf("%d\n",values[1]);
        //values[1] =temp_values;
        write(led_fd,values,2);
        //usleep(1000000); // 100ms
        usleep(50000);


        // Turn off 8 LEDs
        printf("LED OFF\n");
        values[1]= 0x01|temp_values[1];
        write(led_fd,values,2);
        usleep(50000);
        close(led_fd);
    }
    return 0;
}
