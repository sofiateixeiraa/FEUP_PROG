#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Robot {
private:
	int x;
	int y;
	int id;
public:
	int getxrobot() const;
	int getyrobot() const;
	int getid() const;
	void setxrobot(unsigned int x);
	void setyrobot(unsigned int y);
	void setidrobot(unsigned int id);
};
