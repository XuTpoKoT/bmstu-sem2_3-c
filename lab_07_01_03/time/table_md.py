table = open("table.txt","w")

for size in [10, 30, 100, 300, 1000, 1500, 2000, 2500, 3000]:
    f1 = open(f"avg_{size}_1.txt","r")
    f2 = open(f"avg_{size}_2.txt","r")
    line = f1.readline().split() 
    t1 = float(line[0])
    line = f2.readline().split() 
    t2 = float(line[0])

    table.write("|{:d}|{:.6f}|{:.6f}|\n".format(size, t1, t2))

    f1.close()
    f2.close()
