import fhelib
import sympy
import numpy as np
import math
np.set_printoptions(threshold=np.inf)

def create_alternating_array(a, b, N):
    result = []
    for i in range(int(N/2)):
            result.append(int(a))
            result.append((b))
    return result


#CoFHEE_main.CoFHEE_tasks.ntt_load_coeff(s_modq, q, N)

N = 128

rng    = np.random.default_rng()
s      = rng.integers(low=-1, high=2, size=8192)
s00    = create_alternating_array( 0,  0, 128)
s01    = create_alternating_array( 0,  1, 128)
s0_1   = create_alternating_array( 0, -1, 128)
s10    = create_alternating_array( 1,  0, 128)
s11    = create_alternating_array( 1,  1, 128)
s1_1   = create_alternating_array( 1, -1, 128)
s_10   = create_alternating_array(-1,  0, 128)
s_11   = create_alternating_array(-1,  1, 128)
s_1_1  = create_alternating_array(-1, -1, 128)


q = 1073748737

s_modq     = [int(x % q) for x in fhelib.orderReverse(s    , int(math.log2(8192)))]
s00_modq   = [int(x % q) for x in fhelib.orderReverse(s00  , int(math.log2(N)))]
s01_modq   = [int(x % q) for x in fhelib.orderReverse(s01  , int(math.log2(N)))]
s0_1_modq  = [int(x % q) for x in fhelib.orderReverse(s0_1 , int(math.log2(N)))]
s10_modq   = [int(x % q) for x in fhelib.orderReverse(s10  , int(math.log2(N)))]
s11_modq   = [int(x % q) for x in fhelib.orderReverse(s11  , int(math.log2(N)))]
s1_1_modq  = [int(x % q) for x in fhelib.orderReverse(s1_1 , int(math.log2(N)))]
s_10_modq  = [int(x % q) for x in fhelib.orderReverse(s_10 , int(math.log2(N)))]
s_11_modq  = [int(x % q) for x in fhelib.orderReverse(s_11 , int(math.log2(N)))]
s_1_1_modq = [int(x % q) for x in fhelib.orderReverse(s_1_1, int(math.log2(N)))]
