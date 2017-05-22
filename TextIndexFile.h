#ifndef __TEXTINDEXFILE__
#define __TEXTINDEXFILE__

#include <iostream>
#include <vector>

#include "recType.h"
#include "RecordFile.h"
#include "MetaLengthBuffer.h"
#include "TextIndexBuffer.h"

using namespace std;


class TextIndexFile {
private:
	vector<IndexElement> mIndexVector;
	
	fstream mIndexStream;

	RecordFile* mRecordFile;
	TextIndexBuffer* mTextIndexBuffer;

public:
	TextIndexFile(string indexFileName, string recordFileName);
	~TextIndexFile();

	void Read(string key);
	void Remove(string key);
	void Append(recType* record, string key);

	void PrintIndex();
	

};
#endif // !__TEXTINDEXFILE__
