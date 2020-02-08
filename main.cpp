/* @Author
* Student Name: Doðu Ozan KUMRU
* Student ID : 150160012
* Date: 06.05.2019 */

#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdio> 

using namespace std;

#define MAX_SIZE 1000

class ingredients {                                                                          //ingredients base class for types 
protected:
	string Name;
public:
	virtual ~ingredients() {}
	virtual void print_operator(){}															 //virtual functions for derived class
	virtual void print_operator2(){}
	virtual string get_name(){
		return 0;
	}
	virtual int get_count() {
		return 0;
	}
	virtual float get_price() {
		return 0;
	}
	virtual int get_type() {
		return 0;
	}
	virtual void set_count(int new_number) {}
};

class type1 : public ingredients {															//type1 class derived from ingredients
	int weight;
	float price_per_grams;
	int type;
public:
	type1(int count, float price, string name) {											//Constructor
		weight = count;
		price_per_grams = price;
		Name = name;
		type = 1;
	}
	type1(int count, string name) {															//Constructor for food class
		weight = count;
		Name = name;
		type = 1;
	}
	~type1() {																				//Deallocate allocated memory
		delete this;
	}
	void print_operator() {
		cout << Name << " " << 1 << " " << weight << " " << price_per_grams << endl;
	}

	void print_operator2() {
		cout << Name << " " << weight << endl;
	}
	string get_name() {																		//Getter function
		return Name;
	}
	int get_count() {																		//Getter function
		return weight;
	}
	float get_price() {																		//Getter function
		return price_per_grams;
	}
	int get_type() {																		//Getter function
		return type;
	}
	void set_count(int new_number) {														//Setter function
		weight = new_number;
	}
};

class type2 : public ingredients {															//type2 class derived from ingredients
	int number;
	float price_per_unit;
	int type;
public:
	type2(int count, float price,string name) {												//Constructor
		number = count;
		price_per_unit = price;
		Name = name;
		type = 2;
	}
	type2(int count, string name) {															//Constructor for food class
		number = count;
		Name = name;
		type = 2;
	}
	~type2() {																				//Deallocate allocated memory
		delete this;
	}
	void print_operator() {
		cout << Name << " " << 2 << " " << number << " " << price_per_unit << endl;
	}

	void print_operator2() {
		cout << Name << " " << number << endl;
	}
	string get_name() {																		//Getter function
		return Name;
	}
	int get_count() {																		//Getter function
		return number;
	}
	float get_price() {																		//Getter function
		return price_per_unit;
	}
	int get_type() {																		//Getter function
		return type;
	}
	void set_count(int new_number) {														//Setter function
		number = new_number;
	}
};

class type3 : public ingredients {															//type3 class derived from ingredients
	int milliliter;
	float price_per_milliliter;
	int type;
public:
	type3(int count, float price, string name) {											//Constructor
		milliliter = count;
		price_per_milliliter = price;
		Name = name;
		type = 3;
	}
	type3(int count, string name) {															//Constructor for food class
		milliliter = count;
		Name = name;
		type = 3;
	}
	~type3() {																				//Deallocate allocated memory
		delete this;
	}
	void print_operator() {
		cout << Name << " " << 3 << " " << milliliter << " " << price_per_milliliter << endl;
	}

	void print_operator2() {
		cout << Name << " " << milliliter << endl;
	}
	string get_name() {																		//Getter function
		return Name;
	}
	int get_count() {																		//Getter function
		return milliliter;
	}
	float get_price() {																		//Getter function
		return price_per_milliliter;
	}
	int get_type() {																		//Getter function
		return type;
	}
	void set_count(int new_number) {														//Setter function
		milliliter = new_number;
	}
};

