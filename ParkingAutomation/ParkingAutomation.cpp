//'ctime': This function or variable may be unsafe. Consider using ctime_s instead. Hatasi icin yazmam gerekti.
#pragma warning(disable:4996)

#include <iostream>
#include <string>
#include <windows.h>
#include <limits>
using namespace std;

const int numFloors = 5;
const int numParkingSpaces = 10;
//Kullanacagim fonksiyonlara rahatlikla erisim saglayabilmem icin bu sekilde bu kisimda tanimladim.
void SelectAction();
bool ListParkingSpots(int selectedFloor = -1);
void FreeSpace(int selectedFloor, int parkSpaceNumber);
void RemoveCar();
void AddCar();
void SetExamples();

//Struct yapim
struct ParkingSpot
{
	string plate;
	time_t entryTime;
};
//Struct yapidan olusturdugum dizi
ParkingSpot parkingLot[numFloors][numParkingSpaces];

int main()
{
	string listedUsername = "Admin";
	string listedPassword = "Admin";
	string username;
	string password;

	int wrongCount = 0;
	//Ornek olarak girdigim park yerleri
	SetExamples();
	cout << "Hosgeldiniz" << endl;
	Sleep(1000);
	system("CLS");
	//wrongCount 3 ten kucuk oldugu surece calisacak
	while (wrongCount < 3) {
		cout << "Kullanici adi giriniz: " << endl;
		cout << "Kullanici Adi: ";
		cin >> username;

		cout << "Sifre giriniz: " << endl;
		cout << "Sifre: ";
		cin >> password;
		//Kullanici adi ve sifre dogru ise bu kisim calisacak ve break ile whiledan cikicak
		if (username == listedUsername && password == listedPassword) {
			cout << "Hosgeldiniz " << username << endl;
			break;
		}
		//Kullanici adi ve ya sifre yanlis ise buraya giricek ve wrongcount articak.
		else {
			cout << "Hatali kullanici adi veya sifre. Lutfen tekrar deneyin." << endl;
			wrongCount++;
		}
	}
	// wrongcount 3 ten buyuk ve ya esitse
	if (wrongCount >= 3) {
		cout << "Giris denemesi 3 kere basarisiz oldu. Program kapatiliyor." << endl;
		//2 sn sonra cikis islemi yapilir
		Sleep(2000);
		exit(0);
	}


	system("cls");
	cout << "Hosgeldiniz " << username << endl;
	//Secim ekrani
	SelectAction();

	return 0;
}
void SelectAction()
{
	int choice;

	while (1) {
		cout << "1. Park halindeki araclar" << endl;
		cout << "2. Park halindeki araci cikart" << endl;
		cout << "3. Yeni arac giriniz" << endl;
		cout << "4. Cikis" << endl;
		cout << "Secenek: ";
		cin >> choice;
		cout << endl;

		switch (choice) {
		case 1:
			ListParkingSpots();
			break;
		case 2:
			RemoveCar();
			break;
		case 3:
			AddCar();
			break;
		case 4:
			return;
		default:
			cout << "Gecersiz secenek girdiniz" << endl;
		}
		cout << endl;
	}
}
void SetExamples()
{
	parkingLot[0][0].plate = "34ABC123";
	parkingLot[0][1].plate = "34EDK123";
	parkingLot[0][2].plate = "34FBG123";
	parkingLot[0][0].entryTime = time(0);
	parkingLot[0][1].entryTime = time(0);
	parkingLot[0][2].entryTime = time(0);
}
bool ListParkingSpots(int selectedFloor)
{
	//Bos yer var mi kontrolu icin
	bool hasEmptyPlace = false;
	//selectedFloor a -1 degeri yollanirsa tum katlari donduruyorum
	if (selectedFloor == -1) {
		for (int floor = 0; floor < numFloors; floor++) {
			for (int space = 0; space < numParkingSpaces; space++) {
				//belirli bir kattaki belirli bir park alanina erisim
				ParkingSpot& spot = parkingLot[floor][space];
				//park alani bos degilse
				if (!spot.plate.empty()) {
					cout << "Kat " << floor + 1 << ", Park Yeri " << space + 1 << ": " << spot.plate << " Park Halinde. Giris: " << ctime(&spot.entryTime);
				}
			}
		}
	}
	//selectedFloor -1 den farkli bir degerse burasi calisiyor
	else {
		for (int space = 0; space < numParkingSpaces; space++) {
			//belirli bir kattaki belirli bir park alanina erisim
			ParkingSpot& spot = parkingLot[selectedFloor - 1][space];
			//park alani bos degilse
			if (!spot.plate.empty()) {
				cout << "Kat " << selectedFloor << ", Park Yeri " << space + 1 << ": " << spot.plate << " Park Halinde. Giris: " << ctime(&spot.entryTime);
			}
			//park alani bossa
			else {
				cout << "Kat " << selectedFloor << ", Park Yeri " << space + 1 << ": " << "Bos" << endl;
				hasEmptyPlace = true;
			}
		}
	}


	return hasEmptyPlace;

}

