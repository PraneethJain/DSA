all: q1 q2 q3 q4

q1: 1/main.o 1/hash.o
	gcc 1/main.o 1/hash.o -o 1/q1.o
q2: 2/main.o 2/hash.o
	gcc 2/main.o 2/hash.o -o 2/q2.o
q3: 3/main.o 3/heap.o
	gcc 3/main.o 3/heap.o -o 3/q3.o
q4: 4/main.o 4/heap.o
	gcc 4/main.o 4/heap.o -o 4/q4.o

1/main.o: 1/main.c
	gcc -c 1/main.c -o 1/main.o
1/hash.o:
	gcc -c 1/hash.c -o 1/hash.o

2/main.o: 2/main.c
	gcc -c 2/main.c -o 2/main.o
2/hash.o:
	gcc -c 2/hash.c -o 2/hash.o

3/main.o: 3/main.c
	gcc -c 3/main.c -o 3/main.o
3/heap.o: 3/heap.c
	gcc -c 3/heap.c -o 3/heap.o

4/main.o: 4/main.c
	gcc -c 4/main.c -o 4/main.o
4/heap.o: 4/heap.c
	gcc -c 4/heap.c -o 4/heap.o

clean:
	rm 1/*.o
	rm 2/*.o
	rm 3/*.o
	rm 4/*.o
