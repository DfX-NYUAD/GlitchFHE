import time
from pyftdi.ftdi import Ftdi
from pyftdi.gpio import GpioAsyncController

CBUS0ON  = 0xFF
CBUS0OFF = 0x00
# Open the FTDI device (replace vendor and product IDs if necessary)
ftdi = Ftdi()
ftdi.open(vendor=0x0403, product=0x6015)  # FTDI vendor and product IDs
ftdi.set_bitmode(CBUS0OFF, ftdi.BitMode.CBUS)
time.sleep(3.1)   # Wait
ftdi.set_bitmode(CBUS0ON, ftdi.BitMode.CBUS)
ftdi.set_cbus_direction(0x01,0x01)
ftdi.close(1)


#direction = 0x10
## Open the FTDI device (replace vendor and product IDs if necessary)
#ftdi = Ftdi()
#ftdi.open(vendor=0x0403, product=0x6001)  # FTDI vendor and product IDs
## Initialize GPIO controller
#gpio = GpioAsyncController()
#gpio.configure('ftdi:///1', direction=direction)
#ftdi.set_cbus_direction(0x01,0x01)
#ftdi.set_cbus_gpio(0x03)
##print("Debug0:", ftdi.get_cbus_gpio())
#gpio.write(0xFF & gpio.direction)
#time.sleep(2.1)   # Wait
#gpio.close()
#time.sleep(3.1)   # Wait
#ftdi.open(vendor=0x0403, product=0x6001)  # FTDI vendor and product IDs
#gpio.configure('ftdi:///1', direction=direction)
#gpio.write(0xFF & gpio.direction)
#gpio.close(1)
#



