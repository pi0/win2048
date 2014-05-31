//#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>

static int Tiles[16];

static int score;

int NoSpaceAvailable(void);
int SpaceAvailable(void);
int NextStep(void);
void InitTiles(void);
void ShiftRight(void);
void ShiftLeft(void);
void ShiftUp(void);
void ShiftDown(void);
void MergeUp(void);
void MergeDown(void);
void MergeLeft(void);
void MergeRight(void);
void PrintTiles(void);


int NoSpaceAvailable(void)
{
	int i = 0;
	int allFill = 1;

	for (i = 0, allFill = 1; i < 16 && allFill; ++i){
		if (Tiles[i] == 0){
			allFill = 0;
		}
	}

	return allFill;
}

int SpaceAvailable(void)
{
	return !NoSpaceAvailable();
}

int NextStep(void)
{
	int random_loc = 0;
	int got_what_we_need = 1;

	// init random numbers generation seed

	if (NoSpaceAvailable()) return 0;

	srand(time(NULL));


	for (got_what_we_need = 1; got_what_we_need; got_what_we_need = 0){
		random_loc = rand() % 16;
		if (Tiles[random_loc] == 0){
			Tiles[random_loc] = 2;
			got_what_we_need = 1;
		}
	}
	return 1; // yes, we got what we need.
}

void InitTiles(void)
{
	int i = 0;
	for (i = 0; i < 16; ++i){
		Tiles[i] = 0;
	}
}

void ShiftRight(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	// most eligible space
	int mes = 0;

	for (i = 0; i <4; ++i){
		mes = 4 * i +4 - 1;
		for (j = mes; j > 4 * i; --j){
			if (Tiles[j] != 0) continue;

			for (k = j - 1; k >= 4 * i; --k){
				if (Tiles[k] != 0) break;
			}
			if (k >= 4 * i && Tiles[k] != 0){ // put k >= 0 and boom, bad logic
				Tiles[j] = Tiles[k];
				Tiles[k] = 0;
			}
		}
	}
}

void ShiftLeft(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	// most eligible space
	int mes = 0;

	for (i = 0; i <4; ++i){
		mes = 4 * i + 0;
		for (j = mes; j < 4 * i +4 - 1; ++j){
			if (Tiles[j] != 0) continue;

			for (k = j + 1; k <= 4 * i +4 - 1; ++k){
				if (Tiles[k] != 0) break;
			}
			if (k <= 4 * i +4 - 1 && Tiles[k] != 0){ // put k >= 0 and boom, bad logic
				Tiles[j] = Tiles[k];
				Tiles[k] = 0;
			}
		}
	}
}

void ShiftDown(void)
{
	int i = 0;
	int j = 0;
	int k = 0;
	// most eligible space
	int mes = 0;

	for (i = 0; i <4; ++i){
		mes = i +4*(4 - 1);
		for (j = mes; j > i; j -= 4){
			if (Tiles[j] != 0) continue;

			for (k = j - 4; k >= i; k -= 4){
				if (Tiles[k] != 0) break;
			}
			if (k >= i && Tiles[k] != 0){ // put k >= 0 and boom, bad logic
				Tiles[j] = Tiles[k];
				Tiles[k] = 0;
			}
		}
	}
}

void ShiftUp(void)
{
	int i = 0;
	int j = 0;
	int k = 0;

	for (i = 0; i <4; ++i){
		for (j = i; j <4*(4 - 1) + i; j += 4){
			if (Tiles[j] != 0) continue;
			for (k = j + 4; k <=4*(4 - 1) + i; k += 4){
				if (Tiles[k] != 0) break;
			}
			if (k <=4*(4 - 1) + i && Tiles[k] != 0){
				Tiles[j] = Tiles[k];
				Tiles[k] = 0;
			}
		}
	}
}

void MergeRight(void)
{
	int i = 0;
	int j = 0;
	int k = 0;

	for (i = 0; i <4; ++i){
		for (j = 4 * i +4 - 1; j > 4 * i; --j){
			if (Tiles[j] == 0) continue;
			for (k = j - 1; k >= 4 * i; --k){
				if (Tiles[k] == 0) continue;
				if (Tiles[k] == Tiles[j]){
					Tiles[j] *= 2;
					score += Tiles[j];
					Tiles[k] = 0;
					j = k;
				}
				break;
			}
		}
	}

}

void MergeLeft(void)
{
	int i = 0;
	int j = 0;
	int k = 0;

	for (i = 0; i <4; ++i){
		for (j = 4 * i; j < 4 * i +4 - 1; ++j){
			if (Tiles[j] == 0) continue;
			for (k = j + 1; k <= 4 * i +4 - 1; ++k){
				if (Tiles[k] == 0) continue;
				if (Tiles[j] == Tiles[k]){
					Tiles[j] *= 2;
					score += Tiles[j];
					Tiles[k] = 0;
					j = k;
				}
				break;
			}
		}
	}

}

void MergeDown(void)
{
	int i = 0;
	int j = 0;
	int k = 0;

	for (i = 0; i <4; ++i){
		for (j =4*(4 - 1) + i; j > i; j -=4){
			if (Tiles[j] == 0) continue;
			for (k = j -4; k >= i; k -=4){
				if (Tiles[k] == 0) continue;
				if (Tiles[j] == Tiles[k]){
					Tiles[j] *= 2;
					score += Tiles[j];
					Tiles[k] = 0;
					j = k;
				}
				break;
			}
		}
	}
}

void MergeUp(void)
{
	int i = 0;
	int j = 0;
	int k = 0;

	for (i = 0; i <4; ++i){
		for (j = i; j <4*(4 - 1) + i; j +=4){
			if (Tiles[j] == 0) continue;
			for (k = j +4; k <=4*(4 - 1) + i; k +=4){
				if (Tiles[k] == 0) continue;
				if (Tiles[j] == Tiles[k]){
					Tiles[j] *= 2;
					score += Tiles[j];
					Tiles[k] = 0;
					j = k;
				}
				break;
			}
		}
	}


}

void PrintTiles()
{
	int i =4, j =4;
	for (i = 0; i <4; ++i){
		for (j = 0; j <4; ++j){
			if (Tiles[4 * i + j] != 0)
				printf("%6d", Tiles[4 * i + j]);
			else
				printf("%6s", "-");
		}
		printf("\n\n");
	}
}

void printHelp()
{
	printf("\nScore : %d\n", score);
	printf("A: left , D: right , W: up , S: down , q : exit\n");
	printf("------------------------------------------------\n\n");
}

void PlayGame()
{
	char userChoice = 'k';
	InitTiles();
	score = 0;

	do{
		if (!NextStep())
			break;
	
		system("cls");
		printHelp();
		PrintTiles();

		userChoice = _getch();
		if (userChoice == '\n') userChoice = _getch();

		switch (userChoice)
		{
			case 'a': MergeLeft(); ShiftLeft(); break;
			case 'd': MergeRight(); ShiftRight(); break;
			case 'w': MergeUp(); ShiftUp(); break;
			case 's': MergeDown(); ShiftDown(); break;
		}
		
	} while (SpaceAvailable() && userChoice != 'q');

}

int main()
{
	PlayGame();

	printf("Game finished !\nPlease enter your name : ");
	char name[20];
	scanf("%s", name);

	FILE* f = fopen("scores.txt","a+");
	fprintf(f, "%s : %d\r\n", name, score); 
	fclose(f);

}
