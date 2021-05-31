#include "game.h"
bool Game::player_move(char move) {
	int new_x = jog.getx();
	int new_y = jog.gety();
	switch (toupper(move)) {
	case 'W': // move-up
		new_x = jog.getx();
		new_y = jog.gety() - 1;
		break;
	case 'X': //move-down
		new_x = jog.getx();
		new_y = jog.gety() + 1;
		break;
	case 'A': //move left
		new_x = jog.getx() - 1;
		new_y = jog.gety();
		break;
	case 'D': //move right
		new_x = jog.getx() + 1;
		new_y = jog.gety();
		break;
	case 'Z': //move diagonal down left
		new_x = jog.getx() - 1;
		new_y = jog.gety() + 1;
		break;
	case 'C': //move diagonal down right
		new_x = jog.getx() + 1;
		new_y = jog.gety() + 1;
		break;
	case 'Q': //move diagonal up left
		new_x = jog.getx() - 1;
		new_y = jog.gety() - 1;
		break;
	case 'E': //move diagonal right
		new_x = jog.getx() + 1;
		new_y = jog.gety() - 1;
		break;
	case 'S': //mantain the same position
		new_x = jog.getx();
		new_y = jog.gety();
		break;
	}
	if (maze[new_y][new_x] == 'r' || maze[new_y][new_x] == '+') //Tried to move to a position ocuppied by 'r'
	{
		cout << "Please try again, valid movements: Q,W,E,A,S,D,Z,X,C \n";
	}
	else {
		maze[jog.gety()][jog.getx()] = ' '; //ocupy the last position with a blank space
		jog.setxjogador(new_x); //update the new position
		jog.setyjogador(new_y); //update the new position
		if (maze[new_y][new_x] == '*' || maze[new_y][new_x] == 'R')
		{
			maze[new_y][new_x] = 'h'; // when the player hits * or R it changes from H to h
			return false;
		}
		if (maze[new_y][new_x] == 'O' )
		{
			maze[new_y][new_x] = 'H'; // when the player hits * or R it changes from H to h
			this->ExitDoor = 1;
		}
		maze[new_y][new_x] = 'H'; //update the position of the player to the new coordinates
	}
	return true;
}

int Game::Line_Distance(int k) {
	return  k - jog.getx();
}

//Compares the distance between the y values of the robot and the player
int Game::Column_Distance(int i) {
	return  i - jog.gety();
}
void Game::MoveRobots() {
	for (int p = 0; p < counter; p++) {
		int new_x = robots[p].getxrobot();
		int new_y = robots[p].getyrobot();
		//cout<< "Initial " << "Pos:" <<new_x << " , "<<new_y<<"\n";

		// if its a faulty robot skip it 
		if (maze[new_y][new_x] == 'r') {
			continue;
		}

		maze[new_y][new_x] = ' ';

		// If the robot is to the left of the player
		if (Line_Distance(new_x) < 0) {
			//move right
			new_x = new_x + 1;
		}
		//If the robot is to the right of the player
		else if (Line_Distance(new_x) > 0) {
			//move left
			new_x--;
		}

		// If the robot is below the player
		if (Column_Distance(new_y) < 0) {
			//Move up
			new_y++;
		}
		//If the robot is above the player
		else if (Column_Distance(new_y) > 0) {
			//Move Downwards
			new_y--;
		}
		
		switch (maze[new_y][new_x]) {

		case 'H'://if the position is occupied by a human
			maze[new_y][new_x] = 'r';
			break;
		case '+':
			maze[new_y][new_x] = 'r';
			break;
		case ' '://if the position is empty, move
			maze[new_y][new_x] = 'R';
			break;

		case 'R':case 'r':case '*': //if the position has a 'R','r' or '*', become a r
			maze[new_y][new_x] = 'r';
			break;
		}

		//cout << "Robot " << game.robots[p].id << " Change to " << game.new_x << "," << game.new_y << "\n";
	}
}
//verifica se ainda existem robôs vivos no labirinto
bool Game::player_win() {
	for (unsigned int r = 0; r < robots.size(); r++) {
		if (maze[robots[r].getyrobot()][robots[r].getxrobot()] == 'R') return false; //se existir algum R maiusculo return false, pois ainda não ganhou
	}
	return true;
}

bool Game::player_lose() {
	if (maze[jog.gety()][jog.getx()] == 'h') return true; // se o maze tiver um h minusculo, o jogador perdeu
	return false;
}

void Game::printMaze() {
	for (unsigned int i = 0; i < maze.size(); i++)
	{
		for (unsigned int k = 0; k < maze[i].size(); k++) //percorre todas as linhas e colunas para imprimir o ficheiro
			cout << maze[i][k];
		cout << '\n';
	}
}

