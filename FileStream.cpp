#include "FileStream.h"



/*
void FileStream::Write(int position, int dataLength) {
	
	if (dataLength > mBuffer.size) {
		cout << "ERROR: out of length buffer size in write" << endl;
		exit(11);
	}

	mStream.seekp(position);
	mStream.write(&mBuffer[0], dataLength);

}

void FileStream::Read(int position, int dataLength) {

	if (dataLength > mBuffer.size) {
		cout << "ERROR: out of length buffer size in read" << endl;
		exit(11);
	}
	mBuffer.clear();
	mBuffer.reserve(dataLength);

	mStream.seekg(position);
	mStream.read(&mBuffer[0], dataLength);

	cout << (char*)mBuffer << endl;
}
*/