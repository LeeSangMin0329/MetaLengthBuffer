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
	
	TextIndexFile f("in.txt", "a.txt", compare);
	Person p("", "", "");

	string order;


	while (true) {
		cout << endl;
		cout << "SYSTEM: input command" << endl;
		cout << "SYSTEM: you select \"printindex\", \"append\", \"remove\" or \"read\"" << endl;
		cout << endl;
		cout << "SYSTEM: input : ";
		cout.flush();
		cin >> order;
		fflush(stdin);

		cout << endl;
		if (order == "printindex") {
			f.PrintIndex();
		}
		else if (order == "append") {
			cout << "SYSTEM: you append Person class { name, age, sex }" << endl;
			cout << "SYSTEM: input name : ";
			cout.flush();
			cin >> p.name;
			fflush(stdin);
			cout << "SYSTEM: inpue age : ";
			cout.flush();
			cin >> p.age;
			fflush(stdin);
			cout << "SYSTEM: input sex : ";
			cout.flush();
			cin >> p.sex;
			fflush(stdin);
			while (true) {
				cout << "SYSTEM: what is the key? : ";
				cout.flush();
				cin >> order;
				fflush(stdin);
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
			fflush(stdin);
			f.Remove(order);
		}
		else if (order == "read") {
			cout << "SYSTEM: input key : ";
			cout.flush();
			cin >> order;
			fflush(stdin);
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