#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//functions
int winnercheck(char array[3][3], char symbol);
int selectionControl(char array[3][3], int selection);

int main(){
    int score1=0;//score user 1
    int score2=0;//score user 2
    int selection;//selection move
    char array[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};//trillise array
    int userTurn=1;//which user should make the next selection

    //Welcome and save usernames
    printf("Welcome to the app!\n");
    printf("please give me the name, first user: ");
    char user1[50];
    scanf("%s", user1);
    printf("please give me the name, second user: ");
    char user2[50];
    scanf("%s", user2);
    printf("users %s, %s are in the app.\n", user1, user2);

    
    while (score1 < 10 && score2 < 10) {
        // cleanup array 
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                array[i][j] = ' ';
            }
        }
        while(1){
            //print the score
            printf("Score: the user %s has %d points, the user %s has %d points", user1, score1, user2, score2);
            //print the array
            printf("\n 1  2  3\n");
            for(int i=0;i<3;i++){
                printf(" ---|---|---\n");
                printf("%d", i+1);
                for(int j=0;j<3;j++){
                    printf("| %c", array[i][j]);
                }
                printf("|\n");
            }
            printf(" ---|---|---\n");

            // the user change selection
            if (userTurn == 1) {
              printf("\n%s, give me your selection (1-9): ", user1);
            } else {
              printf("\n%s, give me your selection (1-9): ", user2);
            }

            scanf("%d", &selection);

            //check selection
            if (!selectionControl(array,selection)) {
                printf("Try again! This selection isn't valid.\n");
                continue;
            }
            char symbol=(userTurn==1)? 'X': 'O';
            int row=(selection-1)/3;
            int col=(selection-1)%3;
            array[row][col]=symbol;

            //check winner
            if(winnercheck(array,symbol)){
                // print array and print winner
                printf("\n 1  2  3\n");
                for(int i=0;i<3;i++){
                printf("|---|---|---|\n");
                printf("%d", i+1);
                for(int j=0;j<3;j++){
                    printf("| %c", array[i][j]);
                }
                printf("|\n");
                }
                printf(" ---|---|---\n");
                
                //check the winner
                if (userTurn == 1) {
                  printf("\n the winner is %s!\n", user1);
                } else {
                  printf("\n the winner is %s!\n", user2);
                }

                //update score
                if (userTurn == 1) {
                    score1++;
                } else {
                    score2++;
                }
                break;
            }
            // control draw
            int arrayFull = 1;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (array[i][j] == ' ') {
                       arrayFull = 0;
                        break;
                    }
                }
                if (!arrayFull) {
                    break;
                }
            }
            if (arrayFull) {
                // printf array and announcement draw
                printf("\n 1  2  3\n");
                for(int i=0;i<3;i++){
                printf(" ---|---|---\n");
                printf("%d", i+1);
                for(int j=0;j<3;j++){
                    printf("| %c", array[i][j]);
                }
                printf("|\n");
                }
                printf(" ---|---|---\n");
            printf("\nDraw!\n");
            break;
            }

            // user change
            if (userTurn == 1) {
              userTurn = 2;
            } else {
              userTurn = 1;
            }

        }
    }

    // printf score
    printf("\nScore: %s %d - %s %d\n", user1, score1, user2, score2);

    // winner of the game
    if (score1 > score2) {
        printf("The %s is the winner!\n", user1);
    } else if (score2 > score1) {
        printf("The %s is the winner!\n", user2);
    } else {
        printf("Draw!\n");
    }

return 0;    
}

//implementations functions
int selectionControl(char array[3][3], int selection){
    int row=(selection-1)/3;
    int col=(selection-1)%3;
    //if the square is empty and exists
    return(selection>=1 && selection<=9 && array[row][col]==' ');
}

int winnercheck(char array[3][3], char symbol) {
    // check horizontal and vertical lines
    for (int i = 0; i < 3; i++) {
        int row_w = 1;
        int col_w = 1;

        for (int j = 0; j < 3; j++) {
            // check horizontal line
            if (array[i][j] != symbol) {
                row_w = 0;
            }

            // check vertical line
            if (array[j][i] != symbol) {
                col_w= 0;
            }
        }

        if (row_w || col_w) {
            return 1;  // win
        }
    }
    // check diagonal lines
    int diag1_w = (array[0][0] == symbol && array[1][1] == symbol && array[2][2] == symbol);
    int diag2_w = (array[0][2] == symbol && array[1][1] == symbol && array[2][0] == symbol);

    if (diag1_w || diag2_w) {
        return 1;  // win
    }

    return 0;  // no one has won
}
