#CFLAGS=-DDEBUG
all: Suffix.exe
  
clean:
	rm Suffix.o Suffix.exe Ukkenons.o
  
Suffix.exe: Ukkenons.o
	g++ -std=c++11 -g -o Suffix.exe Ukkenons.o
  
Ukkenons.o: Ukkenons.cpp
	g++ -std=c++11 -c -g Ukkenons.cpp $(CFLAGS)