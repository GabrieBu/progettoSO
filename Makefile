all: attivatore.o alimentazione.o atomo.o master.o inibitore.o libscissione.o definizioni.h
	gcc attivatore.o alimentazione.o atomo.o master.o inibitore.o libscissione.o definizioni.h progetto
clean:
	rm -f *.o