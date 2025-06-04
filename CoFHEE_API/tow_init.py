import math
import random
import decimal
import sympy
import math


def modexp_sw ( g, u, p ):
  """computes s = (g ^ u) mod p
  args are base, exponent, modulus
  (see Bruce Schneier's book, _Applied Cryptography_ p. 244)"""
  s = 1
  while u != 0:
    if u & 1:
      s = (s * g)%p
    u >>= 1
    g = (g * g)%p;
  return s


def modInverse(a, m) :
    a = a % m;
    for x in range(1, m) :
        if ((a * x) % m == 1) :
            return x
    return 1

def primRoots(modulo, cmul, nroots):
  roots = []
  hit   = 0
  for g in range(1, modulo) :
    if (hit == nroots) :
      break
    else :
      for powers in range (1, modulo) :
        pow_mod = pow(g, powers) % modulo
        if (pow_mod == 1) :
          if (powers == modulo-1) :
            if (pow(g, cmul) < modulo) :
              roots.append(pow(g, cmul))
              hit = hit + 1
          else :
            break
  return roots


def egcd_sw(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd_sw(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv_sw(a, m):
    g, x, y = egcd_sw(a, m)
    if g != 1:
        x = 0
    else:
        x = x % m
    return x




#-------------------------------------------------------
#Below is fixed to size of N that hardware supports
#-------------------------------------------------------
def load_tow_param(q, N, N_inv, w):
  NSIZE     = int(128)
  NSQSIZE   = NSIZE*2
  DWIDTH    = int(128)
  POLYDEG   = int(N)
  
  #--------------------Global variables---------------------------
  modulus   = q
  barretk   = math.ceil(math.log(modulus, 2))
  barretk   = 2*barretk
  md_param  = math.floor((2**(barretk))//modulus)
  invpolydeg = q_inv
  nth_rou    = w
  print("-----Modulus, Barret k and md, Nth Root of Unity-----------")
  print("Modulus :",   modulus)
  print("Barret k :",  barretk)
  print("Barret md :", md_param)
  print("Primitive root of unity :", nth_rou)   ##GENTWDL
  print("--------------------------------------------------------------------------")
  #--------------------------------------------------------------
  
  
  #-------------------------------------------------------
  #All the variables with fhe_ prefix will be programmed
  #in CCS0302 hardware
  #------------------------------------------------------
  fhe_bk       = barretk    #barrett
  fhe_bmd      = md_param   #barrett
  fhe_N        = modulus
  fhe_NINV     = invpolydeg
  
  #-------------------------------------------------------
  #Derive other values to be programmed from above
  #-------------------------------------------------------
  
  
  fhe_log2ofN    = math.ceil(math.log(fhe_N, 2))
  fhe_ctl2       = int(fhe_log2ofN)
  
  
  
  print ("#------------------------------------------------------------------")
  print ("#INFO: Initial Values")
  print ("#------------------------------------------------------------------")
  print ("INFO: Value of Modulus         := %s" % fhe_N)
  print ("INFO: Value of NINV            := %s" % fhe_NINV)
  print ("INFO: Value of LOG2(modulus)   := %d" % int(fhe_log2ofN))
  print ("#------------------------------------------------------------------")
  
  #--------------------------------------------------------------------
  #Convert the values to be programmed to hexadecimal of required size
  #--------------------------------------------------------------------
  fhe_N              = "{0:#0{1}x}".format(int(fhe_N),int(NSIZE/4)+2)
  fhe_NINV           = "{0:#0{1}x}".format(int(fhe_NINV),int(NSIZE/4)+2)
  fhe_log2ofN        = "{0:#0{1}x}".format(int(fhe_log2ofN),12+2)
  fhe_polydeg        = "{0:#0{1}x}".format(int(POLYDEG),4+2)
  
  fhe_bk             = "{0:#0{1}x}".format(int(fhe_bk),int(32/4)+2)
  fhe_bmd            = "{0:#0{1}x}".format(int(fhe_bmd),int(2*NSIZE/4)+2)
  
  print ("INFO: Loading Initial Values to the FHE Hardware")
  CoFHEE_tasks.write_serial_128    (CoFHEE_header.GPCFG_N_ADDR[0],     CoFHEE_init_val.fhe_N)
  CoFHEE_tasks.write_serial_128    (CoFHEE_header.GPCFG_NINV_ADDR[0],  CoFHEE_init_val.fhe_NINV)
  CoFHEE_tasks.write_serial        (CoFHEE_header.GPCFG_FHECTL_ADDR,   CoFHEE_init_val.fhe_ctl)
  CoFHEE_tasks.write_serial_256    (CoFHEE_header.GPCFG_NSQ_ADDR[0],   CoFHEE_init_val.fhe_bmd)   
  CoFHEE_tasks.write_serial        (CoFHEE_header.GPCFG_NSQ_ADDR[5],   CoFHEE_init_val.fhe_bk[2:])