class Stock {																				//Stock class for stock.txt
	ingredients *stocks[MAX_SIZE];
	int stock_num;
public:
	Stock() {
		stock_num = 0;
	}
	void Read_Stock() {																		//Read from stock.txt
		FILE* file;
		char name[100];
		int type, count;
		float price;
		char source[1000];
		file = fopen("stock.txt", "r");
		if (!file) {
			cout << "File opening failed" << endl;
			return;
		}
		fgets(source, 1000, file);
		while (fgets(source, 1000, file)) {
			sscanf(source, "%[^\t\n] %d %d %f", name, &type, &count, &price);

			if (type == 1) {																//Create ingrediendts
				ingredients *ptr = new type1(count, price, name);
				stocks[stock_num] = ptr;
				stock_num++;
			}
			if (type == 2) {
				ingredients *ptr = new type2(count, price, name);
				stocks[stock_num] = ptr;
				stock_num++;
			}
			if (type == 3) {
				ingredients *ptr = new type3(count, price, name);
				stocks[stock_num] = ptr;
				stock_num++;
			}
		}
		fclose(file);
	}
	void print_operators() {																	
		for (int i = 0; i < stock_num; i++) {
			stocks[i]->print_operator();
		}
	}
	float cost(string name, int number) {													//Calculate cost
		for (int i = 0; i < stock_num; i++) {
			if ((stocks[i]->get_name()) == name) {
				return (stocks[i]->get_price()) * number;
			}
		}
		return 0;
	}
	bool enough(string name, int number) {													//Look for enough stock
		for (int i = 0; i < stock_num; i++) {
			if ((stocks[i]->get_name()) == name) {
				if ((stocks[i]->get_count()) < number) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		return false;
	}
	void re_stock(string name, int number) {												//Edit stock
		for (int i = 0; i < stock_num; i++) {
			if ((stocks[i]->get_name()) == name) {
				stocks[i]->set_count((stocks[i]->get_count()) - number);
			}
		}
	}
	void print_stock() {																	//Write last version of stock to stock.txt
		FILE* file;
		file = fopen("stock.txt", "w");
		if (!file) {
			cout << "File opening failed" << endl;
			return;
		}
		fprintf(file, "Name	Type	ItemCount	Price\n");
		for (int i = 0; i < stock_num; i++) {
			char name[100];
			strcpy(name, stocks[i]->get_name().c_str());
			fprintf(file, "%s", name);
			if (stocks[i]->get_price() < 1) {
				if (stocks[i]->get_price() < 0.1) {
					fprintf(file, "	%d	%d	%.2f\n", stocks[i]->get_type(), stocks[i]->get_count(), stocks[i]->get_price());
				}
				else if (stocks[i]->get_name() == "beef") {
					fprintf(file, "	%d	%d	0.44\n", stocks[i]->get_type(), stocks[i]->get_count());
				}
				else {
					fprintf(file, "	%d	%d	%.1f\n", stocks[i]->get_type(), stocks[i]->get_count(), stocks[i]->get_price());
				}
			}
			else {
				fprintf(file, "	%d	%d	%.f\n", stocks[i]->get_type(), stocks[i]->get_count(), stocks[i]->get_price());
			}
		}
		fclose(file);
	}
};

class Food {																				//Food class for food in the menu.txt
	string Name;
	ingredients *Ingredient[MAX_SIZE];
	int Ingredient_num;
	float price;
public:
	Food (char* name) {
		Name = name;
		Ingredient_num = 0;
	}
	~Food() {																				//Deallocate allocated memory
		delete this;
	}
	void print_operator() {
		cout << Name << endl;
		for (int i = 0; i < Ingredient_num; i++) {
			Ingredient[i]->print_operator2();
		}
		cout << price << endl;
	}
	void set_price(float price) {															//Setter function
		this->price = price;
	}
	string get_name() {																		//Getter function
		return Name;
	}
	float get_price() {																		//Getter function
		return price;
	}
	bool enough(string name, int number, Stock s1) {										//Look for enough stock
		if (Ingredient_num == 0) {
			if (!(s1.enough(name, number))) {
				return false;
			}
		}
		for (int i = 0; i < Ingredient_num; i++) {
			if (!(s1.enough(Ingredient[i]->get_name(), (Ingredient[i]->get_count())*number))) {
				return false;
			}
		}
		return true;
	}
	void re_stock(string name, int number, Stock s1) {										//Edit stock
		if (Ingredient_num == 0) {
			s1.re_stock(name, number);
		}
		for (int i = 0; i < Ingredient_num; i++) {
			s1.re_stock(Ingredient[i]->get_name(), (Ingredient[i]->get_count())*number);
		}
	}
	friend class Menu;
};

class Menu {																				//Menu class for menu.txt
	Food * foods[MAX_SIZE];
	int food_num;
public:
	Menu() {
		food_num = 0;
	}
	void read_menu(Stock s1) {																//Read from menu.txt
		FILE* file;
		char name[100];
		int number;
		char str[100];
		char str2[100];
		string food_ingredient;
		char source[1000];
		char source2[1000];
		char f_ingr[100];
		file = fopen("menu.txt", "r");
		if (!file) {
			cout << "File opening failed" << endl;
			return;
		}
		fgets(source, 1000, file);
		while (fgets(source, 1000, file)) {
			sscanf(source, "%[^\t\n] %[^\t\n]", name, source2);
			Food* fptr = new Food(name);
			float cost = 0;
			stringstream ss1(source2);
			while (getline(ss1, food_ingredient, ',')) {
				if (food_ingredient != "N/A") {
					strcpy(f_ingr, food_ingredient.c_str());
					sscanf(f_ingr, "%d %s %[^\t\n]", &number, str, str2);
					string gram = "gram";
					string ml = "ml";
					string red = "red";
					if (str == gram) {														//Create foods
						ingredients *ptr = new type1(number, str2);
						cost += s1.cost(str2, number);
						fptr->Ingredient[fptr->Ingredient_num] = ptr;
						fptr->Ingredient_num++;
					}
					else if (str == ml) {
						ingredients *ptr = new type3(number, str2);
						cost += s1.cost(str2, number);
						fptr->Ingredient[fptr->Ingredient_num] = ptr;
						fptr->Ingredient_num++;
					}
					else if (str == red) {
						ingredients *ptr = new type2(number, "red paper");
						cost += s1.cost("red paper", number);
						fptr->Ingredient[fptr->Ingredient_num] = ptr;
						fptr->Ingredient_num++;
					}
					else {
						ingredients *ptr = new type2(number, str);
						cost += s1.cost(str, number);
						fptr->Ingredient[fptr->Ingredient_num] = ptr;
						fptr->Ingredient_num++;
					}
					for (int i = 0; i < 10; i++) {
						str2[i] = 0;
					}
				}
				else {
					cost = s1.cost(name, 1);
				}
			}
			fptr->set_price(cost);
			foods[food_num] = fptr;
			food_num++;
		}
		fclose(file);
	}

	void print_operators() {
		for (int i = 0; i < food_num; i++) {
			foods[i]->print_operator();
		}
	}
	float cost(string name, int number) {													//Calculate cost
		for (int i = 0; i < food_num; i++) {
			if ((foods[i]->get_name()) == name) {
				return (foods[i]->get_price()) * number;
			}
		}
		return 0;
	}
	bool enough(string name, int number, Stock s1) {										//Look for enough stock
		for (int i = 0; i < food_num; i++) {
			if ((foods[i]->get_name()) == name) {
				if (foods[i]->enough(name, number, s1)) {
					foods[i]->re_stock(name, number, s1);
					return true;
				}
				else {
					return false;
				}
			}
		}
		return false;
	}
};

int main() {
	Stock s1;
	s1.Read_Stock();

	Menu m1;
	m1.read_menu(s1);

	FILE* file;																				//Read from order.txt
	file = fopen("order.txt", "r");
	if (!file) {
		cout << "File opening failed" << endl;
		return 0;
	}
	char source[1000];
	char ingredient[100];
	int number, iteration_num;
	float cost, total_cost;
	for (int k = 0; k < 5; k++) {
		total_cost = 0;
		fgets(source, 1000, file);
		if (source[0] == 'T') {
			cout << "Table" << k + 1 << " ordered:" << endl;
			fgets(source, 1000, file);
			sscanf(source, "%d", &iteration_num);
			for (int i = 0; i < iteration_num; i++) {
				fgets(source, 1000, file);
				sscanf(source, "%d %[^\t\n]", &number, ingredient);
				if (m1.enough(ingredient, number,s1)) {
					cost =m1.cost(ingredient, number);
					total_cost += cost;
					cout << number << " " << ingredient << " cost: " << cost << endl;	
				}
				else {
					cout << "We don't have enough " << ingredient << endl;
				}
			}
			float tip, total;																//Write checkouts
			tip = (total_cost / 100) * 15;
			total = tip + total_cost + (total_cost / 100) * 8;
			cout << "Tip is " << tip << endl;
			cout << "Total cost: " << total << " TL" << endl;
			cout << "**************************" << endl;
		}
		iteration_num = 0;
	}
	fclose(file);

	s1.print_stock();

	return 0;
}