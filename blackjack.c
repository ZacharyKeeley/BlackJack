// Zachary Keeley blackjack program. 24 July 2018
// Blackjack program with selectable AI
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// here we create a random number for our cards
int randomCardGenerator(int r){

    srand(time(NULL));
    r = rand() % (12) + 2; //change random numbers to include jack, queen, king
    if(r>10 && r <13){ // if we draw a jack, queen, or king
        r=10; //changes the value to 10
    }else if(r==13){ //if we draw an ace
        r=11; //changes to value to 11
    }
    return r;
}

//delay function
void delay (int milliseconds){

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

void checkBlackJack(int playerSum){
    /*if((playerSum>21) && (r1 || r2 ==11)){ // if the player busts but has an ace
        //printf("The player has %d. The player has busted.\n", playerSum);
        //exit(0);
        r1=1; // changes one of the aces to aces low
        playerSum-10; //subtracts 10 from the sum of the player's cards*/
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
        hitFunction(n, playerSum); // function calls itself if the player enters yes
    }else if(n == 'n'){// if the player selects no
        printf("The player has %d.\n", playerSum); //tells the player the value of his/her hand
    }
}

int dealerAI(int playerSum, int dealerSum){
    while(playerSum<dealerSum){
        if((dealerSum<=21) && (dealerSum>playerSum)){
            printf("The dealer wins.");
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
    int r, r2, r3, r4, d = 1000, playerSum, dealerSum, difficulty;
    char n, n2, n3;

    r = randomCardGenerator(r); // player's first card
    delay(d); //delays the random function so that we don't get the same number twice
    r2 = randomCardGenerator(r2);// player's second card
    delay(d); //delays again
    r4 = randomCardGenerator(r4); //dealer's first card
    playerSum = r+r2; //sums the player's card to make it easier to read

    //Intro and asking the user to select a difficulty
    printf("Welcome to Blackjack!\n");
  //  printf("Select a difficulty: (1 for easy, 2 for medium, 3 for difficult)\n");
  //  scanf("%d", &difficulty);

    // exception handling, only triggers if the user enters a number outside the requested range.
    /*while(difficulty > 3 || difficulty < 1){
        printf("Please enter a number between 1 and 3\n");
        scanf("%d", &difficulty);
    }*/
    // printf() create a card drawing
    printf("The dealer is dealt a(n): %d\n", r4);
    printf("You are dealt the following two cards: \n");

    if(r == 13 && r2 == 13){ //if the user draws 2 aces, changes one of them to aces low
        r = 1;
        playerSum = 12;
    }

    printf("%d and %d (%d)\n", r, r2, playerSum);

    printf("Hit? (y/n)\n");
    scanf(" %c", &n);
    // add exception handling later
    // start the game
    hitFunction(n, playerSum);
    /*if( n == 'y'){ //if the player decides to hit
        r3 = randomCardGenerator(r3); //generates a random card
        playerSum += r3; // adds the value of the new card to the sum of the other cards
        printf("%d\n", r3);  // tells the player the value of the drawn card

        checkBlackJack(playerSum); // blackjack function call
        scanf("%d", &n2);
        if (n2=='y'){  //if the players decides to hit again...
            r3 = randomCardGenerator(r3);
            playerSum += r3;
            printf("%d", r3);
            checkBlackJack(playerSum);
            //scanf();
        }*/

    r = randomCardGenerator(r);
    delay(d);
    dealerSum = r + r4;
    printf("The dealer has %d.\n", dealerSum);
    dealerAI(playerSum, dealerSum);
    /*switch(difficulty){
        case 3:
            difficultAI(r, r4, playerSum, dealerSum);

    }*/
    return 0;
}
