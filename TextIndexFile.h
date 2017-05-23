/*
This class is used to store data using indexes.
The buffer is a variable field buffer using metadata, and the index is implemented by the IndexElement class.
The details of the IndexElement class are as follows :

    class IndexElement {
	public:
		streampos addr;
		string field;
	}

	- field is the key value of the index to be compared,
	- addr is the absolute descriptor value of the actual record.

< How to use >

	- Initialize the constructor.

		TextIndexFile(string indexFileName, string recordFileName, bool (*compare)(IndexElement a, IndexElement b))

		indexFileName  : The path where Index File
		recordFileName : The path where the actual record is stored
		compare		   : (Function Pointer) to compare key to be stored

		* File must exist in path

	- Method.

		bool Read(recType& record, string key);
			- Store the read record in the record passed as parameter.
			  Returns true if read was successful or false.

		void Remove(string key);
			- Find and remove records with the same key.

		void Append(recType& record, string key);
			- Store record and key received as parameter.

		void PrintIndex();
			- Print all existing indexes.
*/

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
