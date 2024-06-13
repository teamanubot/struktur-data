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
#include <random>
using namespace std;

struct Barang {
    string nama;
    string kode_Barang;
    int jumlah;
    float harga;
};

vector<Barang> stokList = {
    {"Pensil", "1000", 100, 2000},
    {"Ember", "1001", 50, 15000},
    {"Pulpen", "1002", 100, 5000}
};

vector<Barang> dataPermanen(stokList);

void sistemMenu();

void sistemSubMenu(void (*targetFunction)());

#endif
