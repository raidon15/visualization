import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# Read data from CSV file
#path_45 = pd.read_csv('/home/benjamin/panda_gym/csv/45_path.csv')
path_agent =pd.read_csv('/home/benjamin/panda_gym/csv/PPO.csv')
#path_perfect=pd.read_csv('/home/benjamin/panda_gym/csv/perfect_path.csv')
# Assuming the CSV file has columns 'x', 'y', and 'z'

# Create a 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlim(-0.1, 0.15)  # Set x-axis limits from 0 to 6
ax.set_xticks(np.arange(-0.1, 0.15, 0.05))
ax.set_ylim(-0.1, 0.3)  # Set x-axis limits from 0 to 6
ax.set_yticks(np.arange(-0.1, 0.3, 0.1))
ax.set_zlim(0.2, 0.6)  # Set x-axis limits from 0 to 6
ax.set_zticks(np.arange(0.2, 0.6, 0.1))
#x_45 = path_45['x'].values
#y_45 = path_45['y'].values
#z_45 = path_45['z'].values

x_agent = path_agent['x'].values
y_agent = path_agent['y'].values
z_agent = path_agent['z'].values

#x_perfect = path_perfect['x'].values
#y_perfect = path_perfect['y'].values
#z_perfect = path_perfect['z'].values

# Plot the 3D line
#ax.plot(x_45, y_45, z_45, label='45º trajectory')
ax.plot(x_agent, y_agent, z_agent, label='agent PPO trajectory')
#ax.plot(x_perfect, y_perfect, z_perfect, label='preferred direction trajectory')
# Customize the plot
#ax.set_title('3D Line Plot from CSV Data')
ax.set_xlabel('X-axis [m]')
ax.set_ylabel('Y-axis [m]')
ax.set_zlabel('Z-axis [m]')
ax.legend()

# Show the plot
plt.show()
