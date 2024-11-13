import pandas as pd
import matplotlib.pyplot as plt

# Read data from CSV files
data = pd.read_csv('/home/benjamin/Downloads/trainning_fixed_direction.csv')


# Assuming both CSV files have a column named 'x' for the x-axis and 'y' for the y-axis

# Plot data from the first CSV file
plt.plot(data['Step'].values,data['SAC'].values, label='SAC')
plt.plot(data['Step'].values,data['DDPG'].values, label='DDPG')
plt.plot(data['Step_PPO'].values,data['PPO'].values, label='PPO')

# Plot data from the second CSV file


# Customize the plot
plt.title('Fixed grasp position and Fixed preferred direction')
plt.xlabel('Steps')  # Add x-axis label
plt.ylabel('Cumulative reward')  # Add y-axis label
plt.legend()  # Display legend
plt.grid()
# Show the plot
plt.show()