#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <ios>
#include <limits>
#include <algorithm>
#include <chrono>
#include <ctime>
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

typedef struct Jogador {
	int x, y;
} Jogador;

typedef struct Robot {
	int x, y;
	int id;
} Robot;

typedef struct Game {
	// Game Maze
	vector<vector<char>> maze;
	// Robot list
	vector<Robot> robots;
	// Player
	Jogador jog;
	// Ids counter
	int counter = 0;
} Game;
Game gm;

bool player_move(char move, Game& game) {
	int new_x = game.jog.x, new_y=game.jog.y;
	switch (toupper(move)) {
	case 'W':
		new_x = game.jog.x;
		new_y = game.jog.y - 1;
		break;
	case 'X':
		new_x = game.jog.x;
		new_y = game.jog.y + 1;
		break;
	case 'A':
		new_x = game.jog.x - 1;
		new_y = game.jog.y;
		break;
	case 'D':
		new_x = game.jog.x + 1;
		new_y = game.jog.y;
		break;
	case 'Z':
		new_x = game.jog.x - 1;
		new_y = game.jog.y + 1;
		break;
	case 'C':
		new_x = game.jog.x + 1;
		new_y = game.jog.y + 1;
		break;
	case 'Q':
		new_x = game.jog.x - 1;
		new_y = game.jog.y - 1;
		break;
	case 'E':
		new_x = game.jog.x + 1;
		new_y = game.jog.y - 1;
		break;
	case 'S':
		new_x = game.jog.x;
		new_y = game.jog.y;
		break;
	} 
	if (game.maze[new_y][new_x] == 'r') {
		cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
	}
	else {
		game.maze[game.jog.y][game.jog.x] = ' ';
		game.jog.x = new_x;
		game.jog.y = new_y;
		if (game.maze[new_y][new_x] == '*' || game.maze[new_y][new_x] == 'R')
		{
			game.maze[new_y][new_x] = 'h';
			return false;
		}
		game.maze[new_y][new_x] = 'H';
		
	}
}
/*
bool player_move(char move, Game& game) {
	int new_x, new_y, aux = 0, aux1 = 0;
	switch (toupper(move)) {
	case 'W':
		new_x = game.jog.x;
		new_y = game.jog.y - 1;
		if (game.maze[new_y][new_x] == 'r') {
			cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
			aux1 = 1;
		}
		else {
			if (game.maze[new_y][new_x] == '*' || game.maze[new_y][new_x] == 'R')
			{
				game.maze[new_y][new_x] = 'h';
				return false;
			}
			game.maze[new_y][new_x] = 'H';
			game.maze[game.jog.x][game.jog.y] = ' ';
			game.jog.x = new_x;
			game.jog.y = new_y;
			aux = 1;
			aux1 = 1;
		} break;
	case 'X':
		new_x = game.jog.x;
		new_y = game.jog.y + 1;
		if (game.maze[new_y][new_x] == 'r') {
			cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
			aux1 = 1;
		}
		else {
			if (game.maze[new_y][new_x] == '*' || game.maze[new_y][new_x] == 'R')
			{
				game.maze[new_y][new_x] = 'h';
				return false;
			};
			game.maze[new_y][new_x] = 'H';
			game.maze[game.jog.x][game.jog.y] = ' ';
			game.jog.x = new_x;
			game.jog.y = new_y;
			aux = 1;
		} break;
	case 'A':
		new_x = game.jog.x - 1;
		new_y = game.jog.y;
		if (game.maze[new_y][new_x] == 'r') {
			cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
		}
		else {
			if (game.maze[new_y][new_x] == '*' || game.maze[new_y][new_x] == 'R')
			{
				game.maze[new_y][new_x] = 'h';
				return false;
			}
			game.maze[new_y][new_x] = 'H';
			game.maze[game.jog.x][game.jog.y] = ' ';
			game.jog.x = new_x;
			game.jog.y = new_y;
			aux = 1;
		} break;
	case 'D':
		new_x = game.jog.x + 1;
		new_y = game.jog.y;
		if (game.maze[new_y][new_x] == 'r') {
			cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
			aux1 = 1;
		}
		else {
			if (game.maze[new_y][new_x] == '*' || game.maze[new_y][new_x] == 'R')
			{
				game.maze[new_y][new_x] = 'h';
				return false;
			}
			game.maze[new_y][new_x] = 'H';
			game.maze[game.jog.x][game.jog.y] = ' ';
			game.jog.x = new_x;
			game.jog.y = new_y;
			aux = 1;
		} break;
	case 'Z':
		new_x = game.jog.x - 1;
		new_y = game.jog.y + 1;
		if (game.maze[new_y][new_x] == 'r') {
			cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
			aux1 = 1;
		}
		else {
			if (game.maze[new_y][new_x] == '*' || game.maze[new_y][new_x] == 'R')
			{
				game.maze[new_y][new_x] = 'h';
				return false;
			};
			game.maze[new_y][new_x] = 'H';
			game.maze[game.jog.x][game.jog.y] = ' ';
			game.jog.x = new_x;
			game.jog.y = new_y;
			aux = 1;
		} break;
	case 'C':
		new_x = game.jog.x + 1;
		new_y = game.jog.y + 1;
		if (game.maze[new_y][new_x] == 'r') {
			cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
			aux1 = 1;
		}
		else {
			if (game.maze[new_y][new_x] == '*' || game.maze[new_y][new_x] == 'R')
			{
				game.maze[new_y][new_x] = 'h';
				return false;
			}
			game.maze[new_y][new_x] = 'H';
			game.maze[game.jog.x][game.jog.y] = ' ';
			game.jog.x = new_x;
			game.jog.y = new_y;
			aux = 1;
		} break;
	case 'Q':
		new_x = game.jog.x - 1;
		new_y = game.jog.y - 1;
		if (game.maze[new_y][new_x] == 'r') {
			cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
			aux1 = 1;
		}
		else {
			if (game.maze[new_y][new_x] == '*' || game.maze[new_y][new_x] == 'R')
			{
				game.maze[new_y][new_x] = 'h';
				return false;
			}
			game.maze[new_y][new_x] = 'H';
			game.maze[game.jog.x][game.jog.y] = ' ';
			game.jog.x = new_x;
			game.jog.y = new_y;
			aux = 1;
		} break;
	case 'E':
		new_x = game.jog.x + 1;
		new_y = game.jog.y - 1;
		if (game.maze[new_y][new_x] == 'r') {
			cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
			aux1 = 1;
		}
		else {
			if (game.maze[new_y][new_x] == '*' || game.maze[new_y][new_x] == 'R')
			{
				game.maze[new_y][new_x] = 'h';
				return false;
			}
			game.maze[new_y][new_x] = 'H';
			game.maze[game.jog.x][game.jog.y] = ' ';
			game.jog.x = new_x;
			game.jog.y = new_y;
			aux = 1;
		} break;
	case 'S':
		new_x = game.jog.x;
		new_y = game.jog.y;
		if (game.maze[new_y][new_x] == 'r') {
			cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C";
			aux1 = 1;
		}
		else {
			if (game.maze[new_y][new_x] == '*' || game.maze[new_y][new_x] == 'R')
			{
				game.maze[new_y][new_x] = 'h';
				return false;
			}
			game.maze[new_y][new_x] = 'H';
			game.maze[game.jog.x][game.jog.y] = ' ';
			game.jog.x = new_x;
			game.jog.y = new_y;
			aux = 1;
		} break;
	}
}
*/
vector<int> diff_distance(const unsigned int x1, const unsigned int y1, const unsigned int x2, const unsigned int y2) {
	int dist_x, dist_y;
	vector<int> diff_positions;
	dist_x = x1 - x2; diff_positions.push_back(dist_x);
	dist_y = y1 - y2; diff_positions.push_back(dist_y);
	return diff_positions;
}

