//T7_G11
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
#include <iomanip> 
//ANA SOFIA TEIXEIRA UP201806466 MIEIC T7
using namespace std;
/* this function clears the screen*/
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
	string time;
	string name;
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
	// Game is over
	bool GAMEOVER = false;
	// Win
	bool Win = false;
	// list
	vector<int> DeadRobots;
} Game;
string mazeSelected;

/*Responsável pelo movimento do jogador*/
bool player_move(char move, Game& game) {
	int new_x = game.jog.x, new_y = game.jog.y;
	switch (toupper(move)) {
	case 'W': // move-up
		new_x = game.jog.x;
		new_y = game.jog.y - 1;
		break;
	case 'X': //move-down
		new_x = game.jog.x;
		new_y = game.jog.y + 1;
		break;
	case 'A': //move left
		new_x = game.jog.x - 1;
		new_y = game.jog.y;
		break;
	case 'D': //move right
		new_x = game.jog.x + 1;
		new_y = game.jog.y;
		break;
	case 'Z': //move diagonal down left
		new_x = game.jog.x - 1;
		new_y = game.jog.y + 1;
		break;
	case 'C': //move diagonal down right
		new_x = game.jog.x + 1;
		new_y = game.jog.y + 1;
		break;
	case 'Q': //move diagonal up left
		new_x = game.jog.x - 1;
		new_y = game.jog.y - 1;
		break;
	case 'E': //move diagonal right
		new_x = game.jog.x + 1;
		new_y = game.jog.y - 1;
		break;
	case 'S': //mantain the same position
		new_x = game.jog.x;
		new_y = game.jog.y;
		break;
	}
	if (game.maze[new_y][new_x] == 'r') //Tried to move to a position ocuppied by 'r'
	{
		cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C \n";
	}
	else {
		game.maze[game.jog.y][game.jog.x] = ' '; //ocupy the last position with a blank space
		game.jog.x = new_x; //update the new position
		game.jog.y = new_y; //update the new position
		if (game.maze[new_y][new_x] == '*' || game.maze[new_y][new_x] == 'R')
		{
			game.maze[new_y][new_x] = 'h'; // when the player hits * or R it changes from H to h
			return false;
		}
		game.maze[new_y][new_x] = 'H'; //update the position of the player to the new coordinates

	}
}
//Compares the distance between the x values of the robot and the player
int Line_Distance(int k, Game& game) {
	return  k - game.jog.x;
}

//Compares the distance between the y values of the robot and the player
int Column_Distance(int i, Game& game) {
	return  i - game.jog.y;
}

void MoveRobots(Game& game) {
	for (int p = 0; p < game.counter; p++) {
		//cout<< "Initial " << "Pos:" <<game.robots[p].x << " , "<<game.robots[p].y<<"\n";

		// if its a faulty robot skip it 
		if (game.maze[game.robots[p].y][game.robots[p].x] == 'r') {
			continue;
		}

		game.maze[game.robots[p].y][game.robots[p].x] = ' ';

		// If the robot is to the left of the player
		if (Line_Distance(game.robots[p].x, game) < 0) {
			//move right
			game.robots[p].x++;
		}
		//If the robot is to the right of the player
		else if (Line_Distance(game.robots[p].x, game) > 0) {
			//move left
			game.robots[p].x--;
		}

		// If the robot is below the player
		if (Column_Distance(game.robots[p].y, game) < 0) {
			//Move up
			game.robots[p].y++;
		}
		//If the robot is above the player
		else if (Column_Distance(game.robots[p].y, game) > 0) {
			//Move Downwards
			game.robots[p].y--;
		}


		switch (game.maze[game.robots[p].y][game.robots[p].x]) {

		case 'H'://if the position is occupied by a human
			game.GAMEOVER = true;
			break;

		case ' '://if the position is empty, move
			game.maze[game.robots[p].y][game.robots[p].x] = 'R';
			break;

		case 'R':case 'r':case '*': //if the position has a 'R','r' or '*', become a r
			game.maze[game.robots[p].y][game.robots[p].x] = 'r';
			// Add to list of dead robots
			game.DeadRobots.push_back(game.robots[p].id);
			break;

		}

		//cout << "Robot " << game.robots[p].id << " Change to " << game.robots[p].x << "," << game.robots[p].y << "\n";

		if (game.DeadRobots.size() == game.counter + 1)
			game.GAMEOVER = true;
	}
}