Game::Game(string Myfile) {
	int Dlinhas, Dcolunas;
	string temp;
	char temp2 = 0;
	char x;
	char m = '\n';
	this->selectedMaze = Myfile;
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

					//Cria jogador
					this->jog.setxjogador(k);
					this->jog.setyjogador(i);
					cout << "Player created in " << this->jog.getx() << "," << this->jog.gety() << "\n";

				}
				else if (temp2 == 'R') {

					// Cria robo e adiciona ao vetor de robos
					Robot myR;
					myR.setxrobot(k);
					myR.setyrobot(i);
					myR.setidrobot(this->counter);
					this->counter++;
					this->robots.push_back(myR);
					cout << "Robot created in " << myR.getxrobot() << "," << myR.getyrobot() << " with id " << myR.getid() << "\n";

				}
				else if (temp2 == '*') {

					// Cria poste eletrificado
					Post post;
					post.x = k;
					post.y = i;
					post.type = 1;
					this->counterp++;
					this->posts.posts.push_back(post);

				}
				else if (temp2 == '+') {

					// Cria poste não eletrificado
					Post post;
					post.x = k;
					post.y = i;
					post.type = 0;
					this->counterp++;
					this->posts.posts.push_back(post);

				}
				else if (temp2 == 'O') {

					// Cria porta
					Post door;
					door.x = k;
					door.y = i;
					door.type = 2;

				}
				line.push_back(temp2);
			}
		}
		// Adiciona a linha ao maze
		this->maze.push_back(line);
	}
	myMap.close();
}

bool Game::playing() {
	fstream winners;
	static chrono::steady_clock::time_point begin = chrono::steady_clock::now(); // inicio da contagem do tempo
	char move;
	printMaze();
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
		if (!player_move(move) && !player_lose())
		{
			cerr << endl << "This position is not available!" << endl; continue;
		}

		if (player_win() && this->ExitDoor == 1 && !player_lose()) { //if the player wins
			chrono::steady_clock::time_point end = chrono::steady_clock::now();// fim da contagem do tempo
			time_t time = chrono::duration_cast<chrono::seconds>(end - begin).count();// guarda o tempo

			cout << endl << endl;
			printMaze(); //imprime o labirinto

			string  wname;
			cout << endl << "Congratulations! You did it!" << endl;
			cout << "Please, enter your name:" << endl;
			cin >> wname; // guarda o nome
			while (wname.size() > 15) { //verifica se tem menos que 15 caracteres e pede até cumprir o requisito
				cout << "Please, enter your name (with a maximum of 15 characters):" << endl;
				cin >> wname;
			}
			string numbermaze = this->selectedMaze.substr(5, 2); // procura o número do maze escolhido no nome do ficheiro
			string winners_file = "MAZE_" + numbermaze + "_WINNERS.TXT"; // cria o título do ficheiro de vencedores
			openWFile(winners_file, wname, time); //abre o ficheiro dos vencedores e escreve lá os nomes dos mesmos
			cout << ifstream(winners_file).rdbuf() << endl; //imprime o ficheiro the vencedores
			return false;

		}
		else printMaze(); // se não existir nenhuma
		if (player_lose()) //jogador perde
		{
			cout << endl << endl;
			cout << endl << "Game over!!" << endl; return 1;
		}
		MoveRobots();
	}
}
void Game::printwinners() {
	string numbermaze = this->selectedMaze.substr(5, 2); // procura o número do maze escolhido no nome do ficheiro
	string winners_file = "MAZE_" + numbermaze + "_WINNERS.TXT"; // cria o título do ficheiro de vencedores
	cout << ifstream(winners_file).rdbuf() << "\n" << endl; //imprime o ficheiro the vencedores
}

void Game::openWFile(string winners_file, string winner_name, const time_t winner_time) {
	fstream winners(winners_file, ios::in);
	string title, div;
	vector <Jogador> winnervec;
	Jogador winner;
	// Verifica se o ficheiro foi aberto
	if (!winners.is_open()) {
		cout << "Something went wrong";
	}
	else {
		getline(winners, title); //le a primeira linha
		getline(winners, div); // le a segunda linha
		while (!winners.eof()) { //le os vencedores
			getline(winners, winner.name, '-');
			getline(winners, winner.time);
			winnervec.push_back(winner); //guarda no vetor
		}
	}
	
    winnervec.pop_back();
     // Add new winner
    winner.name = winner_name;
    int wn= static_cast<long int>(winner_time);
    stringstream ss;
    ss << wn;
    ss>>winner.time;
    winnervec.push_back(winner);

    winners.close();

    for (int i = 0; i < winnervec.size(); i++)
    {
			cout <<  winnervec[i].name << endl;
    }
    

    
	int max_idx;
	// One by one move boundary of unsorted subarray 
    for (int i = 0; i < winnervec.size(); i++) 
    { 
        // Find the maximum element in unsorted array 
        max_idx = i; 
        for (int j = i+1; j < winnervec.size(); j++) 
        if (stoi(winnervec[j].time) > stoi(winnervec[max_idx].time)) 
            max_idx = j; 
  
        // Swap the found minimum element with the first element 
		Jogador temp = winnervec[i];
		Jogador temp2 = winnervec[max_idx];
		winnervec[max_idx] = temp;
		winnervec[i] = temp2;

    } 

    ofstream winner2;
    winner2.open(winners_file, fstream::out | fstream::trunc);
    winner2.close();

    // Write to file
    fstream winners1(winners_file, ios::app);
	winners1 << title << endl;
	winners1 << div << endl;
	for (int i = 0; i<winnervec.size(); i++ ){
			winners1 << winnervec[i].name << "-" << winnervec[i].time  << endl;
		
		}
	winners1.close();
}