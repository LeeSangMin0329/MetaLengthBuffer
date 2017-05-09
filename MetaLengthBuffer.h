#pragma once

#ifndef __METALENGTHBUFFER__
#define __METALENGTHBUFFER__
#include "FileStream.h"

class MetaLengthBuffer : public FileStream {
private:
	int mUnpackCount;

public:
	MetaLengthBuffer(string fileName);
	~MetaLengthBuffer();


	// Inheritance Virtual Method Area

	void Pack(string data);
	string UnPack();
	void Write();
	void Read();
};



#endif // !__METALENGTHBUFFER__
