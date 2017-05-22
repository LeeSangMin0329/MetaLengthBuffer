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

	MakeAvaliList();

}

void MetaLengthBuffer::MakeAvaliList() {
	int recSize = 0;
	int deleteCheck = 0;
	mReadPos = 0;
	AvailPack pk;
	int recCount = 0;

	mStream.seekg(0, ios::end);
	streampos eof = mStream.tellg();
	mStream.seekg(0, ios::beg);

	cout << "SYSTEM: Print Record storage" << endl;

	while (mReadPos < eof) {
		mStream.read(reinterpret_cast<char*>(&recSize), sizeof(int));
		mStream.read(reinterpret_cast<char*>(&deleteCheck), sizeof(int));
		
		if (deleteCheck == -1) {
			pk.addr = mReadPos;
			pk.extraSpace = recSize;
			mAvailList.push_front(pk);
			cout << "    Record :" << recCount << ",\tRecord Size :"<< recSize<< "\tDeleted Record" << endl;
		}
		else {
			cout << "    Record :" << recCount << ",\tRecord SIze :" << recSize << endl;
		}
		recCount++;
		mReadPos += recSize;
		mStream.seekg(mReadPos);
	}

	mStream.flush();
}

int MetaLengthBuffer::CheckWorstFit(int size) {
	list<AvailPack>::iterator iter = mAvailList.begin();

	if (mAvailList.empty()) {
		return -1;
	}

	int max = 0;
	for (iter = mAvailList.begin(); iter != mAvailList.end(); iter++) {
		if ((*iter).extraSpace > max) {
			max = (*iter).extraSpace;
			mIter = iter;
		}
	}
	
	if (size == max)
		return 1;

	// sizeof(int)*2 = minimum write metadata space so if extra space less than this, useless forever
	if (size < (max - sizeof(int)*2))
		return 0;
	else
		return -1; // go eof
}

streampos MetaLengthBuffer::Remove(streampos addr) {
	mStream.seekg(0, ios::end);

	if (!mStream.tellg()) {
		cout << "ERROR: no data in file" << endl;
		return -1;
	}

	int recSize = 0;
	mWritePos = addr;
	mStream.seekg(mWritePos);

	AvailPack pk;
	pk.addr = mWritePos;
	mStream.read(reinterpret_cast<char*>(&recSize), sizeof(int));
	pk.extraSpace = recSize;

	mStream.seekg(mWritePos);
	mStream.seekg(sizeof(int), ios::cur);
	int fieldSize = -1;
	mStream.write(reinterpret_cast<char*>(&fieldSize), sizeof(int));

	mStream.flush();

	mAvailList.push_front(pk);

	cout << "SYSTEM: Record absolute addr " << addr << " was removed" << endl;

	return addr;
}

MetaLengthBuffer::~MetaLengthBuffer() {
	mStream.close();
	if (mFieldBufPool != NULL)
		delete(mFieldBufPool);
}

void MetaLengthBuffer::BufferFlush() {
	mBuffer.clear();
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

streampos MetaLengthBuffer::Write() {
	if (mBuffer.empty()) {
		cout << "ERROR: no elements in Write" << endl;
	}

	
	int recSize = 0;

	recSize = sizeof(int);
	for (int i = 0; i < mBuffer.size(); i++) {
		recSize += mBuffer[i].size() + 1 + sizeof(int);
	}
	
	int check = CheckWorstFit(recSize);

	if (check == 1) { // just size
		mWritePos = (*mIter).addr;
		mStream.seekp(mWritePos);


		mStream.write(reinterpret_cast<char*>(&recSize), sizeof(int));

		int fieldSize = 0;
		for (int i = 0; i < mBuffer.size(); i++) {
			fieldSize = mBuffer[i].size() + 1;
			mStream.write(reinterpret_cast<char*>(&fieldSize), sizeof(int));
			mStream.write(mBuffer[i].c_str(), fieldSize);
		}

		// iterator delete
		mAvailList.erase(mIter);
	}
	else if (check == 0) { // extra space exist
		mWritePos = (*mIter).addr;
		mStream.seekp(mWritePos);


		mStream.write(reinterpret_cast<char*>(&recSize), sizeof(int));

		int fieldSize = 0;
		for (int i = 0; i < mBuffer.size(); i++) {
			fieldSize = mBuffer[i].size() + 1;
			mStream.write(reinterpret_cast<char*>(&fieldSize), sizeof(int));
			mStream.write(mBuffer[i].c_str(), fieldSize);
		}

		(*mIter).addr = mStream.tellg();
		recSize = (*mIter).extraSpace - recSize;
		mStream.write(reinterpret_cast<char*>(&recSize), sizeof(int));
		fieldSize = -1;
		mStream.write(reinterpret_cast<char*>(&fieldSize), sizeof(int));

		(*mIter).extraSpace = recSize;
	}
	else { // go eof
		mStream.seekp(0, ios::end);
		mWritePos = mStream.tellp();

		mStream.write(reinterpret_cast<char*>(&recSize), sizeof(int));

		int fieldSize = 0;
		for (int i = 0; i < mBuffer.size(); i++) {
			fieldSize = mBuffer[i].size() + 1;
			mStream.write(reinterpret_cast<char*>(&fieldSize), sizeof(int));
			mStream.write(mBuffer[i].c_str(), fieldSize);
		}
	}

	mStream.flush();
	mBuffer.clear();

	return mWritePos;
}

streampos MetaLengthBuffer::Read(streampos addr) {
	mStream.seekg(0, ios::end);

	if (!mStream.tellg()) {
		cout << "ERROR: no data in file" << endl;
		return -1;
	}

	int recSize = 0;

	mReadPos = addr;
	mStream.seekg(mReadPos);

	mBuffer.clear();
	
	recSize = 0;
	mStream.read(reinterpret_cast<char*>(&recSize), sizeof(int));
	
	int fieldSize = 0;
	recSize -= sizeof(int);
	while(recSize > 0) {
		mStream.read(reinterpret_cast<char*>(&fieldSize), sizeof(int));
		
		// deleted record read
		if (fieldSize == -1) {
			cout << "SYSTEM: Record addr " << addr<< " was deleted record" << endl;
			return -1;
		}

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
		
		recSize -= (fieldSize + sizeof(int));
	}

	mStream.flush();
	mUnpackCount = 0;

	return addr;
}