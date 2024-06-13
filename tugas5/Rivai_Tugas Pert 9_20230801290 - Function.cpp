#include "Rivai_Tugas Pert 9_20230801290 - Library.hpp"

void cetak(const string& pesan) {
    cout << pesan;
}

template<typename T, typename... Args>
void cetak(const string& pesan, const T& value, const Args&... args) {
    stringstream ss;
    ss << value;
    cetak(pesan + ss.str(), args...);
}

void gerakGaris(const string& kata, int jumlah) {
    int garis = jumlah;
    while (garis--) {
        cetak(kata);
        Sleep(5);
    }
}

void systemClose() {
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}

void systemPause() {
    #ifdef _WIN32
        system("pause");
    #else
        system("read -p 'Press Enter to continue...' key");
    #endif
}

string formatAngka(int angka) {
    stringstream ss;
    ss << fixed << setprecision(0) << angka;
    string strAngka = ss.str();
    string hasil;
    int n = strAngka.length();
    int counter = 0;
    for (int i = n - 1; i >= 0; i--) {
        hasil = strAngka[i] + hasil;
        counter++;
        if (counter == 3 && i > 0) {
            hasil = "." + hasil;
            counter = 0;
        }
    }
    return hasil;
}

int getValidInt() {
    char buffer[100];
    int validInput, value;
    do {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
                len--;
            }
            validInput = 0;
            for (size_t i = 0; i < len; i++) {
                if (!isspace(buffer[i])) {
                    validInput = 1;
                    break;
                }
            }
            if (!validInput) {
                cetak("Masukkan Angka : ");
                continue;
            }
            validInput = 1;
            for (size_t i = 0; i < len; i++) {
                if (i == 0 && buffer[i] == '-') {
                    continue;
                }
                if (!isdigit(buffer[i])) {
                    validInput = 0;
                    break;
                }
            }
            if (validInput) {
                sscanf(buffer, "%d", &value);
            } else {
                cetak("Masukkan Angka Bukan Huruf/Simbol : ");
            }
        }
    } while (!validInput);
    return value;
}

bool isValidString(const string& str) {
    bool valid = true;
    bool alphabeticFound = false;
    for (char c : str) {
        if (isalpha(c)) {
            alphabeticFound = true;
        } else if (!isspace(c) && !isdigit(c)) {
            valid = false;
            break;
        }
    }
    return valid && alphabeticFound;
}

void getValidString(string& str) {
    bool valid = false;
    do {
        getline(cin, str);
        bool onlyEnter = true;
        for (char c : str) {
            if (!isspace(c)) {
                onlyEnter = false;
                break;
            }
        }
        if (onlyEnter) {
            cetak("Masukkan Hanya Huruf : ");
            continue;
        }
        if (!isValidString(str)) {
            cetak("Masukkan Hanya Huruf Dan Spasi, Angka Setelah Huruf Diperbolehkan : ");
            continue;
        }
        valid = true;
    } while (!valid);
}

void noticeDefault() {
    cetak("Masukkan Dengan Benar\n");
    cetak("Silahkan Coba Lagi.");
    getch();
    systemClose();
}

void hitungMundur(int count) {
	cetak("\nProgram Keclose dalam ");
    for (int i = count; i >= 0; --i) {
        cetak(to_string(i));
        this_thread::sleep_for(chrono::seconds(1));
        for (size_t j = 0; j < 1; ++j) {
            cetak("\b \b");
        }
    }
}

void noticeExit() {
	systemClose();
    cetak("Terima Kasih Telah Menggunakan >_<");
    thread afkSebentar(hitungMundur, 3);
    afkSebentar.join();
    DWORD pid = GetCurrentProcessId();
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    GenerateConsoleCtrlEvent(CTRL_C_EVENT, pid);
    TerminateProcess(hProcess, 0);
    CloseHandle(hProcess);
    exit(EXIT_SUCCESS);
}
