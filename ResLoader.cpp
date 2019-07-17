#include "ResLoader.h"
#include <map>
using namespace std;

struct Info
{
	double x, y, width, height;
};

map<String, Info> s_ImageMap;


void ResLoader::init()
{
	// 把音乐文件添加到音乐管理器
	MusicManager::preload("res/sound/fly.wav");
	MusicManager::preload("res/sound/hit.wav");
	MusicManager::preload("res/sound/click.wav");
	MusicManager::preload("res/sound/point.wav");
	MusicManager::preload("res/sound/swoosh.wav");

	// 预加载图片
	Image::preload("res/atlas.png");

	// 打开 atlas.bin 文件
	ifstream file("res/atlas.bin");
	// 读取图片信息
	while (!file.eof())
	{
		char name[21];
		double width, height, x, y;
		// 读取图片名称、宽高、起始点坐标
		file >> name >> width >> height >> x >> y;
		// 创建 Info
		Info info = { x, y, width, height };
		s_ImageMap.insert(make_pair(name, info));
	}
}

Image * ResLoader::getImage(String imageName)
{
	Info info = s_ImageMap.at(imageName);
	return new Image("res/atlas.png", info.x, info.y, info.width, info.height);
}