#ifndef __TEXTINDEXBUFFER__
#define __TEXTINDEXBUFFER__

#include "FileStream.h"

class IndexElement {
public:
	streampos addr;
	string field;
};

class TextIndexBuffer : public FileStream{
private:
	vector<IndexElement>& mIndexVector;

	char* mFieldBufPool;
	int mFieldBufPoolSize;

public:
	TextIndexBuffer(string indexFileName, vector<IndexElement>& index);

	// Inheritance Virtual Method Area
	void Pack(string data);
	string UnPack();
	int Write() { return 0; };
	streampos Read(streampos addr) { return 0; };
	streampos Remove(streampos addr) { return 0; };
};


#endif // !__TEXTINDEXBUFFER__
