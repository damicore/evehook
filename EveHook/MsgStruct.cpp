#include "stdafx.h"
#include <string>

#include "MsgStruct.h"


DlgLnStruct::DlgLnStruct()
{
}

DlgLnStruct::~DlgLnStruct()
{
}

unsigned int DlgLnStruct::getMaxSize() const
{
	return this->maxSize;
}

unsigned int DlgLnStruct::getSize() const
{
	return this->size;
}

UStr DlgLnStruct::getuStr() const
{
	return this->uStr;
}

//if the string was longer than 16 bytes then it is stored in a 
//pointer at the same place where the string would be.
std::string DlgLnStruct::getString() const{
	std::string msgString;

	if (this->size < 16) {
		msgString = std::string(this->uStr.hereStr);
	}
	else {
		msgString = std::string((char*)this->uStr.strPtr);
	}

	return msgString;
}

void DlgLnStruct::setSize(size_t newSize)
{
	this->size = newSize;
}

//test with strings of size 10, 20 and 40
//let's rather memcpy to where they were, that way if the whole script is loaded there I'll have no problem
void DlgLnStruct::setStr(const std::string& newString)
{
	if (this->size < 16 && newString.size() < 16) { 
		//delete uStr.strPt;
		memcpy(&(this->uStr.hereStr), newString.c_str(), newString.size() +1 );
		}
	else if (this->size < 16 && newString.size() >= 16) {	
		//case for completion, not sure it can be done 
		char *allocStr = new char[newString.size()];
		this->uStr.strPtr = allocStr;
		memcpy(this->uStr.strPtr, newString.c_str(), newString.size() + 1) ;
		}
	else if (this->size >= 16 && newString.size() < 16) {
		memcpy(&(this->uStr.hereStr), newString.c_str(), newString.size() + 1);
	}
	else if (this->size >= 16 && newString.size() >= 16) {
		char *allocStr = new char[newString.size()];
		//delete uStr.strPt;
		this->uStr.strPtr = allocStr;
	}
	this->size = newString.size(); //-1?
	this->maxSize = newString.size() | 0b1111;
}
