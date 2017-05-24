#pragma once

// Buffered type Interface.
// If you use Buffer, you must inheritance this class in type

/*
class recType {
public:
	virtual void Pack(FileStream* f) = 0;
	virtual void UnPack(FileStream* f) = 0;
};

	- Pack 	  : Call 'f-> Pack (string field);' in the order that you want to put in at the buffer.
	- UnPack  : Call 'f-> UnPack ();' in the order you want to import in the buffer.
*/

#ifndef __RECTYPE__
#define __RECTUPE__
#include "FileStream.h"

class recType {
public:
	virtual void Pack(FileStream* f) = 0;
	virtual void UnPack(FileStream* f) = 0;
};

#endif // !__RECTYPE__
