#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Hutang
{
    string nama;
    long long int nomorWa;
    long int jumlahHutang;
};

string getCurrentTime()
{
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    char timeStr[100];
    if (strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&now_time)))
    {
        return string(timeStr);
    }
    else
    {
        return "Error";
    }
}

void inputPengeluaran(string &timeNow)
{
    cin.ignore();
    timeNow = getCurrentTime();
}

void inputHutang(int &jumlahData, Hutang *dataHutang)
{
    cout << endl;
    cout <<"===================================="<<endl;
    cout << "Masukkan jumlah data penghutang : ";
    cin >> jumlahData;
    cout <<"====================================";
    cout << endl;
    cin.ignore();

    for (int i = 0; i < jumlahData; i++)
    {
        cout << endl;
        cout << "-Masukkan nama penghutang ke-" << i + 1 << " : ";
        getline(cin, dataHutang[i].nama);
        cout << "Masukkan nomor WhatsApp penghutang ke-" << i+1 << " : ";
        cin >> dataHutang[i].nomorWa;
        cout << "Masukkan jumlah hutang ke-" << i+1 << " : Rp.";
        cin >> dataHutang[i].jumlahHutang;
        cin.ignore();
        
    }
}

void tampilkanHutang(int jumlahData, Hutang *dataHutang, string &timeNow )
{
   
    
    for (int i = 0; i < jumlahData; i++)
    {
        cout << "---------------------------------" << endl;
        cout << "Penghutang " << i + 1 << ":" << endl;
        cout << "Nama: " << dataHutang[i].nama << endl;
        cout << "Nomor WhatsApp: " << dataHutang[i].nomorWa << endl;
        cout << "Jumlah Hutang: " << dataHutang[i].jumlahHutang << endl;
        cout << "---------------------------------" << endl;
        
        
    }

    // Menampilkan waktu penyimpanan
    cout << "\nData disimpan pada waktu: " << timeNow << endl;
}

void simpanAkun(string userName, int userPassword)
{
    ofstream file("akun.txt", ios::app);
    if (file.is_open())
    {
        file << userName << " " << userPassword << endl;
        file.close();
        cout << "Akun berhasil disimpan.\n";
    }
    else
    {
        cout << "Gagal menyimpan akun.\n";
    }
}

