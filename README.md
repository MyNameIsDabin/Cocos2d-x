내가 Cocos2d-x 에서 편하게 쓰려고 설계한 클래스들. 다른사람이 써도 누이좋고 매부좋고

# Aseprite

Aseprite 를 통해 작업한 도트 애니메이션을 json 파일로 추출할 수 있는데, 이를 cocos2d-x 에서 파싱하여 사용하기 쉽게 하려구 만든 클래스 입니다.
코코스 내부의 Animate 클래스를 기반으로 하여 만들었습니다.
참고로, json 을 반드시 array 타입으로 추출해야 합니다.

예문)
<pre><code>Aseprite m_Aseprite;
 
//json 파일을 'ANIMATION_STAND' 키 값에 insert 한다. 'ANIMATION_STAND' 는 enum으로 선언한 상수다.
Aseprite.insert(ANIMATION_STAND, "sprite/player_stand.json", 0.25f);
 
//실제 스프라이트에서 사용하는 부분
Sprite* sprTest = Sprite::createWithSpriteFrame(m_Aseprite.getSpriteFrame(ANIMATION_STAND, 0));
m_sprTest ->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
m_sprTest ->setPosition(POSITION_CENTER(m_SpriteCoin));
m_sprTest ->runAction(m_Aseprite.animate(ANIMATION_STAND, true)); //애니메이션 run!
addChild(m_sprTest);
</code></pre>

# Binary Reader/Writer

C/C++ 의 기존 데이터 Reader/Writer 구조체 및 클래스보다 사용하기 좋게 한번 더 맵핑한 클래스 입니다.
기존에는 데이터를 쓸 때 Java나 C# 의 데이터 스트림 클래스와 같이 버퍼를 동적으로 할당하지 못했기 때문에 그 부분을 해결하고자 Wrapper 클래스를 따로 추가하였습니다.
이건 새로 만들어도 좋지만 cocos2d-x 내부의 Wrapper 클래스를 그대로 가져와 수정하였습니다.

<pre><code>
//데이터 쓰기
BinaryDataWriter saveData(SAVE_FILE_NAME);

saveData.writeString(m_UserName);

saveData.writeInt(m_SaveVersion);

saveData.writeInt(m_UserCoin);

saveData.close();
</code></pre>

<pre><code>
//데이터 읽기
BinaryDataReader loadData;	

//파일이 존재하는지
if (loadData.open(SAVE_FILE_NAME) == false)
{
		return;
}

m_UserName = loadData.readString();

m_SaveVersion = loadData.readInt();

m_UserCoin = loadData.readInt();

loadData.clear();
</code></pre>
