import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib import animation
import csv
import numpy as np

colors = ['r', 'g', 'b', 'y']
x = []
ys = dict()
ys2 = dict()
ys3 = dict()
mpl.style.use('default')

with open('../../output/result.txt','r') as csvfile:
	plots = csv.reader(csvfile, delimiter=',')
	for row in plots:
		if 't' not in row[0]:
			key = int(row[0])
			if key not in ys:
				ys[key] = []
				ys2[key] = []
				ys3[key] =[]
			ys[int(row[0])].append(float(row[1]))
			ys2[int(row[0])].append(float(row[2]))
			ys3[int(row[0])].append(float(row[3]))
		else:
			index = row[0].index('t')
			x.append(float(row[0][index + 4:]))

plt.subplot(121)
for y in ys:
	plt.plot(x, ys[y])
	plt.xlabel('Time (s)')
	plt.ylabel('Distance travelled (m)')	

plt.subplot(122)

for y in ys3:
	plt.plot(x, ys3[y])
	plt.xlabel('Time (s)')
	plt.ylabel('Speed (m/s)')
plt.show()


    
# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure()
ax = plt.axes(xlim=(0, 1000), ylim=(-2, 2))

t1 = np.zeros((len(x),len(ys)))
t2 = np.zeros((len(x),len(ys)))
for n in range(0,len(ys)):
    temp = ys[n]
    temp2 = ys2[n]
    for i in range(0,len(x)):
        t1[i][n] = temp[i]
        t2[i][n] = temp2[i]
print(t1[0])
print(t2[0])
point, = ax.plot(t1[0],t2[0],'o')

# animation function.  This is called sequentially
def animate(i):
    x = t1[i]
    y = t2[i]
    point.set_data(x, y)
    return point

ani = animation.FuncAnimation(fig, animate, interval=1, blit = False, repeat = False)

plt.show()