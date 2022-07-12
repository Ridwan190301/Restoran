#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <limits>

using namespace std;

fstream file;

// class
class Menu; class Makanan; class Minuman; class Pegawai; class Kasir; class Admin;
class DBaseMenu; class DBasePegawai; class Order;

//buat head menu
Menu* head;
//buat head pegawai
Pegawai* headPegawai;

//buat head order
Order* headOrder;

//function
void menuKasir(), menuAdmin(), menuPemilik(), header(), footer(string pesan), menumakanan(), menuminuman();
void konfirmasi(), pembayaran(), menu_tambahdata(), menu_hapusdata(), menu_rubahdata();

//variabel banyak data
int data = 0, order = 0;

class penjumlahan{
public:
    int a;
    penjumlahan(int harga = 0) {
        this -> a = harga;
    }

    penjumlahan operator + (penjumlahan const &obj) {
        penjumlahan hasil;
        hasil.a = a + obj.a;
        return hasil;
    }
};

class Order {
public:
    string nama;
    int harga, jumlah, totalHarga;
    Order* next;

    Order() {
        next = NULL;
    }

    Order(string nama, int harga, int jumlah) {
        this -> nama = nama;
        this -> harga = harga;
        this -> jumlah = jumlah;
        this -> next = NULL;
    }

    void tampil(Order* head) {
        Order* temp = head;
        penjumlahan t1(0);
//        totalHarga = 0;
        data = 0;

        while (temp != NULL) {
            penjumlahan t2(temp->harga * temp -> jumlah);
            data++;
            cout << data << ") Nama\t\t:" << temp -> nama << endl;
            cout << "   Harga\t: " << temp -> harga << endl;
            cout << "   Jumlah\t: " << temp -> jumlah << "\n" << endl;

            t1 = t1 + t2;
            totalHarga = t1.a;

            // Update temp
            temp = temp->next;
        }
    }
};

//class menu
class Menu {
public:
    string nama, kategori;
    int harga;
    Menu* next;

    Menu() {
        next = NULL;
    }

    Menu(string nama, string kategori, int harga){
        this->nama = nama;
        this->kategori = kategori;
        this->harga = harga;
        this->next = NULL;
    }

    void tampil() {
        data = 0;
        Menu* temp = head;

        while (temp != NULL) {
            data++;
            cout << data << ") Nama\t\t:" << temp -> nama << endl;
            cout << "   Harga\t: " << temp -> harga << "\n" << endl;

            // Update temp
            temp = temp->next;
        }
    }

    //mengecek ada tidaknya menu dengan kategori makanan/minuman
    int cekData(string kategori) {
        Menu* temp = head;
        while (temp != NULL) {
            if (kategori == temp -> kategori) {
                //data ditemukan
                return 1;
            }
            // Update temp
            temp = temp->next;
        }
        //data tidak ditemukan
        return 0;
    }

    string stringify() {
        string datastring = "";
        Menu* temp = head;
        while (temp != NULL) {
            datastring = datastring + "Nama:" + temp->nama + "\nHarga: " + to_string(temp->harga) + "\nKategori: " + temp->kategori + "\n\n";
            // Update temp
            temp = temp->next;
        }
        datastring = datastring + "END";
        return datastring;
    }
};

//class makanan
class Makanan: public Menu {
public:
    void showData() {
        data = 0;
        Menu* temp = head;
        while (temp != NULL) {
            if (temp -> kategori == "Makanan") {
                data++;
                cout << data << ") Nama\t\t:" << temp -> nama << endl;
                cout << "   Harga\t: " << temp -> harga << "\n" << endl;
            }
            // Update temp
            temp = temp->next;
        }
    }
};

//class minuman
class Minuman: public Menu {
public:
    void showData() {
        data = 0;
        Menu* temp = head;
        while (temp != NULL) {
            if (temp -> kategori == "Minuman") {
                data++;
                cout << data << ") Nama\t\t:" << temp -> nama << endl;
                cout << "   Harga\t: " << temp -> harga << "\n" << endl;
            }
            // Update temp
            temp = temp->next;
        }
    }
};

//objek makanan, minuman
Makanan makanan;
Minuman minuman;

//class pegawai
class Pegawai {
public:
    string nama, jabatan;
    int noPegawai;
    Pegawai* next;

    Pegawai() {
        next = NULL;
    }

