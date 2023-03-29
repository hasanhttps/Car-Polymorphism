#include <iostream>
#include <cassert>
#include <vector>
using namespace std;
typedef unsigned short ushort;



class Car {
public:
	size_t id;
	static size_t staticId;
	string marka;
	string model;
	ushort year;
	ushort price;



	Car() : id(++staticId) { }
	Car(string marka, string model, ushort year, ushort price) : Car() {
		setMarka(marka);
		setModel(model);
		setYear(year);
	}



	void setMarka(string marka) {
		this->marka = marka;
	}
	void setModel(string model) {
		this->model = model;
	}
	void setYear(ushort year) {
		this->year = year;
	}
	void setPrice(ushort price) {
		this->price = price;
	}
	virtual void getSound() {
		cout << "Car sound.";
	}
	virtual void print() const{
		cout << "Marka : " << marka << endl
			<< "Model : " << model << endl
			<< "Year : " << year << endl;
	}
};



size_t Car::staticId = 0;



class Manual : public Car {
public:
	ushort gearCount;

	Manual() : gearCount(0) { }
	Manual(string marka, string model, ushort year, ushort price, ushort gearCount) : gearCount(gearCount),
		Car(marka, model, year, price) { }




	void getSound() override {
		cout << "Manual Car sound.";
	}
	void print() const{
		Car::print();
		cout << "Gear Count : " << gearCount << endl;
	}



};




class Automatic : public Car {
public:
	bool isHand;


	Automatic() : isHand() {}
	Automatic(string marka, string model, ushort year, ushort price,bool isHand) : isHand(isHand),
			Car(marka, model, year, price) { }


	void getSound() override {
		cout << "Automatic Car sound.";
	}
	void print() const{
		Car::print();
		cout << "Gear Type : " << ((isHand) ? "Hand" : "Foot") << endl;
	}
};




class Bmw : public Automatic {
	ushort grilleCount;// Izgara sayi
public:

	Bmw() : grilleCount(0) { }
	Bmw(ushort grilleCount, string marka, string model, ushort year, ushort price, bool isHand) : grilleCount(grilleCount),
		Automatic(marka, model, year, price, isHand) {  }

	void print() const{
		Automatic::print();
		cout << "Grille Count : " << grilleCount << endl;
	}

	friend ostream& operator<<(ostream& print, const Bmw& other) {
		other.print();

		return print;
	}
};


class TeslaTruck : public Manual {
	bool selfDrive;
public:

	TeslaTruck() {}
	TeslaTruck(bool selfDrive, string marka, string model, ushort year, ushort price, ushort gearCount) : selfDrive(selfDrive),
			Manual(marka, model, year, price, gearCount) {}


	void print() const {
		Manual::print();
		cout << "Self Drive Mode : " << boolalpha << selfDrive << endl;
	}

	friend ostream& operator<<(ostream& print, const TeslaTruck& other) {
		other.print();

		return print;
	}

	
};


class Base {
public:
	vector<Bmw*> bmws;
	vector<TeslaTruck*> teslas;

	Base() { }
	Base(vector<Bmw*> bmws, vector<TeslaTruck*> teslas) : bmws(bmws), teslas(teslas) { }

};	


void show(const Base& other) {
	for (int i = 0; i < other.bmws.size(); i++) cout << (*other.bmws[i]) << endl;
	for (int i = 0; i < other.teslas.size(); i++) cout << (*other.teslas[i]) << endl;
}


int main() {
	Bmw* bm1 = new Bmw(2, "Bmw", "CX-5", 2022, 50000, true);
	Bmw* bm2 = new Bmw(2, "Bmw", "CX-6", 2023, 150000, false);


	vector<Bmw*> bmws;

	bmws.push_back(bm1);
	bmws.push_back(bm2);


	TeslaTruck* t1 = new TeslaTruck(true, "Bmw", "CX-5", 2022, 50000, 6);
	TeslaTruck* t2 = new TeslaTruck(false, "Bmw", "CX-6", 2023, 150000, 4);


	vector<TeslaTruck*> teslas;

	teslas.push_back(t1);
	teslas.push_back(t2);

	Base base(bmws, teslas);
	show(base);
}