// hangman.cpp
// Hangman game illustrates string library functions, 
// character arrays, arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype. we'll define this below.
int processGuess(char* word, const char* targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char* wordBank[] = {"computer", "president", "trojan", "program",
                          "coffee", "library", "football", "popcorn", 
                          "science", "engineer"};

const int numWords = 10;

int main()
{
  srand(time(0));
  char guess;
  bool wordGuessed = false;
  int numTurns = 10;
  int i;
  int guess_result = 0;

  // Pick a random word from the wordBank
  const char* targetWord = wordBank[rand() % numWords];

  // More initialization code as needed
  char word[80];  // a blank array to use to build up the answer
                  // It should be initialized with *'s and then
                  //  change them to the actual letters when the 
                  //  user guesses the letter


  for (i=0;i<strlen(targetWord);i++)
  {
	word[i] = '*';
  }
  word[i] = '\0';
  

  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  i = numTurns;
  while(i>0)
  {
	cout<<"Current word: "<<word<<endl;
	cout<<i<<" remain...Enter a letter to guess:";
	cin>>guess;
	if(processGuess(word,targetWord,guess))
	{
		if(strcmp(word,targetWord) == 0)
		{
			break;
		}
	}
	else
	{
		i--;
	}
  }
  // Priknt out end of game status
  if(i)
  {
	cout<<"The word was: "<<word<<". You win!"<<endl;
  }
  else
  {
	cout<<"Too many turns...You lose"<<endl;
  }

  return 0;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to 
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
int processGuess(char* word, const char* targetWord, char guess)
{
	int i = 0;
	int hitnum = 0;
	for(i=0;i<strlen(targetWord);i++)
	{
		if(targetWord[i] == guess and word[i] == '*')
		{	
			hitnum++;
			word[i] = guess;
		}
	}

	return hitnum; 
}


