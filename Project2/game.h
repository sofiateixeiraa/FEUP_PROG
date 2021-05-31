#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <ios>
#include <limits>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip> 
#include "robot.h"
#include "jogador.h"
#include "geral.h"
#include "post.h"
#include "maze.h"
// #include "maze.h"
#include <windows.h>

using namespace std;

class Game {
private:
	Jogador jog;
	vector<Robot> robots;
	Maze posts;
	vector<vector<char>> maze;
	Maze door;
	int counter = 0;
	int counterp = 0;
	string selectedMaze;
	int ExitDoor = 0;
public:
	Game(string Myfile);
	Jogador getjog() const;
	vector<Robot> getrobots() const;
	vector<vector<char>> getmaze() const;
	int getcounter() const;
	void openWFile(string winners_file, string winner_name, const time_t winner_time);
	bool playing();
	void printMaze();
	bool player_lose();
	bool player_win();
	bool player_win2();
	void MoveRobots();
	void printwinners();
	bool player_move(char move);
	int Column_Distance(int i);
	int Line_Distance(int k);
};
