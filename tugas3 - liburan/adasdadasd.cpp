#include <iostream>
using namespace std;

int main() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (j == 3 || i == 0 || i == 5)
                cout << "*";
            else
                cout << " ";
        }
        cout << "  ";
        for (int j = 0; j < 7; j++) {
            if ((i == 0 && j % 3 != 0) || (i == 1 && j % 3 == 0) || (i - j == 2) || (i + j == 8))
                cout << "*";
            else
                cout << " ";
        }
        cout << "   ";
        for (int j = 0; j < 7; j++) {
            if (((j == 0 || j == 6) && i != 5) || (i == 5 && j > 0 && j < 6))
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }
    return 0;
}



