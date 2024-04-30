#include "hangman.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

Hangman::Hangman(){
    //initializes all private variables to 0 or empty
    attempts = gamesWon  = gamesLost = points = hintsUsed = perfectGames = 0;
    word = category = "";
    difficulty = ' ';
}

/* Apart from setting the difficulty this function also sets the attempts and fills the word bank based on the difficulty chosen */
void Hangman::setDifficulty( string d ){
   difficulty = d;
   if( difficulty == "E" ){
      attempts = 7;
      fillBank( "animalsEasy.txt", "Animals" );
      fillBank( "foodAndDrinksEasy.txt", "Food & Drinks" );
      fillBank( "gamesEasy.txt", "Games" );

   }
   else if( difficulty == "M" ){
      attempts = 6;
      fillBank( "animalsMedium.txt", "Animals" );
      fillBank( "foodAndDrinksMedium.txt", "Food & Drinks" );
      fillBank( "gamesMedium.txt", "Games" );

   }
   else if(difficulty == "H"){
      attempts = 5;
      fillBank( "animalsHard.txt", "Animals" );
      fillBank( "foodAndDrinksHard.txt", "Food & Drinks" );
      fillBank( "gamesHard.txt", "Games" );
   }else{
      cout << "invalid input, retry\n";
   }
}

/* This function will open the file and insert each word in that file into the unordered map under the correct key */
void Hangman::fillBank( const string filename, const string category ){

   fstream in;
   string words;
   in.open( filename );

   if( in.fail() ){
      cerr << "Could not open file." << endl;
      exit(1);
   }

   while( getline( in, words ) ){
      wordBank[category].push_back(words);
   }

   in.close();

}

/* This function will randomly choose one of the 3 categories */
string Hangman::chooseCat(){
   vector<string> tmpCat { "Animals", "Food & Drinks", "Games" };
   int i;
   srand( time( NULL ) );

   i = rand() % tmpCat.size(); // just chooses a category from the tmp vector above

   return tmpCat[i];
}

/* Using the category chosen in chooseCat(), this function will randomly choose a word from that category and pop it from the vector so it isnt chosen again */
string Hangman::chooseWord( string c ){

   vector<string>& words = wordBank[c]; //temporary vector to help with returning the random word

   int i = rand() % words.size(); // this will randomly choose a number, we will use that to access the position of the random word

   string randomWord = words[i]; // storing it in a variable so we can remove it from the wordBank without losing the current word

   words.erase(words.begin()+i); // this will go to the position randomly chosen and erase the word

   return randomWord;
}

/*
 displayMan - Will print out the current art of the man given the number of attempts
   Parameters: the current number of attempts
   Returns: Nothing
*/
void Hangman::displayMan( int n ){

   if( difficulty == "E" ){
      vector<std::string> HANGMANPICS = {
         "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="
      };
      cout << HANGMANPICS[n] << endl;
   }
   else if( difficulty == "M" ){
      vector<std::string> HANGMANPICS = {
         "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="
      };
      cout << HANGMANPICS[n] << endl;

   }
   else{
      vector<std::string> HANGMANPICS = {
         "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="
      };
      cout << HANGMANPICS[n] << endl;
   }
}

void Hangman::startGame(){
   //intro message
   cout << "=======================\n" << "| Welcome to Hangman! |\n" << "=======================" << endl;

   int option = 0, wordSize;
   string difficulty, category, word, subWord1, subWord2;
   size_t foundSpace, sim = 100;
   //Menu call

   while(option != 4){
      option = menu();
      

      switch(option){
         case 1: 
            //first, the user has to choose a difficulty
            cout << "Choose Difficulty (E | M | H):\n";
            cin >> difficulty;
            setDifficulty(difficulty);

            //chooses word and category based on difficulty
            category = chooseCat();
            word = chooseWord(category);

            cout << word << endl;

            wordSize = word.size();
            cout << wordSize << " " << endl;

            foundSpace = word.find(' ');

            sim = foundSpace;

            cout << sim;

            //these two for loops and the cout that prints a space is what 
            for(int i = 0; i < sim; i++){ 
               cout << "_";
            }
            cout << " ";
            for(int i = sim+1; i < wordSize; i++){
               cout << "_";
            }
            cout << endl;

            break;
         case 2: 
            cout << "STATS\n";
            break;
         case 3: 
            cout << "TUTORIAL\n";
            break;
         case 4: 
            cout << "Thank You For Playing!" << endl << "Here are your session stats:\n";
            printStats();
            return;
      }
   }
}

//displays menu and gets the choice of the player
int Hangman::menu(){
   int choice;
   cout << "1 | Play Game \n2 | Session Stats \n3 | Game Tutorial \n4 | Quit \nYour Pick: ";
   cin >> choice;
   
   return choice; 
}

void Hangman::hints(){

}

void Hangman::printStats(){

}