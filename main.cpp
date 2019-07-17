//---------------------------------------------------------
// 程序名称：FlappyBird
// 作者：Nomango
// 最后更新：2018-3-14
// 编译环境：Visual Studio 2017 / Easy2D v2.0.0-beta6
// 项目类型：Win32 Application
//---------------------------------------------------------

#include <easy2d.h>
#include "SplashScene.h"
#include "ResLoader.h"
#include "resource.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	// 初始化窗口
	if (Game::init("FlappyBird", 288, 512, (LPCTSTR)IDI_ICON1, "flappybird_nomango"))
	{
		// 加载图片和音乐资源
		ResLoader::init();
		// 修改节点默认中心点，便于让图片居中显示
		Node::setDefaultPiovt(0.5, 0.5);
		// 节点不生成默认形状
		Node::setDefaultShapeEnable(false);
		// 打开碰撞检测
		ShapeManager::setCollisionEnable(true);

		// 创建 Splash 场景
		auto scene = new SplashScene();
		// 创建淡入淡出式的场景切换动画
		auto transition = new TransitionFade(0, 1);
		// 进入 Splash 场景
		SceneManager::enter(scene, transition);

		// 开始游戏
		Game::run();
	}
	// 回收游戏资源
	Game::uninit();
	return 0;
}