bool cekAkun(string userName, int userPassword)
{
    ifstream file("akun.txt");
    string line;
    while (getline(file, line))
    {
        if (line == userName + " " + to_string(userPassword))
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

long int totalHutang(int jumlahData, Hutang *dataHutang, int index)
{
    if (index == jumlahData)
    {
        return 0;
    }
    else
    {
        return dataHutang[index].jumlahHutang + totalHutang(jumlahData, dataHutang, index + 1);
    }
}

void utangsmall(Hutang *dataHutang, int jumlahData)
{
    sort(dataHutang, dataHutang + jumlahData, [](Hutang a, Hutang b) {
        return a.jumlahHutang < b.jumlahHutang;
    });
}

void utangBIG(Hutang *dataHutang, int jumlahData)
{
    
    sort(dataHutang, dataHutang + jumlahData, [](Hutang a, Hutang b) {
        return a.jumlahHutang > b.jumlahHutang;
    });
}

int carinama(Hutang *dataHutang, int jumlahData, string target, Hutang &result)
{
    // Melakukan iterasi melalui setiap elemen dalam array
    for (int i = 0; i < jumlahData; ++i)
    {
        // Jika nilai pada indeks ke-i sama dengan nilai target
        if (dataHutang[i].nama == target)
        {
            // Menyimpan data penghutang yang ditemukan
            result = dataHutang[i];
            // Mengembalikan indeks di mana nilai target ditemukan
            return i;
        }
    }
    // Jika nilai target tidak ditemukan dalam array, mengembalikan -1
    return -1;
}

int carinomor(Hutang *dataHutang, int jumlahData, long long int target, Hutang &result)
{
    // Melakukan iterasi melalui setiap elemen dalam array
    for (int i = 0; i < jumlahData; ++i)
    {
        // Jika nilai pada indeks ke-i sama dengan nilai target
        if (dataHutang[i].nomorWa == target)
        {
            // Menyimpan data penghutang yang ditemukan
            result = dataHutang[i];
            // Mengembalikan indeks di mana nilai target ditemukan
            return i;
        }
    }
    // Jika nilai target tidak ditemukan dalam array, mengembalikan -1
    return -1;
}


int main()
{
    int choice;
    string userName;
    int userPassword;
    char exitChoice = 'Y'; // Initialize exitChoice
    char exit = 'N';
    string nama;
    long long int nomorWa;
    

    while (exitChoice != 'Q' && exitChoice != 'q')
    {
        cout << "+--------------------------------+\n";
        cout << "             AKUHEMAT\n";
        cout << "Selamat datang di AkuHemat :)\n";
        cout << "1. Login Akun\n";
        cout << "2. Buat Akun\n";
        cout << "Pilihan anda: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            cout << "Masukkan nama pengguna : ";
            cin >> userName;
            cout << "Masukkan kata sandi (dalam bentuk bilangan bulat): ";
            cin >> userPassword;

            cout << endl;

            if (cekAkun(userName, userPassword))
            {
                cout << "==============================="<<endl;;
                cout << "Selamat datang! Login berhasil.\n";
                cout << "===============================";
                cout << endl;
                
                // Input pengeluaran keuangan
                string timeNow;
                inputPengeluaran(timeNow);

                // Input data hutang
                int jumlahData;
                Hutang dataHutang[100]; // Maksimal 100 data penghutang
                inputHutang(jumlahData, dataHutang);

                // Pilihan untuk melihat data penghutang
                cout <<endl;
                cout << "-Apakah Anda ingin mencari urutan daftar data penghutang? (Y/N): ";
                char pilihan;
                cin >> pilihan;
                if (pilihan == 'Y' || pilihan == 'y')
                {
                    cout << "Pilih metode sorting (pengurutan): \n";
                    cout << "1. Dari nominal terbesar \n";
                    cout << "2. Dari nominal terkecil \n";
                    int sortChoice;
                    cout << "Pilihan Anda: ";
                    cin >> sortChoice;
                    if (sortChoice == 2)
                    {
                        utangsmall(dataHutang, jumlahData);
                        
                    }
                    else if (sortChoice == 1)
                    {
                        utangBIG(dataHutang, jumlahData);
                    }
                    else
                    {
                        cout << "Pilihan tidak valid. Menampilkan data tanpa sorting.\n";
                    }
                     
                
                    if (sortChoice==2)
                    {
                        cout << "\n-Daftar Hutang " <<"dari nominal terkecil :" << endl;
                        cout << endl;
                    }
                    else if (sortChoice==1)
                    {
                        cout << "\n-Daftar Hutang " <<"dari nominal terbesar :" << endl;
                        cout << endl;
                    }

                    tampilkanHutang(jumlahData, dataHutang, timeNow);

                    // Menampilkan total hutang
                    cout << "Total Hutang kepada Anda: " << totalHutang(jumlahData, dataHutang, 0) << endl;
                }

                cout <<endl;
                cout << "-Apakah anda ingin mencari nama penghutang? (Y/N): ";
                char pilihan_n;
                cin >> pilihan_n;
                if (pilihan_n == 'Y')
                {
                    cout << "Masukkan nama penghutang yang ingin anda cari: ";
                    cin >> nama;
                    cin.ignore();
                    Hutang result;
                    int idx = carinama(dataHutang, jumlahData, nama, result);
                        if (idx != -1)
                        {
                        cout <<endl;
                        cout << "Nomor WhatsApp "<<result.nama<<" : "<< result.nomorWa << endl;
                        cout << "Jumlah Hutang: Rp." << result.jumlahHutang << endl;
                        }
                    else
                    {
                    cout << "Nama penghutang tidak ditemukan.\n";
                    }   
                }
                else
                {
                   

                }
                cout <<endl;
                cout << "-Apakah anda ingin mencari nomor penghutang? (Y/N): ";
                char pilihan_num;
                cin >> pilihan_num;
                if (pilihan_num == 'Y')
                {
                    cout << "Masukkan nomor WhatsApp penghutang yang ingin anda cari: ";
                    cin >> nomorWa;
                    cin.ignore();
                    Hutang result;
                    int idx = carinomor(dataHutang, jumlahData, nomorWa, result);
                        if (idx != -1)
                        {
                        cout <<endl;
                        cout << "Nama penghutang: " << result.nama << endl;
                        cout << "Jumlah Hutang: Rp." << result.jumlahHutang << endl;
                        }
                    else
                    {
                    cout << "Nomor penghutang tidak ditemukan.\n";
                    }   
                }
                else
                {
                    

                }
                
            }
            else
            {
                cout << "Login gagal. Username atau password salah.\n";
            }
        }
        else if (choice == 2)
        {
            cout << "Masukkan nama pengguna baru: ";
            cin >> userName;
            cout << "Masukkan kata sandi baru (dalam bentuk bilangan bulat): ";
            cin >> userPassword;
            simpanAkun(userName, userPassword);
            cout << "Akun berhasil dibuat.\n";
        }
        else
        {
            cout << "Pilihan tidak valid.\n";
        }

        cout << endl;
        cout << "Program selesai. Ketik 'Q' untuk keluar, Atau Ketik 'Y' untuk Melanjutkan Program: ";
        cin >> exitChoice;
        cin.ignore();
    }

    return 0;
}
