#ifndef LETTERFORM_H
#define LETTERFORM_H
#include <Windows.h>
#include <cstring>

class Letterform
{
public:
	//调用改变颜色后，应在改变结束处进行一次white参数调用以恢复字体颜色
	static void SetColor(const char* color);


	//很不幸，经过测试控制台只能输出相同字号和字体的文字，所以SetFont只有最后一次有作用，故SetFont的调用应当在main函数的开头。
	static void SetFont(int size, const char* name);


	//将字体所有设置恢复至初始值
	static void ReSetFont();

protected:

private:
};

#endif //LETTERFORM_H