    Pegawai(string nama, int noPegawai, string jabatan) {
        this -> nama = nama;
        this -> noPegawai = noPegawai;
        this -> jabatan = jabatan;
        this -> next = NULL;
    }

    //login
    string login() {
        system("cls");
        cout << "=========================================================" << endl;
        cout << "===================== Resto FoodRE ======================" << endl;
        cout << "=========================================================\n" << endl;
        cout << "Login Pegawai" << endl;
        cout << "=========================================================" << endl;
        cout << "No Pegawai: ";
        cin >> noPegawai;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        //validasi login
        Pegawai* temp = headPegawai;
        while (temp != NULL) {
            if (temp -> noPegawai == noPegawai) {
                this -> nama = temp -> nama;
                this -> jabatan = temp -> jabatan;
                return temp -> jabatan;
            }
            // Update temp
            temp = temp->next;
        }
        return "";
    }
};

//buat objek Order
Order beli;

//class kasir
class Kasir: public Pegawai {
public:
    // constraktor set headoreder menjadi null
    Kasir() {
        headOrder = NULL;
    }

    //pilih menu
    int pilih(string kategori) {
        int jumlah, pilihan;
        Menu* node = head;

        system("cls");
        header();
        cout << "\n===================   Pilih Produk   ====================" << endl;
        if (kategori == "Makanan") {
            makanan.showData();
        } else {
            minuman.showData();
        }
        cout << "=========================================================" << endl;
        cout << "\nMasukkan pilihan: ";
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        //reset data
        data = 0;

        //cari data di Menu
        while (node != NULL) {
                //cek data sesuai kategori
            if (node -> kategori == kategori) {
                data++;
                //cek sesuai pilihan
                if (data == pilihan) {
                    cout << "Jumlah: ";
                    cin >> jumlah;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    //data ditemukan. Buat linked list order
                    Order* newNode = new Order(node->nama, node->harga, jumlah);

                    if (headOrder == NULL) {
                        order++;
                        headOrder = newNode;
                    } else {
                        Order* temp = headOrder;
                        while (temp->next != NULL) {
                            if (temp -> nama != newNode -> nama) {
                                // Update temp
                                temp = temp->next;
                            } else {
                                break;
                            }
                        }

                        //menu baru diorder
                        if (temp -> nama != newNode -> nama) {
                            temp->next = newNode;
                            order++;
                        }

                        //pernah diorder
                        if (order == 1 || temp -> nama == newNode -> nama) {
                            temp -> jumlah = temp -> jumlah + jumlah;
                        }
                    }
                    //data ditemukan
                    return 1;
                }
            }
            // Update node
            node = node->next;
        }
        //data tidak ditemukan
        return 0;
    }

    void bayar() {
        int kembalian, uang;

        cout << "Masukkan nominal pembayaran: ";
        cin >> uang;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        kembalian = uang - beli.totalHarga;

        //cek apakah uang lebih dari totalharga
        if (uang >= beli.totalHarga) {
            system("cls");

            header();

            cout << "\n==================== Struk Pembelian ====================\n";

            cout << "\nDaftar produk:\n";
            cout << "=========================================================\n";

            beli.tampil(headOrder);

            cout << "=========================================================\n";
            cout << "Total harga\t:" << beli.totalHarga << endl;
            cout << "Pembayaran\t:" << uang << endl;
            cout << "Kembalian\t:" << kembalian << endl;

            cout << "=========================================================\n";
            cout << "      ============= TRANSAKSI SELESAI =============      \n";
            cout << "=========================================================\n";

            //set headOrder null
            headOrder = NULL;
            getch();
        } else {
            footer("MAAF UANG ANDA TIDAK CUKUP UNTUK MELAKUKAN PEMBAYARAN");
            getch();
        }
    }

    int hapusbeli() {
        int pilihan;

        konfirmasi();

        if (headOrder != NULL) {
            cout << "\n====================== Hapus Data =======================" << endl;
            cout << "\nMasukkan pilihan: ";
            cin >> pilihan;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            //temp2 = data sebelum
            Order *temp1 = headOrder, *temp2 = NULL;

            if (order < pilihan) {
                footer("Pilihan tidak tersedia di daftar.");
            } else if (pilihan == 1) {
                // Hapus headorder
                //kurangi order;
                order--;

                // rubah headorder
                headOrder = headOrder->next;
                delete temp1;
                footer("Data berhasil dihapus.");
            } else {
                // cari data
                while (pilihan-- > 1) {

                    // rubah temp2
                    temp2 = temp1;

                    // rubah temp1
                    temp1 = temp1->next;
                }

                //rubah next pointer sebelumnya
                temp2->next = temp1->next;

                // Hapus
                order--;
                delete temp1;
                footer("Data berhasil dihapus.");
            }
        }
    }
};

