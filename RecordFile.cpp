#include "RecordFile.h"

RecordFile::RecordFile(FileStream* buffer) {
	mBuffer = buffer;
}

int RecordFile::Read(recType& record, int recaddr) {
	if (recaddr == -1) {
		cout << "rack read addr info" << endl;
		return -1;
	}
	mBuffer->Read(recaddr);
	record.UnPack(mBuffer);
	return 0;
}

int RecordFile::Write(recType& record, int recaddr) {
	if (recaddr == -1) {
		cout << "rack write addr info" << endl;
		return -1;
	}
	record.Pack(mBuffer);
	mBuffer->Write(recaddr);
	return 0;
}

int RecordFile::Append(const recType& record) {
	return 0;
}