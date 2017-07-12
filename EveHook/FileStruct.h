#include <string>
#include "MsgStruct.h"

#pragma once
class FileStruct
{
public:
	FileStruct();
	~FileStruct();
	DlgLnStruct* curLnPtr() const;
	int curFileIndex;
	int curLineIndex;
	int qttyOfLines;
	int unknown;
	int fileSize;
	void *startingPointer;
	//etc...
};

