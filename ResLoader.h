#pragma once
#include <easy2d.h>
#include <fstream>

// 小鸟、水管、地面的掩码
#define BIRD_BITMASK	0x0001
#define PIPE_BITMASK	0x0010
#define GROUND_BITMASK	0x0100


// 资源管理工具
class ResLoader
{
public:
	static void init();
	static Image* getImage(String imageName);
};