bool player_win(Game& game, const vector<Robot>& robots) {
	for (unsigned int r = 0; r < robots.size(); r++) {
		if (game.maze[robots[r].y][robots[r].x] == 'R') return false; //se existir algum R maiusculo return false, pois ainda não ganhou
	}
	return true;
}

bool player_lose(Game& game) {
	if (game.maze[game.jog.y][game.jog.x] == 'h') return true; // se o maze tiver um h minusculo, o jogador perdeu
	return false;
}
void printMaze(vector<vector<char>> maze) {
	for (unsigned int i = 0; i < maze.size(); i++)
	{
		for (unsigned int k = 0; k < maze[i].size(); k++) //percorre todas as linhas e colunas para imprimir o ficheiro
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
		"You are  in a maze of high-voltage fences. There are also some interceptor robots that will try to destroy you.\n"
		"If you touch the maze or any of these robots, that is the end of the game.\n"
		"The robots are destroyed when they touch the fences or when they collide with each other.\n"
		"Every time you move in any direction, each robot moves one cell closer to your new location, in whichever direction is the shortest path.\n"
		"The robots will follow you!\n";

	cout << "MOVEMENTS:\n"
		"The movement is indicated by typing one of the letters:\n"
		"Q (Forward-left);\nW(Forward);\nE(Forward-Right);\n"
		"A(Center-Left);\nS(Maintain the same position);\nD(Center-Right);\n"
		"Z (Back-left);\nX(Back);\nC(Back-right).\n\n"
		"You can't move to cells occupied by destroyed robots.\n"
		"The above mentioned letters may be typed in uppercase or lowercase.\n"
		"You can exit the game by typing CTRL - Z, in Windows, or CTRL - D, in Linux." << endl << endl;
	cout << "You lose when you are caught by any robot that is alive or you if you encounter an high-voltage fence." << endl << endl;
	cout << "You win when all robots are destroyed." << endl;
}
/*Shows the game menu*/

/*verifica se o movimento é válido*/
bool valid_movement(char move)
{
	//If it's a valid movement (Q,W,E,A,S,D,,Z,X,C) returns true
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
int menu() {
	int mode, op = 0;
	ClearScreen();
	while (op == 0) {
		cout << "(0) - Exit\n\n";
		cout << "(1) - Instructions\n\n";
		cout << "(2) - Let's Play!!\n\n";
		cin >> mode;
		if (mode <= -1 || mode >= 3) { //if the option chosen was not between 0 and 2
			cout << "Invalid option. Try again: \n";
		}
		else
			op = 1;
	}
	ClearScreen();
	return mode;
}
/*escolhe o labirinto em que se vai jogar*/
string choose_maze() {
	int numberMaze, aux = 0;;
	string maze_file, winners_file, number;
	while (aux == 0)
	{
		cout << "Choose the maze number (Available 1, 4, 8): ";
		cin >> numberMaze;
		if (cin.eof())  // Ctrl+Z, Ctrl+D
		{
			cout << endl << endl;
			cout << "You exited the game!" << endl;
			aux = 1;
		}
		if (cin.fail() || cin.peek() != '\n') //Invalid input
		{
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << endl << endl;
			cerr << "Not valid! Try again!" << endl; continue;
		}
		if (numberMaze == 0)
		{
			menu();

		}
		while (numberMaze != 4 && numberMaze != 8 && numberMaze != 12 && numberMaze != 1) {
			cout << "Choose the maze number (Available 1, 4, 8, 12): ";
			cin >> numberMaze;
		}

		if (numberMaze > 0 && numberMaze < 10)
		{
			number = "0" + to_string(numberMaze); //se o número introduzido pelo utilizador for superior entre 0 e 10
			maze_file = "MAZE_" + number + ".TXT";
		}
		else {
			number = to_string(numberMaze); //se o número introduzido pelo utilizador for superior a 10
			maze_file = "MAZE_" + number + ".TXT";
		}
		return maze_file;
	}
}

/*abre o ficheiro dos vencedores*/
void openWFile(string Myfile, string winner_name, const time_t winner_time) {
	fstream winners(Myfile, ios::in);
	string title, div;
	vector <Jogador> winnervec;
	Jogador winner;
	// Verify if the file was read
	if (!winners.is_open()) {
		cout << "Something went wrong";
	}
	else {
		getline(winners, title); //read the first line
		getline(winners, div); // read the second line
		while (!winners.eof()) { //read the existing winners
			getline(winners, winner.name, '-');
			getline(winners, winner.time);
			winnervec.push_back(winner); //store in the vector
		}
	}
	fstream winners1(Myfile, ios::app); //append
	string line;
	winners1 << winner_name << "-" << winner_time << endl; //write this winner name
	winners1.close();
}

bool playing(Game& board) {
	fstream winners;
	static chrono::steady_clock::time_point begin = chrono::steady_clock::now(); // inicio da contagem do tempo
	char move;
	while (true)
	{
		cout << "Next movement? "; cin >> move;
		if (cin.eof()) //deteta ctrl+z, no windows, e ctrl +d, no linux
		{
			cin.clear();
			cout << endl << endl;
			cout << "YOU LEFT THE GAME!" << endl;
			exit(1);
			return 1;
		}
		if (!(valid_movement(move) && cin.peek() == '\n')) // verifica se a entrada é um movimento válido
		{
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << endl << endl;
			cerr << "Invalid Movement. Try again!" << endl; continue;
		}
		if (!player_move(move, board) && !player_lose(board))
		{
			cerr << endl << "This position is not available!" << endl; continue;
		}

		if (player_win(board, board.robots) && !player_lose(board)) { //if the player wins
			chrono::steady_clock::time_point end = chrono::steady_clock::now();// fim da contagem do tempo
			time_t time = chrono::duration_cast<chrono::seconds>(end - begin).count();// guarda o tempo

			cout << endl << endl;
			printMaze(board.maze); //imprime o labirinto

			string  wname;
			cout << endl << "Congratulations! You did it!" << endl;
			cout << "Please, enter your name:" << endl;
			cin >> wname; // guarda o nome
			while (wname.size() > 15) { //verifica se tem menos que 15 caracteres e pede até cumprir o requisito
				cout << "Please, enter your name (with a maximum of 15 characters):" << endl;
				cin >> wname;
			}
			string numbermaze = mazeSelected.substr(5, 2); // procura o número do maze escolhido no nome do ficheiro
			string winners_file = "MAZE_" + numbermaze + "_WINNERS.TXT"; // cria o título do ficheiro de vencedores
			openWFile(winners_file, wname, time); //abre o ficheiro dos vencedores e escreve lá os nomes dos mesmos
			cout << ifstream(winners_file).rdbuf() << endl; //imprime o ficheiro the vencedores
			return false;

		}
		else printMaze(board.maze); // se não existir nenhuma
		if (player_lose(board)) //jogador perde
		{
			cout << endl << endl;
			cout << endl << "Game over!!" << endl; return 1;
		}
		MoveRobots(board);
	}
}

int main() {
	int option = menu();
	if (option == 1) { //Show the instructions
		showInstructions();
	}
	if (option == 0) { // Exit the game
		cout << "See you soon...";
	}
	if (option == 2) { //Play the game
		mazeSelected = choose_maze(); //o jogador escolhe que labirinto quer jogar
		Game board = FindMaze(mazeSelected);
		playing(board);
	}
	return 0;
}
