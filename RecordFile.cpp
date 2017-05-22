#include "RecordFile.h"

RecordFile::RecordFile(FileStream* buffer) {
	mBuffer = buffer;
}

streampos RecordFile::Read(recType& record, streampos recaddr) {
	if (static_cast<int>(recaddr) == -1) {
		cout << "rack read addr info" << endl;
		return -1;
	}
	if(mBuffer->Read(recaddr) >= 0)
		record.UnPack(mBuffer);
	else {
		cout << "ERROR: Record read Fail" << endl;
		return -1;
	}

	return 0;
}

/* non use this program
int RecordFile::Write(recType& record, int recaddr) {
	if (recaddr == -1) {
		cout << "rack write addr info" << endl;
		return -1;
	}
	record.Pack(mBuffer);
	mBuffer->Write();
	return 0;
}
*/

streampos RecordFile::Append(recType& record) {
	mBuffer->BufferFlush();

	record.Pack(mBuffer);
	
	return mBuffer->Write();
}

streampos RecordFile::Remove(streampos recaddr) {
	if (static_cast<int>(recaddr) == -1) {
		cout << "Invalied addr" << endl;
		return recaddr;
	}
	mBuffer->Remove(recaddr);
	return recaddr;
}