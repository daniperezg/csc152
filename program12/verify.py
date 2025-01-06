# verify.py by Daniela Perez. Submitted for CSC 152 on November 26, 2024

import sys

def verify(p, g, gd, x, r, s):
    # ((g^d)^r mod p * r^s mod p) mod p 
    left_side = (pow(gd, r, p) * pow(r, s, p)) % p

    # (g^x) mod p 
    right_side = pow(g, x, p)

    if left_side == right_side:
        return 1
    else:
        return 0


def main():
    #p, g, gd, x, r, and s 
    if len(sys.argv) != 7:
        print("Usage: python sign.py <p> <g> <gd> <x> <r> <s>")
        sys.exit(1)

    p = int(sys.argv[1])
    g = int(sys.argv[2])
    gd = int(sys.argv[3])
    x = int(sys.argv[4])
    r = int(sys.argv[5])
    s = int(sys.argv[6])

    answer = verify(p, g, gd, x, r, s)

    print(answer)

if __name__ == "__main__":
    main()