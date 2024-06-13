## Penjelasan Program ##
Berikut adalah penjelasan lengkap mengenai program di atas yang diimplementasikan menggunakan beberapa file kode C++ :

### Struktur Direktori dan File
- `Rivai_Tugas Pert 9_20230801290 - Library.hpp`
- `Rivai_Tugas Pert 9_20230801290 - Function.cpp`
- `Rivai_Tugas Pert 9_20230801290 - Inti.cpp`
- `Rivai_Tugas Pert 9_20230801290 - Main.cpp`

### File: `Rivai_Tugas Pert 9_20230801290 - Library.hpp`

```cpp
#ifndef PUSTAKA_HPP
#define PUSTAKA_HPP
#define Rivai_Munte main

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <conio.h>
#include <windows.h>
#include <stack>
#include <string>
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>
using namespace std;

struct Buku {
    string judul;
    string penulis;
    int tahunTerbit;
};

void sistemMenu();
void sistemSubMenu(void (*targetFunction)());

#endif
```

**Penjelasan:**
- Header guard (`#ifndef PUSTAKA_HPP ... #endif`) digunakan untuk mencegah multiple inclusions.
- `#define Rivai_Munte main` mendefinisikan alias untuk fungsi `main`.
- Mengimpor beberapa library standar C++ dan Windows-specific untuk menangani berbagai operasi.
- Mendefinisikan struktur `Buku` untuk menyimpan informasi buku.
- Deklarasi dua fungsi: `sistemMenu` dan `sistemSubMenu`.

### File: `Rivai_Tugas Pert 9_20230801290 - Function.cpp`

```cpp
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
```

**Penjelasan:**
- `cetak` adalah fungsi template untuk mencetak pesan ke konsol.
- `gerakGaris` untuk mencetak garis secara perlahan.
- `systemClose` dan `systemPause` untuk membersihkan dan menjeda konsol.
- `formatAngka` untuk memformat angka dengan titik ribuan.
- `getValidInt` untuk mendapatkan input integer yang valid dari pengguna.
- `isValidString` dan `getValidString` untuk memvalidasi dan mendapatkan input string yang valid.
- `noticeDefault` untuk memberikan pemberitahuan kesalahan input.
- `hitungMundur` dan `noticeExit` untuk menangani penghentian program dengan hitungan mundur.

### File: `Rivai_Tugas Pert 9_20230801290 - Inti.cpp`

