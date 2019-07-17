#include "GameScene.h"
#include "ResLoader.h"
#include "GameOverLayer.h"

GameScene::GameScene()
{
	// 添加背景
	auto background = new Sprite(ResLoader::getImage("bg_day"));
	background->setPivot(0, 0);
	this->add(background);

	// 添加水管
	pipes = new Pipes();
	this->add(pipes);

	// 添加小鸟
	bird = new Bird();
	bird->setPos(60, Window::getHeight() / 2);
	this->add(bird);

	// 添加地面
	ground = new Ground();
	this->add(ground);

	// 添加得分
	scoreImage = new Number();
	scoreImage->setPos(Window::getWidth() / 2, 50);
	scoreImage->setNumber(0);
	this->add(scoreImage);

	// 添加 ready 图片
	ready = new Sprite(ResLoader::getImage("text_ready"));
	ready->setPos(Window::getWidth() / 2, Window::getHeight() / 2 - 70);
	this->add(ready);

	// 添加教程图片
	tutorial = new Sprite(ResLoader::getImage("tutorial"));
	tutorial->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 30);
	this->add(tutorial);

	started = false;
	score = 0;
}

void GameScene::onEnter()
{
	// 进入场景时播放音效
	MusicManager::play("res/sound/swoosh.wav");
}

void GameScene::onUpdate()
{
	// 按下鼠标左键或按下空格键
	if (Input::isMouseLButtonPress() || 
		Input::isKeyPress(KeyCode::SPACE))
	{
		this->jump();
	}

	// 判断游戏是否已经开始
	if (started)
	{
		// 模拟小鸟下落
		bird->movePosY(bird->speed);
		// 模拟小鸟所受重力
		bird->speed += 0.4;
		// 若小鸟纵坐标小于 0，限制它继续往上飞
		if (bird->getPosY() < 0) {
			bird->setPosY(0);
			bird->speed = 0;
		}
		// 判断小鸟是否飞过了水管
		if (!pipes->pipes[0]->scored &&
			pipes->pipes[0]->getPosX() <= bird->getPosX())
		{
			// 加分
			score++;
			scoreImage->setNumber(score);
			// 标记
			pipes->pipes[0]->scored = true;
			// 播放音效
			MusicManager::play("res/sound/point.wav");
		}
		// 若小鸟纵坐标小于地面，游戏结束
		if (Window::getHeight() - bird->getPosY() <= 123) {
			// 让小鸟停止
			bird->setPosY(Window::getHeight() - 123);
			bird->setStatus(0);
			// 让小鸟脸朝下
			bird->setRotation(90);
			// 显示游戏结束界面
			this->gameover();
		}
	}
}

void GameScene::onCollide(Node * node1, Node * node2)
{
	// 只要有碰撞产生，就说明小鸟死亡
	if (bird->living) {
		this->die();
	}
}

void GameScene::start()
{
	// 隐藏 ready 图片
	ready->runAction(new ActionFadeOut(0.4));
	tutorial->runAction(new ActionFadeOut(0.4));
	// 开始移动水管
	pipes->start();
	// 设置小鸟状态为 2
	bird->setStatus(2);
}

void GameScene::jump()
{
	if (!started) {
		// 若游戏还没有开始，开始游戏
		started = true;
		start();
	}
	if (bird->living) {
		// 如果小鸟还活着，给小鸟一个向上的速度
		bird->speed = -7.2;
		// 设置小鸟状态为 3
		bird->setStatus(3);
		// 播放音效
		MusicManager::play("res/sound/fly.wav");
	}
}

void GameScene::die()
{
	// 小鸟死亡
	bird->living = false;
	// 播放音效
	MusicManager::play("res/sound/hit.wav");
	// 停止地面
	ground->stop();
	// 停止水管
	pipes->stop();
	// 隐藏得分
	scoreImage->runAction(new ActionFadeOut(0.5));
	// 闪动白屏
	auto white = new Sprite(ResLoader::getImage("white"));
	white->setPivot(0, 0);
	white->setOpacity(0);
	white->setScale(16, 16);
	white->runAction(new ActionTwo(new ActionFadeIn(0.1), new ActionFadeOut(0.1)));
	this->add(white);
}

void GameScene::gameover()
{
	started = false;
	this->setAutoUpdate(false);
	// 显示得分面板
	this->add(new GameOverLayer(score));
}
