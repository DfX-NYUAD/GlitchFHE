import CoFHEE_header
import CoFHEE_init_val
import serial
import codecs
import time


ser = serial.Serial(
       port='/dev/tty.usbserial-A19H2LBS',
       #port='/dev/ttyS4',
       #baudrate=9600,
       baudrate=19200,
       #baudrate=1024000,
       #baudrate=16000,
       #baudrate=1000000,
       #baudrate=230400,
       parity=serial.PARITY_NONE,
       stopbits=serial.STOPBITS_ONE,
       bytesize=serial.EIGHTBITS
       )


def read_serial(addr):
  #time.sleep(.0001)
  rdstring  = b"\x4D\x4D\x4D\x4D"
  addrstring = addr[6] + addr[7] + addr[4] + addr[5] + addr[2] + addr[3] + addr[0] + addr[1]
  addrstring    = codecs.decode(addrstring, "hex")
  ser.write(rdstring)
  ser.write(addrstring)
  s = ser.read(4)
  s = codecs.encode(s, "hex")
  s = str(s)
  s = s[8] + s[9] + s[6] + s[7] + s[4] + s[5] + s[2] + s[3]
  return s


def write_serial(addr, data):
  wrstring   = b"\x34\x34\x34\x34"
  #wrstring   = "0x34343434"
  addrstring = addr[6] + addr[7] + addr[4] + addr[5] + addr[2] + addr[3] + addr[0] + addr[1]
  addrstring    = codecs.decode(addrstring, "hex")
  #addrstring    = addrstring.decode("hex")
  datastring = data[6] + data[7] + data[4] + data[5] + data[2] + data[3] + data[0] + data[1]
  datastring = codecs.decode(datastring, "hex")
  #datastring = datastring.decode("hex")
  ser.write(wrstring)
  ser.write(addrstring)
  ser.write(datastring)

def write_serial_128(addr, data):
  data = data[2:]
  for x in range(0, int(128/32)):
    addr_loc = hex(int(addr, 16) + x*4)
    addr_loc = addr_loc[2:]
    data_loc = data[-8*x-8:(int(128/4))-8*x]
    write_serial(addr_loc, data_loc)


def read_serial_128(addr):
  s_1x = ""
  for x in range(0, int(128/32)):
    addr_loc = hex(int(addr, 16) + x*4)
    addr_loc = addr_loc[2:]
    s_1x = read_serial(addr_loc) + s_1x
  #print ("The value is %s" %  s_1x)
  return s_1x



def write_serial_256(addr, data):
  data = data[2:]
  for x in range(0, int(256/32)):
    addr_loc = hex(int(addr, 16) + x*4)
    addr_loc = addr_loc[2:]
    data_loc = data[-8*x-8:(int(256/4))-8*x]
    write_serial(addr_loc, data_loc)


def write_serial_1x(addr, data):
  data = data[2:]
  for x in range(0, int(CoFHEE_init_val.NSIZE/32)):
    addr_loc = hex(int(addr, 16) + x*4)
    addr_loc = addr_loc[2:]
    data_loc = data[-8*x-8:(int(CoFHEE_init_val.NSIZE/4))-8*x]
    write_serial(addr_loc, data_loc)

def write_serial_2x(addr, data):
  data = data[2:]
  for x in range(0, int(CoFHEE_init_val.NSQSIZE/32)):
    addr_loc = hex(int(addr, 16) + x*4)
    addr_loc = addr_loc[2:]
    data_loc = data[-8*x-8:(int(CoFHEE_init_val.NSQSIZE/4))-8*x]
    write_serial(addr_loc, data_loc)


def read_serial_1x(addr):
  s_1x = ""
  for x in range(0, int(CoFHEE_init_val.NSIZE/32)):
    addr_loc = hex(int(addr, 16) + x*4)
    addr_loc = addr_loc[2:]
    s_1x = read_serial(addr_loc) + s_1x
  #print ("The value is %s" %  s_1x)
  return s_1x

def read_serial_2x(addr):
  s_2x = ""
  for x in range(0, int(CoFHEE_init_val.NSQSIZE/32)):
    addr_loc = hex(int(addr, 16) + x*4)
    addr_loc = addr_loc[2:]
    s_2x = read_serial(addr_loc) + s_2x
  #print ("The value is %s" %  s_2x)
  return s_2x


#-------------------------------------------------------
#Verify Chip Signature
#-------------------------------------------------------
print ("INFO: Reading the Signature Register")
cleq_sign = read_serial  (CoFHEE_header.GPCFG_SIGNATURE)

if (cleq_sign == "0cc50302") :
  print ("INFO: Signature Read Correctly as %s" % cleq_sign)
else :
  print ("ERROR: Signature Read Wrong as %s instead of 0CC50302" % cleq_sign)
  print ("##### Exiting the Code because of above Error")
  exit()


#switch UART speed
print ("INFO: Switching UART speed")
#baudrate=512000,
write_serial (CoFHEE_header.GPCFG_UARTS_BAUD_CTL,  "0000005E")
write_serial (CoFHEE_header.GPCFG_UARTM_BAUD_CTL,  "0000005E")
#baudrate=1024000,
#write_serial (CoFHEE_header.GPCFG_UARTS_BAUD_CTL,  "0000002E")
#write_serial (CoFHEE_header.GPCFG_UARTM_BAUD_CTL,  "0000002E")
#baudrate=64000,
#CoFHEE_tasks.write_serial (CoFHEE_header.GPCFG_UARTM_BAUD_CTL,  "0000005D")

time.sleep(2)

print ("INFO: Disconnecting from SLOWER Serial Port of FHE Hardware")
print(ser.close())


