#pragma once

#ifndef __METALENGTHBUFFER__
#define __METALENGTHBUFFER__
#include "FileStream.h"
#include <list>

class AvailPack {
public:
	streampos addr;
	int extraSpace;
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
	list<AvailPack>::iterator mIter;

	void MakeAvaliList();
	int CheckWorstFit(int size);

public:
	MetaLengthBuffer(string fileName);
	~MetaLengthBuffer();

	// Inheritance Virtual Method Area

	void Pack(string data);
	string UnPack();
	streampos Write();
	streampos Read(streampos addr);
	streampos Remove(streampos addr);
	void BufferFlush();
};



#endif // !__METALENGTHBUFFER__
