#include "uas-header.hpp"

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
            cout << "ID : " << row[0] << "\nJudul : " << row[1] << "\nPenulis : " << row[2] << "\nKategori : " << row[3] << "\nStatus : " << row[4] << "\nQuantity : " << row[5] << endl;

            stringstream borrowers_query;
            borrowers_query << "SELECT u.username FROM book_borrowers bb JOIN users u ON bb.user_id = u.id WHERE bb.book_id = " << row[0];
            if (mysql_query(conn, borrowers_query.str().c_str())) {
                cerr << "QUERY gagal : " << mysql_error(conn) << endl;
                continue;
            }

            MYSQL_RES* borrowers_res = mysql_store_result(conn);
            if (borrowers_res == nullptr) {
                cerr << "mysql_store_result gagal : " << mysql_error(conn) << endl;
                continue;
            }

            MYSQL_ROW borrower_row;
            if (mysql_num_rows(borrowers_res) > 0) {
                cout << "Dipinjam oleh : \n";
                while ((borrower_row = mysql_fetch_row(borrowers_res))) {
                    cout << "- " << borrower_row[0] << endl;
                }
                cout << endl;
            }

            mysql_free_result(borrowers_res);
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
            cout << "ID : " << row[0] << ", \nJudul : " << row[1] << ", \nPenulis : " << row[2] << ", \nKategori : " << row[3] << ", \nStatus : " << row[4] << ", \nQuantity : " << row[5];

            stringstream borrowers_query;
            borrowers_query << "SELECT u.username FROM book_borrowers bb JOIN users u ON bb.user_id = u.id WHERE bb.book_id = " << row[0];
            if (mysql_query(conn, borrowers_query.str().c_str())) {
                cerr << "QUERY gagal : " << mysql_error(conn) << endl;
                continue;
            }

            MYSQL_RES* borrowers_res = mysql_store_result(conn);
            if (borrowers_res == nullptr) {
                cerr << "mysql_store_result gagal : " << mysql_error(conn) << endl;
                continue;
            }

            MYSQL_ROW borrower_row;
            if (mysql_num_rows(borrowers_res) > 0) {
                cout << "Dipinjam oleh : \n";
                while ((borrower_row = mysql_fetch_row(borrowers_res))) {
                    cout << "- " << borrower_row[0] << endl;
                }
                cout << endl;
            }

            mysql_free_result(borrowers_res);
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
        check_query << "SELECT status, quantity FROM books WHERE id = " << book_id;
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
        if (row && string(row[0]) == "available" && atoi(row[1]) > 0) {
            stringstream borrow_query;
            borrow_query << "UPDATE books SET quantity = quantity - 1 WHERE id = " << book_id;
            if (mysql_query(conn, borrow_query.str().c_str())) {
                cerr << "BORROW gagal : " << mysql_error(conn) << endl;
            } else {
                stringstream insert_borrow_query;
                insert_borrow_query << "INSERT INTO book_borrowers (book_id, user_id) VALUES (" << book_id << ", " << user_id << ")";
                if (mysql_query(conn, insert_borrow_query.str().c_str())) {
                    cerr << "INSERT gagal : " << mysql_error(conn) << endl;
                }

                if (atoi(row[1]) - 1 == 0) {
                    stringstream status_query;
                    status_query << "UPDATE books SET status = 'unavailable' WHERE id = " << book_id;
                    if (mysql_query(conn, status_query.str().c_str())) {
                        cerr << "UPDATE STATUS gagal : " << mysql_error(conn) << endl;
                    }
                }
                cout << "Buku berhasil dipinjam." << endl;
            }
        } else if (row && string(row[0]) == "unavailable") {
            cout << "Buku sudah tidak tersedia." << endl;
        } else {
            cout << "Buku tidak ditemukan." << endl;
        }

        mysql_free_result(res);
    }
}

