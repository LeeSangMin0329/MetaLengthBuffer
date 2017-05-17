#include "MetaLengthBuffer.h"

MetaLengthBuffer::MetaLengthBuffer(string fileName) : FileStream() {
	mStream.open(fileName, ios::in | ios::out | ios::binary);
	if (!mStream.good()) {
		cout << "ERROR: open fail" << endl;
		exit(1);
	}
	mUnpackCount = 0;
	mFieldBufPoolSize = 0;
	mReadPos = 0;
	mWritePos = 0;
}

MetaLengthBuffer::~MetaLengthBuffer() {
	mStream.close();
	if (mFieldBufPool != NULL)
		delete(mFieldBufPool);
}

void MetaLengthBuffer::Pack(string data) {
	mBuffer.push_back(data);
}

string MetaLengthBuffer::UnPack() {
	if (mBuffer.empty()) {
		cout << "ERROR: no elements in UnPack" << endl;
		exit(11);
	}
	return mBuffer[mUnpackCount++];
}

void MetaLengthBuffer::Write() {
	if (mBuffer.empty()) {
		cout << "ERROR: no elements in Write" << endl;
	}

	mStream.seekp(mWritePos);

	int recSize = 0;
	for (int i = 0; i < mBuffer.size(); i++) {
		recSize += mBuffer[i].size() + 1 + sizeof(int);
	}
	
	mStream.write(reinterpret_cast<char*>(&recSize), sizeof(int));
	
	int fieldSize = 0;
	for (int i = 0; i < mBuffer.size(); i++) {
		fieldSize = mBuffer[i].size() + 1;
		mStream.write(reinterpret_cast<char*>(&fieldSize), sizeof(int));
		mStream.write(mBuffer[i].c_str(), fieldSize);
	}

	mWritePos = mStream.tellp();
	mBuffer.clear();
}

void MetaLengthBuffer::Read() {
	mStream.seekg(0, ios::end);

	if (!mStream.tellg()) {
		cout << "ERROR: no data in file" << endl;
		return;
	}

	mStream.seekg(mReadPos);
	mBuffer.clear();
	
	int recSize = 0;
	mStream.read(reinterpret_cast<char*>(&recSize), sizeof(int));
	cout << recSize << endl;
	
	int fieldSize = 0;
	
	for (int i = 0; recSize > 0; i++) {
		mStream.read(reinterpret_cast<char*>(&fieldSize), sizeof(int));
		
		// Field buffer pooling
		if (fieldSize > mFieldBufPoolSize) {
			if (mFieldBufPool != NULL) {
				delete(mFieldBufPool);
			}
			mFieldBufPool = new char[fieldSize];
			mFieldBufPoolSize = fieldSize;
		}

		mStream.read(mFieldBufPool, fieldSize);

		mBuffer.push_back(mFieldBufPool);
		cout << "f : "<< mBuffer[i] << endl;
		recSize -= (fieldSize + sizeof(int));
	}

	mReadPos = mStream.tellg();
	mUnpackCount = 0;
}