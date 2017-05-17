#pragma once

#ifndef __PERSON__
#define __PERSON__

#include "recType.h"

class Person : public recType {
public:
	string name;
	string age;
	string sex;
	
	Person(string, string, string);
	void Print();

// Inheritance Virtual Method area
	void Pack(FileStream* f);
	void UnPack(FileStream* f);
};

Person::Person(string name, string age, string sex) {
	this->name = name;
	this->age = age;
	this->sex = sex;
}

void Person::Pack(FileStream* f) {
	f->Pack(name);
	f->Pack(age);
	f->Pack(sex);
}

void Person::UnPack(FileStream* f) {
	name = f->UnPack();
	age = f->UnPack();
	sex = f->UnPack();
}

void Person::Print() {
	cout << "name : " << name << endl;
	cout << "age : " << age << endl;
	cout << "sex : " << sex << endl;
}
#endif // !__PERSON__
