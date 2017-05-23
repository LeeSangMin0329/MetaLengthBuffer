#include "TextIndexFile.h"
#include "Person.h"

using namespace std;

// user customize
bool compare(IndexElement a, IndexElement b) {
	if (a.field[0] < b.field[0])
		return true;
	else
		return false;
}

int main(void) {
	
	TextIndexFile f("Index.dat", "Record.dat", compare);
	Person p("", "", "");

	string order;


	while (true) {
		cout << endl;
		cout << "SYSTEM: input command" << endl;
		cout << "SYSTEM: you select \"printindex\", \"append\", \"remove\" or \"read\"" << endl;
		cout << endl;
		cout << "SYSTEM: command : ";
		cout.flush();
		cin >> order;

		cout << endl;
		if (order == "printindex") {
			f.PrintIndex();
		}
		else if (order == "append") {
			cout << "SYSTEM: you append Person class { name, age, sex }" << endl;
			cout << "SYSTEM: input name : ";
			cout.flush();
			cin >> p.name;
			cout << "SYSTEM: inpue age : ";
			cout.flush();
			cin >> p.age;
			cout << "SYSTEM: input sex : ";
			cout.flush();
			cin >> p.sex;
			while (true) {
				cout << "SYSTEM: what is the key? { name, age, sex } : ";
				cout.flush();
				cin >> order;
				if (order == "name") {
					f.Append(p, p.name);
					break;
				}
				else if (order == "age") {
					f.Append(p, p.age);
					break;
				}
				else if (order == "sex") {
					f.Append(p, p.sex);
					break;
				}
				else {
					cout << "SYSTEM: Invalid key section, try again" << endl;
					cout.flush();
				}
			}
		}
		else if (order == "remove") {
			cout << "SYSTEM: input key : ";
			cout.flush();
			cin >> order;
			f.Remove(order);
		}
		else if (order == "read") {
			cout << "SYSTEM: input key : ";
			cout.flush();
			cin >> order;
			if(f.Read(p, order))
				p.Print();
		}
		else {
			cout << "SYSTEM: Invalid command, try again" << endl;
			cout.flush();
		}
	}

	return 0;
}