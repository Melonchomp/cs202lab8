#include "hangman.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set> 
#include <algorithm>
#include <cctype>

using namespace std;

/*
 Member: Ahmed
 Description: Default constructor of the Hangman class
*/
Hangman::Hangman(){
    //initializes all private variables to 0 or empty
    attempts = gamesWon  = gamesLost = points = hintsUsed = perfectGames = 0;
    word = category = "";
    difficulty = ' ';
    hasUnusedLetters = false;
}

/* 
 Member: Chris
 Description: Apart from setting the difficulty this function also sets the attempts and fills the word bank based on the difficulty chosen
*/
void Hangman::setDifficulty( string d ){

   transform( d.begin(), d.end(), d.begin(), ::toupper ); // we first convert the difficulty to upper case so no matter what case entered it will work

   difficulty = d;
   if( difficulty == "E" ){
      attempts = 6;
      fillBank( "animalsEasy.txt", "Animals" );
      fillBank( "foodAndDrinksEasy.txt", "Food & Drinks" );
      fillBank( "gamesEasy.txt", "Games" );

   }
   else if( difficulty == "M" ){
      attempts = 5;
      fillBank( "animalsMedium.txt", "Animals" );
      fillBank( "foodAndDrinksMedium.txt", "Food & Drinks" );
      fillBank( "gamesMedium.txt", "Games" );

   }
   else if(difficulty == "H"){
      attempts = 4;
      fillBank( "animalsHard.txt", "Animals" );
      fillBank( "foodAndDrinksHard.txt", "Food & Drinks" );
      fillBank( "gamesHard.txt", "Games" );
   }else{
      cout << "invalid input, retry\n";
   }
}

/* 
 Member: Chris
 Description: This function will open the file and insert each word in that file into the unordered map under the correct key
*/
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

/* 
 Member: Chris
 Description: This function will randomly choose one of the 3 categories and return which category was chosen
*/
string Hangman::chooseCat(){
   vector<string> tmpCat { "Animals", "Food & Drinks", "Games" };
   int i;
   srand( time( NULL ) );

   i = rand() % tmpCat.size(); // just chooses a category from the tmp vector above

   return tmpCat[i];
}

/* 
 Member: Chris
 Description: Using the category chosen in chooseCat(), this function will randomly choose a word from that category and pop it from the vector so it isnt
              chosen again. It will then return the word chosen to be used later in the game
*/
string Hangman::chooseWord( string c ){

   vector<string>& words = wordBank[c]; //temporary vector to help with returning the random word

   int i = rand() % words.size(); // this will randomly choose a number, we will use that to access the position of the random word

   string randomWord = words[i]; // storing it in a variable so we can remove it from the wordBank without losing the current word

   words.erase(words.begin()+i); // this will go to the position randomly chosen and erase the word

   return randomWord;
}

/*
 Member: Chris
 displayMan - Will print out the current art of the man given the number of attempts
   Parameters: the current number of attempts
   Returns: Nothing
*/
void Hangman::displayMan( int n ){

   if( difficulty == "E" ){
      vector<std::string> HANGMANPICS = {
         "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
         "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",

      };
      cout << HANGMANPICS[n] << endl;
   }
   else if( difficulty == "M" ){
      vector<std::string> HANGMANPICS = {
         "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
          "  +---+\n  |   |\n      |\n      |\n      |\n      |\n========="
      };
      cout << HANGMANPICS[n] << endl;

   }
   else{
      vector<std::string> HANGMANPICS = {
         "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
         "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
         "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
      };
      cout << HANGMANPICS[n] << endl;
   }
}

