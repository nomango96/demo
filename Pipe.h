#pragma once
#include <easy2d.h>

// 水管类
// 游戏中小鸟碰到会死亡的水管
class Pipe
	: public Node
{
public:
	Pipe();
	~Pipe();

public:
	bool scored;	// 标志小鸟是否飞过了该水管
};

