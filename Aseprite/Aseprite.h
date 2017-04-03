#pragma once

#include "cocos2d.h"
using namespace cocos2d;

class Aseprite
{
private:

	//�ִϸ��̼�
	cocos2d::Map<int, Animation*> m_MapAnimation;

public:
	Aseprite();
	~Aseprite();

	/** Ű ���� ���� animate �׼��� ��ȯ
		@param key		��� �� �ִϸ��̼� Ű ��
		@param repeat	�ִϸ��̼� �ݺ� ����
	*/
	Action* animate(const int& key, bool repeat);

	/** Aseprite ���� ������ json (Array Ÿ��) ������ ������� ���� �ִϸ��̼��� Ű ���� insert �Ѵ�
		@param key		�߰��� �ִϸ��̼� Ű ��
		@param json		json ������ ���
		@param dpu		�ִϸ��̼� �����Ӵ� �������
	*/
	void insert(const int& key, const std::string& json, float dpu);

	/** Ű ���� �ش��ϴ� �ִϸ��̼� �� idx��° ������ ������ ��ȯ
		@param key		�ִϸ��̼��� Ű ��
		@param idx		�������� �ε�����(���° ������ ����)
	*/
	SpriteFrame* getSpriteFrame(const int& key, const int& idx);
};