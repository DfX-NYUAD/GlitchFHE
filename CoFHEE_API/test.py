from sympy import ntt, symbols, intt

# Define a list of numbers for NTT
data = [1, 2, 3, 4]

# Apply NTT
ntt_result = ntt(data, 5)
print(ntt_result)


data = [0, 4, 3, 2]
intt_result = intt(data, 5)
print(intt_result)



