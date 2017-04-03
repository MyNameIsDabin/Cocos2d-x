#include "BinaryDataReader.h"

BinaryDataReader::BinaryDataReader()
{
	//empty
}

BinaryDataReader::BinaryDataReader(const char* file)
{
	open(file);
}

bool BinaryDataReader::open(const char* file)
{
	clear();

	if (!FileUtils::getInstance()->isFileExist(file))
	{
		return false;
	}

	m_Data = FileUtils::getInstance()->getDataFromFile(file);

	m_Seek = 0;

	m_FileSize = m_Data.getSize();

	m_Buffer = (char*)m_Data.getBytes();

	return true;
}

bool BinaryDataReader::readBool()
{
	bool data = false;
	memcpy(&data, &m_Buffer[m_Seek], sizeof(bool));
	m_Seek += sizeof(bool);

	return data;
}

long long BinaryDataReader::readLongLong()
{
	long long data = -1LL;
	memcpy(&data, &m_Buffer[m_Seek], sizeof(long long));
	m_Seek += sizeof(long long);

	return data;
}

int BinaryDataReader::readInt()
{
	int data = -1;
	memcpy(&data, &m_Buffer[m_Seek], sizeof(int));
	m_Seek += sizeof(int);

	return data;
}

short BinaryDataReader::readShort()
{
	short data = -1;
	memcpy(&data, &m_Buffer[m_Seek], sizeof(short));
	m_Seek += sizeof(short);

	return data;
}

double BinaryDataReader::readDouble()
{
	double data = -1.0;
	memcpy(&data, &m_Buffer[m_Seek], sizeof(double));
	m_Seek += sizeof(double);

	return data;
}

float BinaryDataReader::readFloat()
{
	float data = -1.0F;
	memcpy(&data, &m_Buffer[m_Seek], sizeof(float));
	m_Seek += sizeof(float);

	return data;
}

std::string BinaryDataReader::readString()
{
	std::string data = "";

	short length = 0;
	memcpy(&length, &m_Buffer[m_Seek], sizeof(short));
	m_Seek += sizeof(length);

	if (length > 0)
	{
		data.resize(length);
		memcpy(&data.at(0), &m_Buffer[m_Seek], sizeof(char)*length);
		m_Seek += sizeof(char)*length;
	}

	return data;
}

void BinaryDataReader::clear()
{
	m_Data.clear();
	m_Seek = 0;
	m_FileSize = 0;
	m_Buffer = nullptr;
}

bool BinaryDataReader::hasNext()
{
	return (m_Seek < m_FileSize);
}