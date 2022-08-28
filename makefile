all: main.out

main.out: main.o
	gcc -o $@ -lm $<

%.o: %.c
	gcc -o $@ -c $<
