/*
 Ahmed Ghazi, Chris Ramos, Kevin Canas
 CS202 Final Lab: Hangman in C++

*/



#ifndef HANGMAN_H
#define HANGMAN_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

class Hangman{
   public:
      Hangman(); // defualt constructor - A
      void displayMan( int n ); // prints out the man dying
      void startGame(); // prints out user interface - A, K, C
      int menu(); // displays main menu and game options, restart, end, difficulty level - A
      void hints(string &hiddenWord, int &numHints, set<char> &usedChars); // will look through array of characters available and the first one that it sees that is in the word will input into answer - K, C
      void printStats(); // will display statistics of the games played in 1 session - A
      void checkWord(string &guessedWord, char guess, set<char> &usedChars); // this will do the guess checking, edit the guessword string, and store any failed guesses in an array - K
      void fillBank( const string, const string ); // fills the map wordBank - C
      string chooseCat(); // will choose one of the categories - C
      string chooseWord( string c ); // this will choose a word from the word bank based on the category - C
      void setDifficulty( string d ); // Depending on difficulty entered will fill word bank with corresponding words and set the corresponding attempts - C

   private:

      unordered_map < string, vector< string > > wordBank; //key is category, value is vector of words in that category
      vector< char > charAvailable; // holds letters that havent been used
      string word; // the word that is going to be guessed
      string category; // the general category that the word belongs to
      int attempts; // could possibly use this to keep track of how many times the user has guessed incorrectly
      int gamesWon; 
      int gamesLost;
      int points; // depends on how many attempts they had left
      int hintsUsed; // the number of hints used in the session
      int perfectGames; // games won without getting any wrong
      string difficulty; // used to keep track of the current difficulty of the game
      bool hasUnusedLetters;
};

#endif