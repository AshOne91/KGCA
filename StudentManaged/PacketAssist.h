#pragma once
#include <string>

class Packet;
class PacketAssist abstract
{
public:
	std::string _filePath;

public:
	PacketAssist();
	virtual ~PacketAssist();

public:
	void OnInit(std::string& path);

public:
	virtual void Serialize(Packet* packet) = 0;
	virtual void Deserialize(Packet* packet) = 0;

public:
	void Serialize();
	void Deserialize();
};
