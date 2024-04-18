#include "hangman.h"
#include <iostream>

Hangman::Hangman(){
    //initializes all private variables to 0 or empty
    attempts = gamesWon  = gamesLost = points = hintsUsed = perfectGames = 0;
    word = category = "";
}

void Hangman::displayMan(){

   vector<std::string> HANGMANPICS = {
      "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
      "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
      "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
      "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
      "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
      "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
      "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="
   };

   cout << HANGMANPICS[0] << endl;
   cout << HANGMANPICS[1] << endl;
   cout << HANGMANPICS[2] << endl;
   cout << HANGMANPICS[3] << endl;
   cout << HANGMANPICS[4] << endl;
   cout << HANGMANPICS[5] << endl;
   cout << HANGMANPICS[6] << endl;
}

void Hangman::startGame(){

}

void Hangman::menu(){

}

void Hangman::hints(){

}

string Hangman::chooseWord( char difficiulty){

   return "";

}