/*
 Members:
   Ahmed - 
   Kevin - 
   Chris - Implemented a boolean check to help with printing out the set of used characters. Helped with erros and logic of some code.
 Description: This is the main play function of our game. 
*/
void Hangman::startGame(){
   //intro message
   cout << "=======================\n" << "| Welcome to Hangman! |\n" << "=======================" << endl;

   string guess;
   bool gameOver;
   int numHints = 1, option;
   string difficulty, category, wordGuess;
   //Menu call

   while(option != 4){

      gameOver = false;
      option = menu();
      set< char > usedLetters;
      set< char >::iterator sit;

      switch(option){
         case 1: 
            //first, the user has to choose a difficulty
            cout << "Choose Difficulty (E | M | H): ";
            cin >> difficulty;
            setDifficulty(difficulty);

            //chooses word and category based on difficulty
            category = chooseCat();
            
            word = chooseWord(category);

            //this for loop makes the string that holds the guesses the same size as the actually word string, including spaces
            for(int i = 0; i < word.size(); i++){
               if(word[i] != ' '){
                  wordGuess.push_back('_');
               }else{
                  wordGuess.push_back(' ');
               }
            }


            while(gameOver == false){
               //ends game if too many wrong attempts have been made

               //prints out the category of the word
               cout << "Category: " << category << endl;

               //outputs the current guess string 
               cout << wordGuess << endl << endl;

               //displays the man every time the user guesses the letter, regardless of the guess being right or wrong
               if(gameOver != true){

                  if( hasUnusedLetters ){
                     cout << "Used Letters: ";
                     for( sit = usedLetters.begin(); sit != usedLetters.end(); sit++ ){
                        if( word.find( *sit ) == string::npos ){
                           cout << *sit;
                           if( next(sit) != usedLetters.end() ){
                           cout << ", ";
                           } 
                        }
                     }
                     cout << endl;
                  }
                  
                  displayMan(attempts);
               }
               if(attempts == 0){
                  gamesLost++;

                  cout << "You're out of attempts. The word was " << word << ". Better luck next time!" << endl;
                  gameOver = true;
                  numHints = 1;
                  break;
               } 

               //user input to get the guess
               if(numHints == 1){
                  cout << "(type 'hint' for a hint)" << endl << "Guess a letter: ";
               }
               else{
                  cout << "Guess a letter: ";
               }
               cin >> guess;

               //makes the guess and uppercase word
               transform( guess.begin(), guess.end(), guess.begin(), ::toupper ); // words to guess are in all caps

               if(guess == "HINT"){
                  hints(wordGuess, numHints, usedLetters);
                  continue;

               }

               //error checking for multiple letters input
               if (guess.size()!= 1){
                  cout << "Too many characters!" << endl;
                  continue; 
               }
               
               //checks if guess[0] is a letter
               if (!isalpha(guess[0])){
                  cout << "Invalid Input!" << endl;
                  continue;
               }


               //function call to checkWord to see if the guess was correct
               checkWord(wordGuess, guess[0], usedLetters);
               //this checks for if the player has won the hangman game
               if(wordGuess == word){
                  gamesWon++;
                  points += attempts;
                  cout << "\nCongratulations, you guessed the word " << word << " with " << attempts << " remaining. Give yourself a pat on the back!\n\n";
                  gameOver == true;
                  numHints = 1;
                  break;
               }
            }

            break;
         case 2: 
            //this case prints the current session stats
            cout << endl;
            printStats();
            cout << endl;
            break;
         case 3: 
            cout << "\nThe object of hangman is to guess the secret word before the stick figure is hung. "
            " Players take turns selecting letters to narrow the word down. Players can take turns or work together. "
            " Gameplay continues until the players guess the word or they run out of guesses and the stick figure is hung.\n\n"; 
            break;
         case 4: 
            cout << "\nThank You For Playing!" << endl << "Here are your session stats:\n\n";
            printStats();
            return;
      }

      wordGuess.clear();
   }
}

/*
 Members: Ahmed
 Description: displays menu and gets the choice of the player
*/
int Hangman::menu(){
   string choice;
   
   do{
      cout << "1 | Play Game \n2 | Session Stats \n3 | Game Tutorial \n4 | Quit \nYour Pick: ";
      cin >> choice;
   }
   while( choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice.size() != 1 );

   return stoi(choice);
}

/*
 Members:
   Kevin - 
   Chris - Implemnted the check for multiple occurences of a letter if it was given by hint, and added it to the used characters set
 Description: If the user asks for a hint, this function will find the first '_' and replace it with the letter and also take away an attempt from the user.
*/
void Hangman::hints(string &hiddenWord, int &numHints, set<char> &usedChars){

   if(numHints == 0){
      cout << "No hints left!" << endl;
      return;
   }
   size_t position = hiddenWord.find('_');
   

   if (position != string::npos) {
      hiddenWord[position] = word[position];
      for( int i = position + 1; i < int(word.size()); i++ ){
         if( word[i] == word[position] ){
            hiddenWord[i] = word[position];
         }
      }
      usedChars.insert(word[position]);
      attempts--;
      numHints--;
      hintsUsed++;
      return;
   } 
 

}

/*
 Member: Ahmed
 Description: 
*/
void Hangman::printStats(){

   cout << "Number of games won: " << gamesWon << endl;
   cout << "Number of games lost: " << gamesLost << endl;
   cout << "Number of hints used: " << hintsUsed << endl;
   cout << "Total points(remaining attempts throughout the session): " << points << endl;
   
   return;
}

/*
 Member: Kevin
 Description: 
*/
void Hangman::checkWord(string &guessedWord, char guess, set<char> &usedChars){

   bool letterInserted = false;

   if(usedChars.find(guess)== usedChars.end()){ //this stores the users guess if it hasn't been guessed before
      usedChars.insert(guess);
   }
   else {
      cout << "You have already guessed " << guess << "!" << endl; // error check for already guessed letters
      return;

   }
   for(int i = 0; i < word.size(); i++ ){ //reveals the guessed letter if it is in the word and decreases their attempts if it isnt
      if(word[i] == guess){
         guessedWord[i] = word[i];
         letterInserted = true; 
      }
   }
   if (letterInserted == false){
      hasUnusedLetters = true;
      attempts--;
   }

   return; 
}