#include "Packet.h"

Packet::Packet(const std::string& filePath, EIOType type) :_filePath(filePath), _type(type)
{
	if (_type == EIOType::Input)
	{
		_ofs.open(filePath, std::ios::binary|std::ios::trunc);
	}
	else
	{
		_ifs.open(filePath, std::ios::binary);
		if (_ifs.is_open())
		{
			int i = 0;
			i = 1;
		}
	}
}

Packet::~Packet()
{
	if (_ofs.is_open())
	{
		_ofs.close();
	}
	if (_ifs.is_open())
	{
		_ifs.close();
	}
}

unsigned __int64 Packet::Size()
{
	if (_ofs.is_open())
	{
		return _ofs.tellp();
	}
	else if (_ifs.is_open())
	{
		_ifs.seekg(0, std::ios::end);
		unsigned __int64 size = _ifs.tellg();
		_ifs.seekg(0, std::ios::beg);
		return size;
	}
	return 0;
}

void Packet::Write(std::string& data)
{
	int size = data.size() + 1;
	_ofs.write((char*)&size, sizeof(int));
	_ofs.write(data.c_str(), data.size()+1);
}

void Packet::Write(__int8 data)
{
	_ofs.write(&data, sizeof(__int8));
}
void Packet::Write(unsigned __int8 data)
{
	_ofs.write((char*)(&data), sizeof(unsigned __int8));
}
void Packet::Write(__int16 data)
{
	_ofs.write((char*)(&data), sizeof(__int16));
}
void Packet::Write(unsigned __int16 data)
{
	_ofs.write((char*)(&data), sizeof(unsigned __int16));
}
void Packet::Write(__int32 data)
{
	_ofs.write((char*)(&data), sizeof(__int32));
}
void Packet::Write(unsigned __int32 data)
{
	_ofs.write((char*)(&data), sizeof(unsigned __int32));
}
void Packet::Write(__int64 data)
{
	_ofs.write((char*)(&data), sizeof(__int64));
}
void Packet::Write(unsigned __int64 data)
{
	_ofs.write((char*)(&data), sizeof(unsigned __int64));
}
void Packet::Write(bool data)
{
	_ofs.write((char*)(&data), sizeof(bool));
}
void Packet::Write(float data)
{
	_ofs.write((char*)(&data), sizeof(float));
}
void Packet::Write(double data)
{
	_ofs.write((char*)(&data), sizeof(double));
}
void Packet::Read(std::string* data)
{
	int size = 0;
	_ifs.read((char*)&size, sizeof(int));
	if (size > 0)
	{
		char* temp = new char[size];
		_ifs.read(temp, size);
		(*data) = temp;
		delete[] temp;
	}
}
void Packet::Read(__int8* data)
{
	_ifs.read((char*)(data), sizeof(__int8));
}
void Packet::Read(unsigned __int8* data)
{
	_ifs.read((char*)(data), sizeof(unsigned __int8));
}
void Packet::Read(__int16* data)
{
	_ifs.read((char*)(data), sizeof(__int16));
}
void Packet::Read(unsigned __int16* data)
{
	_ifs.read((char*)(data), sizeof(unsigned __int16));
}
void Packet::Read(__int32* data)
{
	_ifs.read((char*)(data), sizeof(__int32));
}
void Packet::Read(unsigned __int32* data)
{
	_ifs.read((char*)(data), sizeof(unsigned __int32));
}
void Packet::Read(__int64* data)
{
	_ifs.read((char*)(data), sizeof(__int64));
}
void Packet::Read(unsigned __int64* data)
{
	_ifs.read((char*)(data), sizeof(unsigned __int64));
}
void Packet::Read(bool* data)
{
	_ifs.read((char*)(data), sizeof(bool));
}
void Packet::Read(float* data)
{
	_ifs.read((char*)(data), sizeof(float));
}
void Packet::Read(double* data)
{
	_ifs.read((char*)(data), sizeof(double));
}

