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
	void setSize(size_t newSize);
	void setStr(const std::string& newString);
private:
	size_t size;
	UStr uStr;	
};

