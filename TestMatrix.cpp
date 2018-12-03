#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {

	try {
		double** tab = new double*[2];
		for (int i = 0; i < 2; ++i)
			tab[i] = new double[2];
		tab[0][0] = 1;
		tab[0][1] = 2;
		tab[1][0] = 0;
		tab[1][1] = 3;
		
		Matrix A("test.txt");
		Matrix B(2, 2, tab);
		for (int i = 0; i < 2; i++) {
			delete [] tab[i];
		}
		delete [] tab;
		Matrix C(3, 3);
		
		cout << "A:\n" << A;
		cout << "--------------" << endl;
		cout << "B:\n" << B;
		cout << "--------------" << endl;

		Matrix AA = A;
		cout << "A == AA: " << (A == AA) << endl;
		cout << "A != AA: " << (A != AA) << endl;
		cout << "A == B: " << (A == B) << endl;
		cout << "A != B: " << (A != B) << endl;
		cout << "--------------" << endl << endl;
		C = A + B;
		cout << "A + B = \n" << C;
		C = A - B;
		cout << "A - B = \n" << C;
		C = A * B;
		cout << "A * B = \n" << C;
		cout << "--------------" << endl << endl;
		A += B;
		cout << "A += B \n" << A;
		A = AA;
		cout << "ok" << endl;
		A -= B;
		cout << "A -= B \n" << A;
		A = AA;
		A *= B;
		cout << "A *= B \n" << A;
		A = AA;
		C = A * 2;
		cout << "A * 5 \n" << A;
		cout << "--------------" << endl << endl;

		cout << "A:\n" << A;
		cout << "--------------" << endl;
		cout << "B:\n" << B;
		cout << "--------------" << endl;
		
		cout << "A(1,0) = " << A(1, 0) << endl;
		A(1, 0) = -10;
		cout << AA;
		cout << "A(1,0) = -10" << endl;
		cout << "A(1,0) = " << A(1, 0) << endl;
		cout << A;
		cout << "--------------" << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	cout << "_________________________________________" << endl;
	cout << "NULL initializing array:" << endl;
	try {
		Matrix EmptyList(2, 2, nullptr);
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	cout << "_________________________________________" << endl;
	cout << "Wrong dimensions:" << endl;
	try {
		Matrix AE(1, 1);
		Matrix BE(1, 2);
		cout << "First:\n";
		cin >> AE;
		cout << "Second:\n";
		cin >> BE;
		Matrix CE = AE * BE;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	cout << "_________________________________________" << endl;
	cout << "Index out of range:" << endl;
	try {
		Matrix A("test.txt");
		cout << "A: " << endl << A << endl;
		A(4, 5) = 1;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	cout << "_________________________________________" << endl;

}
