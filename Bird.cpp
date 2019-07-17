#include "Bird.h"
#include "ResLoader.h"


Bird::Bird()
{
	living = true;
	speed = 0;

	// 创建帧动画，0.1 秒切换一次
	animation = new Animation(0.1);
	// 随机小鸟颜色
	int mode = Random::range(0, 2);
	// 为不同颜色的小鸟加载不同的帧动画
	if (mode == 0)
	{
		this->open(ResLoader::getImage("bird0_0"));
		animation->addKeyframe(ResLoader::getImage("bird0_0"));
		animation->addKeyframe(ResLoader::getImage("bird0_1"));
		animation->addKeyframe(ResLoader::getImage("bird0_2"));
		animation->addKeyframe(ResLoader::getImage("bird0_1"));
	}
	else if (mode == 1)
	{
		this->open(ResLoader::getImage("bird1_0"));
		animation->addKeyframe(ResLoader::getImage("bird1_0"));
		animation->addKeyframe(ResLoader::getImage("bird1_1"));
		animation->addKeyframe(ResLoader::getImage("bird1_2"));
		animation->addKeyframe(ResLoader::getImage("bird1_1"));
	}
	else
	{
		this->open(ResLoader::getImage("bird2_0"));
		animation->addKeyframe(ResLoader::getImage("bird2_0"));
		animation->addKeyframe(ResLoader::getImage("bird2_1"));
		animation->addKeyframe(ResLoader::getImage("bird2_2"));
		animation->addKeyframe(ResLoader::getImage("bird2_1"));
	}
	// 循环运行帧动画
	this->runAction(new ActionLoop(animation));

	// 初始化飞翔动画（上下微微浮动）
	auto moveBy = new ActionMoveBy(0.4, Vector(0, 8));
	fly = new ActionLoop(new ActionTwo(moveBy, moveBy->reverse()));

	// 初始化旋转动画（小鸟坠落时，先抬头，后低头）
	rotate = new ActionSequence(
		3,								// 由 3 个动画组成
		new ActionRotateTo(0.2, -15),	// 0.2 秒内旋转至 -15 度
		new ActionDelay(0.2),			// 等待 0.2 秒
		new ActionRotateTo(0.5, 90)		// 0.5 秒内旋转至 90 度（小鸟头朝下）
	);
	// 保留这个动画，防止引擎自动回收
	rotate->retain();

	// 设置初始化状态为 1
	this->setStatus(1);

	// 为小鸟添加形状
	// 小鸟、水管、地面的类别掩码分别设置为 0x0001 0x0010 0x0100
	// 小鸟的碰撞掩码设置为水管和地面的类别掩码的或运算，则小鸟会与它们发生碰撞
	// 水管和地面的碰撞掩码设置为小鸟的类别掩码，则它们都可以与小鸟发生碰撞
	// 但水管和地面之间不会产生碰撞
	auto circle = new Circle();
	circle->setCategoryBitmask(BIRD_BITMASK);
	circle->setCollisionBitmask(PIPE_BITMASK | GROUND_BITMASK);
	this->setShape(circle);
}

Bird::~Bird()
{
	// 释放曾经保留的动画
	rotate->release();
}

void Bird::setStatus(int status)
{
	// 小鸟一共有 4 种状态
	// 0 表示小鸟不动
	// 1 表示小鸟上下浮动
	// 2 表示游戏刚开始时，小鸟停止浮动，并开始旋转
	// 3 表示小鸟向上飞时，先抬头，后低头
	switch (status)
	{
	case 0:
		this->stopAllActions(); break;
	case 1:
		this->runAction(fly); break;
	case 2:
		fly->stop();					// 停止上下晃动动画
		animation->setInterval(0.05);	// 加速小鸟扇动翅膀的速度
		this->runAction(rotate);		// 旋转小鸟
		break;
	case 3:
		this->runAction(rotate);		// 旋转小鸟
		break;
	default:
		break;
	}
}
