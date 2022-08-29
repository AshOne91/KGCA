#pragma once
class FrameSkip
{
public:
	FrameSkip()
		: _timer(0.0f)
		, _secPerFrame(0.0f)
	{}
	~FrameSkip() {}

public:
	void Clear()
	{
		SetFramePerSec(10.0f);
		_timer = 0.0;
	}

	void SetFramePerSec(float fps)
	{
		_secPerFrame = 1.0f / fps;
		_timer = 0.0f;
	}

	bool Update(float dt)
	{
		_timer += dt;
		if (_timer >= _secPerFrame)
		{
			_timer -= _secPerFrame;
			return true;
		}
		return false;
	}

private:
	float _timer;
	float _secPerFrame;
};

