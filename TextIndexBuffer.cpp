#include "TextIndexBuffer.h"

TextIndexBuffer::TextIndexBuffer(string indexFileName, vector<IndexElement>& index) : mIndexVector(index) {
	mStream.open(indexFileName, ios::in | ios::out | ios::binary);
	if (!mStream.good()) {
		cout << "ERROR: Index open fail" << endl;
		exit(1);
	}

	//mIndexVector = index;
}

// write index
void TextIndexBuffer::Pack(string data) {
	mStream.seekp(0, ios::beg);
	int feildSize;

	for (int i = 0; i < mIndexVector.size(); i++) {
		feildSize = mIndexVector[i].field.size() + 1;
		mStream.write(reinterpret_cast<char*>(&(mIndexVector[i].addr)), sizeof(streampos));
		mStream.write(reinterpret_cast<char*>(&feildSize), sizeof(int));
		mStream.write(mIndexVector[i].field.c_str(), feildSize);
	}
}

// read index
string TextIndexBuffer::UnPack() {
	mStream.seekg(0, ios::end);
	streampos eof = mStream.tellg();
	mStream.seekg(0, ios::beg);
	streampos readPos = 0;

	if (!eof) {
		cout << "SYSTEM: no data in index" << endl;
		return "";
	}
	mIndexVector.clear();

	IndexElement element;
	int fieldSize;
	while (readPos < eof) {
		mStream.read(reinterpret_cast<char*>(&(element.addr)), sizeof(streampos));
		mStream.read(reinterpret_cast<char*>(&fieldSize), sizeof(int));

		if (fieldSize > mFieldBufPoolSize) {
			if (mFieldBufPool != NULL) {
				delete(mFieldBufPool);
			}
			mFieldBufPool = new char[fieldSize];
			mFieldBufPoolSize = fieldSize;
		}
		mStream.read(mFieldBufPool, fieldSize);
		element.field = mFieldBufPool;

		mIndexVector.push_back(element);
		readPos += sizeof(streampos) + sizeof(int) + fieldSize;
	}
	
	
	return "";
}

