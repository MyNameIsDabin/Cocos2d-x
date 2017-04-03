#include "Aseprite.h"
#include "BaseUtil.h"

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/filestream.h"
using namespace rapidjson;

Aseprite::Aseprite()
{
}

Aseprite::~Aseprite()
{
}

Action* Aseprite::animate(const int& key, bool repeat)
{
	Action* anim = nullptr;

	if (repeat == true)
	{
		anim = RepeatForever::create(Animate::create(m_MapAnimation.at(key)));
	}
	else
	{
		anim = Animate::create(m_MapAnimation.at(key));
	}

	return anim;
}

void Aseprite::insert(const int& key, const std::string& json, float dpu)
{
	CCASSERT(json.size()>0, "json filename should not be nullptr");

	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(json);

	if (fullPath.size() == 0)
	{
		//만약 json파일이 존재하지 않으면 리턴
		CCLOG("cocos2d: SpriteFrameCache: can not find %s", json.c_str());
		return;
	}

	SpriteFrameCache* sprFrameCache = SpriteFrameCache::getInstance();

	std::string data = FileUtils::getInstance()->getStringFromFile(fullPath);

	std::string texturePath("");

	//json 파일과 동일한 이름의 png 파일을 찾는다
	texturePath = BaseUtil::changeFileExtension(json, ".png");

	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(texturePath.c_str());
	texture->setAliasTexParameters();

	if (texture)
	{
		Document document;

		Animation* animation = Animation::create();
		animation->setDelayPerUnit(dpu);

		if (!document.Parse<0>(data.c_str()).HasParseError())
		{
			const rapidjson::Value& documentFrames = document["frames"];

			for (SizeType i = 0; i < documentFrames.Size(); i++)
			{
				std::string spriteFrameName = documentFrames[i]["filename"].GetString();

				//Aseprite 의 json 파일의 경우 filename 이름의 넘버링 사이에 공백이 있다.
				//공백을 먼저 언더바('_')로 변경하고 확장자를 .png 로 변경하여 스프라이트 프레임에 추가한다
				spriteFrameName = spriteFrameName.replace(spriteFrameName.find_last_of(" "), 1, "_");
				spriteFrameName = BaseUtil::changeFileExtension(spriteFrameName, ".png");

				float x = static_cast<float>(documentFrames[i]["frame"]["x"].GetDouble());
				float y = static_cast<float>(documentFrames[i]["frame"]["y"].GetDouble());
				float w = static_cast<float>(documentFrames[i]["frame"]["w"].GetDouble());
				float h = static_cast<float>(documentFrames[i]["frame"]["h"].GetDouble());
				float ox = static_cast<float>(documentFrames[i]["spriteSourceSize"]["x"].GetDouble());
				float oy = static_cast<float>(documentFrames[i]["spriteSourceSize"]["y"].GetDouble());
				float ow = static_cast<float>(documentFrames[i]["spriteSourceSize"]["w"].GetDouble());
				float oh = static_cast<float>(documentFrames[i]["spriteSourceSize"]["h"].GetDouble());

				bool rotated = documentFrames[i]["rotated"].GetBool();

				// check ow/oh
				if (!ow || !oh)
				{
					CCLOGWARN("cocos2d: WARNING: originalWidth/Height not found on the SpriteFrame. AnchorPoint won't work as expected. Regenrate the .json");
				}

				// abs ow/oh
				ow = abs(ow);
				oh = abs(oh);

				// create frame
				SpriteFrame* sprFrame = SpriteFrame::createWithTexture(texture,
					Rect(x, y, w, h),
					rotated,
					Vec2(ox, oy),
					Size((float)ow, (float)oh)
					);

				// add sprite frame
				SpriteFrameCache::getInstance()->addSpriteFrame(sprFrame, spriteFrameName);

				animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName));
			}
		}
		else
		{
			CCLOG("cocos2d: SpriteFrameCache: Couldn't load texture");
		}

		m_MapAnimation.insert(key, animation);
	}
}

SpriteFrame* Aseprite::getSpriteFrame(const int& key, const int& idx)
{
	return m_MapAnimation.at(key)->getFrames().at(idx)->getSpriteFrame();
}