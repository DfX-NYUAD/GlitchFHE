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
NSIZE     = int(128)
NSQSIZE   = NSIZE*2
DWIDTH    = int(128)
#POLYDEG   = int(8192)
POLYDEG   = int(8192)

#--------------------Global variables---------------------------
#Find a prime number P = const_mul * (2**log2POLYDEG) + 1
log2polydeg = int(math.log(POLYDEG, 2))

const_mul = 2 # for 128
#const_mul = 1 # for 256
#const_mul = 24 # for 512
#const_mul = 3 # for 4096
#const_mul = 5 # for 8192

nroot     = 1 # Exit after finding nroot

modulus   = const_mul * 2**log2polydeg + 1            #GENTWDL
###modulus   = 1152921504606830593             #Custom Parameters

###barretk   = 45;           #barrett
#barretk   = 120;             #barrett
###md_param  = math.floor((2**barretk)/modulus)   #barrett            #GENTWDL
#md_param  = 1152921504606863360      #barrett   #Custom Parameters

barretk   = math.ceil(math.log(modulus, 2))
barretk   = 2*barretk
md_param  = math.floor((2**(barretk))//modulus)

###invpolydeg = modInverse(POLYDEG, modulus)
invpolydeg = modinv_sw(POLYDEG, modulus)
print("-----Modulus, Barret k and md, Nth Root of Unity and Selected Nth root of unity-----------")
print("Modulus :",   modulus)
print("Barret k :",  barretk)
print("Barret md :", md_param)
print("-----Finding the Nth (N = POLYDEG) root of unity for the above modulus-----------")

#primitive_roots = primRoots(modulus, const_mul, nroot)            #GENTWDL
primitive_roots = []
primitive_roots.append(int(653157713588759055))           #Custom Parameters

print("Primitive root of unity :", primitive_roots)   ##GENTWDL
nth_rou = primitive_roots[0]            #GENTWDL
print("Selected Nth Root of Unity", nth_rou)  #GENTWDL
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


lst   = list(range(modulus-1))               #GENTWDL
seq   = random.sample(lst, POLYDEG)          #GENTWDL
seq2  = random.sample(lst, POLYDEG)          #GENTWDL
twdl  = random.sample(lst, POLYDEG)          #GENTWDL
fseq  = random.sample(lst, POLYDEG)          #GENTWDL
fseq2 = random.sample(lst, POLYDEG)          #GENTWDL
ftwdl = random.sample(lst, POLYDEG)          #GENTWDL
#exec(open("oleg_input.txt").read())
#exec(open("oleg_twiddle.txt").read())
tempdata = random.sample(lst, POLYDEG)
print("-----DBG-2-----------")
for i in range(POLYDEG):
  fseq[i]  = "{0:#0{1}x}".format(int(seq[i]), int(NSIZE/4)+2)
  fseq2[i] = "{0:#0{1}x}".format(int(seq2[i]),int(NSIZE/4)+2)
  #ftwdl[i] = "{0:#0{1}x}".format(int((nth_rou**i)%modulus), int(NSIZE/4)+2)  #GENTWDL
  #print(" << DBG: Twiddle Value : %s" % int(modexp_sw(twdl[1],i,modulus)))
  #print(" << DBG: Twiddle Value : %s" % ftwdl[i])
print("-----DBG-1-----------")