//objek menu
Menu menu;

//class admin
class Admin: public Pegawai {
private:
    int cek;
public:
    void bacadata() {
        system("cls");
        header();
        cout << "\n======================   Produk   =======================" << endl;
        if (head != NULL) {
            menu.tampil();
            footer("");
        } else {
            footer("Data masih kosong.");
        }
    }

    void tambahdata() {
        string nama, kategori;
        int harga;

        cout << "Nama Produk: ";
        getline(cin, nama);
        cout << "Kategori (Makanan/Minuman): ";
        getline(cin, kategori);
        cout << "Harga: ";
        cin >> harga;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Menu* newNode = new Menu(" " + nama, kategori, harga);

        if (head == NULL) {
            data++;
            head = newNode;
        } else {
            Menu* temp = head;
            while (temp->next != NULL) {

                // Update temp
                temp = temp->next;
            }

            // Insert data.
            temp->next = newNode;
            data++;
        }
    }

    void hapusdata() {
        string hapus;
        cek = 0;

        if (head != NULL) {
            cout << "Nama Produk: ";
            getline(cin, hapus);

            Menu *temp1 = head, *temp2 = NULL;

            cek++;
            while(temp1 != NULL) {
                if (temp1->nama == " " + hapus) {
                    break;
                }
                temp2 = temp1;
                temp1 = temp1->next;
                cek++;
            }

            if (data < cek) {
                footer("Data tidak ditemukan.");
            } else if (cek == 1) {
                // rubah headorder
                head = head->next;
                delete temp1;
                data--;
                footer("Data berhasil dihapus.");
            } else {
                //rubah next pointer sebelumnya
                temp2->next = temp1->next;

                delete temp1;
                data--;
                footer("Data berhasil dihapus.");
            }
        }
    }

    void rubahdata() {
        string rubah;

        cek = 0;

        if (head != NULL) {
            cout << "Nama produk: ";
            getline(cin, rubah);

            Menu* temp = head;

            cek++;
            while (temp != NULL) {
                if (temp -> nama == " " + rubah) {
                    break;
                }
                temp = temp -> next;
                cek++;
            }

            if (data < cek) {
                footer("Data tidak ditemukan.");
            } else {
                cout << "\nData Baru" << endl;
                cout << "====================" << endl;

                cout << "Nama Produk: ";
                getline(cin, temp->nama);
                temp -> nama = " " + temp -> nama;
                cout << "Kategori (Makanan/Minuman): ";
                getline(cin, temp->kategori);
                cout << "Harga: ";
                cin >> temp->harga;

                footer("Data berhasil dirubah.");
            }
        }
    }
};

//database menu
class DBaseMenu {
    string filename = "DBaseMenu.txt";
public:
    string nama, kategori, coba;
    int harga;
    //buat head menjadi null
    DBaseMenu() {
        head = NULL;
    }

    //baca data
    void read() {
        file.open(filename);

        if (!file.is_open()) {
            file.open(filename, ios::trunc | ios::out);
            file << "END";
            file.close();
            file.open(filename);
        }

        while(!file.eof()) {
            file >> coba;
            getline(file, nama);
            file >> coba;
            file >> harga;
            file >> coba;
            file >> kategori;

            if (coba == "END") {
                break;
            }

            Menu* newNode = new Menu(nama, kategori, harga);

            if (head == NULL) {
//                data++;
                head = newNode;
            } else {
//                data++;

                //perlu head dari menu
                Menu* temp = head;
                while (temp->next != NULL) {

                    // Update temp
                    temp = temp->next;
                }

                // Insert data.
                temp->next = newNode;
            }
        }

        file.close();
    }

    void update() {
        file.open(filename, ios::out);
        file << menu.stringify();
        file.close();
    }
};

//database pegawai
class DBasePegawai {
    string filename = "DBasePegawai.txt";
public:
    string nama, jabatan, coba;
    int noPegawai;

    DBasePegawai() {
        headPegawai = NULL;
    }

