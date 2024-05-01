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

using namespace std;

class Hangman{
   public:
      Hangman(); // defualt constructor
      void displayMan( int n ); // prints out the man dying - C
      void startGame(); // prints out user interface - A
      int menu(); // displays main menu and game options, restart, end, difficulty level - A
      void hints(); // will look through vector of characters available and the first one that it sees that is in the word will input into answer - K
      void printStats(); // will display statistics of the games played in 1 session

      //kevin, write all the setter and getters for the stats portion of this code
      void checkWord(string &guessedWord, char guess); // this will do the guess checking, edit the guessword string, and store any failed guesses in an array
      void fillBank( const string, const string ); // fills the map wordBank - C
      string chooseCat(); // will choose one of the categories - C
      string chooseWord( string c ); // this will choose a word from the word bank based on the category - C
      string getDifficulty() const { return difficulty; } // - C
      void setDifficulty( string d ); // Depending on difficulty entered - C
      int getAttempts() const { return attempts; } // - C
      string getWord() const { return word; } // - C
      void setWord( string w ){ word = w; } //- C
      
      /* What if we had files for each category that contained a bunch of words. We could do something similar to
         to what we did at Pelli where we read from a file, and wrote to that same file. So basically as long as they keep 
         playing we update the files so that the same word isnt used twice and when they choose to end the game, we reset
         the files. We can either go down the list or randomize it.
      */

      

   private:

      unordered_map < string, vector< string > > wordBank; //key is category, value is vector of words in that category
      vector< char > charAvailable; // holds letters that havent been used
      string word; // the word that is going to be guessed
      string category; // the general category that the word belongs to
      int attempts; // could possibly use this to keep track of how many times the user has guessed incorrectly
      int gamesWon; 
      int gamesLost;
      int points; // depends on how many attempts they had left
      int hintsUsed;
      int perfectGames; // games won without getting any wrong
      string difficulty; // used to keep track of the current difficulty of the game
   
};

#endif