#Parameters
e_mu                   = 0     # mean
e_sigma                = 3.2   # standard deviation
e_bound                = 19    # bound (values beyond this range should be clipped)
N                      = 8192
delta                  = 2**32
ntowers_qi             = 2
ntowers_pi             = 1
ntowers                = ntowers_qi + ntowers_pi
primes, primes_diffs   = find_ntt_primes_near_input(delta, ntowers, N)
qi                     = primes[0:ntowers_qi]
pi                     = primes[ntowers_qi:ntowers]
Q                      = 1
P                      = 1
prim_roots             = []

for x in qi:
    Q *= x

for x in pi:
    P *= x

for x in qi:
  prim_roots.append(find_prim_root(x, N))


sk, pk, evk  = generate_keys_ckks(N, Q, e_mu, e_sigma, e_bound, P, "false")


#Tower 0 elements: 9358 4495 11276 8869 1061 1222 12287 6071 5016 14551 9912 9066 2811 374 13789 8492 2131 3517 10966 7582 5483 2717 11186 9008 5441 1763 281 9072 2276 5378 12690 11300
#Tower 1 elements: 9118 4255 12956 9109 1301 1462 13007 6791 5736 15751 11112 10266 2571 134 15469 8732 2371 3757 11686 8302 6203 1997 12386 10208 5201 1523 41 9312 2516 5618 13410 12020
#qs: 16001 17921


#q = 16001
#N = 32
#tow0 = [9358, 4495, 11276, 8869,  1061,  1222,  12287,  6071,  5016,  14551,  9912 ,  9066 ,  2811,  374,  13789,  8492,  2131,  3517,  10966,  7582,  5483,  2717,  11186,  9008 ,  5441,  1763,  281,  9072,  2276,  5378,  12690,  11300]
#tow1 = [9118, 4255, 12956, 9109,  1301,  1462,  13007,  6791,  5736,  15751,  11112,  10266,  2571,  134,  15469,  8732,  2371,  3757,  11686,  8302,  6203,  1997,  12386,  10208,  5201,  1523,  41 ,  9312,  2516,  5618,  13410,  12020]
#tow0 = [(x % q) for x in tow0]
#tow1 = [(x % q) for x in tow1]
#
#print("------------")
#find_prim_root(q, N)
#poly_mul(tow0, tow1, 16001), poly_mul_ntt(tow0, tow1, q, N, 211, 12519)
#ntt(tow0, q, N, 6889), sympy.ntt(tow0, q)
#find_prim_root(q, N)
#(83**N) % q
qi, pi, modInverse(4295344129, 4295049217)
q0 = 4295049217
q1 = 4295294977
q2 = 4295344129
modInverse(8192, q0), modInverse(8192, q1), modInverse(8192, q2), prim_roots

