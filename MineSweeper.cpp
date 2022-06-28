#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "classes.h"
using namespace std;
#define WIDTH 25
#define HEIGHT 16

void AssignNumbers(Board& board, sf::Sprite numbers[HEIGHT][WIDTH], map<int, sf::Texture>& textures) {
    for (int j = 0; j < HEIGHT; j++) // j = row             //setPosition(x_pos, y_pos)
        for (int i = 0; i < WIDTH; i++) { // i = column
            numbers[j][i].setPosition((i * 32.f), (j * 32.f));
            switch (board.board[j][i]->AdjMineCount()) {
            case 1:
                numbers[j][i].setTexture(textures[1]);
                break;
            case 2:
                numbers[j][i].setTexture(textures[2]);
                break;
            case 3:
                numbers[j][i].setTexture(textures[3]);
                break;
            case 4:
                numbers[j][i].setTexture(textures[4]);
                break;
            case 5:
                numbers[j][i].setTexture(textures[5]);
                break;
            case 6:
                numbers[j][i].setTexture(textures[6]);
                break;
            case 7:
                numbers[j][i].setTexture(textures[7]);
                break;
            case 8:
                numbers[j][i].setTexture(textures[8]);
                break;
            case 0:
                break;
            }
        }
}

void Reset(Board &board, bool &won, bool &lost, int &mineCount, bool &debug_mode, sf::Sprite numbers[HEIGHT][WIDTH], map<int, sf::Texture>& textures, string filename = "") {
    //reset board
    board.ResetBoard(filename);
    //reset number sprite array
    AssignNumbers(board, numbers, textures);
    //reset other variables
    won = false;
    lost = false;
    //debug_mode = false; // <-decided to leave debug mode on when resetting board
    mineCount = 0;
    for (int j = 0; j < HEIGHT; j++) // j = row
        for (int i = 0; i < WIDTH; i++) // i = column
            if (board.board[j][i]->HasMine())
                mineCount++;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

    //Load Textures

    sf::Texture debug_;
        debug_.loadFromFile("images/debug.png");
    sf::Texture digits_;
        digits_.loadFromFile("images/digits.png");
    sf::Texture face_happy_;
        face_happy_.loadFromFile("images/face_happy.png");
    sf::Texture face_lose_;
        face_lose_.loadFromFile("images/face_lose.png");
    sf::Texture face_win_;
        face_win_.loadFromFile("images/face_win.png");
    sf::Texture flag_;
        flag_.loadFromFile("images/flag.png");
    sf::Texture mine_;
        mine_.loadFromFile("images/mine.png");
    sf::Texture number_1_;
        number_1_.loadFromFile("images/number_1.png");
    sf::Texture number_2_;
        number_2_.loadFromFile("images/number_2.png");
    sf::Texture number_3_;
        number_3_.loadFromFile("images/number_3.png");
    sf::Texture number_4_;
        number_4_.loadFromFile("images/number_4.png");
    sf::Texture number_5_;
        number_5_.loadFromFile("images/number_5.png");
    sf::Texture number_6_;
        number_6_.loadFromFile("images/number_6.png");
    sf::Texture number_7_;
        number_7_.loadFromFile("images/number_7.png");
    sf::Texture number_8_;
        number_8_.loadFromFile("images/number_8.png");
    map<int, sf::Texture> textures;
        textures[1] = number_1_;
        textures[2] = number_2_;
        textures[3] = number_3_;
        textures[4] = number_4_;
        textures[5] = number_5_;
        textures[6] = number_6_;
        textures[7] = number_7_;
        textures[8] = number_8_;
    sf::Texture test_1_;
        test_1_.loadFromFile("images/test_1.png");
    sf::Texture test_2_;
        test_2_.loadFromFile("images/test_2.png");
    sf::Texture test_3_;
        test_3_.loadFromFile("images/test_3.png");
    sf::Texture tile_hidden_;
        tile_hidden_.loadFromFile("images/tile_hidden.png");
    sf::Texture tile_revealed_;
        tile_revealed_.loadFromFile("images/tile_revealed.png");
    
    
    //Create Sprites

    map<int, sf::IntRect> digits; //digits array
    digits[0] = sf::IntRect(0, 0, 21, 32);
    digits[1] = sf::IntRect(21, 0, 21, 32);
    digits[2] = sf::IntRect(42, 0, 21, 32);
    digits[3] = sf::IntRect(63, 0, 21, 32);
    digits[4] = sf::IntRect(84, 0, 21, 32);
    digits[5] = sf::IntRect(105, 0, 21, 32);
    digits[6] = sf::IntRect(126, 0, 21, 32);
    digits[7] = sf::IntRect(147, 0, 21, 32);
    digits[8] = sf::IntRect(168, 0, 21, 32);
    digits[9] = sf::IntRect(189, 0, 21, 32);
    digits[-1] = sf::IntRect(210, 0, 21, 32); //-1 represents negative sign here

   sf::Sprite digit_0; //digit sprites
        digit_0.setTexture(digits_);
        digit_0.setPosition(0, 512);
    sf::Sprite digit_1;
        digit_1.setTexture(digits_);
        digit_1.setPosition(21, 512);
    sf::Sprite digit_2;
        digit_2.setTexture(digits_);
        digit_2.setPosition(42, 512);
    sf::Sprite digit_3;
        digit_3.setTexture(digits_);
        digit_3.setPosition(63, 512);

    sf::Sprite debug; //button sprites
        debug.setTexture(debug_);
        debug.setPosition(496, 512);
    sf::Sprite face_happy;
        face_happy.setTexture(face_happy_);
        face_happy.setPosition(368,512);
    sf::Sprite face_lose;
        face_lose.setTexture(face_lose_);
        face_lose.setPosition(368, 512);
    sf::Sprite face_win;
        face_win.setTexture(face_win_);
        face_win.setPosition(368, 512);
    sf::Sprite test_1;
        test_1.setTexture(test_1_);
        test_1.setPosition(560, 512);
    sf::Sprite test_2;
        test_2.setTexture(test_2_);
        test_2.setPosition(624, 512);
    sf::Sprite test_3;
        test_3.setTexture(test_3_);
        test_3.setPosition(688, 512);

    sf::Sprite mine[HEIGHT][WIDTH]; //tile sprite arrays
    sf::Sprite flag[HEIGHT][WIDTH];
    sf::Sprite tile_hidden[HEIGHT][WIDTH];
    sf::Sprite tile_revealed[HEIGHT][WIDTH];
    sf::Sprite numbers[HEIGHT][WIDTH]; //numbers assigned after board initialization
    for (int j = 0; j < HEIGHT; j++) // j = row             //setPosition(x_pos, y_pos)
        for (int i = 0; i < WIDTH; i++) { // i = column
            tile_hidden[j][i].setTexture(tile_hidden_);
            tile_hidden[j][i].setPosition((i*32.f),(j*32.f));
            tile_revealed[j][i].setTexture(tile_revealed_);
            tile_revealed[j][i].setPosition((i*32.f),(j*32.f));
            flag[j][i].setTexture(flag_);
            flag[j][i].setPosition((i*32.f),(j*32.f));
            mine[j][i].setTexture(mine_);
            mine[j][i].setPosition((i*32.f),(j*32.f));
        }


    //Initialize Board
    Board board = Board();


    //Assign numbers Sprite Array their Appropriate Textures (based on loaded board)
    for (int j = 0; j < HEIGHT; j++) // j = row             //setPosition(x_pos, y_pos)
        for (int i = 0; i < WIDTH; i++) { // i = column
            numbers[j][i].setPosition((i * 32.f), (j * 32.f));
            switch (board.board[j][i]->AdjMineCount()) {
            case 1:
                numbers[j][i].setTexture(number_1_);
                break;
            case 2:
                numbers[j][i].setTexture(number_2_);
                break;
            case 3:
                numbers[j][i].setTexture(number_3_);
                break;
            case 4:
                numbers[j][i].setTexture(number_4_);
                break;
            case 5:
                numbers[j][i].setTexture(number_5_);
                break;
            case 6:
                numbers[j][i].setTexture(number_6_);
                break;
            case 7:
                numbers[j][i].setTexture(number_7_);
                break;
            case 8:
                numbers[j][i].setTexture(number_8_);
                break;
            case 0:
                break;
            }
        }


    //Game Loop

    int row;
    int col;
    int mineCount = 0;
    for (int j = 0; j < HEIGHT; j++) // j = row
        for (int i = 0; i < WIDTH; i++) // i = column
            if (board.board[j][i]->HasMine())
                mineCount++;
    bool lost = false;
    bool won = false;
    bool debug_mode = false;

    while (window.isOpen()) {

        //Event Handling (game logic)
        sf::Event event;
        while (window.pollEvent(event)) {

            //Close window (QUIT)
            if (event.type == sf::Event::Closed)
                window.close();

            //Left mouse click (REVEAL)/(BUTTONS)
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                row = event.mouseButton.y / 32;
                col = event.mouseButton.x / 32;

                //if in bounds of board and tile is not flagged and tile is not revealed
                if (row < HEIGHT && col < WIDTH && row >= 0 && col >= 0 && !lost && !won &&
                    !board.board[row][col]->HasFlag() && !board.board[row][col]->IsRevealed()){
                    if (board.board[row][col]->HasMine()) { //if tile has mine
                        board.board[row][col]->Reveal(); //lost, reveal all mines
                        lost = true;
                        for (int j = 0; j < HEIGHT; j++)
                            for (int i = 0; i < WIDTH; i++)
                                if (board.board[j][i]->HasMine())
                                    board.board[j][i]->Reveal();
                    }
                    else //if tile does not have mine
                        board.RevealTile(row, col);
                }

                //debug console output
                //cout << "row: " << row << " col: " << col << endl;
                //cout << event.mouseButton.x/32 << " " << event.mouseButton.y/32 << endl;
                //cout << board.board[row][col]->AdjMineCount() << endl;
                //cout << board.board[row][col]->GetTileNumber() << endl;

                //if debug button pressed
                if (event.mouseButton.y > 511 && event.mouseButton.y < 577 &&
                    event.mouseButton.x > 495 && event.mouseButton.x < 560 && !lost && !won)
                    debug_mode = !debug_mode; //toggle debug mode

                //if reset button pressed
                if (event.mouseButton.y > 511 && event.mouseButton.y < 577 &&
                    event.mouseButton.x > 367 && event.mouseButton.x < 433)
                    Reset(board, won, lost, mineCount, debug_mode, numbers, textures); //reset board

                //if test 1 button pressed
                if (event.mouseButton.y > 511 && event.mouseButton.y < 577 &&
                    event.mouseButton.x > 559 && event.mouseButton.x < 625)
                    Reset(board, won, lost, mineCount, debug_mode, numbers, textures, "boards/testboard1.brd"); //load test_1

                //if test 2 button pressed
                if (event.mouseButton.y > 511 && event.mouseButton.y < 577 &&
                    event.mouseButton.x > 624 && event.mouseButton.x < 690)
                    Reset(board, won, lost, mineCount, debug_mode, numbers, textures, "boards/testboard2.brd"); //load test_2

                //if test 3 button pressed
                if (event.mouseButton.y > 511 && event.mouseButton.y < 577 &&
                    event.mouseButton.x > 689 && event.mouseButton.x < 755)
                    Reset(board, won, lost, mineCount, debug_mode, numbers, textures, "boards/testboard3.brd"); //load test_3
            }

            //Right mouse click (FLAG TILE)
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                row = event.mouseButton.y / 32;
                col = event.mouseButton.x / 32;

                //if in bounds of board and tile is not revealed
                if(row < HEIGHT && col < WIDTH && row >= 0 && col >= 0 && !lost && !won && !board.board[row][col]->IsRevealed()){
                    if (board.board[row][col]->HasFlag()) //if tile is flagged
                        mineCount++; //increase mine count if unflagging
                    else
                        mineCount--; //decrease mine count if flagging
                    board.board[row][col]->Flag(); //flag or unflag tile
                }
            }
        }

        //Check win condition (all non-mine tiles are revealed)
        won = true; //temporarily set true to be corrected by win condition check
        for (int j = 0; j < HEIGHT; j++) // j = row
            for (int i = 0; i < WIDTH; i++) // i = column
                if (!board.board[j][i]->HasMine() && !board.board[j][i]->IsRevealed())
                    won = false;

        //NMI (drawing)
        window.clear(sf::Color::Black);
        for (int j = 0; j < HEIGHT; j++) // j = row
            for (int i = 0; i < WIDTH; i++) { // i = column

                //draw tiles
                if (board.board[j][i]->IsRevealed()) {
                    window.draw(tile_revealed[j][i]);
                    //draw numbers if revealed tile's mine count is greater than zero
                    if (board.board[j][i]->AdjMineCount() != 0 && !board.board[j][i]->HasMine())
                        window.draw(numbers[j][i]);
                }
                else {
                    window.draw(tile_hidden[j][i]);
                }

                //draw flags
                if (board.board[j][i]->HasFlag())
                    window.draw(flag[j][i]);

                //draw buttons
                if (lost)
                    window.draw(face_lose);
                else if (won)
                    window.draw(face_win);
                else
                    window.draw(face_happy);
                window.draw(debug);
                window.draw(test_1);
                window.draw(test_2);
                window.draw(test_3);

                //Draw mine counter
                if (mineCount < 0) { //use all four digits (digit_0 neg sign)
                    digit_0.setTextureRect(digits[-1]);
                    digit_3.setTextureRect(digits[abs(mineCount)%10]);
                    digit_2.setTextureRect(digits[abs(mineCount)/10%10]);
                    digit_1.setTextureRect(digits[abs(mineCount)/100%10]);
                    window.draw(digit_0);
                    window.draw(digit_1);
                    window.draw(digit_2);
                    window.draw(digit_3);
                }
                else { //only use three digits
                    digit_2.setTextureRect(digits[mineCount%10]);
                    digit_1.setTextureRect(digits[mineCount/10%10]);
                    digit_0.setTextureRect(digits[mineCount/100%10]);
                    window.draw(digit_0);
                    window.draw(digit_1);
                    window.draw(digit_2);
                }

                //draw mines (for loss or debug mode)
                if (lost || debug_mode) {
                    if (board.board[j][i]->HasMine())
                        window.draw(mine[j][i]);
                }
            }
        window.display();
    }

    return 0;
}