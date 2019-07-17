#include "Pipe.h"
#include "ResLoader.h"


Pipe::Pipe()
{
	scored = false;

	// 随机水管高度
	// 范围：与屏幕顶部最小距离不小于 100 像素
	// 与屏幕底部最小距离不小于地面上方 100 像素
	double landHeight = ResLoader::getImage("land")->getHeight();
	double height = Random::range(100, Window::getHeight() - landHeight - 100);
	
	// 创建上水管
	auto pipe1 = new Sprite(ResLoader::getImage("pipe_above"));
	pipe1->setPivot(1, 1);
	pipe1->setPosY(height - 60);

	// 设置水管形状
	// 类别掩码和碰撞掩码的设置原因参考 Bird.cpp
	auto rt1 = new Rect(pipe1);
	rt1->setCategoryBitmask(PIPE_BITMASK);
	rt1->setCollisionBitmask(BIRD_BITMASK);
	pipe1->setShape(rt1);

	// 创建下水管
	auto pipe2 = new Sprite(ResLoader::getImage("pipe_below"));
	pipe2->setPivot(1, 0);
	pipe2->setPosY(height + 60);

	// 设置水管形状
	auto rt2 = new Rect(pipe2);
	rt2->setCategoryBitmask(PIPE_BITMASK);
	rt2->setCollisionBitmask(BIRD_BITMASK);
	pipe2->setShape(rt2);

	// 把上下水管添加为子成员
	this->addChild(pipe1);
	this->addChild(pipe2);
}


Pipe::~Pipe()
{
}
