import sys

if len(sys.argv) == 2:
    size = int(sys.argv[1])
else:
    size = int(input("Size: "))

for i in range(1, 3):
    f_in = open(f"time_{size}_{i}.txt", "r")
    f_out = open(f"avg_{size}_{i}.txt", "w")

    sum_time = 0.0
    for j in range(1, 11):
        sum_time += float(f_in.readline())
    f_out.write(f"{sum_time / 10}\n")

    f_in.close()
    f_out.close()
