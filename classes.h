#pragma once
#include <string>
#include <random>
using namespace std;
#define WIDTH 25
#define HEIGHT 16
// [HEIGHT][WIDTH]

class Tile
{
	bool mine;
	bool flagged;
	short int adjMines;
	bool revealed;
	unsigned int tileNumber;

public:
	Tile() { //unused default constructor
		mine = false;
		flagged = false;
		adjMines = 0;
		revealed = false;
		tileNumber = 0;
	}

	Tile(bool mineTile, short int adj, unsigned int tileNum) { //constructor used
		mine = mineTile;
		flagged = false;
		adjMines = adj;
		revealed = false;
		tileNumber = tileNum;
	}

	bool HasMine() { //whether or not tile contains mine
		return mine;
	}

	void Reveal() { //reveals tile
		revealed = true;
	}

	void Flag() { //flag or unflag tile
		if (flagged == false)
			flagged = true;
		else
			flagged = false;
	}

	bool HasFlag() { //whether or not tile is flagged
		return flagged;
	}

	bool IsRevealed() {
		return revealed;
	}

	short int AdjMineCount() { //returns number of nearby mines
		return adjMines;
	}

	unsigned int GetTileNumber() { //returns tile number
		return tileNumber;
	}
};

struct Board
{
	Tile* board[HEIGHT][WIDTH]; //16 rows of 25 columns

