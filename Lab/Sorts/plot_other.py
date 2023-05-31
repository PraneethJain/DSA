import matplotlib.pyplot as plt

selection_comps = [15, 55, 5050, 500500, 5000050000]
selection_swaps = [5, 10, 100, 1000, 10000, 100000]

insertion_comps = [10, 28, 2303, 253377, 24898722, 2497393268]
insertion_swaps = [8, 22, 2210, 252384, 24888736, 2497293280]


x_labels = ['5', '10', '100', '1000', '10000','100000']

plt.plot(selection_comps,color='blue',label='Selection')
plt.plot(insertion_comps, color='red', label='Insertion')

# plt.plot(selection_swaps,color='blue',label='Selection')
# plt.plot(insertion_swaps, color='red', label='Insertion')


plt.xlabel('Array Size')
plt.ylabel('Comparisons')
plt.xticks(range(len(x_labels)), x_labels)

# Add legend
plt.legend()

# Show the graph
plt.show()