// Zachary Keeley blackjack program. 24 July 2018
// Blackjack program with functioning AI
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// here we create a random number for our cards
int randomCardGenerator()
{
    int value;
    srand(time(NULL));
    value = rand() % (13) + 2; //generates a random number between 2 and 13

    if (value > 10 && value < 14) // if we draw a jack, queen, or king
    {
        value=10; //changes the value to 10
    }
    else if ( value == 14) //if we draw an ace
    {
        value=11; //changes the value to 11
    }
    return value;
}

//delay function
void delay (int milliseconds)
{

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

void checkBlackJack(int playerSum, int *skipDealer)
{

    if (playerSum > 21)
    {
        printf("The player has %d. The player has busted.\n", playerSum);
        *skipDealer = 1;
    }
    else if (playerSum == 21)
    {
        printf("Blackjack!");
        *skipDealer = 1;
    }
    else if (playerSum < 21)
    {
        printf("The player has %d.\n", playerSum);
        printf("Hit? (y/n)\n");
    }
}

// recursive function that..
int hitFunction(char response, int playerSum, int *skipDealer){ //receives either yes or no from the player and the sum of the player's current hand
    if(response == 'y') // if the user selected to hit
    {
        int card;
        card = randomCardGenerator(); // generates a random card
        playerSum += card; //adds the value of the drawn card to the sum of the player's hand
        printf("The player has been dealt a(n): %d\n", card); //tells the player the value of the drawn card
        checkBlackJack(playerSum, skipDealer); // calls our blackjack function
        scanf(" %c", &response); // asks the player to enter yes or no
/*      while(n != 'y' || 'n'){
            printf("Please enter 'y' or 'n'\n");
            scanf(" %c", &response);
}*/
        hitFunction(response, playerSum, skipDealer); // function calls itself if the player enters yes
    }
    else if (response == 'n') // if the player selects no
    {
        printf("The player has %d.\n", playerSum); //tells the player the value of his/her hand
        return playerSum;
    }
}

void dealerAI(int playerSum, int dealerSum, float *chips, int wager) // receives the value of the player's hand the value of the dealer's hand
{
    while (playerSum >= dealerSum)
    {
        delay(1000);
        int card = randomCardGenerator();
        dealerSum += card;
        printf("The dealer draws a %d. The dealer has %d\n", card, dealerSum);

        if (dealerSum>playerSum && dealerSum <= 21)
        {
            printf("The dealer wins.\n");
            *chips = *chips - wager; // the player loses his/her bet
        }
        else if (dealerSum > 21)
        {
            printf("The dealer busts.\n"); //if the dealer busts
            *chips += wager; //the player wins his/her bet
        }
        else if (dealerSum == playerSum)
        {
            printf("Tie.\n");
            *chips += wager; //the player wins if he/she ties with the dealer
        }
    }
}

int main(void){ //use malloc to fix potential memory leak
    //variables
    int i, milliseconds = 900, playerSum, dealerSum, card[4]={0}, bustCheck=0, skipDealer = 0;
    int *skipDealerPointer = &skipDealer;
    char response;
    float chips = 500, wager;
    float *chipPointer = &chips;

    printf("Welcome to Blackjack!\n"); //intro
    printf("You have been given 500 chips.\n");
    printf("BlackJack pays 3:2.\n");
    //create a card drawing
    while (1 == 1) // this starts the game loop
    {

        //resetting the hands back to 0
        dealerSum=0;
        playerSum=0;

        for (i = 0; i < 3; i++) //creates the 3 initial cards. Index 0 and 1 are for the player; index 2 is for the dealer
        {
            card[i] = randomCardGenerator();
            delay(milliseconds);
        }

        playerSum = card[0] + card[1]; //sums the player's cards to make it easier to read
        printf("How many chips would you like to wager?\n");
        scanf("%f", &wager);

        while (wager > chips) // exception handling
        {
            printf("Please enter a wager up to %.2f chips:\n", chips);
            scanf("%f", &wager);
        }

        printf("The dealer is dealt a(n): %d\n", card[2]);
        printf("You are dealt the following two cards: \n");

        if (card[0] == 11 && card[1] == 11) //if the user draws 2 aces, changes one of them to aces low
        {
            card[0] = 1;
            playerSum = 12;
        }

        printf("%d and %d (%d)\n", card[0], card[1], playerSum);

        printf("Hit? (y/n)\n");
        scanf(" %c", &response);
        // add exception handling later

        hitFunction(response, playerSum, skipDealerPointer); //hitFunction is our game engine

        delay(milliseconds);
        if (skipDealer == 0)
        {
            card[3] = randomCardGenerator(); //generates the dealers forth card
            dealerSum = card[2] + card[3];
            printf("The dealer has %d.\n", dealerSum);
            dealerAI(playerSum, dealerSum, &chips, wager); //function call to basic dealer AI
            printf("You have %.2f chips.\n", chips);
        }
        if (chips <= 0) //if the player squanders their money
        {
            printf("Game Over.\n");
            delay(5000);
            exit(0);
        }
    }
}
