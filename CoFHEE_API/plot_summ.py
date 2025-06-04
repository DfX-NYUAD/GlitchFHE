import summ

import matplotlib.pyplot as plt
import numpy as np

# Get data
summ = summ.summ

# Extract x, y, variables
x = [item[0][0] for item in summ]
y = [item[0][1] for item in summ]

# Choose which variable to visualize (index 0–7)
var_idx = 0  # first variable

var_values = [item[1][var_idx] for item in summ]

# Normalize size for scatter (adjust scaling as needed)
sizes = np.array(var_values) * 50  # scale factor for dot size

plt.figure(figsize=(8, 6))
scatter = plt.scatter(x, y, c=var_values, s=sizes, cmap='viridis', alpha=0.7, edgecolors='k')

# Add colorbar
cbar = plt.colorbar(scatter)
cbar.set_label(f'Variable {var_idx + 1} value')

# Labels and title
plt.xlabel('X')
plt.ylabel('Y')
plt.title(f'Scatter Plot with Variable {var_idx + 1} as Color and Size')

# Optional: show value labels on points
for i, val in enumerate(var_values):
    plt.text(x[i], y[i], str(val), fontsize=8, ha='center', va='center', color='white')

    plt.grid(True)
    plt.show()

