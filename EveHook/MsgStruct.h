#pragma once
union UStr{
	char hereStr[16];
	void* strPtr;
};

class MsgStruct
{
public:
	MsgStruct();
	~MsgStruct();
	size_t getSize() const;
	UStr getuStr() const;
	std::string getString() const;
private:
	int size;
	UStr uStr;	
};

