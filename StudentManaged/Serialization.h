#pragma once
class Packet;
class SerializableInterface abstract
{
public:
	virtual void Serialize(Packet* packet) = 0;
	virtual void Deserialize(Packet* packet) = 0;
};
