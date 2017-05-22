#pragma once

/*
buffer ���� ����� ���� �𸣰� ����ϴ� RecordFile�� recaddr�� absoulte descriptor�� ���°� �̻��ϴ�.
�̰� ������ �򰥸��� �� �����̴�.
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
