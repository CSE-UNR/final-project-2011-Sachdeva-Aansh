//Aansh Sachdeva
//Date: 07/21/2024
//Final Project

#include <stdio.h>
#define SIZE 10
#define FILE_NAME "easy.txt"

void clearGame(char game[][SIZE]);
void loadGame(char game[][SIZE]);
int ships(FILE* fp, char game[][SIZE]);
int playGame(char guess[][SIZE], char ships[][SIZE]);
int displayScore(char guess[][SIZE], char ships[][SIZE]);
int location(int rows, char cols);

int main(){
    char guess[SIZE][SIZE], ship[SIZE][SIZE];
    char playAgain;
    int turns, numShip;
    FILE* fp2;
    
    fp2 = fopen(FILE_NAME, "r");
    if(fp2 == NULL){
        printf("Cannot load game. Exiting...\n");
        return 0;
    }
    
    numShip = ships(fp2, ship);
    fclose(fp2);
    
    do{
        clearGame(guess);
        turns = playGame(guess, ship);
        
        loadGame(guess);
        printf("YOU WON!\n");
        printf("It only took you %d turns to hit %d spots and destroy the ships.\n", turns, numShip);
        printf("Your score is: %d\n", 100 - turns + numShip);
        printf("Play again? (Y/N) ");
        scanf(" %c", &playAgain); 
    }while(playAgain == 'Y' || playAgain == 'y');
    
    return 0;
}


//Functions

void clearGame(char game[][SIZE]){
	for(int rows = 0; rows < SIZE; rows++){
		for(int cols = 0; cols < SIZE; cols++){
			game[rows][cols] = ' ';
		}
	}
}

void loadGame(char game[][SIZE]){
	printf("   A B C D E F G H I J\n");
	for(int rows = 0; rows < SIZE; rows++){
		printf("%2d ", rows + 1);

		for(int cols = 0; cols < SIZE; cols++){
			printf("%c ", game[rows][cols]);
		}
		printf("\n");
	}
}

int ships(FILE* fp, char game[][SIZE]){
	char fake;
	int ship = 0;
	for(int rows = 0; rows < SIZE; rows++){
        	for(int cols = 0; cols < SIZE; cols++){
            		fscanf(fp, " %c", &fake);
            		game[rows][cols] = fake;
            
            		if(fake == 'S'){
                		ship++;
            		}
       		}
   	}
    
    return ship;
}

int playGame(char guess[][SIZE], char ships[][SIZE]){
	int row, col, numMoves = 0;
	char colLetter;
	
	while(!displayScore(guess, ships)){
		loadGame(guess);
		
		printf("        FIRE AWAY!\n");
		printf("(enter a spot in the grid like A1) ");
		scanf(" %c%d", &colLetter, &row);
		
		while(!location(colLetter, row)){
			printf("Try again!\n");
			printf("(enter a spot in the grid like A1) ");
			scanf(" %c%d", &colLetter, &row);
		}
		
		row--;
		col = colLetter - 'A';
		
		if(ships[row][col] == 'S'){
			guess[row][col] = 'X';
		}
		else{
			guess[row][col] = 'O';
		}
		numMoves++;
	}
	loadGame(guess);
	
	return numMoves;
}

int displayScore(char guess[][SIZE], char ships[][SIZE]){
	for(int row = 0; row < SIZE; row++){
		for(int col = 0; col < SIZE; col++){
			if(ships[row][col] == 'S' && guess[row][col] != 'X'){
				return 0;
			}
		}
	}
	return 1;
}

int location(int rows, char cols){
	if(cols < 'A' || cols > 'J'){
		printf("Invalid column letter.\n");
		return 0;
	}
	if(rows < 1 || rows > 10){
		printf("Invalid row number.\n");
		return 0;
	}
	return 1;
}
