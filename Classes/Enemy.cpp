#include "Enemy.h"
#include "Global.h"
#include "SimpleAudioEngine.h"
#include <string>

using namespace std;
using namespace CocosDenshion;

#define PAR_RANGE 100
#define EAGLE_SCALE 0.3f
#define FLYAWAY_DIS (PAR_RANGE+50)
#define EAGLE_PAR_SEED 150
#define EAGLE_ATT_SEED 250
Enemy::Enemy()
{
	_sprite = NULL;
	_moveType = MOVE_NULL;
	_parSpeed = EAGLE_PAR_SEED;
	_attSpeed = EAGLE_ATT_SEED;
	_attBiginPos = CCPoint(0,0);
}

Enemy::~Enemy()
{
}

Enemy* Enemy::create(ENEMY_TYPE type)
{
    Enemy *pRet = new Enemy();
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

bool Enemy::init(ENEMY_TYPE type)
{
	if ( !CCNode::init() )
    {
        return false;
    }
	_type = type;
	string spriteName;
	switch(_type)
	{
	case EAGLE:
		spriteName = "eagle_fly_left.png";
		_parSpeed = EAGLE_PAR_SEED;
		_attSpeed = EAGLE_ATT_SEED;
		break;
	default:
		break;
	}
	_sprite = CCSprite::createWithSpriteFrameName(spriteName.c_str());
	_sprite->setPosition(getRandomPos());
	_sprite->setScale(EAGLE_SCALE);
	this->addChild(_sprite);

	this->scheduleUpdate();
	this->setMoveType(MOVE_PATROL);
	return true;
}

void Enemy::update(float dt)
{
	if(g_gameScene->isGameOver()) return;
	Player* player = g_gameScene->getPlayer();
	CCPoint pos = _sprite->getPosition();
	CCRect dieRect = player->getSprite()->boundingBox();
	CCRect patrolRect = CCRect(dieRect.getMinX()-PAR_RANGE,
		dieRect.getMinY()-PAR_RANGE,
		dieRect.getMaxX()+PAR_RANGE,
		dieRect.getMaxY());
	
	if(!player->isSterlth())
	{
		if(patrolRect.containsPoint(pos))
		{
			if(dieRect.containsPoint(pos))
			{
				player->hit();
			}
			else 
			{
				setMoveType(MOVE_ATTACK);
			}
		}
	}
}
void Enemy::setMoveType(MOVETYPE mtype)
{
	if(_moveType == mtype) return;
	_moveType = mtype;

	switch (_moveType)
	{
	case MOVE_ATTACK:
		attack();
		break;
	case MOVE_PATROL:
		{
			patrolMove();
		}
		break;
	case MOVE_FLYAWAY:
		flyAway();
		break;
	default:
		break;
	}
}
void Enemy::patrolMove()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float dist1, dist2;
	CCPoint pos = _sprite->getPosition();
	CCPoint playerPos = g_gameScene->getPlayer()->getSprite()->getPosition();
	CCPoint newPos;
	do
	{
		newPos = getRandomPos();
		dist1 = pos.getDistance(newPos);
		dist2 = pos.getDistance(playerPos);
	}while(dist1 < 100 /*&& dist2 < 50*/);
	_sprite->stopAllActions();
	CCMoveTo *move = CCMoveTo::create(dist1/_parSpeed, newPos);
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(Enemy::patrolMove));
	CCSequence* action = CCSequence::create(move, callback, NULL);
	_sprite->runAction(action);

	setDirection(pos,newPos);
}

void Enemy::attack()
{
	CCPoint pos = _sprite->getPosition();
	CCPoint playerPos = g_gameScene->getPlayer()->getSprite()->getPosition();

	// ÒôÐ§
	SimpleAudioEngine *_soundEffect = SimpleAudioEngine::sharedEngine();
	_soundEffect->preloadEffect("eagle_yeal.wav");
	_soundEffect->playEffect("eagle_yeal.wav");

	float dist1 = pos.getDistance(playerPos);

	_attBiginPos = pos;

	_sprite->stopAllActions();
	CCMoveTo *move = CCMoveTo::create(dist1/_attSpeed, playerPos);
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(Enemy::attackEnd));
	CCSequence* action = CCSequence::create(move, callback, NULL);
	_sprite->runAction(action);

	setDirection(pos,playerPos);
}

void Enemy::attackEnd()
{
	setMoveType(MOVE_FLYAWAY);
}

void Enemy::flyAway()
{
	int x = 0;
	CCPoint pos = _sprite->getPosition();
	if(_attBiginPos.x <= pos.x)
	{
		x = pos.x + FLYAWAY_DIS;
		if(x > SCREEN_WIDTH-50)	x = x-2*FLYAWAY_DIS;
	}
	else
	{
		x = pos.x - FLYAWAY_DIS;
		if(x<50) x = x + 2*FLYAWAY_DIS;
	}

	CCPoint endPoint = CCPoint(x,pos.y + 50);
	float dist1 = pos.getDistance(endPoint);

	_sprite->stopAllActions();
	CCMoveTo *move = CCMoveTo::create(dist1/_parSpeed, endPoint);
	CCCallFunc* callback = CCCallFunc::create(this, callfunc_selector(Enemy::flyAwayEnd));
	CCSequence* action = CCSequence::create(move, callback, NULL);
	_sprite->runAction(action);
	setDirection(pos,endPoint);
}

void  Enemy::flyAwayEnd()
{
	setMoveType(MOVE_PATROL);
}

void Enemy::setDirection(CCPoint curPos,CCPoint newPos)
{
	if(newPos.x>curPos.x)
	{
		setDirection(DIRECT_RIGHT);
	}
	else
	{
		setDirection(DIRECT_LEFT);
		
	}
}

void Enemy::setDirection(DIRECTTYPE direct)
{
	string imageStr = "eagle_";
	switch (_moveType)
	{
	case MOVE_ATTACK:
		imageStr += "dive_";
		break;
	case MOVE_PATROL:
		imageStr += "fly_";
		break;
	case MOVE_FLYAWAY:
		imageStr += "fly_";
		break;
	default:
		break;
	}
	switch (direct)
	{
	case DIRECT_LEFT:
		imageStr += "left";
		break;
	case DIRECT_RIGHT:
		imageStr += "right";
		break;
	default:
		break;
	}
	imageStr += ".png";
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCSpriteFrame *frame = cache->spriteFrameByName(imageStr.c_str());
	if(frame)
		_sprite->setDisplayFrame(frame);

}