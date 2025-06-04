import numpy as np
import sympy
import secrets
import math
from typing import Optional
from scipy.stats import norm
from sympy.ntheory.residue_ntheory import nthroot_mod

#generate prime numbers closer to delta
def is_prime(n):
    """Check if a number is prime."""
    if n <= 1:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True

def find_ntt_primes_near_input(input_number, n, N):
    """Find n prime numbers of the form k * 2^N + 1 near the input number."""
    primes = []
    diff   = []
    #k = int((0.9*input_number)/(2*N))
    k = int((input_number)/(2*N))

    # Generate numbers of the form k * 2^N + 1
    while len(primes) < n:
        candidate = k * (2 * N) + 1
        if is_prime(candidate):
            #if abs(candidate - input_number) < abs(primes[-1] - input_number) if primes else True:
          primes.append(candidate)
          diff.append(abs(1/input_number - 1/candidate))
        k += 1

    return primes, diff

#Polynomial operations

def poly_mul(p1, p2, q) :
  """Multiply two negacyclic polynomials.
  Note that this is not an optimal implementation.
  """
  N = len(p1)

  # Multiply and pad the result to have length 2N-1
  prod        = np.polymul(p1, p2)
  prod_padded = np.zeros(2 * N - 1)
  prod_padded[: len(prod)] = prod

  # Use the relation x^N = -1 to obtain a polynomial of degree N-1
  result = prod_padded[:N]
  result[:-1] -= prod_padded[N:]
  result = result % q
  return result


def poly_add(p1, p2, q) :
  coeff=np.add(p1, p2)
  result = coeff % q
  return result


def poly_sub(p1, p2, q) :
  coeff=np.subtract(p1, p2)
  result = coeff % q
  return result

def gen_rand(n, Q):
  k              = math.ceil(math.log2(Q))
  #random_numbers = [secrets.token_bytes(k) for _ in range(n)]  # 16 bytes = 128 bits
  random_numbers = [int.from_bytes(secrets.token_bytes(k), 'big') for _ in range(n)]
  return random_numbers

