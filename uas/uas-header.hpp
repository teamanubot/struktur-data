#ifndef UAS_HEADER_HPP
#define UAS_HEADER_HPP

#include <iostream>
#include <mysql/mysql.h>
#include <sstream>
#include <termios.h>
#include <unistd.h>

using namespace std;

extern const char* hostname;
extern const char* user;
extern const char* pass;
extern const char* dbname;
extern unsigned int port;
extern const char* unixsocket;
extern unsigned long clientflag;

MYSQL* connect_db();
bool authenticate_user(MYSQL* conn, const string& username, const string& password);
string get_username_by_id(MYSQL* conn, int user_id);
void get_books(MYSQL* conn);
void search_books(MYSQL* conn, const string& keyword);
void borrow_book(MYSQL* conn, int book_id, int user_id);
void return_book(MYSQL* conn, int book_id, int user_id);
string get_password();
int login_user();
void admin_menu(MYSQL* conn);
void user_menu(MYSQL* conn, int user_id);

#endif