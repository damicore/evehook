#include "stdafx.h"
#include "FileStruct.h"


FileStruct::FileStruct()
{
}


FileStruct::~FileStruct()
{
}

DlgLnStruct* FileStruct::curLnPtr() const
{
	DlgLnStruct *curLine = (DlgLnStruct*)((int)startingPointer + curLineIndex * 28);
	return curLine;
}