void robot_move(Game& board, Robot& r) {

	vector<int> diff_positions;
	diff_positions = diff_distance(board.jog.x, board.jog.y, r.x, r.y);
	board.maze[r.y][r.x] = ' '; // posição onde os robôs estavam fica com whitespace
	if (diff_positions[0] > 0) r.x = r.x + 1;
	else if (diff_positions[0] < 0) r.x -= 1;

	if (diff_positions[1] > 0) r.y += 1;
	else if (diff_positions[1] < 0) r.y -= 1;

	switch (board.maze[r.y][r.x]) // nova posição dos robôs
	{
	case '*': case 'R': case 'r':
		board.maze[r.y][r.x] = 'r'; break;

	case 'H':
		board.maze[r.y][r.x] = 'h'; break;

	default:
		board.maze[r.y][r.x] = 'R'; break;
	}
}
void robots_move(Game& board) {
	for (Robot r : board.robots) {
		if (board.maze[r.y][r.x] == 'r') continue;
		robot_move(board, r);
	}
}
bool robot_dead(Game& game, const Robot& r) {
	if (game.maze[r.y][r.x] == 'r') return true;
	return false;
}

bool player_win(Game& game, const vector<Robot>& robots) {
	for (unsigned int r = 0; r < robots.size(); r++) {
		if (game.maze[robots[r].y][robots[r].x] == 'R') return false;
	}
	return true;
}

