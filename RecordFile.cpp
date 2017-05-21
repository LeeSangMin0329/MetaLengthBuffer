#include "RecordFile.h"

RecordFile::RecordFile(FileStream* buffer) {
	mBuffer = buffer;
}

int RecordFile::Read(recType& record, int recaddr) {
	if (recaddr == -1) {
		cout << "rack read addr info" << endl;
		return -1;
	}
	if(mBuffer->Read(recaddr) > 0)
		record.UnPack(mBuffer);

	return 0;
}

int RecordFile::Write(recType& record, int recaddr) {
	if (recaddr == -1) {
		cout << "rack write addr info" << endl;
		return -1;
	}
	record.Pack(mBuffer);
	mBuffer->Write();
	return 0;
}

int RecordFile::Append(recType& record) {
	record.Pack(mBuffer);
	mBuffer->Write();
	return 0;
}

int RecordFile::Remove(int recaddr) {
	if (recaddr == -1) {
		cout << "Invalied addr" << endl;
		return recaddr;
	}
	mBuffer->Remove(recaddr);
	return recaddr;
}