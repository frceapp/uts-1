#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#define MAX_SETOR_TARIK 100

typedef char string[255];

void daftarNasabah(char *nama, char *alamat, int *ktp, int *pin);
void displayNasabah(string nama, string alamat, int ktp, int saldo);
void displaySetorTarik(int setor[], int tarik[], int count_setor, int count_tarik);
bool checkPIN(bool *blokir, int pin);
void setorTarikUang(int saldo, int arr[], int count);

int main() {
	char nama[255], alamat[255];
	int pilihan, pin = 0, ktp=0, saldo = 0, count_setor = 0, count_tarik = 0, saldo_input;

	bool blokir = false, pin_valid = false;

	int setor[MAX_SETOR_TARIK], tarik[MAX_SETOR_TARIK];
	
	do {
		system("cls");
		
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
				daftarNasabah(nama, alamat, &ktp, &pin);
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

					if (count_setor <= 99) {
						setorTarikUang(saldo_input, setor, count_setor);
						saldo += saldo_input;
						count_setor++;
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
						if (count_tarik <= 99) {
							setorTarikUang(saldo_input, tarik, count_tarik);
							saldo -= saldo_input;
							count_tarik++;
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

void daftarNasabah(char *nama, char *alamat, int *ktp, int *pin) {
	puts("Data Nasabah Baru");
    printf("Nama: ");
    scanf("%s", nama);
    printf("Alamat: ");	
    scanf("%s", alamat);
    printf("Nomor KTP: ");
    scanf("%d", ktp);
    printf("Setup PIN: ");
    scanf("%d", pin);
    puts("Data nasabah baru berhasil disimpan!");
}

bool checkPIN(bool *blokir, int pin) {
	int input_pin, kesempatan = 3, pin_benar=true;

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
				(*blokir) = true;
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
	arr[count] = saldo;
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
	if (count_setor == 0 && count_tarik == 0){
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




