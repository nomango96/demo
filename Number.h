#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <easy2d.h>


// 数字类
// 显示得分时，用于将 int 型数字转化为图片的类
class Number :
	public Node
{
public:
	Number();

	int getNumber();					// 获取它代表的数字
	void setNumber(int number);			// 将 int 转化为图片（大）
	void setLittleNumber(int number);	// 将 int 转化为图片（小）

protected:
	int number;
};

