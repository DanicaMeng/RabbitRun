#include "Item.h"
#include "Global.h"
#include "DataM.h"
#include "SimpleAudioEngine.h"
#include <string>
#include <time.h>

using namespace std;
using namespace CocosDenshion;

Item::Item():
_eat(false)
{
}

Item::~Item()
{
}


//在屏幕上生成道具
Item* Item::create(ITEM_TYPE type)
{
    Item *pRet = new Item();
    if (pRet && pRet->init(type))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}




bool Item::init(ITEM_TYPE type)
{
	if ( !CCNode::init() )
    {
        return false;
    }
	_type = type;
	string spriteName;
	switch(_type)
	{
	case CARROT:
		spriteName = "carrot.png";
		_score = 20;
		break;
	case CABBAGE:
		spriteName = "cabbage.png";
		_score = 10;
		break;
	case STERLTH_CARROT:
		spriteName = "carrot_sterlth.png";
		_score = 0;
		break;
	case ICE_CARROT:
		spriteName = "carrot_ice.png";
		_score = 10;
		break;
	default:
		break;
	}
	_sprite = CCSprite::create(spriteName.c_str());   //生成精灵
	_sprite->setPosition(getRandomPos());  //设置位置
	_sprite->setScale(0.15f);
	this->addChild(_sprite);
	this->scheduleOnce(schedule_selector(Item::removeSprite),10);
	this->scheduleUpdate();
	return true;
}
void Item::removeSprite(float dt)
{
	this->removeFromParent();
}

void Item::update(float dt)
{
	if(_eat || g_gameScene->isGameOver()) return;
	Player* player = g_gameScene->getPlayer();
	if(player->getSprite()->boundingBox().containsPoint(_sprite->getPosition()))
	{
		DataM::getInstance()->addScore(_score); 
		player->eatItem(_type);
		_eat = true;

		// 闪烁
		CCActionInterval *blinkAction = CCBlink::create(0.4f, 3);
		CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(Item::deleteItem));
		CCSequence *action = CCSequence::create(blinkAction, callback, NULL);
		this->runAction(action);

	}
}

void Item::deleteItem()
{
	this->removeFromParent();
}
