#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string FENCE = "########################################";

struct Node {
	int key{};
	double d{};
	char c;
	Node *next;
	Node *prev;
};

class List {
	int size{1};
	Node *head;
	Node *tail;
public:
	//konstruktor
	List() {
		this->head = this->tail = NULL;
	}
	void display();
	bool unique_key(int key);
	void insert_user_node(int key);
	void insert_x_nodes(int amount);
	bool find_node(int key);
	void remove_node(int key);
	void display_first_x_keys(int amount);
	void display_last_x_keys(int amount);
	void display_nodes_amount();
	void destroy_list();
};
//metoda wyswietla wszystkie wezly w liscie
void List::display() {
	if (this->size == 0) {
		cout << "Lista jest pusta!" << endl;
	}
	else {
		Node *temp_list = this->head;

		while (true) {
			cout << "Klucz: " << temp_list->key << "\t"
				<< "Double: " << temp_list->d << "\t"
				<< "Char: " << temp_list->c << endl;
			if (this->head == this->tail) {
				break;
			}
			else {
				temp_list = temp_list->next;
				if (temp_list == this->head) {
					break;
				}
			}
		}
	}
}
//metoda sprawdza czy podany klucz jest unikalny w liscie
bool List::unique_key(int key) {

	if (this->size != 1) {
		Node *temp_list = this->head;

		while (true) {
			if (temp_list->key == key) {
				return false;
			}
			else {
				//przechodzenie w liscie
				temp_list = temp_list->next;
				if (temp_list == this->head) {
					break;
				}
			}
		}
		return true;
	}
	else {
		return true;
	}
	
}
//metoda wpisuje klucz uzytkownika do listy
void List::insert_user_node(int key) {
	
	Node *user_node = new Node;
	Node *temp_node = this->head;  //potrzebne w przypadku przechodzenia listy po wezlach

	int random_double{};
	
	//sprawdzenie czy podany klucz jest unikalny w liscie
	if (unique_key(key) != true || key == 0) {	//key == 0 potrzebne zeby aktywowac warunek
		int random_key{};						//dla metody insert_x_nodes
		do {
			random_key = (rand() % 100098) + 99;
		} while (unique_key(random_key) != true);
		//warunek zeby nie wyswietlalo za kazdym razem dla metody insert_x_nodes
		if (key != 0) {
			cout << "Klucz: " << key << " nie jest unikalny!"
				<< " Wpisuje: " << random_key << endl;
		}
		user_node->key = random_key;
	}
	else {
		user_node->key = key;
	}
	
	user_node->d = random_double = rand() % 9000 - 1000;
	user_node->c = 'T';

	//jesli lista jest pusta
	if (this->size == 1) {
		this->head = this->tail = user_node;
		user_node->next = user_node->prev = user_node;
	}
	//jesli lista ma jeden element
	else if (this->size == 2) {
		if (user_node->key < this->head->key) {
			this->head = user_node;
			user_node->next = user_node->prev = this->tail;
			this->tail->next = this->tail->prev = user_node;
		}
		else {
			this->tail = user_node;
			user_node->prev = user_node->next = this->head;
			this->head->next = this->head->prev = user_node;
		}
	}
	//jesli lista ma wiecej elementow
	else {
		while (true) {
			if (user_node->key < temp_node->key) {
				//ustalenie next i prev dla nowego wezla
				user_node->next = temp_node;
				user_node->prev = temp_node->prev;
				//ustalenie polaczen do nowego wezla
				temp_node->prev->next = user_node;
				temp_node->prev = user_node;
				//jesli zamieniamy pierwszy wezel listy to w trzeba ustalic nowy head
				if (temp_node->key == this->head->key) {
					this->head = user_node;
				}
				break;
			}
			else {
				//w przypadku gdy podana liczba jest wieksza niz ogon
				if (temp_node->next->key == this->head->key) {
					//ustalenie next i prev dla nowego wezla
					user_node->next = temp_node->next;
					user_node->prev = temp_node;
					//ustalenie polaczen do nowego wezla
					temp_node->next->prev = user_node;
					temp_node->next = user_node;
					//ustalenie nowego tail
					this->tail = user_node;
					break;
				}
				else {
					temp_node = temp_node->next;
				}
			}
		}
	}

	//zwiekasza rozmiar listy
	this->size++;
	
}
//metoda dodaje x wezlow do listy
void List::insert_x_nodes(int amount) {
	if (amount >= 99 && amount <= 99999) {
		for (int i = 0; i < amount; i++) {
			insert_user_node(0);
		}
	}
	else {
		cout << FENCE << endl
			<< "Podana liczba musi byc z przedzialu od 99 do 99999" 
			<< endl << FENCE << endl;
	}
}
//metoda wyszukuje wezel z podanym kluczem
bool List::find_node(int key) {

	if (this->head != NULL) {
		Node *temp_node = this->head;  //potrzebne w przypadku przechodzenia listy po wezlach

		int place{ 1 };

		while (true) {
			if (key == temp_node->key) {
				cout << FENCE << endl
					<< "Podany klucz: '" << key
					<< "' znajduje sie na: " << place
					<< " miejscu listy." << endl;
				return true;
				break;
			}
			//jestli temp_node dojdzie do konca i wczesniej nie wypisze
			//to znaczy ze podany klucz nie znajduje sie w liscie
			else if (temp_node == this->tail) {
				cout << FENCE << endl
					<< "Klucz '" << key << "' nie znajduje sie w liscie." << endl;
				return false;
				break;
			}
			else {
				temp_node = temp_node->next;
				place++;
			}
		}
	}
	else {
		cout << "Lista jest pusta." << endl;
	}
}
//motoda usuwa klucz o podanym kluczu
void List::remove_node(int key) {

	Node *temp_node = this->head;  //potrzebne w przypadku przechodzenia listy po wezlach
	
	if (find_node(key) != false) {
		while (true) {
			if (temp_node->key == key) {
				
				if (temp_node == this->head) {
					this->head = temp_node->next;
				}
				else if (temp_node == this->tail) {
					this->tail = temp_node->prev;
				}
				//zmiana polaczen w liscie
				temp_node->prev->next = temp_node->next;
				temp_node->next->prev = temp_node->prev;
				delete temp_node;

				this->size--;
				cout << "Dlatego zostal usuniety." << endl;
				break;
			}
			else {
				temp_node = temp_node->next;
			}
		}
	}
	else {
		cout << "Dlatego nie zostal usuniety." << endl;
	}
}
//metoda wyswietla x pierwszych kluczy
void List::display_first_x_keys(int amount) {

	if (this->head != NULL) {
		Node *temp_node = this->head;  //potrzebne w przypadku przechodzenia listy po wezlach

		if (this->size > amount) {
			cout << FENCE << endl
				<< "Pierwsze " << amount << " kluczy:" << endl;

			while (amount != 0) {
				cout << temp_node->key << " ";
				temp_node = temp_node->next;
				amount--;
			}
		}
		else {
			cout << FENCE << endl
				<< "Lista jest za mala zeby wywietlic " << amount << " pierwszych kluczy.";
		}

		cout << endl;
	}
	else {
		cout << FENCE << endl << "Lista jest pusta!" << endl;
	}
}
//metoda wyswietla x ostatnich kluczy
void List::display_last_x_keys(int amount) {
	if (this->head != NULL) {
		Node *temp_node = this->tail;  //potrzebne w przypadku przechodzenia listy po wezlach

		vector<int> temp_vec;

		if (this->size > amount) {
			cout << FENCE << endl
				<< "Ostatnie " << amount << " kluczy:" << endl;

			while (amount != 0) {
				temp_vec.push_back(temp_node->key);
				temp_node = temp_node->prev;
				amount--;
			}
			for (int i = 0; i < (int)temp_vec.size(); i++)
				cout << temp_vec.at(i) << " ";
		}
		else {
			cout << FENCE << endl
				<< "Lista jest za mala zeby wywietlic " << amount << " ostatnich kluczy.";
		}

		cout << endl;
	}
	else {
		cout << FENCE << endl << "Lista jest pusta!" << endl;
	}
}
//metoda wyswietla ilosc wezlow
void List::display_nodes_amount() {
	if (this->size != 1) {
		cout << FENCE << endl
			<< "Liczba wezlow w liscie wynosi: " << this->size << endl;
	}
	else {
		cout << FENCE << endl
			<< "Liczba wezlow w liscie wynosi: " << this->size-1 << endl;
	}
}
//metoda usuwa wszystkie wezly
void List::destroy_list() {

	Node *temp_node = this->head;  //potrzebne w przypadku przechodzenia listy po wezlach

	while (true) {
		if (temp_node == this->tail) {
			delete temp_node;
			this->head = this->tail = NULL;
			this->size = 1;
			break;
		}
		else {
			temp_node = temp_node->next;
			delete temp_node->prev;
		}
	}

}
//funkcja czyta z pliku
int read_from_file(int &amount, int *list) {

	ifstream file;
	file.open("inlab02.txt");
	if (!file.is_open()) {
		cout << "Brak pliku" << endl;
		return -5;
	}
	else {
		file >> amount;
		for (int i = 0; i < 5; i++)
			file >> list[i];
		file.close();
	}
	return 0;
}

int main() {
	srand(time(NULL));

	clock_t begin, end;
	double time_spent;

	int amount{}, list[5]{};

	begin = clock();
	read_from_file(amount, list);

	List myList;

	myList.find_node(list[1]);
	myList.insert_x_nodes(amount);
	myList.display_nodes_amount();
	myList.display_first_x_keys(20);
	myList.insert_user_node(list[2]);
	myList.display_first_x_keys(20);
	myList.insert_user_node(list[3]);
	myList.display_first_x_keys(20);
	myList.insert_user_node(list[4]);
	myList.remove_node(list[2]);
	myList.display_first_x_keys(20);
	myList.remove_node(list[1]);
	myList.display_first_x_keys(20);
	myList.remove_node(list[4]);
	myList.display_nodes_amount();
	myList.find_node(list[4]);
	myList.display_last_x_keys(11);
	myList.destroy_list();
	myList.display_last_x_keys(11);
	myList.display_nodes_amount();

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << endl << "Czas wykonania programu: " << time_spent << " sekund" << endl;

}
