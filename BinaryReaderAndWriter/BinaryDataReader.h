#pragma once

#include "cocos2d.h"
using namespace cocos2d;

class BinaryDataReader
{
private:
	CC_SYNTHESIZE(Data, m_Data, Data);

	CC_SYNTHESIZE(int, m_Seek, Seek);

	CC_SYNTHESIZE(int, m_FileSize, FileSize);

	CC_SYNTHESIZE(char*, m_Buffer, Buffer);

public:
	BinaryDataReader();
	BinaryDataReader(const char* file);
	bool open(const char* file);

	bool readBool();
	long long readLongLong();
	int readInt();
	short readShort();
	double readDouble();
	float readFloat();
	std::string readString();

	void clear();
	bool hasNext();
};