import sys
import matplotlib.pyplot as plt
n = len(sys.argv)
f1 = open(sys.argv[1],'r')
quicksort = [0.000003, 0.000002, 0.000034, 0.000266, 0.002405, 0.012674]
selection = [float(num.split(' ')[-1]) for num in f1.readlines()]
if n>2:
	f2 = open(sys.argv[2],'r')
	insertion = [float(num.split(' ')[-1]) for num in f2.readlines()]
if n>3:
	f3 = open(sys.argv[3],'r')
	bubble = [float(num.split(' ')[-1]) for num in f3.readlines()]
if n>4:
	f4 = open(sys.argv[4],'r')
	merge = [float(num.split(' ')[-1]) for num in f4.readlines()]
if n>5:
	f5 = open(sys.argv[5],'r')
	heap = [float(num.split(' ')[-1]) for num in f5.readlines()]
#print(selection,insertion,merge,heap,sep="\n")
x_labels = ['5', '10', '100', '1000', '10000','100000']

plt.plot(quicksort,color='yellow',label='Inbuilt quicksort')
plt.plot(selection, color='red', label=sys.argv[1][:sys.argv[1].rfind('.')])
if n>2:
	plt.plot(insertion, color='green', label=sys.argv[2][:sys.argv[2].rfind('.')])
if n>3:
	plt.plot(bubble, color='violet', label=sys.argv[3][:sys.argv[3].rfind('.')])
if n>4:
	plt.plot(merge, color='blue', label=sys.argv[4][:sys.argv[4].rfind('.')])
if n>5:
	plt.plot(heap, color='orange', label=sys.argv[5][:sys.argv[5].rfind('.')])

plt.xlabel('Array Size')
plt.ylabel('Time Taken')
plt.title('Time Taken for different sorting techniques vs Array Size')
plt.xticks(range(len(x_labels)), x_labels)

# Add legend
plt.legend()

# Show the graph
plt.show()