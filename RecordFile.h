#pragma once

#ifndef __RECORDFILE__
#define __RECORDFILE__
#include "FileStream.h"
#include "recType.h"

class RecordFile {
private:
	FileStream* mBuffer;
public:
	RecordFile(FileStream* buffer);
	int Read(recType& record, int racaddr = -1);
	int Write(recType& record, int recaddr = -1);
	int Append(const recType& record, int recaddr = -1);
};

#endif // !__RECORDFILE__
