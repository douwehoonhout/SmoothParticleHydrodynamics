import matplotlib.pyplot as plt
import csv

colors = ['r', 'g', 'b', 'y']
x = []
ys = dict()
ys2 = dict()

with open('../../output/result.txt','r') as csvfile:
	plots = csv.reader(csvfile, delimiter=',')
	for row in plots:
		if 't' not in row[0]:
			key = int(row[0])
			if key not in ys:
				ys[key] = []
				ys2[key] = []
			ys[int(row[0])].append(float(row[1]))
			ys2[int(row[0])].append(float(row[2]))
		else:
			index = row[0].index('t')
			x.append(float(row[0][index + 4:]))

plt.subplot(121)
for y in ys:
	plt.plot(x, ys[y], colors[y % len(colors)])
	plt.xlabel('Time')
	plt.ylabel('Distance travelled')
plt.show()	
plt.pause(1)

plt.subplot(122)
for y in ys2:
	plt.plot(x, ys2[y], colors[y % len(colors)])
	plt.xlabel('Time')
	plt.ylabel('Speed')
plt.show()
