#ifndef HANGMAN_H
#define HANGMAN_H

#include <iostream>
#include <string>


//This will be the header file for our hangman game
// yes

class Hangman{
    public:

      // I think we'll need a multi map
      /* What if we had files for each category that contained a bunch of words. We could do something similar to
         to what we did at Pelli where we read from a file, and wrote to that same file. So basically as long as they keep 
         playing we update the files so that the same word isnt used twice and when they choose to end the game, we reset
         the files. We can either go down the list or randomize it.
      */

    private:

      std::string word; // the word that is going to be guessed
      std::string category; // the general category that the word belongs to
      int attempts; // could possibly use this to keep track of how many times the user has guessed incorrectly

};

#endif