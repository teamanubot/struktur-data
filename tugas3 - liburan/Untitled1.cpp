#include <iostream>
#include <string.h>
using namespace std;

void datadiri(string &nama, string &nim) {
	cout << "Data Diri\n" << endl;
	cout << "Nama : " << nama << endl;
	cout << "NIM  : " << nim << endl;
}

int main() {
	string nama = "Rivai";
	string nim = "20230801290";
	datadiri(nama, nim);
	return 0;
}
