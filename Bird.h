#pragma once
#include <easy2d.h>

// 小鸟类
class Bird :
	public Sprite
{
public:
	Bird();

	~Bird();

	void setStatus(int status);	// 设置小鸟状态

public:
	bool living;
	double speed;
	Action * fly;
	Animation * animation;
	Action * rotate;
};

