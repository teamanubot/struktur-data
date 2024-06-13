#include "Rivai_Tugas Pert 8_20230801290 - Function.cpp"

class LinkedList {
private:
    Node* head;
    int newData;
    int posisi;
    void setNewData() {
        cetak("Masukkan data : ");
        newData = getValidInt();
    }

    void setPosisi() {
        cetak("Masukkan posisi : ");
        posisi = getValidInt();
    }
public:
    LinkedList() : head(NULL), newData(0), posisi(0) {}

    void insertDepan() {
        systemClose();
        setNewData();
        Node* newNode = new Node();
        newNode->data = newData;
        newNode->next = head;
        head = newNode;
        cetak("\n\n\n");
    }

    void insertTengah() {
        systemClose();
        setNewData();
        setPosisi();
        if (posisi < 0) {
            cetak("Posisi tidak valid.\n\n\n");
            return;
        }
        if (posisi == 0) {
            insertDepan();
            return;
        }
        Node* newNode = new Node();
        newNode->data = newData;
        Node* current = head;
        for (int i = 0; current != NULL && i < posisi - 1; i++) {
            current = current->next;
        }
        if (current == NULL) {
            cetak("Posisi tidak valid.\n\n\n");
            delete newNode;
            return;
        }
        newNode->next = current->next;
        current->next = newNode;
        cetak("\n\n\n");
    }

    void insertBelakang() {
        systemClose();
        setNewData();
        Node* newNode = new Node();
        newNode->data = newData;
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
            return;
        }
        Node* last = head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
        cetak("\n\n\n");
    }

    void deleteDepan() {
        systemClose();
        if (head == NULL) {
            cetak("List kosong.\n\n\n");
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void deleteTengah() {
        systemClose();
        setPosisi();
        if (posisi < 0) {
            cetak("Posisi tidak valid.\n\n\n");
            return;
        }
        if (head == NULL) {
            cetak("List kosong.\n\n\n");
            return;
        }
        if (posisi == 0) {
            deleteDepan();
            return;
        }
        Node* current = head;
        Node* prev = NULL;
        for (int i = 0; current != NULL && i < posisi; i++) {
            prev = current;
            current = current->next;
        }
        if (current == NULL) {
            cetak("Posisi tidak valid.\n\n\n");
            return;
        }
        prev->next = current->next;
        delete current;
        cetak("\n\n\n");
    }

    void deleteBelakang() {
        systemClose();
        if (head == NULL) {
            cetak("List kosong.\n\n\n");
            return;
        }
        if (head->next == NULL) {
            delete head;
            head = NULL;
            return;
        }
        Node* secondLast = head;
        while (secondLast->next->next != NULL) {
            secondLast = secondLast->next;
        }
        delete secondLast->next;
        secondLast->next = NULL;
    }

    void tampilkanData() {
        systemClose();
        if (head == NULL) {
            cetak("List kosong.\n\n\n");
            return;
        }
        Node* current = head;
        while (current != NULL) {
            cetak(to_string(current->data), " -> ");
            current = current->next;
        }
        cetak("NULL\n\n\n");
    }

    void cariData() {
        systemClose();
        setNewData();
        Node* current = head;
        int posisi = 0;
        bool ditemukan = false;
        while (current != NULL) {
            if (current->data == newData) {
                cetak("Data ditemukan pada posisi : ", posisi, "\n");
                ditemukan = true;
            }
            current = current->next;
            posisi++;
        }
        if (!ditemukan) {
            cetak("Data tidak ditemukan dalam list.\n");
        }
        cetak("\n\n");
    }

    int hitungElemen() {
        systemClose();
        Node* current = head;
        int count = 0;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        cetak(to_string(count), "\n\n\n");
        return count;
    }

    void clear() {
        while (head != NULL) {
            deleteDepan();
        }
    }

    ~LinkedList() {
        clear();
    }
};

LinkedList list;

void sistemMenu() {
    string _Menu;
    systemClose();
    gerakGaris("=", 100);
    cetak("\n\t\t\t\tAplikasi Beta Sudah Dekat ^_^\n");
    gerakGaris("=", 100);
    cetak("\n1. Insert Depan\n");
    cetak("2. Insert Tengah\n");
    cetak("3. Insert Belakang\n");
    cetak("4. Delete Depan\n");
    cetak("5. Delete Tengah\n");
    cetak("6. Delete Belakang\n");
    cetak("7. Tampilkan Data\n");
    cetak("8. Cari Data\n");
    cetak("9. Hitung Elemen\n");
    cetak("10. Keluar Aplikasi\n");
    cetak("\nMasukkan Pilihan Menu Sesuai Nomor Menu Atau Tulis Nama Menunya : ");
    getline(cin, _Menu);

    if (_Menu == "1" || _Menu == "insert depan") {
    	list.insertDepan();
    	sistemSubMenu(&sistemMenu);
    } else if (_Menu == "2" || _Menu == "insert tengah") {
    	list.insertTengah();
    	sistemSubMenu(&sistemMenu);
    } else if (_Menu == "3" || _Menu == "insert belakang") {
    	list.insertBelakang();
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "4" || _Menu == "delete depan") {
    	list.deleteDepan();
    	sistemSubMenu(&sistemMenu);
    } else if (_Menu == "5" || _Menu == "delete tengah") {
    	list.deleteTengah();
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "6" || _Menu == "delete belakang") {
    	list.deleteBelakang();
    	sistemSubMenu(&sistemMenu);
    } else if (_Menu == "7" || _Menu == "tampilkan data") {
    	list.tampilkanData();
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "8" || _Menu == "cari data") {
    	list.cariData();
    	sistemSubMenu(&sistemMenu);
    } else if (_Menu == "9" || _Menu == "hitung elemen") {
    	list.hitungElemen();
        sistemSubMenu(&sistemMenu);
    } else if (_Menu == "10" || _Menu == "keluar aplikasi") {
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
