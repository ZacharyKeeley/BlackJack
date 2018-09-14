// Zachary Keeley blackjack program. 24 July 2018
// Blackjack program with selectable AI
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// here we create a random number for our cards
int randomCardGenerator(){
    int cardValue;
    srand(time(NULL));
    cardValue = rand() % (12) + 2; //generates a random number between 2 and 13
    if(cardValue>10 && cardValue <13){ // if we draw a jack, queen, or king
        cardValue=10; //changes the value to 10
    }else if(cardValue==13){ //if we draw an ace
        cardValue=11; //changes to value to 11
    }
    return cardValue;
}

//delay function
void delay (int milliseconds){

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

void checkBlackJack(int playerSum){

    if(playerSum>21){
        printf("The player has %d. The player has busted.\n", playerSum);
        exit(0);
    }else if(playerSum==21){
        printf("Blackjack!");
        exit(0);
    }else if(playerSum<21){
        int n;
        printf("The player has %d.\n", playerSum);
        printf("Hit? (y/n)\n");
    }
}

// recursive function that..
void hitFunction(char n, int playerSum){ //receives either yes or no from the player and the sum of the player's current hand
    if(n == 'y'){ // if the user selected to hit
        int r;
        r = randomCardGenerator(r); // generates a random card
        playerSum+=r; //adds the value of the drawn card to the sum of the player's hand
        printf("The player has been dealt a(n): %d\n", r); //tells the player the value of the drawn card
        checkBlackJack(playerSum); // calls our blackjack function
        scanf(" %c", &n); // asks the player to enter yes or no
       /* while(n != 'y' || 'n'){
            printf("Please enter 'y' or 'n'\n");
            scanf(" %c", &n);
        }*/
        hitFunction(n, playerSum); // function calls itself if the player enters yes
    }else if(n == 'n'){// if the player selects no
        printf("The player has %d.\n", playerSum); //tells the player the value of his/her hand
    }
}

void dealerAI(int playerSum, int dealerSum){ // receives the value of the player's hand the value of the dealer's hand
    while(playerSum>dealerSum){
        if(dealerSum>playerSum && dealerSum<=21){
            printf("The dealer wins.");
            break;
        }else if (dealerSum>21){
            printf("The dealer busts.");
            break;
        }
        delay(1000);
        int r =randomCardGenerator(r);
        dealerSum+=r;
        printf("The dealer draws a %d. The dealer has %d\n", r, dealerSum);
    }
}
int mediumAI(){ //dealer will randomly hit

}
int difficultAI(int r1, int r2, int playerSum, int dealerSum){
/*    while (playerSum>dealerSum){
        delay(1000);
        int r3 = randomCardGenerator(r3);
        dealerSum+=r3;
        printf("The dealers is dealt a(n) %d.\n", r3);
        printf("The dealer has %d.\n", dealerSum);
    }
    if(((dealerSum - playerSum)>0) && (dealerSum <=21)){
        printf("The dealer wins.\n");
    }else if(dealerSum>21){
        printf("The dealer busts.\n");*/

}

int main(void){
    //variables
    // r = first card, r2 = second card, etc...
    int i, r, r2, r3, r4, d = 950, playerSum, dealerSum, difficulty, cardArray[10]={0};
    char n, n2, n3;
    for (i=0;i<4;i++){ //creates the 4 initial cards. index 1 and 2 are for the player; 3,4 for the dealer
        cardArray[i]=randomCardGenerator(i);
        delay(d);
    }
    r = randomCardGenerator(r); // player's first card
    delay(d); //delays the random function so that we don't get the same number twice
    r2 = randomCardGenerator(r2);// player's second card
    delay(d); //delays again
    r4 = randomCardGenerator(r4); //dealer's first card
    playerSum = r+r2; //sums the player's card to make it easier to read

    //Intro
    printf("Welcome to Blackjack!\n");
    // printf() create a card drawing
    printf("The dealer is dealt a(n): %d\n", r4);
    printf("You are dealt the following two cards: \n");

    if(cardArray[0] == 11 && cardArray[1] == 11){ //if the user draws 2 aces, changes one of them to aces low
        r = 1;
        playerSum = 12;
    }

    printf("%d and %d (%d)\n", r, r2, playerSum);

    printf("Hit? (y/n)\n");
    scanf(" %c", &n);
    // add exception handling later
    // start the game
    hitFunction(n, playerSum); //hitFunction is our game engine

    r = randomCardGenerator(r);
    delay(d);
    dealerSum = r + r4;
    printf("The dealer has %d.\n", dealerSum);
    dealerAI(playerSum, dealerSum); //function call to basic dealer AI
    return 0;
}
