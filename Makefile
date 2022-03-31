all: zing zing2 fconc

zing2: main.o zing2.o
        gcc -o zing2 main.o zing2.o
zing2.o: zing2.c
        gcc -Wall -c zing2.c

zing: main.o zing.o
        gcc -o zing main.o zing.o
main.o: main.c
        gcc -Wall -c main.c

fconc : concatination.o
        gcc -o fconc concatination.o
concatination.o: concatination.c
        gcc -Wall -c concatination.c

