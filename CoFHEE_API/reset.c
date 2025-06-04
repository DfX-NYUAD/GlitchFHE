/* These are standard headers used in Unix systems */
#include <stdio.h>
#include <unistd.h>
#include <ftdi.h>
#define CBUS0ON  0xFF  /* CBUS0 PIN */
#define CBUS0OFF 0xF0  /* CBUS0 PIN */
int main()
{
    unsigned char c = 0;
    /* cbus is the FTDI context, we'll use this to control the
     * FTDI devices later. We'd need to initialise it first
     */
    struct ftdi_context cbus;
    ftdi_init(&cbus);
    /*  Open FTDI Devices based on FTDI VID/PID */
    if(ftdi_usb_open(&cbus, 0x0403, 0x6015) < 0) {
        puts("Can't open device");
        return 1;
    }
    /* Enable bitbang mode with a single output line */
    ftdi_set_bitmode(&cbus, CBUS0OFF, BITMODE_CBUS);
   /*Write output, pause 1 second */
    //c ^= CBUS0; /* C = C XOR C which will flip the bits*/
    //ftdi_write_data(&cbus, &c, 1);
    //usleep(1000000); /* pause for 200000 microseconds*/
    //c ^= CBUS0; /* C = C XOR C which will flip the bits*/
    //ftdi_write_data(&cbus, &c, 1);
    usleep(3000000); /* pause for 200000 microseconds*/
    ftdi_set_bitmode(&cbus, CBUS0ON, BITMODE_CBUS);
    //c ^= CBUS0; /* C = C XOR C which will flip the bits*/
    //ftdi_write_data(&cbus, &c, 1);
    ftdi_usb_close(&cbus);
}
