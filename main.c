#include "stdio.h"
#include "stdlib.h"
#include "math.h"

void initArray(char** board, int length);
void testinitAray(char** board, int length);
void printBoard(char** baord, int length);
int bounds(char** board, int length, int x, int y); //0 if out of bounds 1 otherwise

int getX(char coordinates[]);
int getY(char coordinate[]);

int validMove(char** board, int length, int x, int y, int a, int b, char player);//1 if valid
int validKingMove(char** board, int length, int x, int y, int a, int b, char player);

void play(char** board, int length, int whoseTurn);

int main() {

	char** arr;
	int boardlength = 8;

	arr = malloc(boardlength * sizeof(char*));

	for (int i = 0; i < boardlength; i++) {
		arr[i] = malloc(boardlength * sizeof(char));

		for (int j = 0; j < boardlength; j++)
			arr[i][j] = ' ';
	}


	initArray(arr, boardlength);
	//testinitAray(arr, boardlength); //chenge checker nums to 2 fro
	printBoard(arr, boardlength);

	play(arr, boardlength, 1);

	for (int i = 0; i < boardlength - 1; i++) {
		free(arr[i]);
	}
	free(arr);

	return 0;


}

void testinitAray(char** board, int length) {
	board[7][0] = '#';
	board[6][1] = 'W';
	board[0][5] = '$';
	board[1][6] = 'B';


}

void initArray(char** board, int length) {
	for (int i = 0; i < length; i += 2) {
		for (int j = 0; j < length; j++) {
			if (j == 0 || j == 2) {
				board[i][j] = 'B';
			}
			else if (j == 1) {
				board[i + 1][j] = 'B';
			}

			if (j == 7 || j == 5) {
				board[i + 1][j] = 'W';
			}
			else if (j == 6) {
				board[i][j] = 'W';
			}
		}
	}
}

void printBoard(char** board, int length) {

	for (int i = length - 1; i >= 0; i--) {
		for (int j = 0; j < length; j++) {
			if (j == 0) {
				printf("%d |%c", i, board[j][i]);
			}
			else if (j == length - 1) {
				printf("|%c|", board[j][i]);
			}
			else {
				printf("|%c", board[j][i]);
			}
		}
		printf("\n");
	}
	for (int i = 0; i < length; i++) {
		if (i == 0) {
			printf("   %c ", i + 'A');
		}
		else if (i == 9) {
			printf("%c\n", i + 'A');
		}
		else {
			printf("%c ", i + 'A');
		}
	}
	printf("\n");
}

int bounds(char** board, int length, int x, int y) { //0 out of bounds
	if (x < 0 || x >= length || y < 0 || y >= length) {
		return 0;
	}
	else {
		return 1;
	}
}

int getX(char coordinate[]) {
	return coordinate[0] - 'A';
}

int getY(char coordinate[]) {
	char* i = &coordinate[1];
	int y = atoi(i);
	return y;
}



int validMove(char** board, int length, int x, int y, int a, int b, char player) { //from x,y to a,b

	if (board[x][y] == player && board[a][b] == ' ') {

		// Checks case of simple move
		if (abs(x - a) == 1) {
			if ((player == 'B') && (b - y == 1))
				return 1;
			else if ((player == 'W') && (b - y == -1))
				return 1;
		}

		// Checks case of a jump
		else if (abs(x - a) == 2) {
			if (player == 'B' && (b - y == 2) &&
				(board[(x + a) / 2][(y + b) / 2] == 'W' || board[(x + a) / 2][(y + b) / 2] == '$'))
				return 1;
			else if (player == 'W' && (b - y == -2) &&
				(board[(x + a) / 2][(y + b) / 2] == 'B' || board[(x + a) / 2][(y + b) / 2] == '#'))
				return 1;
		}
	}
	// If move is neither a simple one or a jump, it is not legal.
	return 0;
}

