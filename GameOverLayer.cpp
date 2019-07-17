#include "GameOverLayer.h"
#include "GameScene.h"
#include "Number.h"
#include "ResLoader.h"
#include <shellapi.h>


GameOverLayer::GameOverLayer(int score)
{
	// 显示 GameOver 图片
	auto gameover = new Sprite(ResLoader::getImage("text_game_over"));
	gameover->setPivot(0.5, 0);
	gameover->setPosY(120);
	this->addChild(gameover);

	// 加载得分板
	initPanel(score);

	// 加载按钮
	initButtons();

	// 整体居中
	this->setPosX(Window::getWidth() / 2);
	// 将节点整体移到屏幕下方
	this->setPosY(Window::getHeight());
	
	// 创建向量，向上运动窗口的高度
	auto vec = Vector(0, -Window::getHeight());
	// 位移动画，让得分面板从底部移动上来
	this->runAction(new ActionMoveBy(1, vec));
}

void GameOverLayer::initPanel(int score)
{
	// 显示得分板
	auto panel = new Sprite(ResLoader::getImage("score_panel"));
	panel->setPosY(Window::getHeight() / 2);
	this->addChild(panel);

	// 获取最高分
	int bestScore = Data::getInt("best_score", 0);

	// 保存最高分
	if (score > bestScore) {
		bestScore = score;
		Data::saveInt("best_score", bestScore);
		// 添加 new 图标
		auto newImage = new Sprite(ResLoader::getImage("new"));
		newImage->setPos(26, 23);
		panel->addChild(newImage);
	}

	// 添加奖牌
	auto modalFrame = getModal(score);
	if (modalFrame) {
		auto modal = new Sprite(modalFrame);
		modal->setPos(-65, 5);
		panel->addChild(modal);
		// 添加闪光
		auto blink = new Sprite(ResLoader::getImage("blink_00"));
		// 闪光动画
		auto frames = new Animation(130);
		frames->addKeyframe(ResLoader::getImage("blink_00"));
		frames->addKeyframe(ResLoader::getImage("blink_01"));
		frames->addKeyframe(ResLoader::getImage("blink_02"));
		frames->addKeyframe(ResLoader::getImage("blink_01"));
		frames->addKeyframe(ResLoader::getImage("blink_00"));
		// 随机闪光位置的动画
		auto action = new ActionCallback([=] {
			double x = Random::range(-modal->getWidth() / 2, modal->getWidth() / 2);
			double y = Random::range(-modal->getHeight() / 2, modal->getHeight() / 2);
			blink->setPos(x, y);
		});
		// 两动画交替循环运行
		blink->runAction(new ActionLoop(new ActionTwo(action, frames)));
		modal->addChild(blink);
	}

	// 显示得分
	auto scoreImage = new Number();
	scoreImage->setPos(91, -27);
	scoreImage->setLittleNumber(score);
	panel->addChild(scoreImage);

	// 显示最高分
	auto bestScoreImage = new Number();
	bestScoreImage->setPos(91, 14);
	bestScoreImage->setLittleNumber(bestScore);
	panel->addChild(bestScoreImage);
}

void GameOverLayer::initButtons()
{
	// 显示重新开始按钮
	auto restartBtnNormal = new Sprite(ResLoader::getImage("button_restart"));
	auto restartBtnSelected = new Sprite(ResLoader::getImage("button_restart"));
	restartBtnSelected->setPosY(5);
	auto restart = new Button(restartBtnNormal, restartBtnSelected);
	// 按下重新开始，进入一个新的 GameScene
	restart->setCallback([] {
		MusicManager::play("res/sound/click.wav");
		SceneManager::enter(new GameScene(), new TransitionFade(0.3, 0.3), false);
	});
	restart->setPosY(360);
	this->addChild(restart);

	// 显示返回主菜单按钮
	auto menuBtnNormal = new Sprite(ResLoader::getImage("button_menu"));
	auto menuBtnSelected = new Sprite(ResLoader::getImage("button_menu"));
	menuBtnSelected->setPosY(5);
	auto menu = new Button(menuBtnNormal, menuBtnSelected);
	// 按下返回主菜单，返回上一个场景
	menu->setCallback([] {
		MusicManager::play("res/sound/click.wav");
		SceneManager::back(new TransitionFade(0.3, 0.3));
	});
	menu->setPosY(420);
	this->addChild(menu);

	// 显示链接按钮
	auto shareBtnNormal = new Sprite(ResLoader::getImage("button_share"));
	auto shareBtnSelected = new Sprite(ResLoader::getImage("button_share"));
	shareBtnSelected->setPosY(5);
	auto share = new Button(shareBtnNormal, shareBtnSelected);
	// 按下链接按钮，打开链接
	share->setCallback([] {
		MusicManager::play("res/sound/click.wav");
		ShellExecuteA(NULL, "open", "https://gitee.com/werelone/FlappyBird", NULL, NULL, SW_SHOWNORMAL);
	});
	share->setPosY(455);
	this->addChild(share);
}

Image* GameOverLayer::getModal(int score)
{
	if (score < 10) {
		return nullptr;
	}
	else if (score >= 10 && score < 20) {
		return ResLoader::getImage("medals_0");	// 铜牌
	}
	else if (score >= 20 && score < 30) {
		return ResLoader::getImage("medals_1");	// 银牌
	}
	else if (score >= 30 && score < 50) {
		return ResLoader::getImage("medals_2");	// 金牌
	}
	else {
		return ResLoader::getImage("medals_3");	// 钻石奖牌
	}
}
