#ifndef __TEXTINDEXFILE__
#define __TEXTINDEXFILE__

#include <iostream>
#include <vector>
#include <algorithm>

#include "recType.h"
#include "RecordFile.h"
#include "MetaLengthBuffer.h"
#include "TextIndexBuffer.h"

using namespace std;


class TextIndexFile {
private:
	vector<IndexElement> mIndexVector;
	bool (*mFuncCompare)(IndexElement a, IndexElement b);

	RecordFile* mRecordFile;
	TextIndexBuffer* mTextIndexBuffer;

public:
	TextIndexFile(string indexFileName, string recordFileName, bool (*compare)(IndexElement a, IndexElement b));
	~TextIndexFile();

	bool Read(recType& record, string key);
	void Remove(string key);
	void Append(recType& record, string key);

	void PrintIndex();
};
#endif // !__TEXTINDEXFILE__
