import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib import animation
import csv
import numpy as np

Writer = animation.writers['ffmpeg']
writer = Writer(fps=15,bitrate=5000)

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
	plt.xlabel('Time')
	plt.ylabel('Distance travelled')	

plt.subplot(122)
for y in ys3:
	plt.plot(x, ys3[y])
	plt.xlabel('Time')
	plt.ylabel('Speed')
plt.show()
    
# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure()
fig.set_size_inches(12.,4.)
ax = plt.axes(xlim=(0, 8000), ylim=(-3.7/2, 1.5*3.7))

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
point, = ax.plot(t1[0,:-1],t2[0,:-1],'o')
point2, = ax.plot(t1[0,-1],t2[0,-1],'yo')

# animation function.  This is called sequentially
def animate(i):
    x = t1[i,:-1]
    y = t2[i,:-1]
    x2 = t1[i,-1]
    y2 = t2[i,-1]
    point.set_data(x, y)
    point2.set_data(x2,y2)
    return point, point2

ani = animation.FuncAnimation(fig, animate, frames = 2000, interval=1, blit = False, repeat = False)
ani.save('lanechange2.mp4',writer=writer)
plt.show()