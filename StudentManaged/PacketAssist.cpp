#include <iostream>
#include <fstream>
#include "PacketAssist.h"
#include "Packet.h"


PacketAssist::PacketAssist()
{

}

PacketAssist::~PacketAssist()
{

}

void PacketAssist::OnInit(std::string& path)
{
	_filePath = path;
	std::ifstream f(path.c_str());
	if (f.good())
	{
		f.close();
	}
	else
	{
		std::ofstream o(path.c_str());
		o.close();
	}
}

void PacketAssist::Serialize()
{
	Packet packet(_filePath, EIOType::Input);
	Serialize(&packet);
}

void PacketAssist::Deserialize()
{
	Packet packet(_filePath, EIOType::Output);
	if (packet.Size() > 0)
	{
		Deserialize(&packet);
	}
}

