/*
KELOMPOK 7 - SESI CR001 :
		1. Rivai - 20230801290
		2. Chandika Eka Prasetya - 20230801268
		3. Yodan Muhammad Surya Adhe - 20230801424
		4. Muhamad Iqbal Al Kautsar - 20230801032
		5. Fandi Fajar Maulana-20230801157
*/

#include "Kelompok 7 (CR001) - Function.cpp"

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
        cetak("Masukkan Jumlah Barang : ");
        barangBaru.jumlah = getValidInt();
        cetak("Masukkan Harga Per Barang : Rp ");
        barangBaru.harga = getValidFloat();
        stok.push_back(barangBaru);
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


void cetakStok(const vector<Barang>& stok) {
    systemClose();
    if (stok.empty()) {
        cetak("Stok barang kosong.\n\n\n");
    } else {
        cetak("Informasi Stok Barang\n\n");
        for (const auto& barang : stok) {
            cetak("Nama Barang : ", barang.nama);
            cetak("\nJumlah Barang : ", formatAngka(barang.jumlah));
            cetak("\nHarga Per Barang : Rp ", formatAngka(barang.harga), "\n\n\n");
        }
    }
}

void manajemenStokBarang() {
	string pilihan;
    systemClose();
    gerakGaris("=", 100);
    cetak("\n\t\t\t\tManajemen Stok Barang\n");
    gerakGaris("=", 100);
    cetak("\n1. Tambah Barang\n");
    cetak("2. Ubah Harga Barang\n");
    cetak("3. List Stok Barang\n");
    cetak("4. Kembali Ke Menu\n");
    cetak("\nMasukkan Pilihan Menu Sesuai Nomor Menu Atau Tulis Nama Menunya : ");
    getline(cin, pilihan);

    if (pilihan == "1" || pilihan == "tambah barang") {
    	tambahStok(stokList);
    	sistemSubMenu(&manajemenStokBarang);
    } else if (pilihan == "2" || pilihan == "ubah harga barang") {
        ubahHarga(stokList);
        sistemSubMenu(&manajemenStokBarang);
    } else if (pilihan == "3" || pilihan == "list stok barang") {
        cetakStok(stokList);
        sistemSubMenu(&manajemenStokBarang);
    } else if (pilihan == "4" || pilihan == "kembali ke menu") {
    	sistemMenu();
    } else {
        noticeDefault();
        manajemenStokBarang();
    }
}

void sistemTransaksi(vector<Transaksi>& transaksi, const string& jenisTransaksi) {
	systemClose();
	Transaksi transaksiBaru;
    double jumlahUang;
    string keterangan;
    if(jenisTransaksi == "pemasukan") {
    	cetak("Masukkan Jumlah Uang Pemasukan : Rp ");
		jumlahUang = getValidDouble();
		cetak("Masukkan Keterangan Pemasukan : ");
		getValidString(keterangan);
		kapitalAwal(keterangan);
		transaksiBaru.jenisTransaksi = jenisTransaksi;
		transaksiBaru.jumlahUang = jumlahUang;
		transaksiBaru.keterangan = keterangan;
		transaksi.push_back(transaksiBaru);
	} else if(jenisTransaksi == "pengeluaran") {
		cetak("Masukkan Jumlah Uang Pengeluaran : Rp ");
		jumlahUang = getValidDouble();
		cetak("Masukkan Keterangan Pengeluaran : ");
		getValidString(keterangan);
		kapitalAwal(keterangan);
		transaksiBaru.jenisTransaksi = jenisTransaksi;
		transaksiBaru.jumlahUang = -jumlahUang;
		transaksiBaru.keterangan = keterangan;
		transaksi.push_back(transaksiBaru);
	}
	cetak("\n\n\n");
}

void hitungTotalKeuangan(const vector<Transaksi>& transaksi) {
    systemClose();
    double totalPemasukan = 0.0;
    double totalPengeluaran = 0.0;
    vector<string> pemasukanList;
    vector<string> pengeluaranList;
    for (const Transaksi& transaksiItem : transaksi) {
        if (transaksiItem.jumlahUang > 0) {
            totalPemasukan += transaksiItem.jumlahUang;
            pemasukanList.push_back(transaksiItem.keterangan + " : Rp " + formatAngka(transaksiItem.jumlahUang));
        } else {
            totalPengeluaran += transaksiItem.jumlahUang;
            pengeluaranList.push_back(transaksiItem.keterangan + " : Rp " + formatAngka(-transaksiItem.jumlahUang));
        }
    }
    cetak("Riwayat Keuangan\n\n");
    cetak("- Pemasukan :\n");
    for (size_t i = 0; i < pemasukanList.size(); ++i) {
        cetak("\t", to_string(i + 1), ". ", pemasukanList[i], "\n");
    }
    cetak("\n- Pengeluaran :\n");
    for (size_t i = 0; i < pengeluaranList.size(); ++i) {
        cetak("\t", to_string(i + 1), ". ", pengeluaranList[i], "\n");
    }
    cetak("\nTotal Pemasukan : Rp ", formatAngka(totalPemasukan));
    cetak("\nTotal Pengeluaran : Rp ", formatAngka(-totalPengeluaran), "\n\n\n");
}

