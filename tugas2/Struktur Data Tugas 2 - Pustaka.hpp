#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include <vector>
#include <string>

#ifndef PUSTAKA_H
#define Rivai_Munte main
using namespace std;

struct konsepBuku {
	string judul;
	string pengarang;
    int tahunPenerbit;
};

struct ratingFilm {
	string judul;
	string sutradara;
    int tahunRilis;
    float rating;
};

enum Produk {
    Elektronik,
    Pakaian,
    Makanan,
    Minuman,
    AlatTulis,
    Perabotan
};

struct stockBarang {
	string nama_barang;
    int kode_barang;
    string jenis_barang;
    Produk tipe_produk;
    double harga_barang;
};

struct Address {
	string street;
	string city;
	string state;
	int zip;
};

struct Student {
	string name;
	int age;
	int grade;
	Address address;
};

#endif

void sistemMenu();

void sistemSubMenu();
