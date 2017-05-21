#ifndef __TEXTINDEXFILE__
#define __TEXTINDEXFILE__

#include <iostream>
#include <vector>

#include "recType.h"
#include "RecordFile.h"
#include "MetaLengthBuffer.h"

using namespace std;

class IndexElement {
public:
	string field;
	streampos addr;
};

class TextIndexFile {
private:
	vector<IndexElement> mIndexVector;
	RecordFile* mRecordFile;

	void WriteIndex();
	void ReadIndex();

public:
	void Read(string key);
	void Remove(string key);
	void Append(recType* record, string key);
	

};
#endif // !__TEXTINDEXFILE__
