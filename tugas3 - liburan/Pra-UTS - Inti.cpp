/*
KELOMPOK 7 - SESI CR001 :
		1. Rivai - 20230801290
		2. Chandika Eka Prasetya - 20230801268
		3. Yodan Muhammad Surya Adhe - 20230801424
		4. Muhamad Iqbal Al Kautsar - 20230801032
		5. Fandi Fajar Maulana-20230801157
*/

#include "Pra-UTS - Function.cpp"

void printArray(int arr[], int size) {
	if (size == 0) {
        cetak("Array kosong.\n");
    } else {
    	for (int i = 0; i < size; i++) {
		cetak(to_string(arr[i]), " ");
		}
	}
    cetak("\n");
}

void sistemBubbleSorting() {
	systemClose();
	int n;
    cetak("Masukkan Panjang array : ");
    n = getValidInt();
    int arr[n];
    for (int i = 0; i < n; i++) {
    	cetak("Masukkan elemen ke-", i+1," : ");
        arr[i] = getValidInt();
    }
    cetak("\n\nArray sebelum pengurutan : ");
    printArray(arr, n);
    bubbleSort(arr, n);
    cetak("Array setelah pengurutan : ");
    printArray(arr, n);
    cetak("\n\n");
}

void penanganNilai() {
	systemClose();
	int n;
    cetak("Masukkan Panjang array : ");
    n = getValidInt();
    int* array = new int[n];
    for (int i = 0; i < n; i++) {
    	cetak("Masukkan elemen ke-", i+1," : ");
        array[i] = getValidInt();
    }
    int total = hitungTotal(array, n);
    cetak("Jumlah total nilai dalam array : ",total);
    int maksimum = cariMaksimum(array, n);
    int minimum = cariMinimum(array, n);
    if (maksimum != -1 && minimum != -1) {
        cetak("\n\nNilai maksimum dalam array : ", maksimum);
        cetak("\nNilai minimum dalam array : ", minimum);
    } else {
        cetak("Array kosong.\n");
    }
    cetak("\n\nArray sebelum pengurutan : ");
    printArray(array, n);
    bubbleSort(array, n);
    cetak("Array setelah pengurutan : ");
    printArray(array, n);
    cetak("\n\n");
}

void sistemFaktorial() {
	systemClose();
	int bilangan;
	cetak("Masukkan bilangan untuk dihitung faktorialnya : ");
    bilangan = getValidInt();
    if (bilangan < 0) {
        cetak("Bilangan harus non-negatif.\n\n");
        systemPause();
        sistemFaktorial();
    } else {
    	unsigned long long faktorial = hitungFaktorial(bilangan);
		cetak("Faktorial dari ", bilangan, " adalah ", faktorial);
	}
    cetak("\n\n");
}

void sistemMenu() {
    string _Menu;
    systemClose();
    gerakGaris("=", 100);
    cetak("\n\t\t\t\tAplikasi Beta Sudah Dekat ^_^\n");
    gerakGaris("=", 100);
    cetak("\n1. Bubble Sorting\n");
    cetak("2. Penanganan Nilai\n");
    cetak("3. Faktorial\n");
    cetak("4. Keluar Aplikasi\n");
    cetak("\nMasukkan Pilihan Menu Sesuai Nomor Menu Atau Tulis Nama Menunya : ");
    getline(cin, _Menu);

    if (_Menu == "1" || _Menu == "bubble sorting") {
    	sistemBubbleSorting();
    	sistemSubMenu(&sistemMenu);
    } else if (_Menu == "2" || _Menu == "penangan nilai") {
    	penanganNilai();
    	sistemSubMenu(&sistemMenu);
    } else if (_Menu == "3" || _Menu == "faktorial") {
    	sistemFaktorial();
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
