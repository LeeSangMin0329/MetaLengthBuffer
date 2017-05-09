#include "MetaLengthBuffer.h"

MetaLengthBuffer::MetaLengthBuffer(string fileName) : FileStream() {
	mStream.open(fileName, ios::in | ios::out | ios::binary);
	if (!mStream.good()) {
		cout << "ERROR: open fail" << endl;
		exit(1);
	}
	mUnpackCount = 0;

	mBuffer.push_back("hilskdfdf");
	mBuffer.push_back("wwdsdf");
	mBuffer.push_back("hilssdfsddfkdfdf");
	mBuffer.push_back("2323");
}

MetaLengthBuffer::~MetaLengthBuffer() {
	mStream.close();
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

	mStream.seekp(0, ios::end);

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

	mBuffer.clear();
}

void MetaLengthBuffer::Read() {
	streampos curSeek = mStream.tellg();
	mStream.seekg(0, ios::end);

	if (!mStream.tellg()) {
		cout << "ERROR: no data in file" << endl;
		return;
	}

	mStream.seekg(curSeek);
	mBuffer.clear();
	
	int recSize = 0;
	mStream.read(reinterpret_cast<char*>(&recSize), sizeof(int));
	cout << recSize << endl;
	
	int fieldSize = 0;
	char* str;
	for (int i = 0; recSize > 0; i++) {
		mStream.read(reinterpret_cast<char*>(&fieldSize), sizeof(int));
		str = new char[fieldSize];
		mStream.read(str, fieldSize);

		mBuffer.push_back(str);
		cout << "f : "<< mBuffer[i] << endl;
		recSize -= (fieldSize + sizeof(int));
		delete(str);
	}
}