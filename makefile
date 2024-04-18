myprogram: main.o hangman.o
	g++ main.o hangman.o -o hangman

main.o: main.cpp hangman.h
	g++ -c main.cpp

hangman.o: hangman.cpp hangman.h
	g++ -c hangman.cpp

clean:
	rm -rf *.o hangman