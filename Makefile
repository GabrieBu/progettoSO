compile:
	gcc attivatore.c -o attivatore
	gcc alimentazione.c -o alimentazione
	gcc atomo.c -o atomo
	gcc master.c -o master
	gcc inibitore.c -o inibitore

run:
	./master
	
clean:
	rm -f *.o
	ls | grep -v "\." | grep -v Makefile | xargs rm