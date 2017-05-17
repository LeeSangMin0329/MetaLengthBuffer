#pragma once

#ifndef __METALENGTHBUFFER__
#define __METALENGTHBUFFER__
#include "FileStream.h"
#include <list>

class AvailPack {
	streampos addr;
	int extraSpace; // ���ﶧ 4byte ���� �� ���� : ��� ���� ����
};

class MetaLengthBuffer : public FileStream {
private:
	int mUnpackCount;
	char* mFieldBufPool;
	int mFieldBufPoolSize;
	streampos mReadPos;
	streampos mWritePos;

	// 
	list<AvailPack> mAvailList;

public:
	MetaLengthBuffer(string fileName);
	~MetaLengthBuffer();

	// Inheritance Virtual Method Area

	void Pack(string data);
	string UnPack();
	int Write(int addr);
	int Read(int addr);
};



#endif // !__METALENGTHBUFFER__
