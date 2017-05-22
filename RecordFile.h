#pragma once

/*
buffer 동작 방식을 전혀 모르고 써야하는 RecordFile이 recaddr에 absoulte descriptor를 쓰는건 이상하다.
이게 구현을 헷갈리게 한 원인이다.
*/

#ifndef __RECORDFILE__
#define __RECORDFILE__
#include "FileStream.h"
#include "recType.h"

class RecordFile {
private:
	FileStream* mBuffer;
public:
	RecordFile(FileStream* buffer);
	streampos Read(recType& record, streampos recaddr = -1);
	//int Write(recType& record, int recaddr = -1);
	streampos Append(recType& record);
	streampos Remove(streampos recaddr = -1);
};

#endif // !__RECORDFILE__
