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
    cetak("2. Hapus Buku\n");;
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
