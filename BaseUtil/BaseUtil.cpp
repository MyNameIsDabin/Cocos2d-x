#include "BaseUtil.h"

Sprite* BaseUtil::changeSprite(Sprite* sprite, const std::string& filename)
{
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
	
	if (texture)
	{
		Rect rect = Rect::ZERO;
		rect.size = texture->getContentSize();

		sprite->setTexture(texture);
		sprite->setTextureRect(rect);
	}

	return sprite;
}

int BaseUtil::random(int min, int max)
{
	std::random_device rd;
	std::mt19937 rEngine(rd());
	std::uniform_int_distribution<> dist(min, max);
	return static_cast<int>(dist(rEngine));
}

float BaseUtil::random(float min, float max)
{
	std::random_device rd;
	std::mt19937 rEngine(rd());
	std::uniform_real_distribution<> dist(min, max);
	return static_cast<float>(dist(rEngine));
}

bool BaseUtil::collisionPoint(const Node* node, const Vec2& point)
{
	Rect nodeRect = node->getBoundingBox();

	if (point.x >= nodeRect.origin.x && point.x <= nodeRect.origin.x + nodeRect.size.width
		&& point.y >= nodeRect.origin.y && point.y <= nodeRect.origin.y + nodeRect.size.height)
	{
		return true;
	}

	return false;
}

bool BaseUtil::collisionRectangle(const Node* node, const Rect& rect)
{
	if (node->getBoundingBox().intersectsRect(rect))
		return true;

	return false;
}

bool BaseUtil::collisionNode(Node* node1, Node* node2)
{
	if (node1->getBoundingBox().intersectsRect(node2->getBoundingBox()))
		return true;

	return false;
}

Vec2 BaseUtil::moveTowardsPoint(const Node* node, const Vec2& point, const float& speed)
{
	return moveTowardsAngle(node, pointDirection(node->getPosition(), point), speed);
}

Vec2 BaseUtil::moveTowardsNode(const Node* node, const Node* other, const float& speed)
{
	return moveTowardsPoint(node, other->getPosition(), speed);
}

Vec2 BaseUtil::moveTowardsAngle(const Node* node, const float& angle, const float& speed)
{
	Vec2 nextPosition = Vec2(-1, -1);
	nextPosition.x = node->getPositionX() + speed * cos(CC_DEGREES_TO_RADIANS(angle));
	nextPosition.y = node->getPositionY() + speed * sin(CC_DEGREES_TO_RADIANS(angle));

	return nextPosition;
}

float BaseUtil::pointDirection(const Vec2& p1, const Vec2& p2)
{
	return CC_RADIANS_TO_DEGREES(atan2f(p2.y - p1.y, p2.x - p1.x));
}

float BaseUtil::pointDirection(const Node* node, const Vec2& point)
{
	return pointDirection(node->getPosition(), point);
}

int BaseUtil::quadrantForAngle(const float& angle)
{
	float _angle = abs(angle);

	int quadrant = 0;

	for (int i = 0; i < 4; i++)
	{
		if (i * 90 <= _angle && _angle < (i * 90) + 90)
		{
			quadrant = i;
			break;
		}
	}

	return  quadrant; //(n-1)»çºÐ¸é
}

Rect BaseUtil::convertToWorldRect(const Node* node)
{
	Rect worldRect = node->getBoundingBox();
	Vec2 originPos = node->getParent()->convertToWorldSpace(node->getPosition());
	worldRect.origin.x = originPos.x - node->getAnchorPoint().x * worldRect.size.width;
	worldRect.origin.y = originPos.y - node->getAnchorPoint().y * worldRect.size.height;

	return worldRect;
}

std::string BaseUtil::debugVec2(const Vec2& vec2)
{
	char strBuf[25];
	sprintf(strBuf, "(%g, %g)", vec2.x, vec2.y);

	return std::string(strBuf);
}

std::string BaseUtil::debugRect(const Rect& rect)
{
	char strBuf[25];
	sprintf(strBuf, "(%g, %g, %g, %g)", rect.getMinX(), rect.getMinY(), rect.getMaxX(), rect.getMaxY());

	return std::string(strBuf);
}

std::string BaseUtil::changeFileExtension(const std::string& fileName, std::string aftExt)
{
	std::string changeName = fileName;
	size_t startPos = fileName.find_last_of(".");
	changeName = changeName.erase(startPos);
	changeName = changeName.append(aftExt);

	return changeName;
}

int BaseUtil::getCurrentData()
{
	time_t timer = time(nullptr);
	struct tm *t = localtime(&timer);

	return ((t->tm_year + 1900) * 10000) + ((t->tm_mon + 1) * 100) + t->tm_mday;
}

long long BaseUtil::getCurrentTime()
{
	long long currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	return currentTime;
}