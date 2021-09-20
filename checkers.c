#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <stdlib.h>

//global board variable so all methods could access
int board[8][8];

//prototype declarations
void repaintBoard();
int validLocationSelectRed(int location);
int validLocationSelectBlack(int location);
int validLocationMoveRed(int pieceLocation, int moveLocation);
int validLocationMoveBlack(int pieceLocation, int moveLocation);
int validLocationMoveKing(int pieceLocation, int moveLocation);
void swap(int pieceLocation, int moveLocation);
void take(int pieceLocation);
bool winCheck();
void kingPiece(int moveLocation);

    

int main(){
    printf("Welcome to checkers\n");
    printf("Select pieces and location by entering the numbers by rows then columns\n");
    printf("For example if you want to select a piece on row 2 and column 1, then input 21\n");

    int i, j;

    //initilizes the board
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++ ){
                board[i][j] = 0;
        
        }
    }

    for(i = 0; i < 3; i++){
        for(j = 0; j < 8; j++ ){
            //if the row is even
            if(i%2 == 0){
                //if column is not even
                if(j%2 != 0){
                board[i][j] = 1;
                }
            }
            else
                if(j%2 == 0){
                    board[i][j] = 1;
                }

        }
    }

    for(i = 5; i < 8; i++){
        for(j = 0; j < 8; j++ ){
            //if the row is even
            if(i%2 == 0){
                //if column is not even
                if(j%2 != 0){
                board[i][j] = 2;
                }
            }
            else
                if(j%2 == 0){
                    board[i][j] = 2;
                }

        }
    }
    //prints the board based on the values in the 2d array
  printf("_|0||1||2||3||4||5||6||7|\n");
    for(i = 0; i < 8; i++){
         printf("%d",i);
        for(j = 0; j < 8; j++ ){
             int partOfBoard = board[i][j];
             switch(partOfBoard){
                case 0:
                    printf("|_|");
                    break;
                case 1:
                    printf("|r|");
                    break;
                case 2:
                    printf("|b|");
                    break;
                case 3:
                    printf("|R|");
                    break;
                case 4:
                    printf("|B|");
                    break;

             }
    
        }
        printf("\n"); 
    }


    bool playing = true;
    //game logic starts here
    while (playing){
        int redLocation;
        int moveLocationRed;
        //0 is no   1 is yes
        int redValid = 0;
        bool redTurn = true;
        //checks if the piece selected is a valid red piece
            do{
            printf("Red's(R) turn!\n");
            printf("Select which chip to move!\n");
            scanf("%d", &redLocation);

            }while((validLocationSelectRed(redLocation) == 0));
            //if the piece is a kinged piece then use the king movement
            if(board[redLocation/10][redLocation%10] == 3){
                do{
                printf("Select a location to move the chip!\n");
                scanf("%d", &moveLocationRed);

                }while((validLocationMoveKing(redLocation,moveLocationRed) == 0));
            }
            //otherwise use the basic red movement
            else{
                do{
                printf("Select a location to move the chip!\n");
                scanf("%d", &moveLocationRed);

                }while((validLocationMoveRed(redLocation,moveLocationRed) == 0));
            }
            swap(redLocation,moveLocationRed);

            //"kinging" piece code
            if(moveLocationRed/10 == 7){
                kingPiece(moveLocationRed);
            }

            int answerRed;
            int pieceTakenLocationRed;
            printf("Did you take any pieces? (1 for yes, 0 for no)\n");
            scanf("%d", &answerRed);
            switch(answerRed){
                case 0:
                    break;
                case 1:
                    printf("Enter the location of the piece taken!\n");
                    scanf("%d", &pieceTakenLocationRed);
                    take(pieceTakenLocationRed);
                    break;
                default:
                    break;

            }
            playing = winCheck();
            //if playing is false then red wins
            if(!playing){
                printf("Red Wins!");
                break;
            }
      
        


        int blackLocation;
        int moveLocationBlack;
        int blackValid = 0;
        bool blackTurn = true;
        repaintBoard();
            do{
            
            printf("Black's(B) turn!\n");
            printf("Select which chip to move!\n");
            scanf("%d", &blackLocation);
            //checks if piece selected is a valid black piece
            }while((validLocationSelectBlack(blackLocation) == 0));
            //checks if piece is "kinged"
            if(board[blackLocation/10][blackLocation%10] == 4){
                //checks if the location selected is valid for kinged piece movement
                do{
                    printf("Select a location to move the chip!\n");
                    scanf("%d", &moveLocationBlack);

                }while((validLocationMoveKing(blackLocation,moveLocationBlack) == 0));
            }

            else{
                //if not a kinged unit, then treats as regular black piece
                do{
                    //checks if the location selected is valid for black piece movement
                    printf("Select a location to move the chip!\n");
                    scanf("%d", &moveLocationBlack);

                }while((validLocationMoveBlack(blackLocation,moveLocationBlack) == 0));
            }
            swap(blackLocation,moveLocationBlack);

            //"kinging" unit code
            if(moveLocationBlack/10 == 0){
                kingPiece(moveLocationBlack);
            }

            int answerBlack;
            int pieceTakenLocationBlack;
            //user input for when player takes a piece
            printf("Did you take any pieces? (1 for yes, 0 for no)\n");
            scanf("%d", &answerBlack);
            switch(answerBlack){
                case 0:
                    break;
                case 1:
                    printf("Enter the location of the piece taken!\n");
                    scanf("%d", &pieceTakenLocationBlack);
                    take(pieceTakenLocationBlack);
                    break;
                default:
                    break;

            }
            //checks if game is won
            playing = winCheck();
            //if playing if false, then black wins
            if(!playing){
                printf("Black Wins!");
                break;
            }
      
    }
}

