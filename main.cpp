#include <iostream>
#include <cctype>
#include <algorithm>
#include "hangman.h"

using namespace std;

int main(){

   Hangman t;
   int currAttempt = 0;
   string userDifficulty, guess, cat;

   while( userDifficulty != "E" && userDifficulty != "M" && userDifficulty != "H" ){
      cout << "Choose a difficulty: ";
      cin >> userDifficulty;
      transform( userDifficulty.begin(), userDifficulty.end(), userDifficulty.begin(), ::toupper );
   }

   t.setDifficulty( userDifficulty );
   cat = t.chooseCat();
   t.setWord( t.chooseWord( cat ) );

   cout << cat << endl;
   cout << t.getWord() << endl;

   // while( currAttempt < t.getAttempts() ){
      
   //    t.displayMan( currAttempt );
   //    currAttempt++;

   // }
   
   return 0;
}