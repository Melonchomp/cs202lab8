/*
 Ahmed Ghazi, Chris Ramos, Kevin Canas
 Lab 8

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
      void displayMan( int n ); // prints out the man dying
      void startGame(); // prints out user interface
      void menu(); // displays main menu and game options, restart, end, difficulty level
      void hints(); // will look through vector of characters available and the first one that it sees that is in the word will input into answer
      void fillBank( const string, const string );
      string chooseCat();
      string chooseWord( string c ); // this will choose a word from the word bank based on the category
      string getDifficulty() const { return difficulty; }
      void setDifficulty( string d );
      int getAttempts() const { return attempts; }
      string getWord() const { return word; }
      void setWord( string w ){ word = w; }

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