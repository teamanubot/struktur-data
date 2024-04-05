#include "Struktur Data Tugas 2 - Pustaka.hpp"

void gerakGaris(const string& kata, int jumlah) {
    int garis = jumlah;
    while (garis--) {
        cout << kata;
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
                cout << "Masukkan Angka : ";
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
                cout << "Masukkan Angka Bukan Huruf/Simbol : ";
            }
        }
    } while (!validInput);
    return value;
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
                cout << "Input tidak valid. Harap masukkan angka yang benar : ";
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
            cout << "Masukkan hanya huruf : ";
            continue;
        }
        if (!isValidString(str)) {
            cout << "Masukkan hanya huruf dan spasi, angka setelah huruf diperbolehkan : ";
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
    cout << "Masukkan Dengan Benar" << endl;
    cout << "Silahkan Coba Lagi." << endl;
    getch();
    systemClose();
}

void noticeExit(){
    systemClose();
    cout << "Terima Kasih Telah Menggunakan >_<";
    exit;
}

void konsep_Buku() {
	systemClose();
	konsepBuku konsepBuku1;
	cout << "Masukkan Judul Buku : ";
	getValidString(konsepBuku1.judul);
	kapitalAwal(konsepBuku1.judul);
	cout << "Masukkan Nama Pengarang : ";
	getValidString(konsepBuku1.pengarang);
	kapitalAwal(konsepBuku1.pengarang);
	cout << "Masukkan Tahun Penerbit : ";
    konsepBuku1.tahunPenerbit = getValidInt();
    cout << "\n\n===================================================" << endl;
    cout << "Judul Buku : " << konsepBuku1.judul << endl;
    cout << "Nama Pengarang : " << konsepBuku1.pengarang << endl;
    cout << "Tahun Penerbit : " << konsepBuku1.tahunPenerbit << endl;
    cout << "===================================================\n\n" << endl;
}

void rating_Film() {
	systemClose();
	ratingFilm ratingFilm1;
	cout << "Masukkan Judul Film : ";
	getValidString(ratingFilm1.judul);
	kapitalAwal(ratingFilm1.judul);
	cout << "Masukkan Nama Sutradara : ";
	getValidString(ratingFilm1.sutradara);
	kapitalAwal(ratingFilm1.sutradara);
	cout << "Masukkan Tahun Rilis : ";
    ratingFilm1.tahunRilis = getValidInt();
    cout << "Masukkan Rating Film : ";
    ratingFilm1.rating = getValidFloat();
    cout << "\n\n===================================================" << endl;
    cout << "Judul Film : " << ratingFilm1.judul << endl;
    cout << "Nama Sutradara : " << ratingFilm1.sutradara << endl;
    cout << "Tahun Rilis : " << ratingFilm1.tahunRilis << endl;
    cout << "Rating Film : " << ratingFilm1.rating << endl;
    cout << "===================================================\n\n" << endl;
}

string getProdukString(Produk produk) {
    switch (produk) {
        case Elektronik:
            return "Elektronik";
        case Pakaian:
            return "Pakaian";
        case Makanan:
            return "Makanan";
        case Minuman:
            return "Minuman";
        case AlatTulis:
            return "Alat Tulis";
        case Perabotan:
            return "Perabotan";
        default:
            return "Entitas Tidak Diketahui";
    }
}

void isiDataBarang(stockBarang &barang) {
	systemClose();
    cout << "Masukkan Nama Barang    : ";
    getValidString(barang.nama_barang);
    kapitalAwal(barang.nama_barang);
    cout << "Masukkan Kode Barang    : ";
    barang.kode_barang = getValidInt();
    cout << "Masukkan Jenis Barang   : ";
    getValidString(barang.jenis_barang);
    kapitalAwal(barang.jenis_barang);
    int pilihan;
    do {
        cout << "\nPilih Tipe Produk\n1: Elektronik\n2: Pakaian\n3: Makanan\n4: Minuman\n5: Alat Tulis\n6: Perabotan\nMasukkan angka pada tipe produk : ";
        pilihan = getValidInt();
        if (pilihan < 1 || pilihan > 6) { 
            cout << "Pilihan tidak valid. Silahkan masukkan lagi." << endl;
        }
    } while (pilihan < 1 || pilihan > 6);
    barang.tipe_produk = static_cast<Produk>(pilihan - 1);
    cout << "Masukkan Harga Barang   : ";
    barang.harga_barang = getValidInt();
}

void tampilkanBarang(const vector<stockBarang> &barangList) {
    systemClose();
    cout << "===============================================" << endl;
    for (const auto &barang : barangList) {
        cout << "Nama Barang    : " << barang.nama_barang << endl;
        cout << "Kode Barang    : " << barang.kode_barang << endl;
        cout << "Jenis Barang   : " << barang.jenis_barang << endl;
        cout << "Tipe Produk    : " << getProdukString(barang.tipe_produk) << endl;
        cout << "Harga Barang   : " << barang.harga_barang << endl;
        cout << "===============================================" << endl;
    }
}

