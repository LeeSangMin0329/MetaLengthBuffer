#pragma once

#ifndef __METALENGTHBUFFER__
#define __METALENGTHBUFFER__
#include "FileStream.h"
#include <list>

class AvailPack {
	streampos addr;
	int extraSpace; // 지울때 4byte 읽은 그 길이 : 사용 가능 공간
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
