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

	//스프라이트 변경
	static Sprite* changeSprite(Sprite* sprite, const std::string& filename);

	//랜덤 함수
	static int random(int min, int max);
	static float random(float min, float max);	

	//충돌체크 함수
	static bool collisionPoint(const Node* node, const Vec2& point);
	static bool collisionRectangle(const Node* node, const Rect& rect);
	static bool collisionNode(Node* node1, Node* node2);

	//해당 방향을 목표로 특정한 속도로 이동했을때 다음 포지션을 반환
	static Vec2 moveTowardsPoint(const Node* node, const Vec2& point, const float& speed);
	static Vec2 moveTowardsNode(const Node* node, const Node* other, const float& speed);
	static Vec2 moveTowardsAngle(const Node* node, const float& angle, const float& speed);

	//특정 포지션을 바라보는 방향
	static float pointDirection(const Vec2& p1, const Vec2& p2);
	static float pointDirection(const Node* node, const Vec2& point);

	//현재 각도가 몇사분면에 해당하는지
	static int quadrantForAngle(const float& angle);

	//노드기준의 Rect를 특정노드 기준의 Rect로 변환
	static Rect convertToWorldRect(const Node* node);

	//디버그
	static std::string debugVec2(const Vec2& vec2);
	static std::string debugRect(const Rect& rect);

	//파일 확장자 변경
	static std::string changeFileExtension(const std::string& fileName, std::string aftExt);

	//시간
	static int getCurrentData(); //20160925
	static long long getCurrentTime();

	//가장 가까운 노드 찾기
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
