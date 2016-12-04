 progetto_pt1 : parte1-main-test-minimale.o Insieme_int.o Insieme_Coppia.o Coppia.o Relazione.o
	g++ -o progetto_pt1 parte1-main-test-minimale.o Insieme_int.o Insieme_Coppia.o Coppia.o Relazione.o

 parte1-main-test-minimale.o : parte1-main-test-minimale.cpp Insieme_Coppia.h Insieme_int.h Coppia.h Relazione.h
	g++ -c parte1-main-test-minimale.cpp -o parte1-main-test-minimale.o

 Relazione.o : Relazione.cpp Insieme_Coppia.h Insieme_int.h Coppia.h Relazione.h
	g++ -c Relazione.cpp -o Relazione.o

 Insieme_int.o : Insieme_int.cpp Insieme_int.h
	g++ -c Insieme_int.cpp -o Insieme_int.o

 Insieme_Coppia.o : Insieme_Coppia.cpp Insieme_Coppia.h Coppia.h
	g++ -c Insieme_Coppia.cpp -o Insieme_Coppia.o

 Coppia.o : Coppia.cpp Coppia.h
	g++ -c Coppia.cpp -o Coppia.o

 clean:
	rm -f *.o
	rm -f progetto_pt1
	@echo Rimozione file oggetto completata
