#pragma once
#include <easy2d.h>
#include "Pipe.h"

// 管理水管运动的类
class Pipes :
	public Sprite
{
public:
	Pipes();
	~Pipes();

	void onUpdate() override;
	void addPipe();	// 添加一根水管
	void start();	// 开始移动
	void stop();	// 停止移动

public:
	int number;		// 水管数量
	Pipe* pipes[3];	// 场景中只有3根水管
};
