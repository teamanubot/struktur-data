#include <iostream>
#include <conio.h>
using namespace std;

int main() {
    const int sks = 4, nim = 201581178;
    char nama[12] = "Mia Kastina", matkul[] = "Struktur Data";
    float nilai1, nilai2, nilai3;
    
    nilai1 = 90;
    nilai2 = 80;
    nilai3 = (nilai1 + nilai2) / 2;

    cout << "Nama Mahasiswa : " << nama << "\n";
    cout << "NIM            : " << nim << "\n";
    cout << "Mata Kuliah    : " << matkul << "\n";
    cout << "SKS            : " << sks << "\n";
    cout << "Nilai Teori    : " << nilai1 << "\n";
    cout << "Nilai Praktek  : " << nilai2 << "\n";
    cout << "Nilai Akhir    : " << nilai3 << "\n";
    getch();
} 