#include "UTS - Function.cpp"

void tambahStok(vector<Barang>& stok) {
    systemClose();
    Barang barangBaru;
    cetak("Masukkan Nama Barang : ");
    getValidString(barangBaru.nama);
    kapitalAwal(barangBaru.nama);
    bool barangDitemukan = false;
    for (auto& barang : stok) {
        if (barang.nama == barangBaru.nama) {
            cetak("Masukkan Jumlah Barang Yang Ingin Ditambahkan : ");
            barangBaru.jumlah = getValidInt();
            barang.jumlah += barangBaru.jumlah;
            barangDitemukan = true;
            cetak("Jumlah Barang Berhasil Ditambahkan.\n\n\n");
            break;
        }
    }
    if (!barangDitemukan) {
    	barangBaru.kode_Barang = to_string(unik_Kode(stok));
        cetak("Masukkan Jumlah Barang : ");
        barangBaru.jumlah = getValidInt();
        cetak("Masukkan Harga Per Barang : Rp ");
        barangBaru.harga = getValidFloat();
        stok.push_back(barangBaru);
        dataPermanen.push_back(barangBaru);
        cetak("Stok Barang Berhasil Ditambahkan.\n\n\n");
    }
}

void ubahHarga(vector<Barang>& stok) {
    systemClose();
    string namaBarang;
    float hargaBaru;
    cetak("Masukkan Nama Barang Yang Akan Diubah Harganya : ");
    getValidString(namaBarang);
    kapitalAwal(namaBarang);
    bool barangDitemukan = false;
    for (auto& barang : stok) {
        if (barang.nama == namaBarang) {
            cetak("Masukkan Harga Baru : Rp ");
            hargaBaru = getValidFloat();
            barang.harga = hargaBaru;
            barangDitemukan = true;
            cetak("Harga Barang Berhasil Diubah.\n\n\n");
            break;
        }
    }
    if (!barangDitemukan) {
        cetak("Nama Barang Tidak Ditemukan Dalam Stok.\n\n\n");
    }
}


void cetakStok(const std::vector<Barang>& stok) {
    systemClose();
    if (stok.empty()) {
        cetak("Stok barang kosong.\n\n\n");
    } else {
        cetak("Informasi Stok Barang\n\n");
        for (size_t i = 0; i < stok.size(); ++i) {
            const Barang& barang = stok[i];
            cetak(to_string(i + 1), ". Nama Barang : ", barang.nama, "\n");
            cetak("   - Kode Barang : ", barang.kode_Barang, "\n");
            cetak("   - Jumlah Barang : ", formatAngka(barang.jumlah), "\n");
            cetak("   - Harga Per Barang : Rp ", formatAngka(barang.harga), "\n\n");
        }
        cetak("\n\n");
    }
}

//// Sorting ////

void ubahPosisi(vector<Barang>& stok) {
    reverse(stok.begin(), stok.end());
    sistemMenu();
}

void ubahPosisiAbjad(vector<Barang>& stok) {
    sort(stok.begin(), stok.end(), [](const Barang& a, const Barang& b) {
        return a.nama < b.nama;
    });
    sistemMenu();
}

void resetPosisi(vector<Barang>& stok, const vector<Barang>& dataPermanen) {
    stok = dataPermanen;
    sistemMenu();
}

//// Sorting ////

void sistemMenu() {
    string _Menu;
    systemClose();
    gerakGaris("=", 100);
    cetak("\n\t\t\t\tRivai - 20230801290\n");
    cetak("\t\t\t\tUTS - Struktur Data\n");
    gerakGaris("=", 100);
    cetak("\n1. Tambah Barang\n");
    cetak("2. Ubah Harga Barang\n");
    cetak("3. List Stok Barang\n");
    cetak("4. Sorting Abjad\n");
    cetak("5. Sorting Reverse\n");
    cetak("6. Reset Sorting\n");
    cetak("7. Sequential Search\n");
    cetak("8. Binary Search\n");
    cetak("9. Keluar Aplikasi\n");
    cetak("\nMasukkan Pilihan Menu Sesuai Nomor Menu Atau Tulis Nama Menunya : ");
    getline(cin, _Menu);

    if (_Menu == "1" || _Menu == "tambah barang") {
    	tambahStok(stokList);
    	sistemSubMenu(&sistemMenu);
    } else if (_Menu == "2" || _Menu == "ubah harga barang") {
        ubahHarga(stokList);
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "3" || _Menu == "list stok barang") {
        cetakStok(stokList);
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "4" || _Menu == "sorting abjad") {
    	ubahPosisiAbjad(stokList);
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "5" || _Menu == "sorting reverse") {
        ubahPosisi(stokList);
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "6" || _Menu == "reset sorting") {
        resetPosisi(stokList, dataPermanen);
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "7" || _Menu == "sequential search") {
    	sequentialSearch(stokList);
    	sistemSubMenu(&sistemMenu);
    } else if (_Menu == "8" || _Menu == "binary search") {
        binarySearch(stokList);
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "9" || _Menu == "keluar aplikasi") {
        noticeExit();
    } else {
        noticeDefault();
        sistemMenu();
    }
}


/// Saya Menggunakan Parameter Pointer Pak ///
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