void perhitunganKeuangan() {
	string pilihan;
    systemClose();
    gerakGaris("=", 100);
    cetak("\n\t\t\t\tPerhitungan Keuangan\n");
    gerakGaris("=", 100);
    cetak("\n1. Pemasukan\n");
    cetak("2. Pengeluaran\n");
    cetak("3. Hitung Total Keuangan\n");
    cetak("4. Kembali Ke Menu\n");
    cetak("\nMasukkan Pilihan Menu Sesuai Nomor Menu Atau Tulis Nama Menunya : ");
    getline(cin, pilihan);
    
    if (pilihan == "1" || pilihan == "pemasukan") {
    	sistemTransaksi(transaksiList, "pemasukan");
    	sistemSubMenu(&perhitunganKeuangan);
    } else if (pilihan == "2" || pilihan == "pengeluaran") {
        sistemTransaksi(transaksiList, "pengeluaran");
        sistemSubMenu(&perhitunganKeuangan);
    } else if (pilihan == "3" || pilihan == "hitung total keuangan") {
        hitungTotalKeuangan(transaksiList);
        sistemSubMenu(&perhitunganKeuangan);
    } else if (pilihan == "4" || pilihan == "kembali ke menu") {
    	sistemMenu();
    } else {
        noticeDefault();
        perhitunganKeuangan();
    }
}

void displayData(const vector<string>& data) {
    if (!data.empty()) {
        cetak("Data yang tersimpan :\n");
        for (size_t i = 0; i < data.size(); ++i) {
            cetak(to_string(i + 1), ". ", data[i], "\n");
        }
        cetak("\n");
    }
}

void simpanData() {
    systemClose();
    string input;
    bool isDuplicate = false;
    cetak("Masukkan data (ketik '!stop' untuk berhenti) :\n");
    do {
        getline(cin, input);
        kapitalAwal(input);
        if (input != "!Stop") {
            isDuplicate = false;
            for (const string& existingData : data) {
                if (existingData == input) {
                    isDuplicate = true;
                    break;
                }
            }
            if (!isDuplicate) {
                data.push_back(input);
                dataPermanen.push_back(input);
            } else {
                cetak("Data '", input, "' sudah ada. Tolong input ulang dengan benar :\n");
            }
        }
    } while (input != "!Stop");
    cetak("\n\n");
}

void ubahPosisi(vector<string>& data) {
    reverse(data.begin(), data.end());
    searchingMenu();
}

void ubahPosisiAbjad(vector<string>& data) {
    sort(data.begin(), data.end());
    searchingMenu();
}

void resetPosisi(vector<string>& data, const vector<string>& dataPermanen) {
    data = dataPermanen;
    searchingMenu();
}

void searchingMenu() {
    string pilihan;
    systemClose();
    displayData(data);
    gerakGaris("=", 100);
    cetak("\n\t\t\t\tProgram Searching\n");
    gerakGaris("=", 100);
    cetak("\n1. Input Data\n");
    cetak("2. Sequential Search\n");
    cetak("3. Binary Search\n");
    cetak("4. Ubah Posisi Data\n");
    cetak("5. Urutkan Data Berdasarkan Abjad\n");
    cetak("6. Reset Posisi\n");
    cetak("7. Kembali Ke Menu\n");
    cetak("\nMasukkan Pilihan Menu Sesuai Nomor Menu Atau Tulis Nama Menunya : ");
    getline(cin, pilihan);
    
    if (pilihan == "1" || pilihan == "input data") {
    	simpanData();
    	sistemSubMenu(&searchingMenu);
    } else if (pilihan == "2" || pilihan == "sequential search") {
    	sequentialSearch(data);
    	sistemSubMenu(&searchingMenu);
    } else if (pilihan == "3" || pilihan == "binary search") {
        binarySearch(data);
        sistemSubMenu(&searchingMenu);
    } else if (pilihan == "4" || pilihan == "ubah posisi data") {
    	ubahPosisi(data);
    } else if (pilihan == "5" || pilihan == "urutkan data berdasarkan abjad") {
    	ubahPosisiAbjad(data);
    } else if (pilihan == "6" || pilihan == "reset posisi") {
        resetPosisi(data, dataPermanen);
    } else if (pilihan == "7" || pilihan == "kembali ke menu") {
        sistemMenu();
    } else {
        noticeDefault();
        searchingMenu();
    }
}

void sistemMenu() {
    string _Menu;
    systemClose();
    gerakGaris("=", 100);
    cetak("\n\t\t\t\tAplikasi Beta Sudah Dekat ^_^\n");
    gerakGaris("=", 100);
    cetak("\n1. Manajemen Stok Barang\n");
    cetak("2. Perhitungan Keuangan\n");
    cetak("3. Searching\n");
    cetak("4. Keluar Aplikasi\n");
    cetak("\nMasukkan Pilihan Menu Sesuai Nomor Menu Atau Tulis Nama Menunya : ");
    getline(cin, _Menu);

    if (_Menu == "1" || _Menu == "manajemen stok barang") {
    	manajemenStokBarang();
    } else if (_Menu == "2" || _Menu == "perhitungan keuangan") {
    	perhitunganKeuangan();
    } else if (_Menu == "3" || _Menu == "searching") {
    	searchingMenu();
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "4" || _Menu == "keluar aplikasi") {
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
