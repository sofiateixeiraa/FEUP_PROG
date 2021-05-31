#pragma once
#include <iostream>

class Post {
public:
	int x;
	int y;
	int type;
public:
	int getxpost() const;
	int getypost() const;
	int gettype() const;
	bool isEletrified();
};