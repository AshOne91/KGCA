#pragma once
#include <iostream>
#include <string>
#include <fstream>

enum class EIOType : int
{
	Input = 0,
	Output = 1
};

class Packet
{
private:
	std::string _filePath;
	EIOType _type;
	std::ofstream _ofs;
	std::ifstream _ifs;

public:
	Packet(const std::string& filePath, EIOType type);
	~Packet();

public:
	unsigned __int64 Size();

public:
	void Write(std::string&);
	void Write(__int8);
	void Write(unsigned __int8);
	void Write(__int16);
	void Write(unsigned __int16);
	void Write(__int32);
	void Write(unsigned __int32);
	void Write(__int64);
	void Write(unsigned __int64);
	void Write(bool);
	void Write(float);
	void Write(double);

public:
	void Read(std::string*);
	void Read(__int8*);
	void Read(unsigned __int8*);
	void Read(__int16*);
	void Read(unsigned __int16*);
	void Read(__int32*);
	void Read(unsigned __int32*);
	void Read(__int64*);
	void Read(unsigned __int64*);
	void Read(bool*);
	void Read(float*);
	void Read(double*);
};