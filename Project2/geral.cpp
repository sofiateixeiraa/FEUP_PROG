#include "geral.h";

void ClearScreen() {
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

int menu() {
	int mode, op = 0;
	ClearScreen();
	while (op == 0) {
		cout << "(0) - Exit\n\n";
		cout << "(1) - Instructions\n\n";
		cout << "(2) - Let's Play!!\n\n";
		cout << "(3) - Winners \n\n";
		cin >> mode;
		if (mode <= -1 || mode >= 4) { //Se a opção escolhida não for entre 0 e 3
			cout << "Invalid option. Try again: \n";
		}
		else
			op = 1;
	}
	ClearScreen();
	return mode;
}

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