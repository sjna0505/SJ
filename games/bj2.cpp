/*******************************************************************************
* CS 103 Twenty-One (Blackjack) PA
* Name: Songjun Na
* USC email: songjunn@usc.edu
* Comments (you want us to know):
*
*
******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
* Global arrays to be used as look-up tables, if desired.
* It is up to you if and how you want to use these 
*/
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
 {"2","3","4","5","6","7",
  "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
* Should permute the deck of cards, effectively shuffling it.
* You must use the Fisher-Yates / Durstenfeld shuffle algorithm
*  described in the assignment writeup.
*/
void shuffle(int cards[])
{
 /******** You complete ****************/

   int i ;
	int j ;
	int temp;
	for(i = NUM_CARDS - 1; i >= 1; i--)
	{
		j = rand() % (i+1);
		temp = cards[i];
		cards[i] = cards[j];
		cards[j] = temp;
	}  


}

/**
* Prints the card in a "pretty" format:   "type-suit"
*  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
*  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
*  Valid Suits are: H, D, C, S
*/
void printCard(int id)
{
 /******** You complete ****************/
   int suits = id/13;
   id = id % 13;
   cout << type[id] << "-" << suit[suits];


}

/**
* Returns the numeric value of the card.
*  Should return 11 for an ACE and can then
*  be adjusted externally based on the sum of the score.
*/
int cardValue(int id)
{
 /******** You complete ****************/
   id %= 13;
   return value[id];




}

/**
* Should print out each card in the hand separated by a space and
* then print a newline at the end.  
* Should use printCard() to print out each card.
*/
void printHand(int hand[], int numCards)
{
 /******** You complete ****************/

   for(int i = 0; i < numCards; i++){
       printCard(hand[i]);
       cout << " ";
   }

   cout << endl;


}

/**
* Should return the total score of the provided hand.  
* ACES should be treated as 11s to make the highest possible hand
*  and only being reduced to 1s as needed to avoid busting.
*/
int getBestScore(int hand[], int numCards)
{
 /******** You complete ****************/
   int sum = 0;
   bool isAce = false;
   int aceCounter = 0;

   for(int i = 0; i < numCards; i++){
       if(hand[i] % 13 == 12){
           isAce = true;
           aceCounter++;
       }
       sum += cardValue(hand[i]);
   }

   if(sum > 21 && isAce == true)
       sum = sum - aceCounter*10;

   return sum;




}

/**
* Main program logic for the game of 21
*/
int main(int argc, char* argv[])
{
 //---------------------------------------
 // Do not change this code -- Begin
 //---------------------------------------
 if(argc < 2){
   cout << "Error - Please provide the seed value." << endl;
   return 1;
 }
 int seed = atoi(argv[1]);
 srand(seed);

 int cards[52];
 int dhand[9];
 int phand[9];
 //---------------------------------------
 // Do not change this code -- End
 //---------------------------------------

 /******** You complete ****************/
   int pCounter = 0;
   int dCounter = 0;
   int cardCounter = 0;
   char input;
   char playing;
   bool isPWin = false;
   bool isDWin = false;
   bool isTie = false;
   bool keepPlaying = true;



   while(keepPlaying == true) {

       for(int i = 0; i < 52; i++){
       cards[i] = i;
       }

       shuffle(cards);

       phand[0] = cards[0];
       dhand[0] = cards[1];
       phand[1] = cards[2];
       dhand[1] = cards[3];
       pCounter = 2;
       dCounter = 2;
       cardCounter = 4;

       cout << "Dealer: " << "? ";
       printCard(dhand[1]);
       cout << endl << "Player: ";
       printHand(phand, pCounter);

       if(getBestScore(phand, pCounter) == 21){
           isPWin = true;
           input = 's';
       }
       else{

           cout << "Type 'h' to hit and 's' to stay:" << endl;
           cin >> input;
       }

       while(input == 'h' || input == 's'){


           if(input == 'h'){
               phand[pCounter] = cards[cardCounter];
               cardCounter++;
               pCounter++;
               cout << "Player: ";
               printHand(phand, pCounter);

               if(getBestScore(phand, pCounter) > 21){
                   cout << "Player busts" << endl;
                   isDWin = true;
                   break;
               }

               else if(getBestScore(phand, pCounter) == 21){
                   isPWin = true;
                   break;
               }

       }

       else if(input == 's'){

           while(getBestScore(dhand, dCounter) < 17){
               dhand[dCounter] = cards[cardCounter];
               dCounter++;
               cardCounter++;
           }

           cout << "Dealer: ";
           printHand(dhand, dCounter);


           if(getBestScore(dhand, dCounter) > 21){
               cout << "Dealer busts" << endl;
               isPWin = true;
               break;
           }

           else if(getBestScore(phand, pCounter) > getBestScore(dhand, dCounter)){
               isPWin = true;
               break;
           }
           else if(getBestScore(dhand, dCounter) > getBestScore(phand, pCounter)){
               isDWin = true;
               break;
           }
           else if(getBestScore(dhand, dCounter) == getBestScore(phand, pCounter)){
               isTie = true;
               break;
           }

       }


       cout << "Type 'h' to hit and 's' to stay:" << endl;
       cin >> input;

   }

   if(isDWin == true){
       cout << "Lose " << getBestScore(phand, pCounter) << " to " <<  getBestScore(dhand, dCounter)  << endl;
       isDWin = false;
   }
   else if(isPWin == true){
       cout << "Win " << getBestScore(phand, pCounter) << " to " << getBestScore(dhand, dCounter) << endl;
       isPWin = false;
   }
   else if(isTie == true){
       cout << "Tie " << getBestScore(phand, pCounter) << " to " << getBestScore(dhand, dCounter) << endl;
       isTie = false;
   }
   else
       break;

   cout << endl << endl << "Play again? [y/n]" << endl;
   cin >> playing;

   if(playing != 'y')
       break;
   }

 return 0;
}
