/*
KELOMPOK 7 - SESI CR001 :
		1. Rivai - 20230801290
		2. Chandika Eka Prasetya - 20230801268
		3. Yodan Muhammad Surya Adhe - 20230801424
		4. Muhamad Iqbal Al Kautsar - 20230801032
		5. Fandi Fajar Maulana-20230801157
*/

#include "Pra-UTS - Library.hpp"

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

string formatAngka(float angka) {
    stringstream ss;
    ss << fixed << setprecision(2) << angka;
    string formatted = ss.str();
    size_t pos = formatted.find(".");
    if (pos != string::npos) {
        string beforeDot = formatted.substr(0, pos);
        string afterDot = formatted.substr(pos + 1);
        int len = beforeDot.length();
        for (int i = len - 3; i > 0; i -= 3) {
            beforeDot.insert(i, ".");
        }
        formatted = beforeDot + "," + afterDot;
    }
    return formatted;
}

float getValidFloat() {
    char buffer[100];
    float value;
    int validInput;
    do {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
                len--;
            }
            validInput = 0;
            int dotCount = 0;
            for (size_t i = 0; i < len; i++) {
                if (!isspace(buffer[i])) {
                    validInput = 1;
                    if (buffer[i] == '.') {
                        dotCount++;
                    } else if (!isdigit(buffer[i])) {
                        validInput = 0;
                        break;
                    }
                }
            }
            if (validInput && dotCount <= 1 && !(dotCount == 1 && len == 1 && buffer[0] == '.')) {
                sscanf(buffer, "%f", &value);
            } else {
                cetak("Input Tidak Valid. Harap Masukkan Angka Yang Benar : ");
                validInput = 0;
            }
        }
    } while (!validInput);
    return value;
}

string formatAngka(double angka) {
    stringstream ss;
    ss << fixed << setprecision(2) << angka;
    string formatted = ss.str();
    size_t pos = formatted.find(".");
    if (pos != string::npos) {
        string beforeDot = formatted.substr(0, pos);
        string afterDot = formatted.substr(pos + 1);
        int len = beforeDot.length();
        for (int i = len - 3; i > 0; i -= 3) {
            beforeDot.insert(i, ".");
        }
        formatted = beforeDot + "," + afterDot;
    }
    return formatted;
}

double getValidDouble() {
    char buffer[100];
    double value;
    int validInput;
    do {
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
                len--;
            }
            validInput = 0;
            int dotCount = 0;
            for (size_t i = 0; i < len; i++) {
                if (!isspace(buffer[i])) {
                    validInput = 1;
                    if (buffer[i] == '.') {
                        dotCount++;
                    } else if (!isdigit(buffer[i])) {
                        validInput = 0;
                        break;
                    }
                }
            }
            if (validInput && dotCount <= 1 && !(dotCount == 1 && len == 1 && buffer[0] == '.')) {
                sscanf(buffer, "%lf", &value);
            } else {
                cetak("Input Tidak Valid. Harap Masukkan Angka Yang Benar : ");
                validInput = 0;
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

void kapitalAwal(string& str) {
    int len = str.length();
    bool wordStart = true;
    for (int i = 0; i < len; i++) {
        if (isalpha(str[i])) {
            if (wordStart) {
                str[i] = toupper(str[i]);
                wordStart = false;
            } else {
                str[i] = tolower(str[i]);
            }
        } else {
            wordStart = true;
        }
    }
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

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int hitungTotal(int* arr, int size) {
    int total = 0;
    for (int i = 0; i < size; ++i) {
        total += arr[i];
    }
    return total;
}

int cariMaksimum(int* arr, int size) {
    if (size == 0) {
        return -1;
    }
    int maksimum = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > maksimum) {
            maksimum = arr[i];
        }
    }
    return maksimum;
}

int cariMinimum(int* arr, int size) {
    if (size == 0) {
        return -1;
    }
    int minimum = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < minimum) {
            minimum = arr[i];
        }
    }
    return minimum;
}

unsigned long long hitungFaktorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * hitungFaktorial(n - 1);
}