    //baca data
    void read() {
        file.open(filename, ios::in);

        while(!file.eof()) {
            file >> coba;
            getline(file, nama);
            file >> coba;
            file >> noPegawai;
            file >> coba;
            file >> jabatan;

            if(coba == "END") {
                break;
            }

            Pegawai* newNode = new Pegawai(nama, noPegawai, jabatan);

            if (headPegawai == NULL) {
                headPegawai = newNode;
            } else {
                Pegawai* temp = headPegawai;
                while (temp->next != NULL) {

                    // Update temp
                    temp = temp->next;
                }

                // Insert data.
                temp->next = newNode;
            }
        }

        file.close();
    }
};

DBaseMenu dbasemenu;
DBasePegawai dbasepegawi;
Pegawai pegawai;
Kasir kasir;
Admin admin;
int main() {
    dbasemenu.read();

    dbasepegawi.read();

ulangi:
    string jabatan = pegawai.login();

    if (jabatan == "Kasir") {
        menuKasir();
    } else if (jabatan == "Admin") {
        menuAdmin();
    } else if (jabatan == "Pemilik") {
        menuPemilik();
    } else {
        footer("Data Tidak Ditemukan.");
        getch();
        goto ulangi;
    }

    return 0;
}

void header() {
    cout << "=========================================================" << endl;
    cout << "===================== Resto FoodRE ======================" << endl;
    cout << "=========================================================\n" << endl;
    cout << "Data Pegawai" << endl;
    cout << "===========================" << endl;
    cout << "Nama\t\t:" << pegawai.nama << endl;
    cout << "Posisi\t\t: " << pegawai.jabatan << endl;
    cout << "No Pegawai\t: " << pegawai.noPegawai << endl;
}

void footer(string pesan) {
    cout << "\n=========================================================" << endl;
    cout << "Informasi: " << pesan << "\nTekan enter." << endl;
    cout << "=========================================================\n" << endl;
}

void menuKasir() {
    int menu;
//    Kasir(pegawai.nama, pegawai.nopegawai, pegawai.jabatan) kasir;

ulangi:
    system("cls");
    header();
//    Menu coba;
//    coba.tampil();
    cout << "\n=======================   Menu   ========================" << endl;
    cout << "1. Makanan" << endl;
    cout << "2. Minuman" << endl;
    cout << "3. Pembayaran" << endl;
    cout << "4. Hapus\n" << endl;
    cout << "5. Keluar" << endl;
    cout << "Masukkan pilihan: ";
    cin >> menu;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (menu) {
        case 1:
            menumakanan();
            goto ulangi;
        case 2:
            menuminuman();
            goto ulangi;
        case 3:
            pembayaran();
            goto ulangi;
        case 4:
            kasir.hapusbeli();
            getch();
            goto ulangi;
        case 5:
            break;
        default:
            footer("Maaf, input yang anda masukkan salah/invalid.");
            getch();
            goto ulangi;
    }
}

void menuAdmin() {
    int menu;

ulangi:
    system("cls");
    header();
    cout << "\n=======================   Menu   ========================" << endl;
    cout << "1. Lihat Data" << endl;
    cout << "2. Tambah Data" << endl;
    cout << "3. Rubah Data" << endl;
    cout << "4. Hapus Data\n" << endl;
    cout << "5. Keluar" << endl;
    cout << "Masukkan pilihan: ";
    cin >> menu;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (menu) {
        case 1:
            admin.bacadata();
            getch();
            goto ulangi;
        case 2:
            menu_tambahdata();
            goto ulangi;
        case 3:
            menu_rubahdata();
            goto ulangi;
        case 4:
            menu_hapusdata();
            goto ulangi;
        case 5:
            dbasemenu.update();
            break;
        default:
            footer("Maaf, input yang anda masukkan salah/invalid.");
            getch();
            goto ulangi;
    }
}

void menuPemilik() {
    int menu;
ulangi:
    system("cls");
    header();
    cout << "\n=======================   Menu   ========================" << endl;
    cout << "1. Kasir" << endl;
    cout << "2. Admin\n" << endl;
    cout << "Masukkan pilihan: ";
    cin >> menu;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (menu) {
        case 1:
            menuKasir();
            break;
        case 2:
            menuAdmin();
            break;
        default:
            footer("Maaf, input yang anda masukkan salah/invalid.");
            getch();
            goto ulangi;
    }
}

