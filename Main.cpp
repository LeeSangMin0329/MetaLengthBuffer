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
	rec.Write(s, 1);
	//rec.Write(m, 1);
	
	Person x("", "", "");
	rec.Read(x, 0);
	x.Print();

	return 0;
}