bool player_lose(Game& game) {
	if (game.maze[game.jog.y][game.jog.x] == 'h') return true;
	return false;
}
void printMaze(vector<vector<char>> maze) {
	for (unsigned int i = 0; i < maze.size(); i++)
	{
		for (unsigned int k = 0; k < maze[i].size(); k++)
			cout << maze[i][k];
		cout << '\n';
	}
}

Game FindMaze(string Myfile) {
	int Dlinhas, Dcolunas;
	Game gm;
	string temp;
	char temp2 = 0;
	char x;
	char m = '\n';
	std::fstream numbers(Myfile, std::ios_base::in);
	numbers >> Dlinhas >> x >> Dcolunas;
	ifstream myMap(Myfile);
	// Verify if the file was read
	if (!myMap.is_open()) {
		cout << "Something went wrong";
	}
	getline(myMap, temp);

	// Read map
	for (int i = 0; i < Dlinhas; i++) {
		vector <char> line;
		// Dcolunas + 1, para ter em conta o \n
		for (int k = 0; k < Dcolunas + 1; k++) {
			// Get char
			myMap.get(temp2);

			if (temp2 != '\n' && temp2 != '\r' && temp2 != '\0') {
				if (temp2 == 'H') {

					//Create player
					gm.jog.x = k;
					gm.jog.y = i;
					cout << "Player created in " << gm.jog.x << "," << gm.jog.y << "\n";

				}
				else if (temp2 == 'R') {

					// Create robot and add it to the list of robots
					Robot myR;
					myR.x = k;
					myR.y = i;
					myR.id = gm.counter;
					gm.counter++;
					gm.robots.push_back(myR);
					cout << "Robot created in " << myR.x << "," << myR.y << " with id " << myR.id << "\n";

				}
				line.push_back(temp2);
				//cout << line[k];
			}
		}
		// Add line to matrix
		gm.maze.push_back(line);
	}
	myMap.close();
	printMaze(gm.maze);// Print Maze
	return gm;
}

