#include "uas-header.hpp"

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