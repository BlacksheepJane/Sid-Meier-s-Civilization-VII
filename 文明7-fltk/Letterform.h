#ifndef LETTERFORM_H
#define LETTERFORM_H
#include <Windows.h>
#include <cstring>

class Letterform
{
public:
	//���øı���ɫ��Ӧ�ڸı����������һ��white���������Իָ�������ɫ
	static void SetColor(const char* color);


	//�ܲ��ң��������Կ���ֻ̨�������ͬ�ֺź���������֣�����SetFontֻ�����һ�������ã���SetFont�ĵ���Ӧ����main�����Ŀ�ͷ��
	static void SetFont(int size, const char* name);


	//�������������ûָ�����ʼֵ
	static void ReSetFont();

protected:

private:
};

#endif //LETTERFORM_H