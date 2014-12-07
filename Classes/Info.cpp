#include "Info.h"
#include "Global.h"

Info::Info()
{
}

Info::~Info()
{
}

bool Info::init()
{
	if ( !CCLayer::init() )
    {
        return false;
    }

	CCSprite *icon = CCSprite::create("gold.png");
	icon->setScale(0.4f);
	icon->setPosition(ccp(SCREEN_CX + 50, SCREEN_HEIGHT - 50));
	this->addChild(icon);

	_score = CCLabelTTF::create("0", FONT_NAME, 60);
	_score->setColor(ccc3(255, 255, 0));
	_score->setPosition(ccp(SCREEN_CX + 150, SCREEN_HEIGHT - 50));
	this->addChild(_score);

	CCSprite *powerBg = CCSprite::create("power_bg.png");
	powerBg->setAnchorPoint(ccp(0, 1));
	powerBg->setPosition(ccp(0, SCREEN_HEIGHT));
	powerBg->setOpacity(160);
	this->addChild(powerBg);

	_power = CCProgressTimer::create(CCSprite::create("power.png"));
	_power->setType(kCCProgressTimerTypeBar);
	_power->setMidpoint(ccp(0, 0.5f));
	_power->setBarChangeRate(ccp(1, 0));
	_power->setPercentage(100.0f);
	_power->setAnchorPoint(ccp(0, 0.5));
	_power->setPosition(ccp(88, 32));
	_power->setOpacity(160);
	powerBg->addChild(_power);

	return true;
}

void Info::updateScore(int score)
{
	char buff[64];
	sprintf(buff, "%d", score);
	_score->setString(buff);
}

void Info::updatePower(float power)
{
	_power->setPercentage(power);
}