#include "RecordFile.h"
#include "MetaLengthBuffer.h"
#include "Person.h"

using namespace std;

int main(void) {
	//MetaLengthBuffer m("a.txt");

	//m.Write();
	//m.Read();
	Person s("�賲��", "23", "��");
	Person m("�̻��", "23", "��");
	RecordFile rec(new MetaLengthBuffer("a.txt"));
	rec.Write(s);
	rec.Write(m);
	
	Person x("", "", "");
	rec.Read(x);
	x.Print();

	return 0;
}