#include "RecordFile.h"
#include "MetaLengthBuffer.h"
#include "Person.h"

using namespace std;

int main(void) {
	//MetaLengthBuffer m("a.txt");

	//m.Write();
	//m.Read();
	Person s("김남영", "23", "남");
	Person m("이", "3", "남");
	RecordFile rec(new MetaLengthBuffer("a.txt"));
	//rec.Write(m, 1);
	//rec.Write(m, 6);
	//rec.Remove(6);

	Person x("", "", "");
	//rec.Read(x, 1);
	x.Print();

	return 0;
}