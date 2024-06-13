#include <iostream>
#include <string>

using namespace std;

void showMenu();
void handleChoice(int choice);
void showMakananMenu();
void handleMakananChoice(int choice);
void showMinumanMenu();
void handleMinumanChoice(int choice);

void pecelLeleMenu();
void handlePecelLeleChoice(int choice);
void nasiGorengMenu();
void handleNasiGorengChoice(int choice);
void esTehMenu();
void handleEsTehChoice(int choice);
void esJerukMenu();
void handleEsJerukChoice(int choice);

int inputQty();
void outputTotal(string itemName, int qty, int price);
void showMenu();
void kembaliKeMakanan();
void kembaliKeMinuman();

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        handleChoice(choice);
    } while (choice != 3);
    return 0;
}

void showMenu() {
    cout << "Menu:\n";
    cout << "1. Makanan\n";
    cout << "2. Minuman\n";
    cout << "3. Exit\n";
    cout << "Pilih menu: ";
}

void handleChoice(int choice) {
    switch (choice) {
        case 1:
            showMakananMenu();
            break;
        case 2:
            showMinumanMenu();
            break;
        case 3:
            cout << "Terima kasih! Sampai jumpa.\n";
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
            break;
    }
}

void showMakananMenu() {
    int choice;
    cout << "Makanan:\n";
    cout << "1. Pecel Lele\n";
    cout << "2. Nasi Goreng\n";
    cout << "3. Kembali Ke Menu\n";
    cout << "Pilih makanan: ";
    cin >> choice;
    handleMakananChoice(choice);
}

void handleMakananChoice(int choice) {
    switch (choice) {
        case 1:
            pecelLeleMenu();
            break;
        case 2:
            nasiGorengMenu();
            break;
        case 3:
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
            showMakananMenu();
            break;
    }
}

void pecelLeleMenu() {
    int choice;
    cout << "Pecel Lele:\n";
    cout << "1. Input Qty\n";
    cout << "2. Total Harga\n";
    cout << "3. Kembali Ke Makanan\n";
    cout << "Pilih opsi: ";
    cin >> choice;
    handlePecelLeleChoice(choice);
}

void handlePecelLeleChoice(int choice) {
    static int qty = 0;
    const int price = 15000;
    switch (choice) {
        case 1:
            qty = inputQty();
            pecelLeleMenu();
            break;
        case 2:
            outputTotal("Pecel Lele", qty, price);
            pecelLeleMenu();
            break;
        case 3:
            kembaliKeMakanan();
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
            pecelLeleMenu();
            break;
    }
}

void nasiGorengMenu() {
    int choice;
    cout << "Nasi Goreng:\n";
    cout << "1. Input Qty\n";
    cout << "2. Total Harga\n";
    cout << "3. Kembali Ke Makanan\n";
    cout << "Pilih opsi: ";
    cin >> choice;
    handleNasiGorengChoice(choice);
}

void handleNasiGorengChoice(int choice) {
    static int qty = 0;
    const int price = 12000;
    switch (choice) {
        case 1:
            qty = inputQty();
            nasiGorengMenu();
            break;
        case 2:
            outputTotal("Nasi Goreng", qty, price);
            nasiGorengMenu();
            break;
        case 3:
            kembaliKeMakanan();
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
            nasiGorengMenu();
            break;
    }
}

void showMinumanMenu() {
    int choice;
    cout << "Minuman:\n";
    cout << "1. Es Teh\n";
    cout << "2. Es Jeruk\n";
    cout << "3. Kembali Ke Menu\n";
    cout << "Pilih minuman: ";
    cin >> choice;
    handleMinumanChoice(choice);
}

void handleMinumanChoice(int choice) {
    switch (choice) {
        case 1:
            esTehMenu();
            break;
        case 2:
            esJerukMenu();
            break;
        case 3:
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
            showMinumanMenu();
            break;
    }
}

void esTehMenu() {
    int choice;
    cout << "Es Teh:\n";
    cout << "1. Input Qty\n";
    cout << "2. Total Harga\n";
    cout << "3. Kembali Ke Minuman\n";
    cout << "Pilih opsi: ";
    cin >> choice;
    handleEsTehChoice(choice);
}

void handleEsTehChoice(int choice) {
    static int qty = 0;
    const int price = 5000;
    switch (choice) {
        case 1:
            qty = inputQty();
            esTehMenu();
            break;
        case 2:
            outputTotal("Es Teh", qty, price);
            esTehMenu();
            break;
        case 3:
            kembaliKeMinuman();
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
            esTehMenu();
            break;
    }
}

void esJerukMenu() {
    int choice;
    cout << "Es Jeruk:\n";
    cout << "1. Input Qty\n";
    cout << "2. Total Harga\n";
    cout << "3. Kembali Ke Minuman\n";
    cout << "Pilih opsi: ";
    cin >> choice;
    handleEsJerukChoice(choice);
}

void handleEsJerukChoice(int choice) {
    static int qty = 0;
    const int price = 7000;
    switch (choice) {
        case 1:
            qty = inputQty();
            esJerukMenu();
            break;
        case 2:
            outputTotal("Es Jeruk", qty, price);
            esJerukMenu();
            break;
        case 3:
            kembaliKeMinuman();
            break;
        default:
            cout << "Pilihan tidak valid. Coba lagi.\n";
            esJerukMenu();
            break;
    }
}

int inputQty() {
    int qty;
    cout << "Masukkan jumlah: ";
    cin >> qty;
    return qty;
}

void outputTotal(string itemName, int qty, int price) {
    int total = qty * price;
    cout << "Total harga " << itemName << ": " << total << " IDR\n";
}


void kembaliKeMakanan() {
    showMakananMenu();
}

void kembaliKeMinuman() {
    showMinumanMenu();
}
