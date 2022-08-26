#pragma once
#include <string>

class BaseObject abstract
{
public:
	BaseObject() = default;
	virtual ~BaseObject() = default;

public:
	//Active �ɴ�
	virtual void OnEnable();
	//DeActive �� ��
	virtual void OnDisable();

public:
	//������ �� �� ȣ�� �ؾ��� �͵� ��
	virtual void Construct();
	//�ı��� ȣ�⿡�� �ؾ��� �͵� ����
	virtual void Destruct();

public:
	virtual bool OnMessage(BaseObject* sender, const std::string& message) = 0;
};
