#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Jogador {
private:
	int x;
	int y;
public:
	string time;
	string name;
	int getx() const;
	int gety() const;
	void setxjogador(unsigned int x);
	void setyjogador(unsigned int y);
};