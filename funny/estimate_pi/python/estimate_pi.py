import sys
import random

def estimate_pi(n):
    point_in_circle = 0
    point_in_total = 0
    for i in range(n):
        x = random.uniform(0, 1)
        y = random.uniform(0, 1)
        if x*x + y*y < 1:
            point_in_circle += 1
        point_in_total += 1

    pi = 4 * (point_in_circle / point_in_total)
    print("estimate pi: ",  pi)

if __name__ == '__main__':
    if (len(sys.argv) < 2):
        print("usage:", sys.argv[0], " n")
        sys.exit()
    estimate_pi(int(sys.argv[1]))