void stock_Barang() {
	vector<stockBarang> barangList;
    char lanjut;
    int pilihan;
    do {
    	systemClose();
        cout << "1. Tambah Barang" << endl;
        cout << "2. Tampilkan Barang" << endl;
        cout << "Pilih menu : ";
        pilihan = getValidInt();
        if (pilihan == 1) {
            do {
                stockBarang barang;
                isiDataBarang(barang);
                barangList.push_back(barang);
                cout << "Ingin menambah barang lagi? (y/n) ";
                cin >> lanjut;
                cin.ignore();
            } while (lanjut == 'y' || lanjut == 'Y');
            cout << "\n\n";
        }
        else if (pilihan == 2) {
            tampilkanBarang(barangList);
        }
        cout << "Lanjut Ke Menu Awal? (y/n) ";
        cin >> lanjut;
        cin.ignore();
    } while (lanjut == 'y' || lanjut == 'Y');
    cout << "\n\n";
    exit;
}

void input_User() {
	Student student1;
    systemClose();
    cout << "==================================" << endl;
    cout << "+++++++ CONTOH INPUT USER ++++++++" << endl;
    cout << "==================================\n" << endl;
    cout << "Masukan Nama   : ";
    getValidString(student1.name);
    kapitalAwal(student1.name);
    cout << "Masukan Umur  : ";
    student1.age = getValidInt();
    cout << "Masukan Nilai : ";
    student1.grade = getValidInt();
    systemClose();
    cout << "Masukan alamat jalan : ";
    getValidString(student1.address.street);
    kapitalAwal(student1.address.street);
    cout << "Masukan Kota         : ";
    getValidString(student1.address.city);
    kapitalAwal(student1.address.city);
    cout << "Masukan Provinsi     : ";
    getValidString(student1.address.state);
    kapitalAwal(student1.address.state);
    cout << "Masukan kode POS     : ";
    student1.address.zip = getValidInt();
    systemClose();
    cout << "=====================================" << endl;
    cout << "Informasi Mahasiswa:" << endl;
    cout << "Name  : " << student1.name << endl;
    cout << "Umur  : " << student1.age << endl;
    cout << "Nilai : " << student1.grade << endl;
    cout << "=====================================\n" << endl;
    cout << "=====================================" << endl;
    cout << "Alamat:" << endl;
    cout << "Jalan    : " << student1.address.street << endl;
    cout << "Kota     : " << student1.address.city << endl;
    cout << "Negara   : " << student1.address.state << endl;
    cout << "Kode POS : " << student1.address.zip << endl;
    cout << "=====================================" << endl;
}

void sistemMenu() {
    string _Menu;
    systemClose();
    gerakGaris("=", 100);
    cout << "\n\t\t\t\tAplikasi Beta Sudah Dekat ^_^\n";
    gerakGaris("=", 100);
    cout << "\n1. Konsep Buku\n";
    cout << "2. Rating Film\n";
    cout << "3. Stock Barang\n";
    cout << "4. Input User\n";
    cout << "5. Keluar Aplikasi\n";
    cout << "\nMasukkan Pilihan Menu Sesuai Nomor Menu Atau Tulis Nama Menunya : ";
    getline(cin, _Menu);

    if (_Menu == "1" || _Menu == "konsep buku") {
    	konsep_Buku();
        sistemSubMenu();
    } else if (_Menu == "2" || _Menu == "rating film") {
    	rating_Film();
        sistemSubMenu();
    } else if (_Menu == "3" || _Menu == "stock barang") {
    	stock_Barang();
        sistemSubMenu();
    } else if (_Menu == "4" || _Menu == "input user") {
    	input_User();
        sistemSubMenu();
    } else if (_Menu == "5" || _Menu == "keluar aplikasi") {
        noticeExit();
    } else {
        noticeDefault();
        sistemMenu();
    }
}

void sistemSubMenu() {
    string subMenu;
    gerakGaris("=", 100);
    cout << "\n\t\t\t\t\t   Pilihan Menu\n";
    gerakGaris("=", 100);
    cout << "\n1. Kembali Ke Awal\n";
    cout << "2. Keluar Aplikasi\n";
    cout << "\nMasukkan Pilihan Menu Sesuai Nomor Menu Atau Tulis Nama Menunya : ";
    getline(cin, subMenu);

    if (subMenu == "1" || subMenu == "kembali ke awal") {
        sistemMenu();
    } else if (subMenu == "2" || subMenu == "keluar aplikasi") {
        noticeExit();
    } else {
        noticeDefault();
        sistemSubMenu();
    }
}