int validKingMove(char** board, int length, int x, int y, int a, int b, char player) {
	if (board[x][y] == player && board[a][b] == ' ') {

		// Checks case of simple move
		if (abs(x - a) == 1) {
			if ((player == '#') && (abs(b - y) == 1))
				return 1;
			else if ((player == '$') && (abs(b - y) == 1))
				return 1;
		}

		// Checks case of a jump
		else if (abs(x - a) == 2) {
			if (player == '#' && (abs(b - y) == 2) &&
				(board[(x + a) / 2][(y + b) / 2] == 'W' || board[(x + a) / 2][(y + b) / 2] == '$'))
				return 1;
			else if (player == '$' && (abs(b - y) == 2) &&
				(board[(x + a) / 2][(y + b) / 2] == 'B' || board[(x + a) / 2][(y + b) / 2] == '#'))
				return 1;
		}
	}
	return 0;
}

void play(char** board, int length, int whoseTurn) {//0 for white and 1 for black
	int blackCheckersLeft = 12;
	int whiteCheckersLeft = 12;

	while (blackCheckersLeft != 0 || whiteCheckersLeft != 0) {
		if (whoseTurn == 0) {
			printf("Player2's turn!\n");
			char coordinatesFrom[10];
			printf("Please choose which checker you'd like to move: ");
			fgets(coordinatesFrom, 10, stdin);
			int xWhiteFrom = getX(coordinatesFrom);
			int yWhiteFrom = getY(coordinatesFrom);

			if (bounds(board, length, xWhiteFrom, yWhiteFrom) == 0) {
				printf("Please enter valid positions.\n");
				continue;
			}

			if (board[xWhiteFrom][yWhiteFrom] != 'W' && board[xWhiteFrom][yWhiteFrom] != '$') {
				printf("Please choose your checker.\n");
				continue;
			}

			char coordinatesTo[10];
			printf("Please enter coordinate you'd like to move to: ");
			fgets(coordinatesTo, 10, stdin);
			int xWhiteTo = getX(coordinatesTo);
			int yWhiteTo = getY(coordinatesTo);

			if (bounds(board, length, xWhiteTo, yWhiteTo) == 0) {
				printf("Please enter valid positions.\n");
				continue;
			}

			if (board[xWhiteTo][yWhiteTo] != ' ') {
				printf("The spot is taken\n");
				continue;
			}

			if (board[xWhiteFrom][yWhiteFrom] == 'W' && validMove(board, length, xWhiteFrom, yWhiteFrom, xWhiteTo, yWhiteTo, 'W') == 1) {
				if (yWhiteTo != 0) {
					board[xWhiteFrom][yWhiteFrom] = ' ';
					board[xWhiteTo][yWhiteTo] = 'W';
					if (abs(xWhiteTo - xWhiteFrom) == 2) {
						board[(xWhiteFrom + xWhiteTo) / 2][(yWhiteFrom + yWhiteTo) / 2] = ' ';
						blackCheckersLeft--;
						printf("The black checker is killed. Number of black checkers left: %d\n", blackCheckersLeft);
					}
				}
				else if (yWhiteTo == 0) {
					board[xWhiteFrom][yWhiteFrom] = ' ';
					board[xWhiteTo][yWhiteTo] = '$';
					printf("The white stone is crowned!\n");
					if (abs(xWhiteTo - xWhiteFrom) == 2) {
						board[(xWhiteFrom + xWhiteTo) / 2][(yWhiteFrom + yWhiteTo) / 2] = ' ';
						blackCheckersLeft--;
						printf("The black checker is killed. Number of black checkers left: %d\n", blackCheckersLeft);
					}
				}
			}
			else if (board[xWhiteFrom][yWhiteFrom] == '$' && validKingMove(board, length, xWhiteFrom, yWhiteFrom, xWhiteTo, yWhiteTo, '$') == 1) {
				board[xWhiteFrom][yWhiteFrom] = ' ';
				board[xWhiteTo][yWhiteTo] = '$';
				if (abs(xWhiteTo - xWhiteFrom) == 2) {
					board[(xWhiteFrom + xWhiteTo) / 2][(yWhiteFrom + yWhiteTo) / 2] = ' ';
					blackCheckersLeft--;
					printf("The black checker is killed. Number of black checkers left: %d\n", blackCheckersLeft);
				}
			}
			else {
				printf("Please make a valid move!\n");
				continue;
			}

			if (blackCheckersLeft == 0)
				break;

			printBoard(board, length);
			whoseTurn = 1;

		}
		else if (whoseTurn == 1) {
			printf("Player1's turn!\n");
			char coordinatesFrom[10];
			printf("Please choose which checker you'd like to move: ");
			fgets(coordinatesFrom, 10, stdin);
			int xBlackFrom = getX(coordinatesFrom);
			int yBlackFrom = getY(coordinatesFrom);

			if (bounds(board, length, xBlackFrom, yBlackFrom) == 0) {
				printf("Please enter valid positions.\n");
				continue;
			}

			if (board[xBlackFrom][yBlackFrom] != 'B' && board[xBlackFrom][yBlackFrom] != '#') {
				printf("Please choose your checker.\n");
				continue;
			}


			char coordinatesTo[10];
			printf("Please enter coordinate you'd like to move to: ");
			fgets(coordinatesTo, 10, stdin);
			int xBlackTo = getX(coordinatesTo);
			int yBlackTo = getY(coordinatesTo);

			if (bounds(board, length, xBlackTo, yBlackTo) == 0) {
				printf("Please enter valid positions.\n");
				continue;
			}

			if (board[xBlackTo][yBlackTo] != ' ') {
				printf("The spot is taken\n");
				continue;
			}

			if (board[xBlackFrom][yBlackFrom] == 'B' && validMove(board, length, xBlackFrom, yBlackFrom, xBlackTo, yBlackTo, 'B') == 1) {
				if (yBlackTo != length - 1) {
					board[xBlackFrom][yBlackFrom] = ' ';
					board[xBlackTo][yBlackTo] = 'B';
					if (abs(xBlackTo - xBlackFrom) == 2) {
						board[(xBlackFrom + xBlackTo) / 2][(yBlackFrom + yBlackTo) / 2] = ' ';
						whiteCheckersLeft--;
						printf("The white stone is killed. Number of white checkers left: %d\n", whiteCheckersLeft);
					}
				}
				else if (yBlackTo == length - 1) {
					board[xBlackFrom][yBlackFrom] = ' ';
					board[xBlackTo][yBlackTo] = '#';
					printf("The black stone is crowned!\n");
					if (abs(xBlackTo - xBlackFrom) == 2) {
						board[(xBlackFrom + xBlackTo) / 2][(yBlackFrom + yBlackTo) / 2] = ' ';
						whiteCheckersLeft--;
						printf("The white stone is killed. Number of white checkers left: %d\n", whiteCheckersLeft);
					}
				}

			}
			else if (board[xBlackFrom][yBlackFrom] == '#' && validKingMove(board, length, xBlackFrom, yBlackFrom, xBlackTo, yBlackTo, '#') == 1) {
				board[xBlackFrom][yBlackFrom] = ' ';
				board[xBlackTo][yBlackTo] = '#';
				if (abs(xBlackTo - xBlackFrom) == 2) {
					board[(xBlackFrom + xBlackTo) / 2][(yBlackFrom + yBlackTo) / 2] = ' ';
					whiteCheckersLeft--;
					printf("The white stone is killed. Number of white checkers left: %d\n", whiteCheckersLeft);
				}
			}
			else {
				printf("Please make a valid move!\n");
				continue;
			}

			if (whiteCheckersLeft == 0)
				break;

			printBoard(board, length);
			whoseTurn = 0;
		}
	}
	if (blackCheckersLeft == 0) {
		printf("The player 2 wins!\n");
	}
	else if (whiteCheckersLeft == 0) {
		printf("The player 1 wins\n");
	}
	else {
		printf("You both draw!\n");
	}

}
