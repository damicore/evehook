#pragma once
union UStr{
	char hereStr[16];
	void* strPtr;
};

class DlgLnStruct
{
public:
	DlgLnStruct();
	~DlgLnStruct();
	unsigned int getMaxSize() const;
	unsigned int getSize() const;
	UStr getuStr() const;
	std::string getString() const;
	void setSize(size_t newSize);
	void setStr(const std::string& newString);
private:
	int reserved;
	UStr uStr;	
	unsigned int size;
	unsigned int maxSize;
};

