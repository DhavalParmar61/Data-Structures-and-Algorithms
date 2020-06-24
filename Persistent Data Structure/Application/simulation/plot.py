import matplotlib.pyplot as plt
import numpy as np

x,y=np.loadtxt('simulation(0.4,0.3,0.3).txt',delimiter=' ',unpack=True)
plt.plot(x,y,label='simulation(0.4,0.3,0.3)')


plt.xlabel('Time')
plt.ylabel('State')
plt.title('(0.4,0.3,0.3)')
plt.legend()
plt.show()
