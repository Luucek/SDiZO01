#include <iostream>
#include <ctime>
#include<fstream>
#include<string>

//funkcja wczytuje dane z pliku
int readFile(int &amount, char &marker);
//funkcja tworzy tablice znacznikow
struct Struktura** createArray(int amount);
//funkcja zwalniajaca pamiec zajeta przez struktury
void removeArray(Struktura** structuresArray, int size);
//funkcja sortujaca struktury
void sortArray(Struktura** structuresArray, int size);
//funkcja zlicza ile razy wystepuje okreslony znak
int markAmount(Struktura** structuresArray, int size, char marker);
//funkcja sprawdza czy wylosowany numer nie zostal wpisany wczesniej
bool checkNumber(int randomNumber, Struktura** structuresArray, int count);

//zmienne globalne
int N;
char mark;

struct Struktura {
	int a;
	char c;
	float f;
};

int main()
{
	srand(time(NULL));
	
	clock_t begin, end;
	double time_spent;

	if (readFile(N, mark) != -1) {
		
		begin = clock();  //rozpoczyna pomiar czasu

		//wyswietla zawartosc podanego pliku:
		//std::cout << N << " " << mark << std::endl;
		
		Struktura** array_of_pointers = createArray(N);

		sortArray(array_of_pointers, N);

		//wyswietla wartosci struktur
		std::cout << "20 posortowanych struktur ze wszystkich " << N << " struktur:" << std::endl << std::endl;
		for (int i = 0; i < 20; i++) {
			std::cout << array_of_pointers[i]->a << " ";
			std::cout << array_of_pointers[i]->c << " ";
			std::cout << array_of_pointers[i]->f << std::endl;
		}
		//wywietla ile razy wygenerowal sie podany znak z pliku:
		std::cout << std::endl << "Ilosc '" << mark << "': " << markAmount(array_of_pointers, N, mark);
		
		//usuwanie zaalokowanych adresow pamieci
		removeArray(array_of_pointers, N);
		
		end = clock();  //konczy pomiar czasu
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		//wyswietla jak dlugo wykonywal sie program
		std::cout << std::endl << std::endl << "Program wykonywal sie: " << time_spent << std::endl;

		system("PAUSE");
		return 1;
	}
	else {
		//jesli odczytanie z pliku sie nie powiedzie to program zwroci wartosc -10
		return -10;
	}
}
int readFile(int &amount, char &marker) {
	std::ifstream myFile("inlab01.txt");
	if (myFile.is_open()) {
		myFile >> amount;
		myFile >> marker;
		myFile.close();
	}
	else {
		std::cout << "Nie mozna odczytac pliku." << std::endl;
		return -1;
	}

	return 1;
}
struct Struktura** createArray(int amount) {

	Struktura **structuresArray = new Struktura*[amount];
	
	int myRandomNumber = 0;

	for (int i = 0; i < amount; i++) {

		structuresArray[i] = new Struktura();

		//sprawdza czy wylosowany numer nie zostal wpisany wczesniej
		do {
			myRandomNumber = rand() % 9000 - 1000;
		} while (checkNumber(myRandomNumber, structuresArray, i) == true);
		
		structuresArray[i]->a = myRandomNumber;

		structuresArray[i] -> c = 'B' + rand() % 22;
		if (i > 0) {
			structuresArray[i] -> f = 1001 + i;
		}
		else {
			structuresArray[i] -> f = 1001;
		}
	}
	
	return structuresArray;
}

void sortArray(Struktura** structuresArray, int size) {

	Struktura* temp_value;
	int OK = 0;

	for (int i = 0; i < size; i++) {
		OK = 1;
		for (int j = 0; j < size - 1; j++) {
			if (structuresArray[j]->a > structuresArray[j + 1]->a) {
				temp_value = structuresArray[j];
				structuresArray[j] = structuresArray[j + 1];
				structuresArray[j + 1] = temp_value;
				OK = 0;
			}
		}
		if (OK != 0)
			return;
	}
}

int markAmount(Struktura** structuresArray, int size, char marker) {
	
	int counter = 0;
	
	for (int i = 0; i < size; i++) {
		if (structuresArray[i]->c == marker) {
			counter++;
		}
	}
	
	return counter;
}

bool checkNumber(int randomNumber, Struktura** structuresArray, int count) {

	for (int i = 0; i < count; i++) {
		if (structuresArray[i]->a == randomNumber) {
			return true;
		}
	}
	return false;
}

void removeArray(Struktura** structuresArray, int size) {

	for (int i = 0; i < size; i++) {
		delete structuresArray[i];
	}

	delete[] structuresArray;
}
