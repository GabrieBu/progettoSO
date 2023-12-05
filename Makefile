master.c: libscissione.h libscissione.c
	gcc libscissione.c -o libscissione

compile:
	gcc -c atomo.c libscissione.c 
	gcc -c attivatore.c libscissione.c
	gcc -c alimentazione.c libscissione.c
	gcc -c inibitore.c libscissione.c
	gcc -c master.c libscissione.c
	gcc atomo.o libscissione.o -o atomo
	gcc attivatore.o libscissione.o -o attivatore
	gcc alimentazione.o libscissione.o -o alimentazione
	gcc inibitore.o libscissione.o -o inibitore
	gcc master.o libscissione.o -o master

start:
	./master
	
clean:
	rm -f *.o
	ls | grep -v "\." | grep -v Makefile | xargs rm