void return_book(MYSQL* conn, int book_id, int user_id) {
    if (conn) {
        stringstream check_query;
        check_query << "SELECT quantity FROM books WHERE id = " << book_id;
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
        if (row) {
            stringstream delete_borrow_query;
            delete_borrow_query << "DELETE FROM book_borrowers WHERE book_id = " << book_id << " AND user_id = " << user_id;
            if (mysql_query(conn, delete_borrow_query.str().c_str())) {
                cerr << "DELETE gagal : " << mysql_error(conn) << endl;
            }

            stringstream return_query;
            return_query << "UPDATE books SET quantity = quantity + 1 WHERE id = " << book_id;
            if (mysql_query(conn, return_query.str().c_str())) {
                cerr << "RETURN gagal : " << mysql_error(conn) << endl;
            } else {
                if (atoi(row[0]) == 0) {
                    stringstream status_query;
                    status_query << "UPDATE books SET status = 'available' WHERE id = " << book_id;
                    if (mysql_query(conn, status_query.str().c_str())) {
                        cerr << "UPDATE STATUS gagal : " << mysql_error(conn) << endl;
                    }
                }
                cout << "Buku berhasil dikembalikan." << endl;
            }
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
        cout << "\nNama pengguna atau kata sandi tidak valid." << endl;
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
        cout << endl;

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
                int quantity;
                cout << "Masukkan judul buku : ";
                cin.ignore();
                getline(cin, title);
                cout << "Masukkan penulis buku : ";
                getline(cin, author);
                cout << "Masukkan kategori buku : ";
                getline(cin, category);
                cout << "Masukkan quantity buku : ";
                cin >> quantity;

                stringstream check_query;
                check_query << "SELECT quantity FROM books WHERE title = '" << title << "'";
                if (mysql_query(conn, check_query.str().c_str())) {
                    cerr << "CHECK QUERY gagal : " << mysql_error(conn) << endl;
                    break;
                }

                MYSQL_RES* res = mysql_store_result(conn);
                if (res == nullptr) {
                    cerr << "mysql_store_result gagal : " << mysql_error(conn) << endl;
                    break;
                }

                MYSQL_ROW row = mysql_fetch_row(res);
                if (row) {
                    stringstream update_query;
                    update_query << "UPDATE books SET quantity = quantity + " << quantity << " WHERE title = '" << title << "'";
                    if (mysql_query(conn, update_query.str().c_str())) {
                        cerr << "UPDATE gagal : " << mysql_error(conn) << endl;
                    } else {
                        cout << "Quantity buku berhasil diperbarui." << endl;
                    }
                } else {
                    stringstream insert_query;
                    insert_query << "INSERT INTO books (title, author, category, status, quantity) VALUES ('" << title << "', '" << author << "', '" << category << "', 'available', " << quantity << ")";
                    if (mysql_query(conn, insert_query.str().c_str())) {
                        cerr << "INSERT gagal : " << mysql_error(conn) << endl;
                    } else {
                        cout << "Buku berhasil ditambahkan." << endl;
                    }
                }

                mysql_free_result(res);
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
                int quantity;
                cout << "Masukkan judul buku baru : ";
                cin.ignore();
                getline(cin, title);
                cout << "Masukkan penulis buku baru : ";
                getline(cin, author);
                cout << "Masukkan kategori buku baru : ";
                getline(cin, category);
                cout << "Masukkan status buku baru (available/unavailable) : ";
                getline(cin, status);
                cout << "Masukkan quantity buku baru : ";
                cin >> quantity;

                stringstream query;
                query << "UPDATE books SET title = '" << title << "', author = '" << author << "', category = '" << category << "', status = '" << status << "', quantity = " << quantity << " WHERE id = " << book_id;
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
        cout << "4. Kembalikan Buku\n";
        cout << "5. Logout\n";
        cout << "6. Keluar\n";
        cout << "Masukkan pilihan : ";
        cin >> choice;
        cout << endl;

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
                int book_id;
                cout << "Masukkan ID buku yang akan dikembalikan : ";
                cin >> book_id;
                return_book(conn, book_id, user_id);
                break;
            }
            case 5 : {
                cout << "Anda telah logout." << endl;
                return;
            }
            case 6 : {
                cout << "Terima kasih. Keluar dari sistem." << endl;
                exit(0);
            }
            default :
                cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    }
}