	Board() { //default constructor for random board

		//random placement of 50 mines
		bool d[HEIGHT][WIDTH];
		for (int j = 0; j < HEIGHT; j++)
			for (int i = 0; i < WIDTH; i++)
				d[j][i] = 0;
		int r1, r2;
		srand(time(NULL)); //seed for RNG
		for (int mineCount = 0; mineCount < 50; mineCount++) {
			r1 = rand() % HEIGHT;
			r2 = rand() % WIDTH;
			if (!d[r1][r2]) //if no mine
				d[r1][r2] = 1;
			else //if mine already exists
				mineCount--;
		}

		//board initialization
		unsigned int tileNumber = 1;
		short int adjMines;
		for (int j = 0; j < HEIGHT; j++) { // j = row
			for (int i = 0; i < WIDTH; i++) { // i = column
				if (tileNumber == 1) { //top left corner tile
					adjMines = d[0][1] + d[1][0] + d[1][1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber == 25) { //top right corner tile
					adjMines = d[0][23] + d[1][23] + d[1][24];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber == 376) { //bottom left tile
					adjMines = d[14][0] + d[14][1] + d[15][1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber == 400) { //bottom right tile
					adjMines = d[14][23] + d[14][24] + d[15][23];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber < 25) { //top tiles
					adjMines = d[j][i - 1] + d[j][i + 1] + d[j + 1][i - 1] + d[j + 1][i] + d[j + 1][i + 1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber % 25 == 1) { //left side tiles
					adjMines = d[j - 1][i] + d[j - 1][i + 1] + d[j][i + 1] + d[j + 1][i] + d[j + 1][i + 1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber % 25 == 0) { //right side tiles
					adjMines = d[j - 1][i] + d[j - 1][i - 1] + d[j][i - 1] + d[j + 1][i] + d[j + 1][i - 1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber > 375) { //bottom tiles
					adjMines = d[j][i - 1] + d[j][i + 1] + d[j - 1][i - 1] + d[j - 1][i] + d[j - 1][i + 1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else { //inside tiles
					adjMines = d[j - 1][i - 1] + d[j - 1][i] + d[j - 1][i + 1] +
						d[j][i - 1] + d[j][i + 1] +
						d[j + 1][i - 1] + d[j + 1][i] + d[j + 1][i + 1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				tileNumber++;
			}
		}
	}

	Board(string filename) { //constructor for importing boards from file

		//import map data from file into array for board initialization
		bool d[HEIGHT][WIDTH];
		string line;
		fstream file(filename, ios::in);
		for (int i = 0; i < HEIGHT; i++) {
			getline(file, line);
			for (int j = 0; j < WIDTH; j++)
				d[i][j] = (bool)stoi(line.substr(j, 1));
		}

		// tile coordinates
		// [0,0] [0,24]
		// [15,0][15,24]

		//initialize board
		unsigned int tileNumber = 1;
		short int adjMines;
		for (int j = 0; j < HEIGHT; j++) { // j = row
			for (int i = 0; i < WIDTH; i++) { // i = column
				if (tileNumber == 1) { //top left corner tile
					adjMines = d[0][1] + d[1][0] + d[1][1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber == 25) { //top right corner tile
					adjMines = d[0][23] + d[1][23] + d[1][24];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber == 376) { //bottom left tile
					adjMines = d[14][0] + d[14][1] + d[15][1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber == 400) { //bottom right tile
					adjMines = d[14][23] + d[14][24] + d[15][23];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber < 25) { //top tiles
					adjMines = d[j][i - 1] + d[j][i + 1] + d[j + 1][i - 1] + d[j + 1][i] + d[j + 1][i + 1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber % 25 == 1) { //left side tiles
					adjMines = d[j - 1][i] + d[j - 1][i + 1] + d[j][i + 1] + d[j + 1][i] + d[j + 1][i + 1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber % 25 == 0) { //right side tiles
					adjMines = d[j - 1][i] + d[j - 1][i - 1] + d[j][i - 1] + d[j + 1][i] + d[j + 1][i - 1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else if (tileNumber > 375) { //bottom tiles
					adjMines = d[j][i - 1] + d[j][i + 1] + d[j - 1][i - 1] + d[j - 1][i] + d[j - 1][i + 1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				else { //inside tiles
					adjMines = d[j - 1][i - 1] + d[j - 1][i] + d[j - 1][i + 1] +
						d[j][i - 1] + d[j][i + 1] +
						d[j + 1][i - 1] + d[j + 1][i] + d[j + 1][i + 1];
					board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
				}
				tileNumber++;
			}
		}
	}

	void RevealTile(int row, int col) { //for revealing tiles with zero nearby mines
		//reveal selected zero tile
		if (board[row][col]->HasFlag() == true) //ignore / don't reveal space if it's flagged
			return;
		board[row][col]->Reveal();
		//if zero tile, check for surrounding hidden tiles and do the same for those
		if (board[row][col]->AdjMineCount() == 0) {
			if (board[row][col]->GetTileNumber() == 1) { //top left corner tile
				if (!board[0][1]->IsRevealed())
					RevealTile(0, 1);
				if (!board[1][0]->IsRevealed())
					RevealTile(1, 0);
				if (!board[1][1]->IsRevealed())
					RevealTile(1, 1);
			}
			else if (board[row][col]->GetTileNumber() == 25) { //top right corner tile
				if (!board[0][23]->IsRevealed())
					RevealTile(0, 23);
				if (!board[1][23]->IsRevealed())
					RevealTile(1, 23);
				if (!board[1][24]->IsRevealed())
					RevealTile(1, 24);
			}
			else if (board[row][col]->GetTileNumber() == 376) { //bottom left tile
				if (!board[14][0]->IsRevealed())
					RevealTile(14, 0);
				if (!board[14][1]->IsRevealed())
					RevealTile(14, 1);
				if (!board[15][1]->IsRevealed())
					RevealTile(15, 1);
			}
			else if (board[row][col]->GetTileNumber() == 400) { //bottom right tile
				if (!board[14][23]->IsRevealed())
					RevealTile(14, 23);
				if (!board[14][24]->IsRevealed())
					RevealTile(14, 24);
				if (!board[15][23]->IsRevealed())
					RevealTile(15, 23);
			}
			else if (board[row][col]->GetTileNumber() < 25) { //top tiles
				if (!board[row][col - 1]->IsRevealed())
					RevealTile(row, col - 1);
				if (!board[row][col + 1]->IsRevealed())
					RevealTile(row, col + 1);
				if (!board[row + 1][col - 1]->IsRevealed())
					RevealTile(row + 1, col - 1);
				if (!board[row + 1][col]->IsRevealed())
					RevealTile(row + 1, col);
				if (!board[row + 1][col + 1]->IsRevealed())
					RevealTile(row + 1, col + 1);
			}
			else if (board[row][col]->GetTileNumber() % 25 == 1) { //left side tiles
				if (!board[row - 1][col]->IsRevealed())
					RevealTile(row - 1, col);
				if (!board[row - 1][col + 1]->IsRevealed())
					RevealTile(row - 1, col + 1);
				if (!board[row][col + 1]->IsRevealed())
					RevealTile(row, col + 1);
				if (!board[row + 1][col]->IsRevealed())
					RevealTile(row + 1, col);
				if (!board[row + 1][col + 1]->IsRevealed())
					RevealTile(row + 1, col + 1);
			}
			else if (board[row][col]->GetTileNumber() % 25 == 0) { //right side tiles
				if (!board[row - 1][col]->IsRevealed())
					RevealTile(row - 1, col);
				if (!board[row - 1][col - 1]->IsRevealed())
					RevealTile(row - 1, col - 1);
				if (!board[row][col - 1]->IsRevealed())
					RevealTile(row, col - 1);
				if (!board[row + 1][col]->IsRevealed())
					RevealTile(row + 1, col);
				if (!board[row + 1][col - 1]->IsRevealed())
					RevealTile(row + 1, col - 1);
			}
			else if (board[row][col]->GetTileNumber() > 375) { //bottom tiles
				if (!board[row][col - 1]->IsRevealed())
					RevealTile(row, col - 1);
				if (!board[row][col + 1]->IsRevealed())
					RevealTile(row, col + 1);
				if (!board[row - 1][col - 1]->IsRevealed())
					RevealTile(row - 1, col - 1);
				if (!board[row - 1][col]->IsRevealed())
					RevealTile(row - 1, col);
				if (!board[row - 1][col + 1]->IsRevealed())
					RevealTile(row - 1, col + 1);
			}
			else { //inside tiles
				if (!board[row - 1][col - 1]->IsRevealed())
					RevealTile(row - 1, col - 1);
				if (!board[row - 1][col]->IsRevealed())
					RevealTile(row - 1, col);
				if (!board[row - 1][col + 1]->IsRevealed())
					RevealTile(row - 1, col + 1);
				if (!board[row][col - 1]->IsRevealed())
					RevealTile(row, col - 1);
				if (!board[row][col + 1]->IsRevealed())
					RevealTile(row, col + 1);
				if (!board[row + 1][col - 1]->IsRevealed())
					RevealTile(row + 1, col - 1);
				if (!board[row + 1][col]->IsRevealed())
					RevealTile(row + 1, col);
				if (!board[row + 1][col + 1]->IsRevealed())
					RevealTile(row + 1, col + 1);
			}
		}
	}

	void ResetBoard (string filename="") {
		for (int j = 0; j < HEIGHT; j++) // j = row
			for (int i = 0; i < WIDTH; i++) // i = column
				delete board[j][i];
		if (filename.compare("") == 0) { //random board generation
			//random placement of 50 mines
			bool d[HEIGHT][WIDTH];
			for (int j = 0; j < HEIGHT; j++)
				for (int i = 0; i < WIDTH; i++)
					d[j][i] = 0;
			int r1, r2;
			srand(time(NULL)); //seed for RNG
			for (int mineCount = 0; mineCount < 50; mineCount++) {
				r1 = rand() % HEIGHT;
				r2 = rand() % WIDTH;
				if (!d[r1][r2]) //if no mine
					d[r1][r2] = 1;
				else //if mine already exists
					mineCount--;
			}

			//board initialization
			unsigned int tileNumber = 1;
			short int adjMines;
			for (int j = 0; j < HEIGHT; j++) { // j = row
				for (int i = 0; i < WIDTH; i++) { // i = column
					if (tileNumber == 1) { //top left corner tile
						adjMines = d[0][1] + d[1][0] + d[1][1];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber == 25) { //top right corner tile
						adjMines = d[0][23] + d[1][23] + d[1][24];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber == 376) { //bottom left tile
						adjMines = d[14][0] + d[14][1] + d[15][1];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber == 400) { //bottom right tile
						adjMines = d[14][23] + d[14][24] + d[15][23];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber < 25) { //top tiles
						adjMines = d[j][i - 1] + d[j][i + 1] + d[j + 1][i - 1] + d[j + 1][i] + d[j + 1][i + 1];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber % 25 == 1) { //left side tiles
						adjMines = d[j - 1][i] + d[j - 1][i + 1] + d[j][i + 1] + d[j + 1][i] + d[j + 1][i + 1];
						//debug console outputs
						//cout << "i: " << i << " j: " << j << endl;
						//cout << "tileNumber: " << tileNumber << ": BR: " << d[j+1][i+1] << " R: " << d[j][i + 1] << " AjdMines: " << adjMines << endl;
						//cout << d[j - 1][i] << "+" << d[j - 1][i + 1] << "+" << d[j][i + 1] << "+" << d[j + 1][i] << "+" << d[j + i][i + 1] << " = " << adjMines << endl << endl;
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber % 25 == 0) { //right side tiles
						adjMines = d[j - 1][i] + d[j - 1][i - 1] + d[j][i - 1] + d[j + 1][i] + d[j + 1][i - 1];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber > 375) { //bottom tiles
						adjMines = d[j][i - 1] + d[j][i + 1] + d[j - 1][i - 1] + d[j - 1][i] + d[j - 1][i + 1];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else { //inside tiles
						adjMines = d[j - 1][i - 1] + d[j - 1][i] + d[j - 1][i + 1] +
							d[j][i - 1] + d[j][i + 1] +
							d[j + 1][i - 1] + d[j + 1][i] + d[j + 1][i + 1];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					tileNumber++;
				}
			}
		}
		else //load board from file
		{
			//import map data from file into array for board initialization
			bool d[HEIGHT][WIDTH];
			string line;
			fstream file(filename, ios::in);
			for (int i = 0; i < HEIGHT; i++) {
				getline(file, line);
				for (int j = 0; j < WIDTH; j++)
					d[i][j] = (bool)stoi(line.substr(j, 1));
			}

			// tile coordinates
			// [0,0] [0,24]
			// [15,0][15,24]

			//initialize board
			unsigned int tileNumber = 1;
			short int adjMines;
			for (int j = 0; j < HEIGHT; j++) { // j = row
				for (int i = 0; i < WIDTH; i++) { // i = column
					if (tileNumber == 1) { //top left corner tile
						adjMines = d[0][1] + d[1][0] + d[1][1];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber == 25) { //top right corner tile
						adjMines = d[0][23] + d[1][23] + d[1][24];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber == 376) { //bottom left tile
						adjMines = d[14][0] + d[14][1] + d[15][1];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber == 400) { //bottom right tile
						adjMines = d[14][23] + d[14][24] + d[15][23];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber < 25) { //top tiles
						adjMines = d[j][i - 1] + d[j][i + 1] + d[j + 1][i - 1] + d[j + 1][i] + d[j + 1][i + 1];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber % 25 == 1) { //left side tiles
						adjMines = d[j - 1][i] + d[j - 1][i + 1] + d[j][i + 1] + d[j + 1][i] + d[j + i][i + 1];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber % 25 == 0) { //right side tiles
						adjMines = d[j - 1][i] + d[j - 1][i - 1] + d[j][i - 1] + d[j + 1][i] + d[j + 1][i - 1];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else if (tileNumber > 375) { //bottom tiles
						adjMines = d[j][i - 1] + d[j][i + 1] + d[j - 1][i - 1] + d[j - 1][i] + d[j - 1][i + 1];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					else { //inside tiles
						adjMines = d[j - 1][i - 1] + d[j - 1][i] + d[j - 1][i + 1] +
							d[j][i - 1] + d[j][i + 1] +
							d[j + 1][i - 1] + d[j + 1][i] + d[j + 1][i + 1];
						board[j][i] = new Tile(d[j][i], adjMines, tileNumber);
					}
					tileNumber++;
				}
			}
		}
	}
};