//method for "kinging a piece"
void kingPiece(int pieceLocation){
    //king red piece
    if(board[pieceLocation/10][pieceLocation%10] == 1){
        board[pieceLocation/10][pieceLocation%10] = 3;
        repaintBoard();
    }
    //king black piece
    else if(board[pieceLocation/10][pieceLocation%10] == 2){
        board[pieceLocation/10][pieceLocation%10] = 4;
        repaintBoard();
    }
    else{
        //do nothing
    }
}

//method for checking if game is already won
bool winCheck(){
    int i, j;
    int redLeft = 0;
    int blackLeft = 0;

    //counts number of pieces left
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++ ){
                //counts number of red pieces left
                if(board[i][j] == 1 || board[i][j] == 3){
                    redLeft = redLeft + 1;
                }
                //counts number of black pieces left
                else if(board[i][j] == 2 || board[i][j] == 4){
                    blackLeft = blackLeft + 1;
                }
                else{
                    //do nothing
                }
                
        
        }
    }
    //if either red or black count is 0, then returns false(someone wins)
    if(redLeft == 0 || blackLeft == 0){
        //false = someone wins
        return false;
    }
    else{
        return true;
    }

}

//makes the piece at the area into 0 which "erases" it
void take(int pieceLocation){
    board[pieceLocation/10][pieceLocation%10] = 0;
    repaintBoard();
}

//method to swap places of the location and the piece
void swap(int pieceLocation, int moveLocation){
    int temp = board[pieceLocation/10][pieceLocation%10];
    board[pieceLocation/10][pieceLocation%10] = board[moveLocation/10][moveLocation%10];
    board[moveLocation/10][moveLocation%10] = temp;
    repaintBoard();
}

