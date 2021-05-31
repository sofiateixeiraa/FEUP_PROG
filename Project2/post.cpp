#include "post.h"

int Post::getxpost() const {
	return x;
}
int Post::getypost() const {
	return y;
}
int Post::gettype() const {
	return type;
}
bool Post::isEletrified() {
	if (this->type == 0) {
		return false;
	}
	if (this->type == 1) {
		return true;
	}
}