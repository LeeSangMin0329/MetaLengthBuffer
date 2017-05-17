#include "RecordFile.h"

RecordFile::RecordFile(FileStream* buffer) {
	mBuffer = buffer;
}

int RecordFile::Read(recType& record, int recaddr) {
	mBuffer->Read();
	record.UnPack(mBuffer);
	return 0;
}

int RecordFile::Write(recType& record, int recaddr) {
	record.Pack(mBuffer);
	mBuffer->Write();
	return 0;
}

int RecordFile::Append(const recType& record, int recaddr) {
	return 0;
}