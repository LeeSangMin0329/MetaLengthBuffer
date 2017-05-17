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
	rec.Write(s);
	rec.Write(m);
	
	Person x("", "", "");
	rec.Read(x);
	x.Print();

	return 0;
}