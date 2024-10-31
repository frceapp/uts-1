#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#define MAX_SETOR_TARIK 100

typedef char string[255]; // alias tipe data untuk menyingkat char variable[255]

void daftarNasabah(string *nama, string *alamat, int *ktp, int *pin, int setor[], int tarik[], bool *blokir, int *saldo, int *count_setor, int *count_tarik); // mendaftarkan nasabah
void initSetorTarik(int arr[]);
void displayNasabah(string nama, string alamat, int ktp, int saldo); // menampilkan data nasabah
void displaySetorTarik(int setor[], int tarik[], int count_setor, int count_tarik); // cek riwayat setor & penarikan
bool checkPIN(bool *blokir, int pin); // mengecek pin
void setorTarikUang(int saldo, int arr[], int count); // memasukan data ke array setor atau tarik

int main() {
	string nama, alamat; // tipe data sama dengan char variable_name[255]
	int pilihan, pin = 0, ktp= 0, saldo = 0, count_setor = 0, count_tarik = 0, saldo_input;
	// count_tarik & saldo_input digunakan untuk menghitung dan indexing array setor & input

	bool blokir = false, pin_valid = false;

	int setor[MAX_SETOR_TARIK], tarik[MAX_SETOR_TARIK]; // jumlah maksimal per array 100
	
	do {
		system("cls"); // mengclear output puts / printf sebelumnya
		
		puts("Menu Bank");
		puts("1. Daftar Nasabah");
		puts("2. Setor Uang");
		puts("3. Tarik Uang");
		puts("4. Lihat Data Nasabah & Saldo");
		puts("5. Lihat Riwayat Setor & Penarikan");
		puts("0. Exit");
		printf("Pilih menu: ");scanf("%d", &pilihan);

		switch (pilihan)
		{
			case 1:
				daftarNasabah(&nama, &alamat, &ktp, &pin, setor, tarik, &blokir, &saldo, &count_setor, &count_tarik);
				getch();
				break;
			case 2:
				if (blokir == true) {
					puts("Data nasabah diblokir!");
					getch();
					break;
				}

				pin_valid = checkPIN(&blokir, pin);
				if (pin_valid == true) {
					printf("Input setoran: ");scanf("%d", &saldo_input);

					if (count_setor <= 99) { // melimit transaksi setor sampai 100 kali
						setorTarikUang(saldo_input, setor, count_setor);
						saldo += saldo_input; // menambah saldo
						count_setor++; // menambah 1 ke index setor sekarang
					}
				}
				
				getch();
				break;
			case 3:
				if (blokir == true) {
					puts("Data nasabah diblokir!");
					getch();
					break;
				}

				pin_valid = checkPIN(&blokir, pin);
				if (pin_valid == true) {
					printf("Tarik sebesar: ");scanf("%d", &saldo_input);

					if (saldo_input <= saldo) {
						if (count_tarik <= 99) { // melimit transaksi tarik sampai 100 kali
							setorTarikUang(saldo_input, tarik, count_tarik);
							saldo -= saldo_input; // mengurangi saldo
							count_tarik++; // menambah 1 ke index tarik sekarang
						}
					} else {
						puts("Maaf, saldo tidak mencukupi!");
					}
				}
				
				getch();
				break;
			case 4:
				/*if (blokir == true){
					puts("Data nasabah diblokir!");
					getch();
					break;
				}*/
				displayNasabah(nama, alamat, ktp, saldo);
				getch();
				break;
			case 5:
				/*if (blokir == true){
					puts("Data nasabah diblokir!");
					getch();
					break;
				}*/
				displaySetorTarik(setor, tarik, count_setor, count_tarik);
				getch();
				break;;
			
			default:
				break;
		}

	} while (pilihan != 0);
	
	getch();
	return 0;
}

void initSetorTarik(int arr[]) {
	int i;
	for (i = 0; i <= MAX_SETOR_TARIK; i++)
	{
		arr[i] = 0; // mengisi semua array dengan 0
	}
};

void daftarNasabah(string *nama, string *alamat, int *ktp, int *pin, int setor[], int tarik[], bool *blokir, int *saldo, int *count_setor, int *count_tarik) {
	puts("Data Nasabah Baru");
    printf("Nama: ");
    scanf("%s", nama);
    printf("Alamat: ");	
    scanf("%s", alamat);
    printf("Nomor KTP: ");
    scanf("%d", ktp);
    printf("Setup PIN: ");
    scanf("%d", pin);

	// mereset variable
	initSetorTarik(setor);
	initSetorTarik(tarik);
	(*blokir) = false;
	(*saldo) = 0;
	(*count_setor) = 0;
	(*count_tarik) = 0;

    puts("Data nasabah baru berhasil disimpan!");
}

bool checkPIN(bool *blokir, int pin) {
	int input_pin, kesempatan = 3;

	if (pin == 0) {
		printf("Belum ditemukan data nasabah!");
		return false;
	}

	while (kesempatan != 0)
	{
		printf("Input PIN:");scanf("%d", &input_pin);

		if (pin != input_pin) {
			kesempatan--;

			if (kesempatan == 0) {
				puts("Maaf data nasabah akan diblokir!");
				(*blokir) = true; // variable blokir akan dikembalikan ke main
			} else {
				printf("PIN yang dimasukkan salah! %d kesempatan lagi!\n", kesempatan);
			}
			
			
		} else {
			return true;
		}
	}

	return false;
}

void setorTarikUang(int saldo, int arr[], int count) {
	arr[count] = saldo; // memasukan data sesuai index sekarang ke array
}

void displayNasabah(string nama, string alamat, int ktp, int saldo){
if (ktp == 0) {
	puts("Belum ada data nasabah!");
} else{
	printf("Nama: %s \nAlamat: %s \nKTP: %d \nSaldo: %d", nama, alamat, ktp, saldo);
}
}


void displaySetorTarik(int setor[], int tarik[], int count_setor, int count_tarik) {
	int i;
	if (count_setor == 0 && count_tarik == 0){ // mengecek transaksi sudah pernah dilakukan atau belum
		puts("Belum ada riwayat transaksi!");
	}
	for (i = 0; i < count_setor; i++)
	{
		printf("Setor: %d\n", setor[i]);
	}

	for (i = 0; i < count_tarik; i++)
	{
		printf("Tarik: %d\n", tarik[i]);
	}
	
}




