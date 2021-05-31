#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "robot.h"
#include "jogador.h"
#include <windows.h>
using namespace std;

int menu();
string choose_maze();
void ClearScreen();
bool valid_movement(char move);
