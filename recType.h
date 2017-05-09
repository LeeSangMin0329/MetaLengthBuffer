#pragma once

// Buffered type Interface.
// If you use MetaLengthBuffer, you must inheritance this class in type

// Pack
// FileStream.Pack(string) and FileStream.Write()

// UnPack
// FileStream.Read() and FileStream.UnPack()

#ifndef __RECTYPE__
#define __RECTUPE__
#include "FileStream.h"

class recType {
public:
	virtual void Pack(FileStream* f) = 0;
	virtual void UnPack(FileStream* f) = 0;
};

#endif // !__RECTYPE__
