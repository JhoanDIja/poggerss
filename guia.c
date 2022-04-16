//  Andrew Geltz
//  COP3223
//  Assignment 5

//  This program generates two poker hands and tells which one wins.
//  I took a structural approach because it made things much cleaner
//  and more logical to access.

//  Include standard libraries and time for random
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//  Cards are made of simply a suit and a value
struct Card{
    int face;
    int suit;
};

//  Each hand is just a set of five cards
struct Hand{
    struct Card cards[5];
};

//  The deck is only going to hold the cards we have already generated.
//  It also has to know how many cards have been dealt so we don't
//  have to iterate through a bunch of blank card objects.
struct Deck{
    struct Card dealtCards[52];
    int numCardsDealt;
};

//  I am making these variables global so that we don't have to deal with
//  managing pointers to local objects.
struct Hand hand1, hand2;
struct Deck deck;

//  These array will hold all of the strings to make printing simple.
static const char *faceStrings[] = {
    "Two","Three","Four","Five","Six","Seven","Eight","Nine",
    "Ten","Jack","Queen","King","Ace"};
static const char *suitStrings[] = {
    "Hearts","Clubs","Diamonds","Spades"};
static const char *rankStrings[] = {
    "High Card","Single Pair","Two Pair","Three of a Kind","Straight",
    "Flush","Full House","Four of a Kind","Straight Flush"};

//  We need functions for generating hands, printing hands and determining
//  which hand won.
void generateHands();
struct Card dealCard();// Look at the generateHands() for more on this
void printHands();
void analyzeHands();

int main(){
    main:
	//  First thing, we need to initialize our deck
    deck.numCardsDealt=0;

    //  Seed our random generator
    srand(time(NULL));

    //  Then generate cards
    generateHands();

    //  Print them
    printHands();

    //  And find the winner
   analyzeHands();
	int choice;
    //  Let the program know were done and no problems
    scanf("\n%d",&choice);
    if(choice == 1){
    	system("cls");
    	goto main;
	}
	else system("exit");
    return 0;
}

void generateHands(){
    int i;// Counter variable

    //  We are going to do both hands in one loop to make the code simpler.
    //  This would be like the dealer alternating giving cards to one
    //  player or the other.
    for(i=0; i<5; i++){
        hand1.cards[i] = dealCard();
        hand2.cards[i] = dealCard();
    }
}

struct Card dealCard(){
    int i;// Counter variable
    int isUnique;// This variable keeps track if there are other matching cards
    struct Card cardToDeal;// Card we will return
    while(1){// Infinite loop, we will brake out when we get the card
        cardToDeal.face = rand()%13;
        cardToDeal.suit = rand()%4;
        isUnique = 1;
        // We only need to check from 0 to the last card we dealt
        for(i=0; i<deck.numCardsDealt; i++){
            if(deck.dealtCards[i].face == cardToDeal.face && deck.dealtCards[i].suit == cardToDeal.suit)
                isUnique = 0;
        }
        // If cardToDeal hasn't been dealt
        if(isUnique){
            deck.numCardsDealt++;
            deck.dealtCards[deck.numCardsDealt] = cardToDeal;
            return cardToDeal;
        }
    }
}

//  The print statement are a little weird here so I will try and explain.
//  The string arrays I declared around line 40 correspond to the indexes
//  of the cards face or suit value. We are essentially getting the string that
//  is at the index of our face or suit.
void printHands(){
    int i;// Counter variable
    printf("Player one has:\n");
    for(i=0; i<5; i++)
        printf("%s of %s\n", faceStrings[hand1.cards[i].face], suitStrings[hand1.cards[i].suit]);
    printf("\nPlayer two has:\n");
    for(i=0; i<5; i++)
        printf("%s of %s\n", faceStrings[hand2.cards[i].face], suitStrings[hand2.cards[i].suit]);
}

