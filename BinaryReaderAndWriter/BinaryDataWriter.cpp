#include "BinaryDataWriter.h"

BinaryDataWriter::BinaryDataWriter(const char* file)
{
	open(file);
}

void BinaryDataWriter::writeBool(const bool& data)
{
	m_VectorData.push_back(std::pair<int, Wrapper>(sizeof(bool), Wrapper(data)));
	m_FileSize += sizeof(bool);
}

void BinaryDataWriter::writeLongLong(const long long& data)
{
	m_VectorData.push_back(std::pair<int, Wrapper>(sizeof(long long), Wrapper(data)));
	m_FileSize += sizeof(long long);
}

void BinaryDataWriter::writeInt(const int& data)
{
	m_VectorData.push_back(std::pair<int, Wrapper>(sizeof(int), Wrapper(data)));
	m_FileSize += sizeof(int);
}

void BinaryDataWriter::writeShort(const short& data)
{
	m_VectorData.push_back(std::pair<int, Wrapper>(sizeof(short), Wrapper(data)));
	m_FileSize += sizeof(short);
}

void BinaryDataWriter::writeDouble(const double& data)
{
	m_VectorData.push_back(std::pair<int, Wrapper>(sizeof(double), Wrapper(data)));
	m_FileSize += sizeof(double);
}

void BinaryDataWriter::writeFloat(const float& data)
{
	m_VectorData.push_back(std::pair<int, Wrapper>(sizeof(float), Wrapper(data)));
	m_FileSize += sizeof(float);
}

void BinaryDataWriter::writeString(const std::string& data)
{
	writeShort(data.size());

	m_VectorData.push_back(std::pair<int, Wrapper>((sizeof(char)*data.size()), Wrapper(data)));
	m_FileSize += sizeof(char)*data.size();
}

void BinaryDataWriter::open(const char* file)
{
	clear();
	m_FilePath = FileUtils::getInstance()->getWritablePath() + file;
}

void BinaryDataWriter::clear()
{
	m_VectorData.clear();
	m_FileSize = 0;
	m_FilePath = "";
}

void BinaryDataWriter::close()
{
	//close�Ҷ� ���Ͽ� �����͸� ����. �ݵ�� �������� close �ؾ��Ѵ�.
	int seek = 0;
	char* buf = (char*)(malloc(m_FileSize));
	memset(buf, 0, m_FileSize);

	for (auto data : m_VectorData)
	{
		int dataSize = data.first;
		Wrapper::Type dataType = data.second.getType();

		if (dataType == Wrapper::Type::INTEGER)
		{
			if (dataSize == sizeof(int))
			{
				int value = data.second.asInt();
				memcpy(&buf[seek], &value, dataSize);
			}
			else //short
			{
				short value = data.second.asInt();
				memcpy(&buf[seek], &value, dataSize);
			}

			seek += dataSize;
		}
		else if (dataType == Wrapper::Type::LONGLONG)
		{
			long long value = data.second.asLongLong();
			memcpy(&buf[seek], &value, dataSize);
			seek += dataSize;
		}
		else if (dataType == Wrapper::Type::BOOLEAN)
		{
			bool value = data.second.asBool();
			memcpy(&buf[seek], &value, dataSize);
			seek += dataSize;
		}
		else if (dataType == Wrapper::Type::FLOAT)
		{
			float value = data.second.asFloat();
			memcpy(&buf[seek], &value, dataSize);
			seek += dataSize;
		}
		else if (dataType == Wrapper::Type::DOUBLE)
		{
			double value = data.second.asDouble();
			memcpy(&buf[seek], &value, dataSize);
			seek += dataSize;
		}
		else if (dataType == Wrapper::Type::STRING)
		{
			if (dataSize > 0)
			{
				std::string value = data.second.asString();

				memcpy(&buf[seek], &value.at(0), dataSize);
				seek += dataSize;
			}
		}
	}

	FILE* fp = fopen(m_FilePath.c_str(), "wb");
	fwrite(buf, sizeof(char), m_FileSize, fp);
	fclose(fp);

	CC_SAFE_FREE(buf);

	return;
}