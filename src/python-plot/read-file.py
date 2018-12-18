import matplotlib.pyplot as plt
from matplotlib import animation
import csv
import numpy as np

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

plt.subplot(122)
for y in ys2:
	plt.plot(x, ys2[y], colors[y % len(colors)])
	plt.xlabel('Time')
	plt.ylabel('Speed')
plt.show()
    
# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure()
ax = plt.axes(xlim=(0, 2500), ylim=(-2, 2))
y = np.zeros(10)

t = np.zeros((len(x),10))
for n in range(0,10):
    temp = ys[n]
    for i in range(0,len(x)):
        t[i][n] = temp[i]
print(t[0])
point, = ax.plot(t[0],y,'o')

# animation function.  This is called sequentially
def animate(i):
    x = t[i]
    y = np.zeros(10)
    point.set_data(x, y)
    return point

ani = animation.FuncAnimation(fig, animate, interval=0.05, blit = False, repeat = False)

plt.show()