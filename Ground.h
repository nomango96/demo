#pragma once
#include <easy2d.h>

// 地面类
// 游戏中最下方一直向左移动的地面
class Ground :
	public Node
{
public:
	Ground();

	void onUpdate() override;
	void stop();

public:
	Sprite * ground1;	// 第一块地面
	Sprite * ground2;	// 第二块地面
};

