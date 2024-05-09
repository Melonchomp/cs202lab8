#include "hangman.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set> 
#include <algorithm>
#include <cctype>
#include <iomanip>

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
   Ahmed, Kevin - implemented check word and hints function and helped with the logic and writing of the gameplay loop
   Chris - Implemented a boolean check to help with printing out the set of used characters. Helped with erros and logic of some code.
 Description: This is the main play function of our game. 
*/
void Hangman::startGame(){
   //intro message
   cout << "=======================\n" << "| Welcome to Hangman! |\n" << "=======================" << endl;

   string guess;
   bool gameOver;
   int numHints = 1, option;
   string difficulty, category, wordGuess, answer;
   //Menu call
   set< char > usedLetters;
   set< char >::iterator sit;

   login();

   while(option != 5){

      gameOver = false;
      option = menu();

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

                  cout << "You're out of attempts. The word was " << word << "." << endl;
                  do{
                     cout << "Start Over(Y/N): ";
                     cin >> answer;
                     transform( answer.begin(), answer.end(), answer.begin(), ::toupper );
                  }
                  while( answer != "Y" && answer != "N" );

                  if( answer == "Y" ){
                     setDifficulty(difficulty);
                     gamesLost = 0;
                     gamesWon = 0;
                     perfectGames = 0;
                     points = 0;
                     hintsUsed = 0;
                     numHints = 1;
                     usedLetters.clear();
                     wordGuess.clear();
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
                  }
                  else if( answer == "N" ){
                     gameOver = true;
                     numHints = 1;
                     usedLetters.clear();
                  }
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
                  player.gamesWon++;
                  player.points += attempts;
                  numHints = 1;
                  cout << "Solved " << wordGuess << "!" << endl;
                  do{
                     cout << "Next Puzzle(Y/N): ";
                     cin >> answer;
                     transform( answer.begin(), answer.end(), answer.begin(), ::toupper );
                  }
                  while( answer != "Y" && answer != "N" );
                  if( answer == "Y" ){
                     setDifficulty(difficulty);
                     usedLetters.clear();
                     wordGuess.clear();
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
                  }
                  else if( answer == "N" ){ break; }
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
            leaderboard.display();
            break;
         case 5: 
            cout << "\nThank You For Playing!" << endl << "Here are your session stats:\n\n";
            printStats();
            leaderboard.saveToFile( "leaderboard.txt" );
            return;
      }
      //clears the guess for the next round
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
      cout << "1 | Play Game \n2 | Session Stats \n3 | Game Tutorial \n4 | Leaderboard \n5 | Quit \nYour Pick: ";
      cin >> choice;
   }
   while( choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice.size() != 1 );

   return stoi(choice);
}

/*
 Members:
   Kevin, Chris - Implemnted the check for multiple occurences of a letter if it was given by hint, and added it to the used characters set
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
      player.hintsUsed++;
      return;
   } 
 

}

/*
 Member: Ahmed
 Description: Prints the stats of the current session
*/
void Hangman::printStats(){

   cout << "Number of games won: " << player.gamesWon << endl;
   cout << "Number of games lost: " << player.gamesLost << endl;
   cout << "Number of hints used: " << player.hintsUsed << endl;
   cout << "Total points(remaining attempts throughout the session): " << player.points << endl;
   
   return;
}

/*
 Member: Kevin
 Description: Checks the word to see if the letter they guessed is correct, makes sure the letter hasnt been guessed already
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

void Hangman::login(){

   string response, username;
   do{
      cout << "New user(Y/N): ";
      cin >> response;

      transform( response.begin(), response.end(), response.begin(), ::toupper );
   }
   while( response != "Y" && response != "N" );

   if( response == "Y" ){
      cout << "Please enter a username: ";
      cin >> username;
      bool usernameExists = false;
      for( size_t i = 0; i < leaderboard.players.size(); i++ ){
         if( leaderboard.players[i].username == username ){
            usernameExists = true;
            break;
         }
      }
      if( usernameExists ){
         cout << "Username already exists. Please choose a different username." << endl;
         login();
      }
      else{
         player.createPlayer( username );
         leaderboard.addPlayer( player );
      }
   }
   else{
      cout << "Please Login\nUsername: ";
      cin >> username;

      bool usernameFound = false;
      for( size_t i = 0; i < leaderboard.players.size(); i++ ){
         if( leaderboard.players[i].username == username ){
            usernameFound = true;
            player = leaderboard.players[i];
            break;
         }
      }
      if( !usernameFound ){
         cout << "Username not found. Please create a new user." << endl;
         login();
      }
      
   }
 


}

void Player::createPlayer( string name ){

   username = name;
   gamesLost = gamesWon = perfectGames = hintsUsed = points = 0;

}

void Leaderboard::addPlayer( const Player& player ){

   players.push_back( player );

}

void Leaderboard::display(){
   sort( players.begin(), players.end(), [](Player& a, Player& b){
      return a.points > b.points;
   });

   cout << "Leaderboard" << endl;
   for( size_t i = 0; i < players.size(); i++ ){
      cout << players[i].username << setw(10) << players[i].points << endl << endl;
   }
}

void Leaderboard::saveToFile( const string & filename ) const{

   ofstream outputFile( filename );

   if( outputFile.fail() ){
      cerr << "Error opening file!" << endl;
      return;
   }
    // Write header with aligned columns
    outputFile << left << setw(20) << "Username"
               << setw(10) << "Points"
               << setw(10) << "Games Won"
               << setw(15) << "Games Lost"
               << setw(15) << "Perfect Games"
               << setw(10) << "Hints Used" << std::endl;

    // Write each player's data to the file with aligned columns
    for ( size_t i = 0; i < players.size(); i++ ) {
        outputFile << left << setw(20) << players[i].username
                   << setw(10) << players[i].points
                   << setw(10) << players[i].gamesWon
                   << setw(15) << players[i].gamesLost
                   << setw(15) << players[i].perfectGames
                   << setw(10) << players[i].hintsUsed << endl;
    }

    outputFile.close();

}

void Leaderboard::readFromFile( const string& filename ) const{

   ifstream in(filename);

   if( in.fail() ){
      cerr << "Failed to open file!" << endl;
      return;
   }

   in.close();
}

istream& operator>> ( istream& in, Player& player ){

   in >> player.username >> player.points >> player.gamesWon >> player.gamesLost >> player.perfectGames >> player.hintsUsed;

}