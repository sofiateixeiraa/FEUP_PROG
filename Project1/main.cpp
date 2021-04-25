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
typedef struct Game {
	int x, y;
	vector<vector<string>> maze;
} Game;

Game read_maze(char* mazenum) {
	Game board;



	return board;
}

bool player_move(char move, Game& game) {
	int new_x, new_y;
	switch (move) {
	case 'w':
		new_x = game.x;
		new_y = game.y-1;
		if (game.maze[new_x][new_y] == "*")
			return false;
		game.maze[new_x][new_y] = 'H';
		game.maze[game.x][game.y] = ' ';
		game.x = new_x;
		game.y = new_y;
    case 'x':
        new_x = game.x;
        new_y = game.y + 1;
        if (game.maze[new_x][new_y] == "*")
            return false;
        game.maze[new_x][new_y] = 'H';
        game.maze[game.x][game.y] = ' ';
        game.x = new_x;
        game.y = new_y;
    case 'a':
        new_x = game.x - 1;
        new_y = game.y;
        if (game.maze[new_x][new_y] == "*")
            return false;
        game.maze[new_x][new_y] = 'H';
        game.maze[game.x][game.y] = ' ';
        game.x = new_x;
        game.y = new_y;
	}
}

int menu() {
    int mode, op = 0;
    ClearScreen();
    while (op == 0) {
        cout << "(0) - Show Rules\n\n";
        cout << "(1) - Let's Play!!\n\n";
        cout << "(2) - Quit game\n\n";
        cin >> mode;
        if (mode <= 0 || mode >= 3) {
            cout << "Invalid option. Try again: \n";
        }
        else
            op = 1;
    }
    ClearScreen();
    return mode;
}

int main() {
    menu();
    int option = menu();
}