void FreeSpace(int selectedFloor, int parkSpaceNumber) {

	//Eger park yeri bos degilse
	if (!parkingLot[selectedFloor - 1][parkSpaceNumber - 1].plate.empty()) {
		//Park yeri bosaltma islemi
		parkingLot[selectedFloor - 1][parkSpaceNumber - 1].plate = "";
		parkingLot[selectedFloor - 1][parkSpaceNumber - 1].entryTime = time(NULL);
		cout << "Park yeri basariyla bosaltilmistir" << endl << endl;
		//İslemden sonra listeyi gormek icin
		ListParkingSpots(selectedFloor);
		cout << "Baska bir islem yapiniz" << endl;
		//islem bittikten sonra secim ekranina donus
		SelectAction();

	}
	//Park yeri bossa
	else {
		cout << "Park Yeri Bostur, Lutfen Dolu Park Yeri Seciniz" << endl;
		RemoveCar();
	}

	FreeSpace(selectedFloor, parkSpaceNumber);
}

void RemoveCar()
{
	int selectedFloor, parkSpaceNumber;

	while (true) {
		cout << "Kat numarasi seciniz: ";
		cin >> selectedFloor;
		if (selectedFloor > 0 && selectedFloor <= numFloors)
		{
			//kattaki arabalari listeler
			ListParkingSpots(selectedFloor);
		}
		else
		{
			cout << "Gecerli bir kat giriniz" << endl;
			RemoveCar();
		}

		cout << "Park Yeri Numarasi Seciniz: ";
		cin >> parkSpaceNumber;
		//Alinan park yeri numarasi 1 den büyük ve esit olabilir ve alinan park yeri numarasi park yeri sayisindan kucuk olmali
		if (parkSpaceNumber >= 1 && parkSpaceNumber <= numParkingSpaces) {
			//Park yeri bosaltma fonksiyonu 
			FreeSpace(selectedFloor, parkSpaceNumber);
			break;
		}
		else {
			cout << "Gecersiz park yeri numarasi. Lutfen tekrar girin." << endl;
		}
	}
}
void AddCar()
{
	int selectedFloor, selectedSpace;

	cout << "Kat numarasi seciniz: ";
	cin >> selectedFloor;

	if (selectedFloor < 1 || selectedFloor > numFloors) {
		cout << "Gecerli bir kat numarasi giriniz" << endl;
		AddCar();
		return;
	}

	bool hasEmptyPlace = ListParkingSpots(selectedFloor);

	if (!hasEmptyPlace) {
		cout << "Bu katta bos yer yoktur. Lutfen baska bir kat seciniz." << endl;
		AddCar();
		return;
	}

	cout << "Park alani seciniz: ";
	cin >> selectedSpace;

	if (selectedSpace < 1 || selectedSpace > numParkingSpaces) {
		cout << "Gecerli bir park alani numarasi giriniz" << endl;
		AddCar();
		return;
	}

	if (parkingLot[selectedFloor - 1][selectedSpace - 1].plate.empty()) {
		cout << "Plaka giriniz: ";
		cin >> parkingLot[selectedFloor - 1][selectedSpace - 1].plate;
		parkingLot[selectedFloor - 1][selectedSpace - 1].entryTime = time(0);
		cout << "Arac basariyle eklenmistir" << endl;
		SelectAction();
	}
	else {
		cout << "Bu park alani doludur. Lutfen bos bir park alanı seciniz." << endl;
		AddCar();
	}
}