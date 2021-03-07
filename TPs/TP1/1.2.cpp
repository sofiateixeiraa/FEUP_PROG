#include <iostream>

using namespace std;

int main() {
	int A, B, C;
	float mean;
	cout << "Please, input 3 integer numbers:\n";
	cout << "A?\n";
	cin >> A;
	cout << "B?\n";
	cin >> B;
	cout << "C?\n";
	cin >> C;
	mean = (A + B + C) / 3;
	cout << "mean = " << mean << endl;
	cout << "A-mean =" << A - mean << endl;
	cout << "B-mean =" << A - mean << endl;
	cout << "C-mean =" << A - mean << endl;
}