def egcd_sw(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd_sw(b % a, a)
        return (g, x - (b // a) * y, y)

def modInverse(a, m):
    g, x, y = egcd_sw(a, m)
    if g != 1:
        x = 0
    else:
        x = x % m
    return x

#def modInverse(a, m) :
#    a = a % m;
#    for x in range(1, m) :
#        if ((a * x) % m == 1) :
#            return x
#    return 1

def bitReverse(num, len):
        """
        integer bit reverse
        input: num, bit length
        output: rev_num
        example: input 6(110) output 3(011)
        complexity: O(len)
        """
        rev_num = 0
        for i in range(0, len):
            if (num >> i) & 1:
                rev_num |= 1 << (len - 1 - i)
        return rev_num

def orderReverse(p, N_bit):
      poly = p.copy()
      """docstring for order"""
      for i, coeff in enumerate(poly):
          rev_i = bitReverse(i, N_bit)
          if rev_i > i:
              coeff ^= poly[rev_i]
              poly[rev_i] ^= coeff
              coeff ^= poly[rev_i]
              poly[i] = coeff
      return poly


def ntt(p, M, N, w):
      poly = p.copy()
      """number theoretic transform algorithm"""
      #print ("poly:", poly)
      N_bit = N.bit_length() - 1
      poly_rev = orderReverse(poly, N_bit)
      #print ("rev_poly:", poly)
      for i in range(0, N_bit):
          points1, points2 = [], []
          for j in range(0, int(N / 2)):
              shift_bits = N_bit - 1 - i
              P = (j >> shift_bits) << shift_bits
              w_P = pow(w, P, M)   #w ** P % M
              even = poly_rev[2 * j]
              odd = poly_rev[2 * j + 1] * w_P
              #print("Stage :", i, "npoint :", j, "even :", poly[2 * j], "odd :", poly[2 * j + 1], "twidde :", w_P, "Result :", (even + odd) % M,  (even - odd) % M )
              points1.append((even + odd) % M)
              points2.append((even - odd) % M)
              # TODO: use barrett modular reduction
              points = points1 + points2
          if i != N_bit:
              poly_rev = points
      return points


def intt(p, M, N, w):
      temp_p = p.copy()
      N_bit = N.bit_length() - 1
      print ("poly and bit length:", temp_p, N_bit)
      N_inv = modInverse(N,  M)
      intt_points = []
      for i in range(N):
        intt_points.append(((temp_p[i]*N_inv) % M))
      """number theoretic transform algorithm"""
      poly = intt_points
      print ("SWDBG: INTT N_inv, w, poly:", N_inv, w, poly)
      poly_rev = orderReverse(poly, N_bit)
      for i in range(0, N_bit):
          points1, points2 = [], []
          for j in range(0, int(N / 2)):
              shift_bits = N_bit - 1 - i
              P = (j >> shift_bits) << shift_bits
              w_P = pow(w, P, M)   #w ** P % M
              even = poly_rev[2 * j]
              odd = poly_rev[2 * j + 1] * w_P
              #print("Stage :", i, "npoint :", j, "even :", poly[2 * j], "odd :", poly[2 * j + 1], "twidde :", w_P, "Result :", (even + odd) % M,  (even - odd) % M )
              points1.append((even + odd) % M)
              points2.append((even - odd) % M)
              # TODO: use barrett modular reduction
              points = points1 + points2
          if i != N_bit:
              poly_rev = points
      #intt_points = []
      #for i in range(N):
      #  intt_points.append(((points[i]*N_inv) % M))
        #print (intt_points)
        #print ((x*N_inv) %  q)
      return points


def find_prim_root(q, N):
   W_N  = nthroot_mod(1, N,   q, all_roots = True)
   W_2N = nthroot_mod(1, 2*N, q, all_roots = True)

   W_2N_prim = []
   W_N_prim  = []

   for x in W_2N:
     i = N
     #i = N-1
     not_prim_root = 0;
     while i > 1:
       #if (((x**i) % q) == 1):
       if (pow(x, int(i), q) == 1):
         not_prim_root = 1;
         break
       i = i/2
       #i = i-1
     if(not_prim_root == 0):
       W_2N_prim.append(x)
       #print(x)

   for x in W_N:
     i = N/2
     #i = N-1
     not_prim_root = 0;
     while i > 1:
       #if (((x**i) % q) == 1):
       if (pow(x,int(i),q) == 1):
         not_prim_root = 1;
         break
       i = i/2
       #i = i-1
     if(not_prim_root == 0):
       W_N_prim.append(x)

   for x in W_2N_prim:
     if (((x * x)  % q) in W_N_prim):
       W_root2N = x
       W_rootN  = (x * x)  % q
       break

   #print("All the primitive 2Nth root:", W_2N_prim,"All the Nth primitive root:",  W_N_prim)
   print("Chosen primitive 2Nth root:", W_root2N,"Chosen Nth primitive root:",  W_rootN)
   return  W_root2N, W_rootN

def poly_mul_ntt(t0, t1, q, N, W_root2N, W_rootN) :
   tow0 = t0.copy()
   tow1 = t1.copy()

   tow0_pre = []
   tow1_pre = []

   for i in range(N):
     tow0_pre.append((tow0[i]*(pow(W_root2N, i, q))) % q)
     tow1_pre.append((tow1[i]*(pow(W_root2N, i, q))) % q)

   #tow0_ntt = ntt(tow0_pre, q, N, W_rootN)
   #tow1_ntt = ntt(tow1_pre, q, N, W_rootN)
   tow0_ntt = sympy.ntt(tow0_pre, q)
   tow1_ntt = sympy.ntt(tow1_pre, q)

   tow_pmul = []
   for i in range(N):
     tow_pmul.append(tow0_ntt[i]*tow1_ntt[i] % q)

   W_root2N_inv  = modInverse(W_root2N, q)
   W_rootN_inv   = modInverse(W_rootN,  q)
   #tow_pmul_intt = intt(tow_pmul, q, N, W_rootN_inv)
   tow_pmul_intt = sympy.intt(tow_pmul, q)

   tow_mul = []
   for i in range(N):
     tow_mul.append((tow_pmul_intt[i]*(pow(W_root2N_inv, i, q))) % q)

   return tow_mul

def gen_rand(n, Q):
  k              = math.ceil(math.log2(Q))
  random_numbers = [secrets.randbits(k) % Q for _ in range(n)]
  return random_numbers


def gen_noise(mu, sigma, bound, size):
  # Generate samples from a normal (continuous) distribution
  samples = np.random.normal(mu, sigma, size)
  # Clip values to be within the bound (-19 to 19)
  samples = np.clip(samples, -bound, bound)
  # Round the samples to get discrete values
  discrete_samples = np.round(samples)
  return(discrete_samples)

def encode_ckks (clrt, N, delta):
  M     = 2*N
  delta = delta
  conjugates = np.conj(clrt)
  # Reverse the order of the conjugates
  reversed_conjugates = conjugates[::-1]
  # Combine the original set with the reversed conjugates
  clrt_exp = np.concatenate((clrt, reversed_conjugates))
  odd_indices    = [k for k in range(M) if k % 2 == 1]
  prim_roots_of_unity = np.array([np.exp(2j * np.pi * k / M) for k in odd_indices])
  # Create the Vandermonde matrix from the roots of unity
  sigma = np.vander(prim_roots_of_unity, increasing=True)
  # Invert the Vandermonde matrix
  sigma_inv = np.linalg.inv(sigma)
  pt_real = np.dot(sigma_inv, clrt_exp)
  pt = delta*pt_real
  pt = np.array([round(x) for x in pt.real])
  return pt

def decode_ckks (pt, N, delta):
  M = 2*N
  delta = delta
  odd_indices    = [k for k in range(M) if k % 2 == 1]
  prim_roots_of_unity = np.array([np.exp(2j * np.pi * k / M) for k in odd_indices])
  # Create the Vandermonde matrix from the roots of unity
  sigma = np.vander(prim_roots_of_unity, increasing=True)
  clrt = np.dot(sigma, pt)
  clrt = [complex(round(x.real), round(x.imag)) for x in clrt / delta]
  return clrt[:int(N/2)]

def generate_keys_ckks(N, q, e_mu, e_sigma, e_bound, p, hybrid):
  rng   = np.random.default_rng()
  s     = rng.integers(low=-1, high=2, size=N)
  e     = gen_noise(e_mu, e_sigma, e_bound, N)
  a     = gen_rand(N, q)
  #b     = poly_sub(e, poly_mul(a, s, q), q)
  b     =  (-1* poly_mul(a, s, q) + e) % q
  qp    =  q*p
  a_evk = gen_rand(N, qp)
  #e_evk = np.int32((2**32) * np.random.normal(loc=0.0, scale=noise_std, size=N))
  e_evk = gen_noise(e_mu, e_sigma, e_bound, N)
  b_evk = poly_sub(e,       poly_mul(a_evk, s, q*p), q*p)
  b_evk = poly_add(b_evk, p*poly_mul(s,     s, q),   q*p)
  sk    = (1, s)
  pk    = (b, a)
  evk   = (b_evk, a_evk)

  return sk, pk, evk

def sample_r(n):
    # Define the probabilities for each value
    probabilities = [1/4, 1/2, 1/4]  # Probability of -1, 0, and 1
    values = [-1, 0, 1]  # Possible values
    # Sample from the distribution
    r = np.random.choice(values, size=n, p=probabilities)
    return r


def encrypt_ckks(pt, q, e_mu, e_sigma, e_bound, N, pk):
  e0     = gen_noise(e_mu, e_sigma, e_bound, N)
  e1     = gen_noise(e_mu, e_sigma, e_bound, N)
  r      = sample_r(N)
  c0     = (poly_mul(r, pk[0], q) + pt + e0) % q
  c1     = (poly_mul(r, pk[1], q)  + e1) % q
  c      = (c0, c1)
  return c

def decrypt_ckks(ct, sk, q):
   pt = poly_add(ct[0], poly_mul(ct[1], sk[1], q), q)
   return(pt)

def rns_split (poly, qi):
  rns_towers = []
  for x in qi:
    rns_towers.append(poly % x)
  return(rns_towers)

def rns_merge (rns_towers, qi, Q, N):
  L    = len(qi)
  poly = [0] * N
  for i in range (0, L):
    Q_hat = Q//qi[i]
    Q_hat_inv = sympy.mod_inverse(Q_hat, qi[i])
    for j in range (0, N):
      poly[j] = (poly[j] + (rns_towers[i][j]*Q_hat_inv*Q_hat) % Q) % Q
      #if (j ==0):
      #  print(poly[j])
  return(poly)


def poly_mul_rns_towers(rns_towers0, rns_towers1, qi):
  result = []
  i = 0
  for x in qi:
    result.append(poly_mul(rns_towers0[i], rns_towers1[i], x))
    i = i+1
  return result

def poly_mul_ntt_rns_towers(rns_towers0, rns_towers1, qi, N, prim_roots):
  result = []
  i = 0
  for x in qi:
    result.append(poly_mul_ntt(rns_towers0[i], rns_towers1[i], x, N, prim_roots[i][0], prim_roots[i][1]))
    i = i+1
  return result

def rescale_rns (rns_towers, qi, l, N):
  result = []
  print("DBG; value of qi, l, N:", qi, l, N)
  for i in range (0, l-1):
    p_inv = sympy.mod_inverse(qi[l-1], qi[i])
    #result.append((p_inv *(rns_towers[i] - rns_towers[l-1])) % qi[i])
    result.append([(p_inv * (rns_towers[i][j] - rns_towers[l-1][j])) % qi[i] for j in range(N)])
    print("DBGSW: i, tow i[0], tow last[0], qi[i], (tow i[0] - tow last[0]) mod qi", i, rns_towers[i][0], rns_towers[l-1][0], qi[i], (rns_towers[i][0] - rns_towers[l-1][0]) % qi[i])
  return(tuple(result))


def rescale_rns_ntt (rns_towers, qi, l, N):
  result = []
  last_tow_intt = sympy.intt(rns_towers[l-1], qi[l-1])
  print("SWDBG: last_tow_intt:", last_tow_intt)
  last_tow_mod_qi = []
  for i in range (0, l-1):
    last_tow_mod_qi.append(last_tow_intt[j] % qi[i] for j in range(N))
    last_tow_mod_qi = sympy.ntt(last_tow_intt, qi[i])
    p_inv = sympy.mod_inverse(qi[l-1], qi[i])
    #result.append((p_inv *(rns_towers[i] - last_tow_mod_qi)) % qi[i])
    result.append([(p_inv * (rns_towers[i][j] - last_tow_mod_qi[j])) % qi[i] for j in range(N)])
  return(tuple(result))


def rescale_rns_ntt_seal (rns_towers, qi, l, N):
  result = []
  last_tow_intt = rns_towers[l-1].copy()
  N_bit = N.bit_length() - 1
  last_tow_intt = orderReverse(last_tow_intt, N_bit)
  print("DBG: last_tow_intt:", last_tow_intt)
  last_tow_intt = sympy.intt(last_tow_intt, qi[l-1])
  last_tow_mod_qi = []
  for i in range (0, l-1):
    last_tow_mod_qi.append(last_tow_intt[j] % qi[i] for j in range(N))
    last_tow_mod_qi = sympy.ntt(last_tow_intt, qi[i])
    last_tow_mod_qi = orderReverse(last_tow_mod_qi, N_bit)
    print("DBG: len of last_tow_mod_qi:", len(last_tow_mod_qi))
    p_inv = sympy.mod_inverse(qi[l-1], qi[i])
    result.append([(p_inv * (rns_towers[i][j] - last_tow_mod_qi[j])) % qi[i] for j in range(N)])
  return(tuple(result))


def rescale_rns_ntt_seal_mod (rns_towers, qi, l, N):
  result = []
  last_tow_intt = rns_towers[l-1].copy()
  N_bit = N.bit_length() - 1
  last_tow_intt = orderReverse(last_tow_intt, N_bit)
  print("DBG: last_tow_intt:", last_tow_intt)
  last_tow_intt   = sympy.intt(last_tow_intt, qi[l-1])
  last_tow_mod_qi = last_tow_intt
  for i in range (0, l-1):
    last_tow_mod_qi = ((last_tow_intt[j] + (qi[l-1] >> 1) + qi[i] - (qi[l-1] >> 1) ) % qi[i] for j in range(N))
    last_tow_mod_qi = sympy.ntt(last_tow_intt, qi[i])
    last_tow_mod_qi = orderReverse(last_tow_mod_qi, N_bit)
    print("DBG: len of last_tow_mod_qi:", len(last_tow_mod_qi))
    p_inv = sympy.mod_inverse(qi[l-1], qi[i])
    result.append([(p_inv * (rns_towers[i][j] - last_tow_mod_qi[j])) % qi[i] for j in range(N)])
  return(tuple(result))


