#include "StartScene.h"
#include "ResLoader.h"
#include "GameScene.h"
#include "Bird.h"
#include "Ground.h"
#include "GameOverLayer.h"
#include <shellapi.h>

StartScene::StartScene()
{
	// 添加背景
	auto background = new Sprite(ResLoader::getImage("bg_day"));
	background->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->add(background);

	// 添加地面
	this->add(new Ground());

	// 添加标题图片
	auto title = new Sprite(ResLoader::getImage("title"));
	title->setPos(Window::getWidth() / 2, 150);
	this->add(title);

	// 添加小鸟
	auto bird = new Bird();
	bird->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->add(bird);

	// 创建开始按钮正常状态和按下状态时显示的精灵
	auto startBtnNormal = new Sprite(ResLoader::getImage("button_play"));
	auto startBtnSelected = new Sprite(ResLoader::getImage("button_play"));
	startBtnSelected->setPosY(5);	// 按钮被选中时向下移动一点点
	// 添加开始按钮
	auto startBtn = new Button(startBtnNormal, startBtnSelected);
	// 按下开始按钮，进入 Game 场景
	startBtn->setCallback([] {
		MusicManager::play("res/sound/click.wav");
		SceneManager::enter(new GameScene(), new TransitionFade(0.3, 0.3));
	});
	startBtn->setPosX(Window::getWidth() / 2);
	startBtn->setPosY(Window::getHeight() - startBtnNormal->getHeight() - 100);
	this->add(startBtn);

	// 添加打开分享链接按钮
	auto shareBtnNormal = new Sprite(ResLoader::getImage("button_share"));
	auto shareBtnSelected = new Sprite(ResLoader::getImage("button_share"));
	shareBtnSelected->setPosY(5);
	auto shareBtn = new Button(shareBtnNormal, shareBtnSelected);
	// 按下按钮打开超链接
	shareBtn->setCallback([] {
		MusicManager::play("res/sound/click.wav");
		ShellExecuteA(NULL, "open", "https://gitee.com/werelone/FlappyBird", NULL, NULL, SW_SHOWNORMAL);
	});
	shareBtn->setPosX(Window::getWidth() / 2);
	shareBtn->setPosY(Window::getHeight() - shareBtnNormal->getHeight() - 80);
	this->add(shareBtn);

	// 添加 copyright 图片
	auto copyright = new Sprite(ResLoader::getImage("brand_copyright"));
	copyright->setPos(Window::getWidth() / 2, Window::getHeight() - 20);
	this->add(copyright);
}

void StartScene::onEnter()
{
	// 进入场景时播放音效
	MusicManager::play("res/sound/swoosh.wav");
}
