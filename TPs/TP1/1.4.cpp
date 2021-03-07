#include <iostream>

using namespace std;

int main() {
	float a, b, c, d, e, f, x, y;
	cout << "a?\n";
	cin >> a;
	cout << "b?\n";
	cin >> b;
	cout << "c?\n";
	cin >> c;
	cout << "d?\n";
	cin >> d;
	cout << "e?\n";
	cin >> e;
	cout << "f?\n";
	cin >> f;
	x = ((c * e) - (b * f)) / ((a * e) - (b * d));
	y = (a * f - c * d) / (a * e - b * d);
	cout << "x=" << x << endl;
	cout << "y=" << y << endl;
}