//reprints the board 
//called when the array is updated to keep the visuals updated
void repaintBoard(){
    //clears console so it only shows 1 board at a time 
    system("cls");
    int i,j;
    printf("_|0||1||2||3||4||5||6||7|\n");
    for(i = 0; i < 8; i++){
         printf("%d",i);
        for(j = 0; j < 8; j++ ){
             int partOfBoard = board[i][j];
             switch(partOfBoard){
                case 0:
                    printf("|_|");
                    break;
                case 1:
                    printf("|r|");
                    break;
                case 2:
                    printf("|b|");
                    break;
                case 3:
                    printf("|R|");
                    break;
                case 4:
                    printf("|B|");
                    break;

             }
    
        }
        printf("\n"); 
    }
    

}

//Method for red side to check if the piece selected is a valid red piece
int validLocationSelectRed(int location){
    if(location > 77){
            repaintBoard();
            printf("Invalid location! Please try again!\n");
            return 0;
        }
        else if(location %10 > 7){
            repaintBoard();
            printf("Invalid location! Please try again!\n");
            return 0;
        }
        else if(board[location/10][location%10] == 0){
            repaintBoard();
            printf("Nothing there! Please try again\n");
            return 0;
        }
        else if(board[location/10][location%10] == 2 || board[location/10][location%10] == 4){
            repaintBoard();
            printf("Wrong Piece! Please try again\n");
            return 0;
        }
        else{
        //means piece there and valid move
        return 1;
        }
}

//method for black side to check if the piece selected is a valid black piece
int validLocationSelectBlack(int location){
    if(location > 77){
            repaintBoard();
            printf("Invalid location! Please try again!\n");
            return 0;
        }
        else if(location %10 > 7){
            repaintBoard();
            printf("Invalid location! Please try again!\n");
            return 0;
        }
        else if(board[location/10][location%10] == 0){
            repaintBoard();
            printf("Nothing there! Please try again\n");
            return 0;
        }
        else if(board[location/10][location%10] == 1 || board[location/10][location%10] == 3){
            repaintBoard();
            printf("Wrong Piece! Please try again\n");
            return 0;
        }
        else{
        //means piece there and valid move
        return 1;
        }
}

//method for red side to check if the location player wants to move to is valid
int validLocationMoveRed(int pieceLocation,int moveLocation){
    
       //checks if red movement is either bottom left or bottom right of the piece
       //moving down left with a red piece = +1 -1
        //moving down right with a red piece = +1 +1
                                //checking moving down left by 1 and 2
       if ( ((((moveLocation/10)-1 == (pieceLocation/10)) && (moveLocation%10)+1 == (pieceLocation%10)) || (((moveLocation/10)-2 == (pieceLocation/10)) && (moveLocation%10)+2 == (pieceLocation%10))) ||
                                 //checking moving down right by 1 and 2
                (((moveLocation/10)-1 == (pieceLocation/10) && (moveLocation%10)-1 == (pieceLocation%10)) || ((moveLocation/10)-2 == (pieceLocation/10) && (moveLocation%10)-2 == (pieceLocation%10)))){
                    return 1;
                }
        //checks if movement location is in the board
        else if(moveLocation % 10 > 7){
            repaintBoard();
            printf("Invalid location! Please try again!\n");
            return 0;
        }
        //checks if movement location has a piece 
        else if(board[moveLocation/10][moveLocation%10] == 1 || board[moveLocation/10][moveLocation%10] == 2 || board[moveLocation/10][moveLocation%10] == 3 || board[moveLocation/10][moveLocation%10] == 4){
            repaintBoard();
            printf("Piece already there! Please try again\n");
            return 0;
        }
        //checks if movement location is in the board
        else if(moveLocation > 77 || moveLocation < 0){
            repaintBoard();
            printf("Invalid location! Please try again!\n");
            return 0;
        }
        repaintBoard();
        printf("Invalid Move! Please try again!\n");
        return 0;
}

