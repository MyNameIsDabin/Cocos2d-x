#pragma once

#include "cocos2d.h"
#include <random>
using namespace cocos2d;

class BaseUtil
{
public:

	enum Direction
	{
		RIGHT_TOP = 0, LEFT_TOP = 1, LEFT_DOWN = 2, RIGHT_DOWN = 3
	};

	//��������Ʈ ����
	static Sprite* changeSprite(Sprite* sprite, const std::string& filename);

	//���� �Լ�
	static int random(int min, int max);
	static float random(float min, float max);	

	//�浹üũ �Լ�
	static bool collisionPoint(const Node* node, const Vec2& point);
	static bool collisionRectangle(const Node* node, const Rect& rect);
	static bool collisionNode(Node* node1, Node* node2);

	//�ش� ������ ��ǥ�� Ư���� �ӵ��� �̵������� ���� �������� ��ȯ
	static Vec2 moveTowardsPoint(const Node* node, const Vec2& point, const float& speed);
	static Vec2 moveTowardsNode(const Node* node, const Node* other, const float& speed);
	static Vec2 moveTowardsAngle(const Node* node, const float& angle, const float& speed);

	//Ư�� �������� �ٶ󺸴� ����
	static float pointDirection(const Vec2& p1, const Vec2& p2);
	static float pointDirection(const Node* node, const Vec2& point);

	//���� ������ ���и鿡 �ش��ϴ���
	static int quadrantForAngle(const float& angle);

	//�������� Rect�� Ư����� ������ Rect�� ��ȯ
	static Rect convertToWorldRect(const Node* node);

	//�����
	static std::string debugVec2(const Vec2& vec2);
	static std::string debugRect(const Rect& rect);

	//���� Ȯ���� ����
	static std::string changeFileExtension(const std::string& fileName, std::string aftExt);

	//�ð�
	static int getCurrentData(); //20160925
	static long long getCurrentTime();

	//���� ����� ��� ã��
	template<typename T>
	static T nearestNode(const Node* node, const cocos2d::Vector<T>* list)
	{
		int minDist = 99999;
		T nearNode = nullptr;

		for (auto other : *list)
		{
			int dist = other->getPosition().distance(node->getPosition());

			if (dist < minDist)
			{
				minDist = dist;
				nearNode = other;
			}
		}

		return nearNode;
	}
};
