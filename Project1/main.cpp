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
	vector<vector<char>> maze;
    vector <Pos> robotpositions;
} Game;

bool read_maze(Game& board1)
{
    ifstream myReadFile;
    myReadFile.open("maze.txt");

    //while (!myReadFile.eof()) {
        for (int i = 0; i < 6; i++) {
            string aux2;
            vector <char> data;
            getline(myReadFile, aux2);
            for (int j = 0; j < 7; j++) {
                data.push_back(aux2.at(j));
            }
            board1.maze.push_back(data);
        }
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++)
            {
                cout << board1.maze[i][j];
            }
            cout << endl;
        }

    return true;
}
/*
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
*/

bool player_move(char move, Game& game) {
    int new_x, new_y, aux = 0, aux1 = 0;
    while (aux == 0 || aux1 == 0) {
        switch (move) {
        case 'w':
        case 'W':
            new_x = game.x;
            new_y = game.y - 1;
            if (game.maze[new_x][new_y] == 'r') {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == '*')
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
            if (game.maze[new_x][new_y] == 'r') {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == '*')
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
            if (game.maze[new_x][new_y] == 'r') {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == '*')
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
            if (game.maze[new_x][new_y] == 'r') {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == '*')
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
            if (game.maze[new_x][new_y] == 'r') {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == '*')
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
            if (game.maze[new_x][new_y] == 'r') {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == '*' || game.maze[new_x][new_y] == 'R')
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
            if (game.maze[new_x][new_y] == 'r') {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == '*' || game.maze[new_x][new_y] == 'R')
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
            if (game.maze[new_x][new_y] == 'r') {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == '*' || game.maze[new_x][new_y] == 'R')
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
            if (game.maze[new_x][new_y] == 'r') {
                cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
                aux1 = 1;
            }
            else {
                if (game.maze[new_x][new_y] == '*' || game.maze[new_x][new_y] == 'R')
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
bool robot_move(char move, Game &gamer) {
    
}

/*
string askWinner() {
    string name;
    cout << "Congratulations!! Please write you name here: ";
    cin >> name;

    return name;
}
*/
/*
int read_maze(Game& board1) {
    int size = 50;
    ifstream in("maze.txt");

    if (!in) {
        cerr << "File can't be opened! " << endl;
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; i++) {
            in >> board1.maze[i][j];
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; i++) {
            in >> board1.maze[i][j];
        }
    }
    return 0;
}
*/
/*Shows the game menu*/
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

/*Instructions function*/
void showInstructions() {
    cout << "OBJECTIVE\nThe game starts \n";
}

int main() {
    menu();
    Game board1;
    int option = menu();
    if (option == 0) { //Show the instructions
        showInstructions();
    }
    if (option == 2) { // Exit the game
        cout << "See you soon...";
    }
    if (option == 1) { //Play the game
        read_maze(board1);
    }
}
