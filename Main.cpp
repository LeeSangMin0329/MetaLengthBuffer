#include "RecordFile.h"
#include "MetaLengthBuffer.h"
#include "Person.h"

using namespace std;

int main(void) {
	//MetaLengthBuffer m("a.txt");

	//m.Write();
	//m.Read();
	Person s("±Ë≥≤øµ", "23", "≥≤");
	Person m("¿ÃªÛπŒ", "23", "≥≤");
	RecordFile rec(new MetaLengthBuffer("a.txt"));
	rec.Write(s, 1);
	//rec.Write(m, 1);
	
	Person x("", "", "");
	rec.Read(x, 0);
	x.Print();

	return 0;
}