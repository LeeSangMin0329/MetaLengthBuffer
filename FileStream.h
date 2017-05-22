#pragma once

// Buffer Interface

// Pack
// input mBuffer

// UnPack
// output mBuffer 

// Write
// write record(mBuffer) use mStream

// Read
// read record(mBuffer) use mStream

#ifndef __FILESTREAM__
#define __FILESTREAM__
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class FileStream {
protected:
	vector<string> mBuffer;
	fstream mStream;
	
public:
	virtual void Pack(string data) = 0;
	virtual string UnPack() = 0;
	virtual streampos Write() = 0;
	virtual streampos Read(streampos addr) = 0;
	virtual streampos Remove(streampos addr) = 0;
	virtual void BufferFlush() = 0;
};

#endif // !__FILESTREAM__
