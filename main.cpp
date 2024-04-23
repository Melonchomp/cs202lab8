#include <iostream>
#include <cctype>
#include <algorithm>
#include "hangman.h"

using namespace std;

int main(){

   Hangman t;
   int currAttempt = 0;
   string userDifficulty, guess, cat;
   char letter;
   bool wordGuessed = false;

   while( userDifficulty != "E" && userDifficulty != "M" && userDifficulty != "H" ){
      cout << "Choose a difficulty: ";
      cin >> userDifficulty;
      transform( userDifficulty.begin(), userDifficulty.end(), userDifficulty.begin(), ::toupper );
   }

   t.setDifficulty( userDifficulty );
   cat = t.chooseCat();
   t.setWord( t.chooseWord( cat ) );
   guess.resize( t.getWord().size(), '_' );

   cout << cat << ": " << t.getWord() << endl;

   t.displayMan( currAttempt );

   while( currAttempt < t.getAttempts() ){

         cout << "Guess a letter: ";
         cin >> letter;
         letter = toupper( letter );
         
         size_t index = t.getWord().find( letter );

         cout << "Letter found at index: " << index << endl;
         if( index == string::npos ){
            currAttempt++;
            t.displayMan( currAttempt );
         }
         else{
            guess[index] == letter;
         }
         cout << guess << endl;
         if( guess == t.getWord() ){
            cout << "Congrats you guessed the word" << endl;
            wordGuessed = true;
            break;
         }
         if( wordGuessed ) break;
   }
   
   return 0;
}