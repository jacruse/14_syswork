run: all
	./run -c 4
	./run -v
	./run -c 4
	./run -v
	./run -r
	./run -v

all: main.o
	gcc -o run main.o 

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *~
	rm -rf *.o
	rm -rf run
