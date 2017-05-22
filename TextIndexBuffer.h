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
	int mIndexSize;

	char* mFieldBufPool;
	int mFieldBufPoolSize;

public:
	TextIndexBuffer(string indexFileName, vector<IndexElement>& index);
	~TextIndexBuffer();

	// Inheritance Virtual Method Area
	void Pack(string data);
	string UnPack();
	void BufferFlush();

	// non use Inheritance Vitual Method Area
	streampos Write() { return 0; };
	streampos Read(streampos addr) { return 0; };
	streampos Remove(streampos addr) { return 0; };
	
};


#endif // !__TEXTINDEXBUFFER__
