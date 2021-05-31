#include "jogador.h"

int Jogador::getx() const {
	return this->x;
}
int Jogador::gety() const {
	return this->y;
}
void Jogador::setxjogador(unsigned int x) {
	this->x = x;
}
void Jogador::setyjogador(unsigned int y) {
	this->y = y;
}
