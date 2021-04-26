#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

void ClearScreen()
{
    #ifdef _WIN32
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    SetConsoleCursorPosition(hStdOut, homeCoords);
    #else
    cout << string(50, '\n');
    #endif
}
typedef struct Pos {
    int xr, yr;
} Pos;

typedef struct Game {
	int x, y;
	vector<vector<string>> maze;
    vector <Pos> robotpositions;
} Game;


Game read_maze(char* mazenum) {
	Game board;


	return board;
}

bool player_move(char move, Game& game) {
    int new_x, new_y, aux = 0, aux1 = 0;
    while (aux == 0 || aux1 == 0) {
        switch (move) {
        case 'w':
        case 'W':
            new_x = game.x;
            new_y = game.y - 1;
            if (game.maze[new_x][new_y] == "r") {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == "*")
                    return false;
                game.maze[new_x][new_y] = 'H';
                game.maze[game.x][game.y] = ' ';
                game.x = new_x;
                game.y = new_y;
                aux = 1;
            }
        case 'x':
        case 'X':
            new_x = game.x;
            new_y = game.y + 1;
            if (game.maze[new_x][new_y] == "r") {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == "*")
                    return false;
                game.maze[new_x][new_y] = 'H';
                game.maze[game.x][game.y] = ' ';
                game.x = new_x;
                game.y = new_y;
                aux = 1;
            }
        case 'a':
        case 'A':
            new_x = game.x - 1;
            new_y = game.y;
            if (game.maze[new_x][new_y] == "r") {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == "*")
                    return false;
                game.maze[new_x][new_y] = 'H';
                game.maze[game.x][game.y] = ' ';
                game.x = new_x;
                game.y = new_y;
                aux = 1;
            }
        case 'd':
        case 'D':
            new_x = game.x + 1;
            new_y = game.y;
            if (game.maze[new_x][new_y] == "r") {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == "*")
                    return false;
                game.maze[new_x][new_y] = 'H';
                game.maze[game.x][game.y] = ' ';
                game.x = new_x;
                game.y = new_y;
                aux = 1;
            }
        case 'z':
        case 'Z':
            new_x = game.x - 1;
            new_y = game.y + 1;
            if (game.maze[new_x][new_y] == "r") {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == "*")
                    return false;
                game.maze[new_x][new_y] = 'H';
                game.maze[game.x][game.y] = ' ';
                game.x = new_x;
                game.y = new_y;
                aux = 1;
            }
        case 'c':
        case 'C':
            new_x = game.x + 1;
            new_y = game.y + 1;
            if (game.maze[new_x][new_y] == "r") {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == "*" || game.maze[new_x][new_y] == "R")
                    return false;
                game.maze[new_x][new_y] = 'H';
                game.maze[game.x][game.y] = ' ';
                game.x = new_x;
                game.y = new_y;
                aux = 1;
            }
        case 'q':
        case 'Q':
            new_x = game.x - 1;
            new_y = game.y - 1;
            if (game.maze[new_x][new_y] == "r") {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == "*" || game.maze[new_x][new_y] == "R")
                    return false;
                game.maze[new_x][new_y] = 'H';
                game.maze[game.x][game.y] = ' ';
                game.x = new_x;
                game.y = new_y;
                aux = 1;
            }
        case 'e':
        case 'E':
            new_x = game.x + 1;
            new_y = game.y - 1;
            if (game.maze[new_x][new_y] == "r") {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == "*" || game.maze[new_x][new_y] == "R")
                    return false;
                game.maze[new_x][new_y] = 'H';
                game.maze[game.x][game.y] = ' ';
                game.x = new_x;
                game.y = new_y;
                aux = 1;
            }
        case 's':
        case 'S':
            new_x = game.x;
            new_y = game.y;
            if (game.maze[new_x][new_y] == "r") {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == "*" || game.maze[new_x][new_y] == "R")
                    return false;
                game.maze[new_x][new_y] = 'H';
                game.maze[game.x][game.y] = ' ';
                game.x = new_x;
                game.y = new_y;
                aux = 1;
            }
        }
    }
}
/*
bool robot_move(char move, Game &gamer) {
    
}
*/
int menu() {
    int mode, op = 0;
    ClearScreen();
    while (op == 0) {
        cout << "(0) - Show Rules\n\n";
        cout << "(1) - Let's Play!!\n\n";
        cout << "(2) - Quit game\n\n";
        cin >> mode;
        if (mode <= -1 || mode >= 3) {
            cout << "Invalid option. Try again: \n";
        }
        else
            op = 1;
    }
    ClearScreen();
    return mode;
}

void showInstructions() {
    cout << "OBJECTIVE\nThe game starts \n";
}

int main() {
    menu();
    int option = menu();
    if (option == 0) {
        showInstructions();
    }
}