```cpp
#include "Rivai_Tugas Pert 9_20230801290 - Function.cpp"

class KelolaTumpukanBuku {
private:
    string judul, penulis;
    int tahunTerbit;
    stack<Buku> tumpukanBuku;

protected:
    void tampilkanInfoBuku(const Buku& buku) {
        cetak("Judul : ", buku.judul);
        cetak("\nPenulis : ", buku.penulis);
        cetak("\nTahun Terbit : ", buku.tahunTerbit, "\n\n\n");
    }

public:
    void tambahBuku(const Buku& buku) {
        tumpukanBuku.push(buku);
        cetak("Buku berhasil ditambahkan ke dalam tumpukan.\n\n\n");
    }

    void hapusBuku() {
        systemClose();
        if (!tumpukanBuku.empty()) {
            tumpukanBuku.pop();
            cetak("Buku paling atas berhasil dihapus dari tumpukan.\n\n\n");
        } else {
            cetak("Tumpukan buku kosong. Tidak ada buku yang bisa dihapus.\n\n\n");
        }
    }

    void lihatBukuPalingAtas() {
        systemClose();
        if (!tumpukanBuku.empty()) {
            Buku bukuPalingAtas = tumpukanBuku.top();
            tampilkanInfoBuku(bukuPalingAtas);
        } else {
            cetak("Tumpukan buku kosong. Tidak ada buku yang bisa dilihat.\n\n\n");
        }
    }

    bool apakahTumpukanKosong() {
        return tumpukanBuku.empty();
    }

    int ukuranTumpukan() {
        return tumpukanBuku.size();
    }

    void tambahBuku2() {
        systemClose();
        cetak("Masukkan judul buku : ");
        getValidString(judul);
        cetak("Masukkan penulis buku : ");
        getValidString(penulis);
        cetak("Masukan tahun terbit buku : ");
        tahunTerbit = getValidInt();
        Buku buku = {judul, penulis, tahunTerbit};
        tambahBuku(buku);


    }

    void cekTumpukanBuku() {
        systemClose();
        if (apakahTumpukanKosong()) {
            cetak("Tumpukan buku kosong.\n\n\n");
        } else {
            cetak("Tumpukan buku tidak kosong.\n\n\n");
        }
    }

    void ukuranTumpukanBuku() {
        systemClose();
        cetak("Ukuran tumpukan buku : ", ukuranTumpukan(), "\n\n\n");
    }
};

KelolaTumpukanBuku kelolaTumpukan;

void sistemMenu() {
    string _Menu;
    systemClose();
    gerakGaris("=", 100);
    cetak("\n\t\t\t\tAplikasi Beta Sudah Dekat ^_^\n");
    gerakGaris("=", 100);
    cetak("\n1. Tambah Buku\n");
    cetak("2. Hapus Buku\n");
    cetak("3. Lihat Buku Paling Atas\n");
    cetak("4. Cek Apakah Tumpukan Kosong\n");
    cetak("5. Lihat Ukuran Tumpukan\n");
    cetak("6. Keluar Aplikasi\n");
    cetak("\nMasukkan Pilihan Menu Sesuai Nomor Menu Atau Tulis Nama Menunya : ");
    getline(cin, _Menu);

    if (_Menu == "1" || _Menu == "tambah buku") {
        kelolaTumpukan.tambahBuku2();
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "2" || _Menu == "hapus buku") {
        kelolaTumpukan.hapusBuku();
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "3" || _Menu == "lihat buku paling atas") {
        kelolaTumpukan.lihatBukuPalingAtas();
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "4" || _Menu == "cek apakah tumpukan kosong") {
        kelolaTumpukan.cekTumpukanBuku();
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "5" || _Menu == "lihat ukuran tumpukan") {
        kelolaTumpukan.ukuranTumpukanBuku();
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "6" || _Menu == "keluar aplikasi") {
        noticeExit();
    } else {
        noticeDefault();
        sistemMenu();
    }
}

void sistemSubMenu(void (*targetFunction)()) {
    string subMenu;
    gerakGaris("=", 100);
    cetak("\n\t\t\t\t\t   Pilihan Menu\n");
    gerakGaris("=", 100);
    cetak("\n1. Kembali Ke Awal\n");
    cetak("2. Keluar Aplikasi\n");
    cetak("\nMasukkan Pilihan Menu Sesuai Nomor Menu Atau Tulis Nama Menunya : ");
    getline(cin, subMenu);

    if (subMenu == "1" || subMenu == "kembali ke awal") {
        (*targetFunction)();
    } else if (subMenu == "2" || subMenu == "keluar aplikasi") {
        noticeExit();
    } else {
        noticeDefault();
        sistemSubMenu(targetFunction);
    }
}
```

**Penjelasan:**
- `KelolaTumpukanBuku` adalah kelas yang mengelola stack buku dengan beberapa metode untuk menambah, menghapus, melihat buku paling atas, memeriksa apakah stack kosong, dan mendapatkan ukuran stack.
- `sistemMenu` adalah fungsi untuk menampilkan menu utama dan mengarahkan pengguna berdasarkan pilihan mereka.
- `sistemSubMenu` adalah fungsi untuk menampilkan submenu setelah tindakan utama dilakukan, memberikan opsi untuk kembali ke menu awal atau keluar dari aplikasi.

### File: `Rivai_Tugas Pert 9_20230801290 - Main.cpp`

```cpp
#include "Rivai_Tugas Pert 9_20230801290 - Inti.cpp"

int Rivai_Munte() {
    sistemMenu();
}
```

**Penjelasan:**
- Mengimpor `Inti.cpp` untuk mengakses semua fungsi dan kelas yang didefinisikan.
- Mendefinisikan fungsi utama dengan alias `Rivai_Munte` yang menjalankan fungsi `sistemMenu` untuk memulai program.

### Cara Kerja Program
1. **Inisialisasi**: Program dimulai dari `Rivai_Munte` yang memanggil `sistemMenu`.
2. **Menu Utama**: Pengguna disajikan dengan beberapa pilihan menu untuk mengelola tumpukan buku.
3. **Operasi Tumpukan Buku**: Pengguna dapat menambah buku, menghapus buku, melihat buku paling atas, memeriksa apakah tumpukan kosong, atau melihat ukuran tumpukan.
4. **Sub Menu**: Setelah melakukan operasi, pengguna diberikan pilihan untuk kembali ke menu utama atau keluar dari aplikasi.
5. **Keluar**: Jika pengguna memilih untuk keluar, program menampilkan pesan terima kasih dan menutup aplikasi dengan hitungan mundur.

### Ringkasan
Program ini menggunakan beberapa file header dan implementasi untuk mengelola tumpukan buku menggunakan stack. Program memberikan antarmuka menu untuk pengguna dengan berbagai opsi untuk menambah, menghapus, melihat, dan memeriksa tumpukan buku. Program juga menangani validasi input dan memberikan pesan yang sesuai untuk memastikan operasi yang valid.