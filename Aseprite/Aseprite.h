#pragma once

#include "cocos2d.h"
using namespace cocos2d;

class Aseprite
{
private:

	//애니메이션
	cocos2d::Map<int, Animation*> m_MapAnimation;

public:
	Aseprite();
	~Aseprite();

	/** 키 값에 따른 animate 액션을 반환
		@param key		재생 할 애니메이션 키 값
		@param repeat	애니메이션 반복 여부
	*/
	Action* animate(const int& key, bool repeat);

	/** Aseprite 에서 추출한 json (Array 타입) 파일을 기반으로 만든 애니메이션을 키 값에 insert 한다
		@param key		추가할 애니메이션 키 값
		@param json		json 파일의 경로
		@param dpu		애니메이션 프레임당 재생간격
	*/
	void insert(const int& key, const std::string& json, float dpu);

	/** 키 값에 해당하는 애니메이션 중 idx번째 프레임 정보를 반환
		@param key		애니메이션의 키 값
		@param idx		프레임의 인덱스값(몇번째 프레임 인지)
	*/
	SpriteFrame* getSpriteFrame(const int& key, const int& idx);
};