/*Instructions function*/
void showInstructions() {
	cout << "OBJECTIVES:\n"
		"You are placed in a maze made up of high-voltage fences and posts. There are also some interceptor robots that\n"
		"will try to destroy you. "
		"If you touch the maze or any of these robots, that is the end of the game.\n"
		"The robots are also destroyed when they touch the fences/posts or when they collide with each other.\n"
		"Every time you move in any direction, each robot moves one cell closer to your new location, \n"
		"in whichever direction is the shortest path.\n"
		"The robots will follow you!\n";

	cout << "POSSIBLE MOVEMENTS:\n"
		"The movement is indicated by typing one of the letters:\n"
		"Q (Forward-left);\nW(Forward);\nE(Forward-Right);\n"
		"A(Center-Left);\nS(Maintain the same position);\nD(Center-Right);\n"
		"Z (Back-left);\nX(Back);\nC(Back-right).\n\n"
		"You can't move to cells occupied by destroyed robots.\n"
		"The above mentioned letters may be typed in uppercase or lowercase.\n"
		"You can exit the game by typing CTRL - Z, in Windows, or CTRL - D, in Linux." << endl << endl;
	cout << "You win when all robots are destroyed." << endl;

	cout << "You lose when you are caught by any robot that is alive or you if you encounter an high-voltage fence." << endl << endl;
}
/*Shows the game menu*/
int menu() {
	int mode, op = 0;
	ClearScreen();
	while (op == 0) {
		cout << "(0) - Exit\n\n";
		cout << "(1) - Instructions\n\n";
		cout << "(2) - Let's Play!!\n\n";
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
bool valid_movement(char move)
{
	switch (toupper(move)) {
	case 'Q': return true;
	case 'W': return true;
	case 'E': return true;
	case 'A': return true;
	case 'S': return true;
	case 'D': return true;
	case 'Z': return true;
	case 'X': return true;
	case 'C': return true;
	}
	return false;
}

string choose_maze() {
	int numberMaze, aux = 0;;
	string maze_file, winners_file, number;

	while (aux == 0)
	{
		cout << "Choose the maze number (Available 1, 4, 8, 12): ";
		cin >> numberMaze;
		if (cin.eof())
		{
			cout << endl << endl;
			cout << "You exited the game!" << endl;
			aux = 1;
		}
		//entrada inválida
		if (cin.fail() or cin.peek() != '\n')
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << endl << endl;
			cerr << "Invalid command. Try again!" << endl; continue;
		}
		if (numberMaze == 0)
		{
			aux = 2;
		}

		if (numberMaze > 0 and numberMaze < 10)
		{
			number = "0" + to_string(numberMaze); // numero do labirinto tem 2 digitos
			maze_file = "MAZE_" + number + ".TXT";
		}
		else {
			number = to_string(numberMaze);
			maze_file = "MAZE_" + number + ".TXT";
		}
		return maze_file;
	}
}
bool playing(Game& board) {
	Robot robot;
	printMaze(board.maze);
	static chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	char move;
	while (true)
	{
		cout << "Next movement? "; cin >> move;
		if (cin.eof())
		{
			cout << endl << endl;
			cout << "YOU LEFT THE GAME!" << endl;
			return 1; //Jogo acaba com Ctrl-Z
		}
		if (!(valid_movement(move) and cin.peek() == '\n')) // verifica se a entrada é um movimento válido
		{
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << endl << endl;
			cerr << "Invalid Movement. Try again!" << endl; continue;
		}
		if (!player_move(move, board) && !player_lose(board))
		{
			cerr << endl << "YOU CAN'T MOVE TO THIS POSITION!" << endl; continue;
		}
		else printMaze(board.maze);

		if (player_lose(board))
		{
			cout << endl << endl;
			cout << endl << "GAME OVER!" << endl; return 1;
		}
		robots_move(board);
	}
}
int main() {
	menu();
	int option = menu();
	if (option == 1) { //Show the instructions
		showInstructions();
	}
	if (option == 0) { // Exit the game
		cout << "See you soon...";
	}
	if (option == 2) { //Play the game
		string number;
		int numberMaze;
		string maze_file;
		string mazeSelected = choose_maze();
		Game board = FindMaze(mazeSelected);
		playing(board);
	}
	return 0;
}