//method for black side to check if the location player wants to move to is valid
int validLocationMoveBlack(int pieceLocation,int moveLocation){
    
       //checks if the movelocation is to the top right or top left of the black piece
       //moving up left with a black piece = -1 -1
        //moving up right with a black piece = -1 +1
                                //checking moving up left by 1 and 2
       if((((moveLocation/10)+1 == (pieceLocation/10) && (moveLocation%10)+1 == (pieceLocation%10)) || ((moveLocation/10)+2 == (pieceLocation/10) && (moveLocation%10)+2 == (pieceLocation%10))) ||
                                 //checking moving up right by 1 and 2
                (((moveLocation/10)+1 == (pieceLocation/10) && (moveLocation%10)-1 == (pieceLocation%10)) || ((moveLocation/10)+2 == (pieceLocation/10) && (moveLocation%10)-2 == (pieceLocation%10)))){
                    return 1;
                }
        //checks if movelocation is in the board
        else if(moveLocation % 10 > 7){
            repaintBoard();
            printf("Invalid location! Please try again!\n");
            return 0;
        }
        //checks if piece is already at the movement location
        else if(board[moveLocation/10][moveLocation%10] == 1 || board[moveLocation/10][moveLocation%10] == 2 || board[moveLocation/10][moveLocation%10] == 3 || board[moveLocation/10][moveLocation%10] == 4 ){
            repaintBoard();
            printf("Piece already there! Please try again\n");
            return 0;
        }
        //checks if move location is in the board
        else if(moveLocation > 77 || moveLocation < 0){
            repaintBoard();
            printf("Invalid location! Please try again!\n");
            return 0;
        }
            repaintBoard();
            printf("Invalid Move! Please try again!\n");
            return 0;


}

int validLocationMoveKing(int pieceLocation, int moveLocation){
    
        //moveLocation/10 is equal to the row location and
        //moveLocation%10 is equal to the column location
        //moving up left with a black piece = -1 -1
        //moving up right with a black piece = -1 +1
        //moving down left with a red piece = +1 -1
        //moving down right with a red piece = +1 +1
                                   //checking moving up left by 1 and 2
        if((((moveLocation/10)+1 == (pieceLocation/10) && (moveLocation%10)+1 == (pieceLocation%10)) || ((moveLocation/10)+2 == (pieceLocation/10) && (moveLocation%10)+2 == (pieceLocation%10))) ||
                                 //checking moving up right by 1 and 2
                (((moveLocation/10)+1 == (pieceLocation/10) && (moveLocation%10)-1 == (pieceLocation%10)) || ((moveLocation/10)+2 == (pieceLocation/10) && (moveLocation%10)-2 == (pieceLocation%10))) ||
                                //checks moving down right by 1 and 2
                (((moveLocation/10)-1 == (pieceLocation/10) && (moveLocation%10)-1 == (pieceLocation%10)) || ((moveLocation/10)-2 == (pieceLocation/10) && (moveLocation%10)-2 == (pieceLocation%10))) ||
                                //checks moving down left by 1 and 2
                ((((moveLocation/10)-1 == (pieceLocation/10)) && (moveLocation%10)+1 == (pieceLocation%10)) || (((moveLocation/10)-2 == (pieceLocation/10)) && (moveLocation%10)+2 == (pieceLocation%10)))){
                    return 1;
        }
        //checks for inputs that are not in the board
        else if(moveLocation > 77 || moveLocation < 0){
            repaintBoard();
            printf("Invalid location! Please try again!\n");
            return 0;
        }
        //checks for inputs that are not in the board
        else if(moveLocation % 10 > 7){
            repaintBoard();
            printf("Invalid location! Please try again!\n");
            return 0;
        }
        //checks if there is already a piece at the location.
        else if(board[moveLocation/10][moveLocation%10] == 1 || board[moveLocation/10][moveLocation%10] == 2 || board[moveLocation/10][moveLocation%10] == 3 || board[moveLocation/10][moveLocation%10] == 4 ){
            repaintBoard();
            printf("Piece already there! Please try again\n");
            return 0;
        }
        else{
            repaintBoard();
            printf("Invalid Move! Please try again!\n");
            return 0;
        }
}







   