void analyzeHands(){
    int i,j;// Counter variable
    // I am going to try and use a system similar to the one in the document
    // We need counts of each face and suit so lets make those first
    int hand1FaceCounts[13];
    int hand1SuitCounts[4];
    int hand2FaceCounts[13];
    int hand2SuitCounts[4];

    // We have to initialize these array to zero. You can iterate but
    // I am going to use the memset function. If you don't know what that
    // means, just iterate through them.
    memset(hand1FaceCounts,0,sizeof(hand1FaceCounts));
    memset(hand1SuitCounts,0,sizeof(hand1SuitCounts));
    memset(hand2FaceCounts,0,sizeof(hand2FaceCounts));
    memset(hand2SuitCounts,0,sizeof(hand2SuitCounts));

    // Now lets go ahead an get those numbers
    for(i=0; i<5; i++){
        hand1FaceCounts[hand1.cards[i].face]++;
        hand1SuitCounts[hand1.cards[i].suit]++;
        hand2FaceCounts[hand2.cards[i].face]++;
        hand2SuitCounts[hand2.cards[i].suit]++;
    }

    // Now we need a bunch of variables to keep track of what each hand has.
    // I am going to abbreviate hand1 into h1 and so on.
    int h1Rank=0, h1Consec=0, h1Straight=0, h1Flush=0, h1Four=0, h1Three=0, h1Pairs=0;
    int h2Rank=0, h2Consec=0, h2Straight=0, h2Flush=0, h2Four=0, h2Three=0, h2Pairs=0;

    // The following chunk of code was taken from the assignment sheet.
    // I adapted it to check both hands.
    // check for flush – 5 cards of the same suit
	for(i=0; i<5; i++){
        if(hand1SuitCounts[i]==5)
            h1Flush=1;
        if(hand2SuitCounts[i]==5)
            h2Flush=1;
	}

	// check for straight – eg. One each of 5,6,7,8,9
	//    locate the first card
	i = 0;
	while (hand1FaceCounts[i] == 0)
		i++;
	//     count the consecutive non-zero faces
	for (; i < 3 && hand1FaceCounts[i]; i++)
		h1Consec++;
	if (h1Consec == 5)
		h1Straight = 1;

    // check for straight – eg. One each of 5,6,7,8,9
	//    locate the first card
	i = 0;
	while (hand2FaceCounts[i] == 0)
		i++;
	//     count the consecutive non-zero faces
	for (; i < 3 && hand2FaceCounts[i]; i++)
		h2Consec++;
	if (h2Consec == 5)
		h2Straight = 1;

	/* check for 4-of-a-kind, 3-of-a-kind, and pairs */
	for (i = 0; i < 14; i++) {
		if (hand1FaceCounts[i] == 4)
			h1Four = 1;
		if (hand1FaceCounts[i] == 3)
			h1Three = 1;
		if (hand1FaceCounts[i] == 2)
			h1Pairs++;
	}
	for (i = 0; i < 14; i++) {
		if (hand2FaceCounts[i] == 4)
			h2Four = 1;
		if (hand2FaceCounts[i] == 3)
			h2Three = 1;
		if (hand2FaceCounts[i] == 2)
			h2Pairs++;
	}

	// Hand 1 ranking
	if (h1Straight && h1Flush)
		h1Rank=8;
	else if (h1Four)
		h1Rank=7;
	else if (h1Three && h1Pairs == 1)
		h1Rank=6;
	else if (h1Flush)
		h1Rank=5;
	else if (h1Straight)
		h1Rank=4;
	else if (h1Three)
		h1Rank=3;
	else if (h1Pairs == 2)
		h1Rank=2;
	else if (h1Pairs == 1)
		h1Rank=1;
	else
		h1Rank=0;

    // Hand 2 ranking
    if (h2Straight && h2Flush)
		h2Rank=8;
	else if (h2Four)
		h2Rank=7;
	else if (h2Three && h2Pairs == 1)
		h2Rank=6;
	else if (h2Flush)
		h2Rank=5;
	else if (h2Straight)
		h2Rank=4;
	else if (h2Three)
		h2Rank=3;
	else if (h2Pairs == 2)
		h2Rank=2;
	else if (h2Pairs == 1)
		h2Rank=1;
	else
		h2Rank=0;

    // Print what each player has
    printf("\nPlayer one has a %s.\n",rankStrings[h1Rank]);
    printf("Player two has a %s.\n",rankStrings[h2Rank]);

    // Determine winner
    // This is where you would expand if you wanted to handle tie breaking
    if(h1Rank>h2Rank)
        printf("That means that player one wins!!!\n");
    else if(h2Rank>h1Rank)
        printf("That means that player two wins!!!\n");
    else
        printf("That means that the two players tie!!!\n");
}
