#include <iostream>

using namespace std;


const char NAMA_PEMBUAT[] = "Muhammad Daffa Khoiro"; 
const char NIM_PEMBUAT[]  = "2500018049";  
const int MAKS_BUKU = 100;             


struct Buku {
    char kodeBuku[20];
    char judulBuku[50];
    char penulis[50];
    int stokBuku;
};


class DigilibSystem {
private:
    Buku daftarBuku[MAKS_BUKU];
    int jumlahBuku;

    // Fungsi helper kustom untuk membandingkan dua buah string/char array
    bool stringSama(const char str1[], const char str2[]) const {
        int i = 0;
        while (str1[i] != '\0' || str2[i] != '\0') {
            if (str1[i] != str2[i]) return false;
            i++;
        }
        return true;
    }

    // Fungsi helper kustom untuk menyalin isi dari satu string ke string lain
    void stringSalin(char target[], const char sumber[]) {
        int i = 0;
        while (sumber[i] != '\0') {
            target[i] = sumber[i];
            i++;
        }
        target[i] = '\0';
    }

    // Fungsi helper kustom untuk membuat spasi rapi (pengganti setw)
    void cetakSpasi(const char str[], int lebarTotal) const {
        int panjang = 0;
        while (str[panjang] != '\0') {
            panjang++;
        }
        cout << str;
        for (int i = 0; i < (lebarTotal - panjang); i++) {
            cout << " ";
        }
    }

    // Ketentuan 7: Fungsi Rekursif Menghitung Total Stok (Private Helper)
    int hitungTotalStokRekursif(int index) const {
        // Base Case: jika index sudah mencapai jumlah buku saat ini
        if (index >= jumlahBuku) {
            return 0;
        }
        // Recursive Case
        return daftarBuku[index].stokBuku + hitungTotalStokRekursif(index + 1);
    }

public:
    // Constructor
    DigilibSystem() {
        jumlahBuku = 0;
    }

    // Ketentuan 1: Fungsi Login Petugas
    bool fungsiLogin() {
        char username[50], password[50];
        cout << "=========================================\n";
        cout << "     LOGIN PETUGAS PERPUSTAKAAN DIGILIB  \n";
        cout << "=========================================\n";
        cout << "Masukkan Username : ";
        cin >> username;
        cout << "Masukkan Password : ";
        cin >> password;
        
        return (stringSama(username, NAMA_PEMBUAT) && stringSama(password, NIM_PEMBUAT));
    }

    // Ketentuan 2 & 6: Tambah Data Buku
    void tambahBuku() {
        cout << "\n--- TAMBAH DATA BUKU ---\n";
        if (jumlahBuku >= MAKS_BUKU) {
            cout << "[Gagal] Penyimpanan perpustakaan sudah penuh!\n";
            return;
        }

        Buku bukuBaru;
        cout << "Masukkan Kode Buku  : ";
        cin >> bukuBaru.kodeBuku;
        
        cout << "Masukkan Judul Buku : ";
        cin.ignore(); // Bersihkan sisa enter di buffer
        cin.getline(bukuBaru.judulBuku, 50);
        
        cout << "Masukkan Penulis    : ";
        cin.getline(bukuBaru.penulis, 50);
        
        cout << "Masukkan Stok Buku  : ";
        while (!(cin >> bukuBaru.stokBuku) || bukuBaru.stokBuku < 0) {
            cout << "Input stok tidak valid. Masukkan angka positif: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // Masukkan ke dalam array primitif
        daftarBuku[jumlahBuku] = bukuBaru;
        jumlahBuku++;
        cout << "[Sukses] Data buku berhasil ditambahkan ke sistem.\n";
    }

    // Ketentuan 3 & 6: Hapus Data Buku Berdasarkan Kode
    void hapusBuku() {
        cout << "\n--- HAPUS DATA BUKU ---\n";
        if (jumlahBuku == 0) {
            cout << "Perpustakaan kosong, tidak ada data yang bisa dihapus.\n";
            return;
        }

        char kodeCari[20];
        cout << "Masukkan Kode Buku yang akan dihapus: ";
        cin >> kodeCari;

        int indexDitemukan = -1;
        for (int i = 0; i < jumlahBuku; i++) {
            if (stringSama(daftarBuku[i].kodeBuku, kodeCari)) {
                indexDitemukan = i;
                break;
            }
        }

        if (indexDitemukan != -1) {
            // Menggeser sisa elemen array ke depan untuk menghapus data buku
            for (int i = indexDitemukan; i < jumlahBuku - 1; i++) {
                daftarBuku[i] = daftarBuku[i + 1];
            }
            jumlahBuku--; // Kurangi hitungan total buku
            cout << "[Sukses] Buku dengan Kode " << kodeCari << " berhasil dihapus.\n";
        } else {
            cout << "[Gagal] Buku dengan Kode " << kodeCari << " tidak ditemukan.\n";
        }
    }

    // Ketentuan 4, 6 & 7: Lihat Seluruh Data Buku & Total Stok
    void lihatBuku() const {
        cout << "\n--- DAFTAR DATA BUKU TERSEDIA ---\n";
        if (jumlahBuku == 0) {
            cout << "Belum ada data buku di perpustakaan.\n";
            return;
        }

        // Header Tabel Manual
        cout << "-----------------------------------------------------------------------\n";
        cetakSpasi("Kode Buku", 15);
        cetakSpasi("Judul Buku", 25);
        cetakSpasi("Penulis", 20);
        cout << "Stok\n";
        cout << "-----------------------------------------------------------------------\n";

        // Menampilkan isi array
        for (int i = 0; i < jumlahBuku; i++) {
            cetakSpasi(daftarBuku[i].kodeBuku, 15);
            cetakSpasi(daftarBuku[i].judulBuku, 25);
            cetakSpasi(daftarBuku[i].penulis, 20);
            cout << daftarBuku[i].stokBuku << "\n";
        }
        cout << "-----------------------------------------------------------------------\n";

        // Memanggil fungsi rekursif dengan index awal 0
        int totalStok = hitungTotalStokRekursif(0);
        cout << "Total Keseluruhan Stok Buku di Perpustakaan: " << totalStok << " eksemplar.\n";
    }
};

// --- FUNGSI UTAMA ---
int main() {
    // Instansiasi objek dari class DigilibSystem
    DigilibSystem digilib;

    // 1. Proses Login
    if (!digilib.fungsiLogin()) {
        cout << "\n[Login Gagal] Username atau Password salah. Program berhenti.\n";
        return 0;
    }

    int pilihanMenu;
    do {
        // 5. Tampilan Menu Utama
        cout << "\n===== MENU UTAMA =====" << endl;
        cout << "1. Tambah Buku" << endl;
        cout << "2. Hapus Buku" << endl;
        cout << "3. Lihat Buku" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih menu (1-4): ";
        
        if (!(cin >> pilihanMenu)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Pilihan tidak valid! Masukkan angka 1-4.\n";
            continue;
        }

        // 6. Alur Program Berdasarkan Pilihan Menu
        switch (pilihanMenu) {
            case 1:
                digilib.tambahBuku();
                break;
            case 2:
                digilib.hapusBuku();
                break;
            case 3:
                digilib.lihatBuku();
                break;
            case 4:
                cout << "\nTerima kasih telah menggunakan DIGILIB!\n";
                break;
            default:
                cout << "Pilihan menu tidak tersedia. Silakan coba lagi.\n";
        }
    } while (pilihanMenu != 4);

    return 0;
}