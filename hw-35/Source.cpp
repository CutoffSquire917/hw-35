#include <iostream>
#include <string>
#include <clocale>
using namespace std;

#pragma region First_realization

class Person {
protected:
	string name;
public:
	Person(string name) : name(name) {}
	virtual string GetName() const {
		return name;
	}
};

class Student : public Person {
public:
	Student(string n) : Person(n) {}
	string GetName() const override {
		return name;
	}
};

class Teacher : public Person {
public:
	Teacher(string n) : Person(n) {}
	string GetName() const override {
		return name;
	}
};

class School1 {
private:
	Person* people[10];
	size_t size;
public:
	School1() : size(0) {}
	void AddPerson(Person* newPerson) {
		if (size < 10) {
			people[size++] = newPerson;
		}
		else {
			cout << "School is full!" << endl;
		}
	}
	Person* GetPerson(const size_t index) const {
		if (index >= size) {
			return nullptr;
		}
		return people[index];
	}
	size_t GetSize() const {
		return size;
	}
	~School1() {
		for (int i = 0; i < size; i++) {
			delete people[i];
		}
	}
};

#pragma endregion

#pragma region Second_realization

class School2 {
private:
	shared_ptr<Person> people[10];
	size_t size;
public:
	School2() : size(0) {}
	void AddPerson(shared_ptr<Person> newPerson) {
		if (size < 10) {
			
			people[size++] = move(newPerson);
		}
		else {
			cout << "School is full!" << endl;
		}
	}
	shared_ptr<Person> GetPerson(const size_t index) const {
		if (index >= size) {
			return nullptr;
		}
		return people[index];
	}
	size_t GetSize() const {
		return size;
	}
};

#pragma endregion

#pragma region Third_realization

class Engine {
public:
	virtual string GetFuelType() const = 0;
	virtual double GetHorsePower() const = 0;
};
class PetrolEngine : public Engine {
public:
	string GetFuelType() const override {
		return "Petrol";
	}
	double GetHorsePower() const override {
		return 150;
	}
};
class ElectricEngine : public Engine {
public:
	string GetFuelType() const override {
		return "Electric";
	}
	double GetHorsePower() const override {
		return 200;
	}
};

class Car {
private:
	Engine* engine;
	string model;
	string serial_number;
	static int unique_number;
public:
	Car(Engine* engine, const string& model)
		: engine(engine), model(model) {
		if (dynamic_cast<PetrolEngine*>(engine)) {
			serial_number = "CP";
		}
		else if (dynamic_cast<ElectricEngine*>(engine)) {
			serial_number = "CE";
		}
		else {
			serial_number = "CU";
		}
		serial_number.append(string(1, char( 65 + (unique_number % 26) ))).append(to_string(unique_number));
		if (serial_number.length() < 5) {
			serial_number.insert(3, "00");
		}
		else if (serial_number.length() < 6) {
			serial_number.insert(3, "0");
		}
		unique_number++;
	}
	Engine* GetEngine() const {
		return engine;
	}
	string GetModel() const {
		return model;
	}
	string GetSerialNumber() const {
		return serial_number;
	}
	~Car() {
		delete engine;
	}
};
int Car::unique_number = 0;

class Company {
private:
	Car* cars[5];
	size_t size;
public: 
	Company() : size(0) {}
	void AddCar(Car* newCar) {
		if (size < 5) {
			cars[size++] = newCar;
		}
		else {
			cout << "Autopark is full!" << endl;
			delete newCar->GetEngine();
			delete newCar;
		}
	}
	void GetCars() const {
		for (size_t i = 0; i < size; i++)
		{
			cout << "Model : " << cars[i]->GetModel() << "\n";
			if (dynamic_cast<PetrolEngine*>(cars[i]->GetEngine())) {
				cout << "Engine type : PetrolEngine" << endl;
			}
			else if (dynamic_cast<ElectricEngine*>(cars[i]->GetEngine())) {
				cout << "Engine type : ElectricEngine" << endl;
			}
			else {
				cout << "Engine type : Unknown" << endl;
			}
			cout << "Fuel type : " << cars[i]->GetEngine()->GetFuelType() << "\n"
				 << "Horse power : " << cars[i]->GetEngine()->GetHorsePower() << "\n"
				<< "Serial number : " << cars[i]->GetSerialNumber() << "\n\n";
		}
	}
	size_t GetSize() const {
		return size;
	}
	Engine* GetBasicEngine(const size_t index) {
		if (index >= size) {
			return nullptr;
		}
		return static_cast<Engine*>(cars[index]->GetEngine());
	}
	~Company() {
		for (size_t i = 0; i < size; i++)
		{
			delete cars[i];
		}
	}
};
#pragma endregion


int main()
{
	setlocale(LC_ALL, "");
#pragma region First_usage

	//School1 school;
	//school.AddPerson(new Student("Alice"));
	//school.AddPerson(new Student("John"));
	//school.AddPerson(new Teacher("Mr. Bob"));
	//for (size_t i = 0; i < school.GetSize(); i++)
	//{
	//	if (dynamic_cast<Teacher*>(school.GetPerson(i))) {
	//		cout << "Teacher - ";
	//	}
	//	else if (dynamic_cast<Student*>(school.GetPerson(i))) {
	//		cout << "Student - ";
	//	}
	//	else {
	//		cout << "Maniac - ";
	//	}
	//	cout << school.GetPerson(i)->GetName() << endl;
	//}
	//Student* student = dynamic_cast<Student*>(school.GetPerson(0));
	//Person* maniac = static_cast<Person*>(student);
	//cout << "Student name after static_cast: " << maniac->GetName() << endl;


#pragma endregion

#pragma region Second_usage

	//School2 school;
	//school.AddPerson(make_shared<Student>("Alice"));
	//school.AddPerson(make_shared<Student>("John"));
	//school.AddPerson(make_shared<Teacher>("Mr. Bob"));
	//for (size_t i = 0; i < school.GetSize(); i++)
	//{
	//	shared_ptr<Person> person = school.GetPerson(i);
	//	if (dynamic_cast<Teacher*>(person.get())) {
	//		cout << "Teacher - ";
	//	}
	//	else if (dynamic_cast<Student*>(person.get())) {
	//		cout << "Student - ";
	//	}
	//	else {
	//		cout << "Maniac - ";
	//	}
	//	cout << school.GetPerson(i)->GetName() << endl;
	//}
	//shared_ptr<Student> to_person = static_pointer_cast<Student>(school.GetPerson(0));
	//shared_ptr<Person> maniac = to_person;
	//cout << "Student name after static_pointer_cast: " << maniac->GetName() << endl;

#pragma endregion

#pragma region Third_usage

	//Company toyota;
	//toyota.AddCar(new Car(new ElectricEngine(), "Land Cruiser 340D"));
	//toyota.AddCar(new Car(new PetrolEngine(), "GT 86"));
	//toyota.GetCars();
	//Engine* temp_e = toyota.GetBasicEngine(0);
	//cout << temp_e->GetFuelType();

#pragma endregion
}