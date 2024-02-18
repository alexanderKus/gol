all:
	cc main.c -o main -g -Wall
optimal:
	cc main.c -o main -Wall -O3
clean:
	rm -f main
