all: Suffix.exe
  
clean:
	rm Suffix.o Suffix.exe
  
Suffix.exe: Suffix.o
	g++ -std=c++11 -g -o Suffix.exe Suffix.o
  
Suffix.o: Suffix.cpp
	g++ -std=c++11 -c -g Suffix.cpp