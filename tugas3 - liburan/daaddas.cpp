#include <iostream>
using namespace std;

int main() {
    int A[3][4] = {
        {17, 22, 12, 20},
        {10, 45, 49, 25},
        {25, 27, 26, 40}
    };
    int TOT = 0;
    for(int I = 0; I <= 2; I++) {
        for(int J = 0; J <= 3; J++) {
            TOT = TOT + A[I][J];
            cout << "A[" << I << "][" << J << "] = " << A[I][J] << endl;
        }
    }
    return 0;
}
