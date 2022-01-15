import matplotlib.pyplot as plt

x = [10, 30, 100, 300, 1000, 1500, 2000, 2500, 3000]
y1, y2 = [], []
for size in x:
    f1 = open(f"avg_{size}_1.txt","r")
    f2 = open(f"avg_{size}_2.txt","r")
    
    y1.append(float(f1.readline().split()[0]))
    y2.append(float(f2.readline().split()[0]))

    f1.close()
    f2.close()

plt.xlabel("Размер массива")
plt.ylabel("Среднее время, мкс")
plt.plot(x, y1, "+-", color="red", label="Mysort")
plt.plot(x, y2, "+-", color="blue", label="Qsort")
plt.legend(loc="best")
plt.show()
