import matplotlib.pyplot as plt
import csv

colors = ['r', 'g', 'b', 'y']
x = []
ys = dict()

with open('../../output/result.txt','r') as csvfile:
	plots = csv.reader(csvfile, delimiter=',')
	for row in plots:
		if 't' not in row[0]:
			key = int(row[0])
			if key not in ys:
				ys[key] = []
			ys[int(row[0])].append(float(row[1]))
		else:
			index = row[0].index('t')
			x.append(float(row[0][index + 4:]))

for y in ys:
	plt.plot(x, ys[y], colors[y % len(colors)])
	plt.ylabel('some numbers')
plt.show()	
