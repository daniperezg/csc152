# sign.py by Daniela Perez. Submitted for CSC 152 on November 26, 2024

import sys
import random
from math import gcd

# compute e. must be 0 < e < p and gcd(e, p-1) = 1
def compute_e(p):
    while True:
        bits = p.bit_length()
        e = random.getrandbits(bits)

        if 0 < e < p and gcd(e,(p-1)) == 1:
            return e
    
def signature(p, g, gd, d, x):
    e = compute_e(p)
    # print(e)

    # r = g^e mod p
    r = pow(g, e, p)

    # modular inverse python 3.8+. e mod (p-1)
    e_inverse = pow(e, -1, p-1)

    # s = e_inv * (x - d * r) mod (p-1)
    s = (e_inverse * (x - d * r)) % (p-1)

    return r, s

def main():
    # check if right input 
    if len(sys.argv) != 6:
        print("Usage: python sign.py <p> <g> <gd> <d> <x>")
        sys.exit(1)

    p = int(sys.argv[1])
    g = int(sys.argv[2])
    gd = int(sys.argv[3])
    d = int(sys.argv[4])
    x = int(sys.argv[5])

    r, s = signature(p, g, gd, d, x)

    print(r)
    print(s)

if __name__ == "__main__":
    main()