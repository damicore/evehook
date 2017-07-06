#include "stdafx.h"
#include <string>

#include "MsgStruct.h"


MsgStruct::MsgStruct()
{
}

MsgStruct::~MsgStruct()
{
}

size_t MsgStruct::getSize() const
{
	return this->size;
}

UStr MsgStruct::getuStr() const
{
	return this->uStr;
}

//if the string was longer than 16 bytes then it is stored in a 
//pointer at the same place where the string would be.
std::string MsgStruct::getString() const{
	std::string msgString;

	if (this->size <= 16) {
		msgString = std::string(this->uStr.hereStr);
	}
	else {
		msgString = std::string((char*)this->uStr.strPtr);
	}

	return msgString;
}