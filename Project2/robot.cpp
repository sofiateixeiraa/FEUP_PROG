#include "robot.h"
int Robot::getxrobot() const {
	return this->x;
}
int Robot::getyrobot() const {
	return this->y;
}
int Robot::getid() const {
	return this->id;
}
void Robot::setxrobot(unsigned int x) {
	this->x = x;
}
void Robot::setyrobot(unsigned int y) {
	this->y = y;
}
void Robot::setidrobot(unsigned int id) {
	this->id = id;
}