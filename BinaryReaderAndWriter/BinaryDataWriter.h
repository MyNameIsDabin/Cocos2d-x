#pragma once
#include "cocos2d.h"
#include "Wrapper.h"
using namespace cocos2d;

class BinaryDataWriter
{
private:

	std::vector<std::pair<int, Wrapper>> m_VectorData;

	CC_SYNTHESIZE(int, m_FileSize, FileSize);

	CC_SYNTHESIZE(std::string, m_FilePath, FilePath);

public:

	BinaryDataWriter(const char* file);

	void writeBool(const bool& data);
	void writeLongLong(const long long& data);
	void writeInt(const int& data);
	void writeShort(const short& data);
	void writeDouble(const double& data);
	void writeFloat(const float& data);
	void writeString(const std::string& data);

	void open(const char* file);
	void clear();
	void close();
};