#include <iostream>
#include <mysql/mysql.h>
#include <sstream>
#include <termios.h>
#include <unistd.h>

using namespace std;

const char* hostname = "127.0.0.1";
const char* user = "root";
const char* pass = "123";
const char* dbname = "paibooks_store";
unsigned int port = 31235;
const char* unixsocket = NULL;
unsigned long clientflag = 0;

MYSQL* connect_db() {
    MYSQL* conn = mysql_init(0);
    if (conn) {
        conn = mysql_real_connect(conn, hostname, user, pass, dbname, port, unixsocket, clientflag);
        if (conn) {
            return conn;
        } else {
            cerr << "Koneksi gagal : " << mysql_error(conn) << endl;
            mysql_close(conn);
            return nullptr;
        }
    } else {
        cerr << "mysql_init gagal" << endl;
        return nullptr;
    }
}

bool authenticate_user(MYSQL* conn, const string& username, const string& password) {
    stringstream query;
    query << "SELECT * FROM users WHERE username = '" << username << "' AND password = '" << password << "'";
    
    if (mysql_query(conn, query.str().c_str())) {
        cerr << "QUERY gagal : " << mysql_error(conn) << endl;
        return false;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (res == nullptr) {
        cerr << "mysql_store_result gagal : " << mysql_error(conn) << endl;
        return false;
    }

    bool authenticated = mysql_num_rows(res) > 0;
    mysql_free_result(res);
    return authenticated;
}

string get_username_by_id(MYSQL* conn, int user_id) {
    stringstream query;
    query << "SELECT username FROM users WHERE id = " << user_id;
    if (mysql_query(conn, query.str().c_str())) {
        cerr << "QUERY gagal : " << mysql_error(conn) << endl;
        return "";
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (res == nullptr) {
        cerr << "mysql_store_result gagal : " << mysql_error(conn) << endl;
        return "";
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    string username = (row) ? row[0]  : "";
    
    mysql_free_result(res);
    return username;
}

void get_books(MYSQL* conn) {
    if (conn) {
        if (mysql_query(conn, "SELECT * FROM books")) {
            cerr << "SELECT gagal : " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result gagal : " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID : " << row[0] << ", Judul : " << row[1] << ", Penulis : " << row[2] << ", Kategori : " << row[3] << ", Status : " << row[4];
            if (row[5]) {
                cout << ", Dipinjam oleh : " << row[5];
            }
            cout << endl;
        }

        mysql_free_result(res);
    }
}

void search_books(MYSQL* conn, const string& keyword) {
    if (conn) {
        string query = "SELECT * FROM books WHERE id = '" + keyword + "' OR title LIKE '%" + keyword + "%'";
        if (mysql_query(conn, query.c_str())) {
            cerr << "SEARCH gagal : " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result gagal : " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID : " << row[0] << ", Judul : " << row[1] << ", Penulis : " << row[2] << ", Kategori : " << row[3] << ", Status : " << row[4];
            if (row[5]) {
                cout << ", Dipinjam oleh : " << row[5];
            }
            cout << endl;
        }

        mysql_free_result(res);
    }
}

void borrow_book(MYSQL* conn, int book_id, int user_id) {
    if (conn) {
        string username = get_username_by_id(conn, user_id);
        if (username.empty()) {
            cout << "Pengguna tidak ditemukan." << endl;
            return;
        }

        stringstream check_query;
        check_query << "SELECT status, borrowed_by FROM books WHERE id = " << book_id;
        if (mysql_query(conn, check_query.str().c_str())) {
            cerr << "CHECK gagal : " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result gagal : " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        if (row && string(row[0]) == "available") {
            stringstream borrow_query;
            borrow_query << "UPDATE books SET status = 'borrowed', borrowed_by = '" << username << "' WHERE id = " << book_id;
            if (mysql_query(conn, borrow_query.str().c_str())) {
                cerr << "BORROW gagal : " << mysql_error(conn) << endl;
            } else {
                cout << "Buku berhasil dipinjam." << endl;
            }
        } else if (row && string(row[0]) == "borrowed") {
            cout << "Buku sudah dipinjam oleh : " << row[1] << endl;
        } else {
            cout << "Buku tidak ditemukan." << endl;
        }

        mysql_free_result(res);
    }
}

string get_password() {
    struct termios oldt, newt;
    string password;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    getline(cin, password);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return password;
}

int login_user() {
    MYSQL* conn = connect_db();
    if (!conn) return -1;

    string username, password;
    cout << "Masukkan nama pengguna : ";
    cin >> username;
    cout << "Masukkan kata sandi : ";
    cin.ignore();
    password = get_password();

    if (authenticate_user(conn, username, password)) {
        cout << "\nLogin berhasil!" << endl;
        cout << "Terhubung ke database dengan sukses." << endl;

        stringstream query;
        query << "SELECT role, id FROM users WHERE username = '" << username << "'";
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "QUERY gagal : " << mysql_error(conn) << endl;
            mysql_close(conn);
            return -1;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result gagal : " << mysql_error(conn) << endl;
            mysql_close(conn);
            return -1;
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        string role = row[0];
        int user_id = atoi(row[1]);

        mysql_free_result(res);
        mysql_close(conn);

        return user_id;
    } else {
        cout << "Nama pengguna atau kata sandi tidak valid." << endl;
        mysql_close(conn);
        return -1;
    }
}

void admin_menu(MYSQL* conn) {
    int choice;
    while (true) {
        cout << "\nMenu Admin :\n";
        cout << "1. Tambah Pengguna\n";
        cout << "2. Tampilkan Semua Pengguna\n";
        cout << "3. Tambah Buku\n";
        cout << "4. Tampilkan Semua Buku\n";
        cout << "5. Perbarui Buku\n";
        cout << "6. Hapus Buku\n";
        cout << "7. Logout\n";
        cout << "8. Keluar\n";
        cout << "Masukkan pilihan : ";
        cin >> choice;

        switch (choice) {
            case 1 : {
                string username, password, role;
                cout << "Masukkan nama pengguna : ";
                cin.ignore();
                getline(cin, username);
                cout << "Masukkan kata sandi : ";
                password = get_password();
                cout << "Masukkan peran (admin/user) : ";
                cin >> role;
                
                stringstream query;
                query << "INSERT INTO users (username, password, role) VALUES ('" << username << "', '" << password << "', '" << role << "')";
                if (mysql_query(conn, query.str().c_str())) {
                    cerr << "INSERT gagal : " << mysql_error(conn) << endl;
                } else {
                    cout << "Pengguna berhasil ditambahkan." << endl;
                }
                break;
            }
            case 2 : {
                if (mysql_query(conn, "SELECT * FROM users")) {
                    cerr << "SELECT gagal : " << mysql_error(conn) << endl;
                    break;
                }

                MYSQL_RES* res = mysql_store_result(conn);
                if (res == nullptr) {
                    cerr << "mysql_store_result gagal : " << mysql_error(conn) << endl;
                    break;
                }

                MYSQL_ROW row;
                while ((row = mysql_fetch_row(res))) {
                    cout << "ID : " << row[0] << ", Nama Pengguna : " << row[1] << ", Password : " << row[2] << ", Peran : " << row[3] << endl;
                }

                mysql_free_result(res);
                break;
            }
            case 3 : {
                string title, author, category;
                cout << "Masukkan judul buku : ";
                cin.ignore();
                getline(cin, title);
                cout << "Masukkan penulis buku : ";
                getline(cin, author);
                cout << "Masukkan kategori buku : ";
                getline(cin, category);

                stringstream query;
                query << "INSERT INTO books (title, author, category, status) VALUES ('" << title << "', '" << author << "', '" << category << "', 'available')";
                if (mysql_query(conn, query.str().c_str())) {
                    cerr << "INSERT gagal : " << mysql_error(conn) << endl;
                } else {
                    cout << "Buku berhasil ditambahkan." << endl;
                }
                break;
            }
            case 4 : {
                get_books(conn);
                break;
            }
            case 5 : {
                int book_id;
                cout << "Masukkan ID buku yang akan diperbarui : ";
                cin >> book_id;
                string title, author, category, status;
                cout << "Masukkan judul buku baru : ";
                cin.ignore();
                getline(cin, title);
                cout << "Masukkan penulis buku baru : ";
                getline(cin, author);
                cout << "Masukkan kategori buku baru : ";
                getline(cin, category);
                cout << "Masukkan status buku baru (available/borrowed) : ";
                getline(cin, status);

                stringstream query;
                query << "UPDATE books SET title = '" << title << "', author = '" << author << "', category = '" << category << "', status = '" << status << "' WHERE id = " << book_id;
                if (mysql_query(conn, query.str().c_str())) {
                    cerr << "UPDATE gagal : " << mysql_error(conn) << endl;
                } else {
                    cout << "Buku berhasil diperbarui." << endl;
                }
                break;
            }
            case 6 : {
                int book_id;
                cout << "Masukkan ID buku yang akan dihapus : ";
                cin >> book_id;

                stringstream query;
                query << "DELETE FROM books WHERE id = " << book_id;
                if (mysql_query(conn, query.str().c_str())) {
                    cerr << "DELETE gagal : " << mysql_error(conn) << endl;
                } else {
                    cout << "Buku berhasil dihapus." << endl;
                }
                break;
            }
            case 7 : {
                cout << "Anda telah logout." << endl;
                return;
            }
            case 8 : {
                cout << "Terima kasih. Keluar dari sistem." << endl;
                exit(0);
            }
            default :
                cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    }
}

void user_menu(MYSQL* conn, int user_id) {
    int choice;
    while (true) {
        cout << "\nMenu Pengguna :\n";
        cout << "1. Tampilkan Semua Buku\n";
        cout << "2. Cari Buku\n";
        cout << "3. Pinjam Buku\n";
        cout << "4. Logout\n";
        cout << "5. Keluar\n";
        cout << "Masukkan pilihan : ";
        cin >> choice;

        switch (choice) {
            case 1 : {
                get_books(conn);
                break;
            }
            case 2 : {
                string keyword;
                cout << "Masukkan ID atau judul buku yang dicari : ";
                cin.ignore();
                getline(cin, keyword);
                search_books(conn, keyword);
                break;
            }
            case 3 : {
                int book_id;
                cout << "Masukkan ID buku yang akan dipinjam : ";
                cin >> book_id;
                borrow_book(conn, book_id, user_id);
                break;
            }
            case 4 : {
                cout << "Anda telah logout." << endl;
                return;
            }
            case 5 : {
                cout << "Terima kasih. Keluar dari sistem." << endl;
                exit(0);
            }
            default :
                cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    }
}

int main() {
    MYSQL* conn = connect_db();
    if (!conn) return 1;

    while (true) {
        int user_id = login_user();
        if (user_id == -1) {
            cout << "Login gagal. Coba lagi." << endl;
            continue;
        }

        stringstream query;
        query << "SELECT role FROM users WHERE id = " << user_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "QUERY gagal : " << mysql_error(conn) << endl;
            mysql_close(conn);
            return 1;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result gagal : " << mysql_error(conn) << endl;
            mysql_close(conn);
            return 1;
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        string role = row[0];
        mysql_free_result(res);

        if (role == "admin") {
            admin_menu(conn);
        } else {
            user_menu(conn, user_id);
        }
    }

    mysql_close(conn);
    return 0;
}