void menumakanan() {
    int pilih;
ulangi:
    system("cls");
    header();
    cout << "\n==================== Produk Makanan =====================" << endl;

    if (makanan.cekData("Makanan") == 1) {
        makanan.showData();

        cout << "=========================================================" << endl;
        cout << "1. Pilih Menu" << endl;
        cout << "2. Kembali\n" << endl;

        cout << "Masukkan pilihan: ";
        cin >> pilih;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilih) {
            case 1:
                cout << "\n";
                if (kasir.pilih("Makanan") != 1) {
                    footer("Pilihan tidak tersedia di daftar menu.");
                    getch();
                }
                goto ulangi;
            case 2:
                break;
            default:
                footer("Maaf, input yang anda masukkan salah/invalid.");
                getch();
                goto ulangi;
        }
    } else {
        footer("Data makanan masih kosong.");
        getch();
    }
}

void menuminuman() {
    int pilih;
ulangi:
    system("cls");
    header();
    cout << "\n==================== Produk Minuman =====================" << endl;

    if (minuman.cekData("Minuman") == 1) {

        minuman.showData();

        cout << "=========================================================" << endl;
        cout << "1. Pilih Menu" << endl;
        cout << "2. Kembali\n" << endl;

        cout << "Masukkan pilihan: ";
        cin >> pilih;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilih) {
            case 1:
                cout << "\n";
                if (kasir.pilih("Minuman") != 1) {
                    footer("Pilihan tidak tersedia di daftar menu.");
                    getch();
                }
                goto ulangi;
            case 2:
                break;
            default:
                footer("Maaf, input yang anda masukkan salah/invalid.");
                getch();
                goto ulangi;
        }
    } else {
        footer("Data minuman masih kosong.");
        getch();
    }
}

void konfirmasi() {
    system("cls");
    header();
    cout << "\n====================== Konfirmasi =======================" << endl;

    if (headOrder != NULL) {
        beli.tampil(headOrder);

        cout << "Total Harga\t: " << beli.totalHarga << endl;
    } else {
        footer("Belum ada transaksi pembelian");
    }
}

void pembayaran() {
    int menu;

up:
    konfirmasi();

    if (headOrder != NULL) {
        cout << "\n=========================================================" << endl;
        cout << "1. Lanjut Bayar" << endl;
        cout << "2. Kembali\n" << endl;

        cout << "Masukkan pilihan: ";
        cin >> menu;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (menu) {
            case 1:
                cout << "\n=========================================================" << endl;
                kasir.bayar();
            case 2:
                break;
            default:
                footer("Maaf, input yang anda masukkan salah/invalid.");
                getch();
                goto up;
        }
    } else {
        konfirmasi();
        getch();
    }
}

void menu_tambahdata() {
    int pilih;

ulangi:
    system("cls");
    header();
    cout << "\n===================   Tambah Data    ====================" << endl;
    cout << "1. Tambah" << endl;
    cout << "2. Kembali\n" << endl;

    cout << "Masukkan pilihan: ";
    cin >> pilih;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (pilih) {
        case 1:
            cout << "\n=========================================================" << endl;
            admin.tambahdata();
            footer("Data Berhasil Di Tambahkan.");
            getch();
            goto ulangi;
        case 2:
            break;
        default:
            footer("Maaf, input yang anda masukkan salah/invalid.");
            getch();
            goto ulangi;
    }
}

void menu_hapusdata() {
    int pilih;

ulangi:
    system("cls");
    header();
    cout << "\n===================    Hapus Data    ====================" << endl;
    cout << "1. Hapus" << endl;
    cout << "2. Kembali\n" << endl;

    cout << "Masukkan pilihan: ";
    cin >> pilih;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (pilih) {
        case 1:
            cout << "\n=========================================================" << endl;
            admin.hapusdata();
            getch();
            goto ulangi;
        case 2:
            break;
        default:
            footer("Maaf, input yang anda masukkan salah/invalid.");
            getch();
            goto ulangi;
    }
}

void menu_rubahdata() {
    int pilih;

ulangi:
    system("cls");
    header();
    cout << "\n===================    Rubah Data    ====================" << endl;
    cout << "1. Rubah" << endl;
    cout << "2. Kembali\n" << endl;

    cout << "Masukkan pilihan: ";
    cin >> pilih;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (pilih) {
        case 1:
            cout << "\n=========================================================" << endl;
            admin.rubahdata();
            getch();
            goto ulangi;
        case 2:
            break;
        default:
            footer("Maaf, input yang anda masukkan salah/invalid.");
            getch();
            goto ulangi;
    }
}


