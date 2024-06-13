/*
KELOMPOK 7 - SESI CR001 :
		1. Rivai - 20230801290
		2. Chandika Eka Prasetya - 20230801268
		3. Yodan Muhammad Surya Adhe - 20230801424
		4. Muhamad Iqbal Al Kautsar - 20230801032
		5. Fandi Fajar Maulana-20230801157
*/

#ifndef PUSTAKA_HPP
#define PUSTAKA_HPP
#define Rivai_Munte main

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip> 
#include <algorithm>
#include <thread>
#include <chrono>
using namespace std;

struct Barang {
    string nama;
    int jumlah;
    float harga;
};

struct Transaksi {
    string jenisTransaksi;
    double jumlahUang;
    string keterangan;
};

vector<Barang> stokList;

vector<Transaksi> transaksiList;

vector<string> data;

vector<string> dataPermanen;

void searchingMenu();

void sistemMenu();

void sistemSubMenu(void (*targetFunction)());

#endif
