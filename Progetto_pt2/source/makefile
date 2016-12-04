LDFLAGS=`wx-config --libs`
COMPILEFLAGS=`wx-config --cxxflags`
CXX=g++
# flag che ordina al compilatore di visualizzare tutti i warning
CXXFLAGS=-Wall

Progetto_pt2: Relazione.o Poset.o Catena.o Temp.o Menu.o Keyboard.o Progetto_pt2.o 
	g++ $(CXXFLAGS) -o ../Progetto_pt2 Relazione.o Poset.o Catena.o Temp.o Menu.o Keyboard.o Progetto_pt2.o $(LDFLAGS)
	@echo "L'applicazione Progetto_pt2 e' stata compilata correttamente"
	@ rm *.o
	@echo "Rimozione file oggetto.. completata"


Relazione.o: Relazione.cpp Relazione.h Coppia.h Insieme.h
	g++ $(CXXFLAGS) -c Relazione.cpp $(COMPILEFLAGS)

Poset.o: Poset.cpp Poset.h Coppia.h Insieme.h Relazione.h
	g++ $(CXXFLAGS) -c Poset.cpp $(COMPILEFLAGS)

Catena.o: Catena.cpp Catena.h Coppia.h Insieme.h Relazione.h Poset.h
	g++ $(CXXFLAGS) -c Catena.cpp $(COMPILEFLAGS)

Temp.o: Temp.cpp Temp.h Coppia.h Insieme.h
	g++ $(CXXFLAGS) -c Temp.cpp $(COMPILEFLAGS)

Menu.o: Menu.cpp Menu.h Progetto_pt2.h Coppia.h Insieme.h Relazione.h Poset.h Catena.h Temp.h
	g++ $(CXXFLAGS) -c Menu.cpp $(COMPILEFLAGS) 

Keyboard.o: Keyboard.cpp Keyboard.h Progetto_pt2.h Coppia.h Insieme.h Relazione.h Poset.h Catena.h Temp.h
	g++ $(CXXFLAGS) -c Keyboard.cpp $(COMPILEFLAGS) 


Progetto_pt2.o: Progetto_pt2.cpp Progetto_pt2.h Menu.h Keyboard.h Coppia.h Insieme.h Relazione.h Poset.h Catena.h Temp.h
	g++ $(CXXFLAGS) -c Progetto_pt2.cpp $(COMPILEFLAGS) 

clean: 
	@ rm *.o
	@echo "Rimozione file oggetto.. completata"

remove: 
	@ rm ../Progetto_pt2.exe ../backup_progetto
	@echo "Rimozione backup_progetto e Progetto_pt2.. completata"
