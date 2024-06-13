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
#include <thread>
#include <chrono>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void sistemMenu();

void sistemSubMenu(void (*targetFunction)());

#endif
