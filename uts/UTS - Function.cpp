#include "UTS - Library.hpp"

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

int unik_Kode(const vector<Barang>& stok) {
    static mt19937 gen(time(0));
    uniform_int_distribution<> dis(1000, 9999999);
    int randomNumber;
    do {
        randomNumber = dis(gen);
    } while (any_of(stok.begin(), stok.end(), [&](const Barang& b) { return b.kode_Barang == to_string(randomNumber); }));
    return randomNumber;
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

// Searching //

void sequentialSearch(const vector<Barang>& stok) {
    systemClose();
    vector<string> targets;
    string targetInput;
    cetak("Masukkan nama/kode barang yang ingin dicari (pisahkan dengan ', ' jika lebih dari satu) : ");
    getline(cin, targetInput);
    kapitalAwal(targetInput);
    istringstream iss(targetInput);
    string target;
    while (getline(iss, target, ',')) {
        target.erase(target.begin(), find_if(target.begin(), target.end(), [](unsigned char ch) { return !isspace(ch); }));
        target.erase(find_if(target.rbegin(), target.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), target.end());
        targets.push_back(target);
    }
    cetak("Sequential Search :\n");
    for (const auto& target : targets) {
        bool found = false;
        const Barang* pointerPak = nullptr;
        for (size_t i = 0; i < stok.size(); ++i) {
            if (stok[i].nama == target || stok[i].kode_Barang == target) {
                pointerPak = &stok[i];
                found = true;
                break;
            }
        }
        if (found) {
            cetak("\tNama/kode barang '", pointerPak->nama, "' ditemukan pada nomor ", to_string(pointerPak - &stok[0] + 1), " (indeks ", pointerPak - &stok[0], ")\n\tHarga Per Barang : Rp ", formatAngka(pointerPak->harga), "\n\n");
        } else {
            cetak("\tNama/kode barang '", target, "' tidak ditemukan.\n\n");
        }
    }
    cetak("\n\n");
}

void binarySearch(const vector<Barang>& stok) {
    systemClose();
    vector<string> targets;
    string targetInput;
    cetak("Masukkan nama/kode barang yang ingin dicari (pisahkan dengan ', ' jika lebih dari satu) : ");
    getline(cin, targetInput);
    kapitalAwal(targetInput);
    istringstream iss(targetInput);
    string target;
    while (getline(iss, target, ',')) {
        target.erase(target.begin(), find_if(target.begin(), target.end(), [](unsigned char ch) { return !isspace(ch); }));
        target.erase(find_if(target.rbegin(), target.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), target.end());
        targets.push_back(target);
    }

    vector<Barang> sortedData = stok;
    sort(sortedData.begin(), sortedData.end(), [](const Barang& a, const Barang& b) {
        return a.nama < b.nama;
    });

    cetak("Binary Search :\n");
    for (const auto& target : targets) {
        int left = 0;
        int right = sortedData.size() - 1;
        bool found = false;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            const Barang* pointerPak = &sortedData[mid];
            if (pointerPak->nama == target || pointerPak->kode_Barang == target) {
                int index = -1;
                for (size_t i = 0; i < stok.size(); ++i) {
                    if (stok[i].nama == pointerPak->nama && stok[i].kode_Barang == pointerPak->kode_Barang) {
                        index = i;
                        break;
                    }
                }
                cetak("\tNama/kode barang '", stok[index].nama, "' ditemukan pada nomor ", to_string(index + 1), " (indeks ", index, ")\n\tHarga Per Barang : Rp ", formatAngka(stok[index].harga), "\n\n");
                found = true;
                break;
            } else if (pointerPak->nama < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (!found) {
            cetak("\tNama/kode barang '", target, "' tidak ditemukan.\n\n");
        }
    }
    cetak("\n\n");
}
