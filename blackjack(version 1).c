// Zachary Keeley blackjack program. 24 July 2018
// Blackjack program with functioning AI
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// here we create a random number for our cards
int randomCardGenerator(){
    int card;
    srand(time(NULL));

    card = rand() % (13) + 2; //generates a random number between 2 and 13
    if(card>10 && card <14){ // if we draw a jack, queen, or king
        card=10; //changes the value to 10
    }else if(card==14){ //if we draw an ace
        card=11; //changes to value to 11
    }

    return card;
}

//delay function
void delay (int milliseconds){

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

void checkBlackJack(int playerSum){

    if(playerSum>21){
        printf("The player has %d. The player has busted.\n", playerSum);
    }else if(playerSum==21){
        printf("Blackjack!");
    }else if(playerSum<21){
        int n;
        printf("The player has %d.\n", playerSum);
        printf("Hit? (y/n)\n");
    }
}

// recursive function that..
void hitFunction(char response, int playerSum){ //receives either yes or no from the player and the sum of the player's current hand
    if(response == 'y'){ // if the user selected to hit
        int card;
        card = randomCardGenerator(); // generates a random card
        playerSum+=card; //adds the value of the drawn card to the sum of the player's hand
        printf("The player has been dealt a(n): %d\n", card); //tells the player the value of the drawn card
        checkBlackJack(playerSum); // calls our blackjack function
        scanf(" %c", &response); // asks the player to enter yes or no
       /* while(n != 'y' || 'n'){
            printf("Please enter 'y' or 'n'\n");
            scanf(" %c", &n);
        }*/
        hitFunction(response, playerSum); // function calls itself if the player enters yes
    }else if(response == 'n'){// if the player selects no
        printf("The player has %d.\n", playerSum); //tells the player the value of his/her hand
    }
}

void dealerAI(int playerSum, int dealerSum){ // receives the value of the player's hand the value of the dealer's hand
    while(playerSum>dealerSum){
        delay(1000);
        int card = randomCardGenerator();
        dealerSum += card;
        printf("The dealer draws a %d. The dealer has %d\n", card, dealerSum);
        if(dealerSum>playerSum && dealerSum<=21){
            printf("The dealer wins.\n");
            break;
        }else if (dealerSum>21){
            printf("The dealer busts.\n");
            break;
        }else if(dealerSum==playerSum){
            printf("Tie.\n");
            break;
        }
    }
}

int main(void){ //use malloc to fix potential memory leak
    //variables
    int i, milliseconds = 900, playerSum, dealerSum, card[4]={0};
    char response;
    printf("Welcome to Blackjack!\n"); //intro
    //create a card drawing
    while(1==1){ //this starts the game loop

        //resetting the hands back to 0
        dealerSum=0;
        playerSum=0;

        for (i=0;i<3;i++){ //creates the 3 initial cards. Index 0 and 1 are for the player; index 2 is for the dealer
            card[i]=randomCardGenerator();
            delay(milliseconds);
        }

        playerSum = card[0]+card[1]; //sums the player's cards to make it easier to read

        printf("The dealer is dealt a(n): %d\n", card[2]);
        printf("You are dealt the following two cards: \n");

        if(card[0] == 11 && card[1] == 11){ //if the user draws 2 aces, changes one of them to aces low
            card[0] = 1;
            playerSum = 12;
        }

        printf("%d and %d (%d)\n", card[0], card[1], playerSum);

        printf("Hit? (y/n)\n");
        scanf(" %c", &response);
        // add exception handling later

        hitFunction(response, playerSum); //hitFunction is our game engine

        delay(milliseconds);
        card[3]=randomCardGenerator(); //generates the dealers forth card
        dealerSum = card[2] + card[3];
        printf("The dealer has %d.\n", dealerSum);
        dealerAI(playerSum, dealerSum); //function call to basic dealer AI
        }
        return 0;
}
