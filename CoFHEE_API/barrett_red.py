def mod_mul_sw(a, b, m, k, md):
    x = a*b
    r = (a, m, k, md)
    return r

def barrett_reduction(a, m, k, md):
    # Step 1: Precompute the constant mu = floor(b^(2k) / m)
    # where b is the base (usually 2 for binary numbers, i.e., b = 2)
    # and k is the number of bits in m
    #k = m.bit_length()
    #mu = (1 << (2 * k)) // m
    
    # Step 2: Compute q = floor(a / m) using mu
    #q = (a * mu) >> (2 * k)
    y_loc       = a*md
    y_loc_shftd = y_loc >> k
    
    # Step 3: Compute r = a - q * m
    #r = a - q * m
    y_red       = a - y_loc_shftd*m
    y_red_sub_m = y_red - m
    
    # Step 4: If r >= m, subtract m to ensure the result is in the range [0, m)
    if y_red >= m:
      r = y_red_sub_m
    else:
      r = y_red
    
    return r

# Example usage
a = 12345678901234567890
m = 987654321

result = barrett_reduction(a, m)
print(f"Barrett reduction of {a} mod {m} is {result}")

