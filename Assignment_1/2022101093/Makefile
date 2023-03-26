all: q1 q2 q3 q4
	
q1: 1/main.o 1/functions.o
	gcc 1/main.o 1/functions.o -o 1/q1.o
q2: 2/main.o 2/functions.o
	gcc 2/main.o 2/functions.o -o 2/q2.o
q3: 3/main.o 3/functions.o
	gcc 3/main.o 3/functions.o -o 3/q3.o
q4: 4/main.o 4/functions.o
	gcc 4/main.o 4/functions.o -o 4/q4.o

1/main.o: 1/main.c
	gcc -c 1/main.c -o 1/main.o
1/functions.o: 1/functions.c
	gcc -c 1/functions.c -o 1/functions.o

2/main.o: 2/main.c
	gcc -c 2/main.c -o 2/main.o

2/functions.o: 2/functions.c
	gcc -c 2/functions.c -o 2/functions.o

3/main.o: 3/main.c
	gcc -c 3/main.c -o 3/main.o

3/functions.o: 3/functions.c
	gcc -c 3/functions.c -o 3/functions.o

4/main.o: 4/main.c
	gcc -c 4/main.c -o 4/main.o

4/functions.o: 4/functions.c
	gcc -c 4/functions.c -o 4/functions.o

clean:
	rm 1/*.o
	rm 2/*.o
	rm 3/*.o
	rm 4/*.o