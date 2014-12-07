#include "Player.h"
#include "DataM.h"
#include "Global.h"
#include "SimpleAudioEngine.h"
#include <cmath>
using namespace CocosDenshion;

static const float MAX_POWER = 50.0f;			// 能量上限 
static const float POWER_TIME = 0.5f;			// 每隔几秒减少一点饥能量
static const float SPEED = 300.0f;				// 速度 
static const float PER_SPEED = 2.5f;			// 每减少一点饥饿度所减少的速度
static const float INIT_SCALE = 0.15f;			// 初始的比例 
static const float ADD_SCALE = 0.05f;			// 每次增加的比例 
static const float REDUCE_SCALE = 0.1f;			// 每次减少的比例 
static const float MAX_SCALE = 2.0f;			// 最大的比例 
static const float STEALTH_TIME = 5.0f;			// 隐身时间
static const float INIT_STEALTH_TIME = 2.0f;	// 刚开始隐身时间（不透明）

Player::Player()
{
}

Player::~Player()
{
}

bool Player::init()
{
	if ( !CCLayer::init() )
    {
        return false;
    }
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("Rabbit.plist");
	createAnimation();

	_sprite = CCSprite::createWithSpriteFrameName("Rabbit_Stand_01.png");
	_sprite->setPosition(getRandomPos());
	_sprite->setScale(0.15f);
	this->addChild(_sprite);
	initAttribute();

	this->scheduleUpdate();
	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

	return true;
}

void Player::initAttribute()
{
	setAnimation("Stand");
	_sterlth = true;
	_speed = SPEED;
	_power = MAX_POWER;
	_scale = 1.0f;
	_sprite->setOpacity(255);
	_sprite->setScale(INIT_SCALE);
	DataM::getInstance()->setPower(_power/MAX_POWER*100.0f);
}

bool Player::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	_touchPos = touch->getLocation();
	return true;
}

void Player::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
	_touchPos = touch->getLocation();
}

void Player::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
	_touchPos.x = 0;
	_touchPos.y = 0;
	setAnimation("Stand");
}

void Player::ccTouchCancelled(CCTouch *touch, CCEvent *event)
{
}

void Player::update(float dt)
{
	if(g_gameScene->isGameOver()) return;
	if(_touchPos.x == 0)
	{
		return;
	}
	_speed = SPEED - (MAX_POWER - _power)*PER_SPEED;
	CCPoint pos = _sprite->getPosition();
	CCPoint newPos;
	float dx = _touchPos.x - pos.x;
	float dy = _touchPos.y - pos.y;
	float dist = sqrt(dx*dx + dy*dy);
	if(abs(dist) < 2) 
	{
		setAnimation("Stand");
		return;
	}
	_sprite->setFlipX(dx < 0);
	setAnimation("Run");
	newPos.x = pos.x + _speed*dt*dx/dist;
	newPos.y = pos.y + _speed*dt*dy/dist;
	if(newPos.x > SCREEN_WIDTH)
	{
		newPos.x = SCREEN_WIDTH;
	}
	else if(newPos.x < 0)
	{
		newPos.x = 0;
	}
	if(newPos.y > SCREEN_HEIGHT)
	{
		newPos.y = SCREEN_HEIGHT;
	}
	else if(newPos.y < 0)
	{
		newPos.y = 0;
	}
	_sprite->setPosition(newPos);
}

void Player::reducePower(float dt)
{
	_power -= 1;
	if(_power <= 0)
	{
		die();
	}
	_speed -= PER_SPEED;
	DataM::getInstance()->setPower(_power/MAX_POWER*100.0f);
}

void Player::eatItem(ITEM_TYPE type)
{
	string soundFile;
	float addPower = 0;
	switch(type)
	{
	case CARROT:
		soundFile = "rabbit_eat_big_carrot.wav";
		_scale += ADD_SCALE;
		_power += 20.f;
		break;
	case CABBAGE:
		soundFile = "rabbit_eat_cabbage.wav";
		_power += 10.f;
		break;
	case STERLTH_CARROT:
		soundFile = "rabbit_eat_small_carrot.wav";
		_sterlth = true;
		_sprite->setOpacity(150);
		this->scheduleOnce(schedule_selector(Player::unsterlth), STEALTH_TIME);
		break;
	case ICE_CARROT:
		soundFile = "rabbit_eat_ice_carrot.wav";
		_scale -= REDUCE_SCALE;
		break;
	default:
		break;
	}
	if(_power > MAX_POWER)
	{
		_power = MAX_POWER;
	}
	// 播放吃的音效
	SimpleAudioEngine *soundEffect = SimpleAudioEngine::sharedEngine();
	soundEffect->playEffect(soundFile.c_str());
	if(_scale < 1.0f)
	{
		_scale = 1.0f;
	}
	else if(_scale > MAX_SCALE)
	{
		_scale = MAX_SCALE;
	}
	_sprite->setScale(INIT_SCALE*_scale);
	DataM::getInstance()->setPower(_power/MAX_POWER*100.0f);
}

void Player::unsterlth(float dt)
{
	_sterlth = false;
	_sprite->setOpacity(255);
}

void Player::hit()
{
	if(_sterlth) return;
	die();
}

void Player::die()
{
	_sprite->setVisible(false);
	g_gameScene->showGameOver();
	this->unschedule(schedule_selector(Player::reducePower));
}

void Player::startGame()
{
	this->schedule(schedule_selector(Player::reducePower),	POWER_TIME); 
	this->scheduleOnce(schedule_selector(Player::unsterlth), INIT_STEALTH_TIME);
}

void Player::restartGame()
{
	_sprite->setPosition(getRandomPos());
	_sprite->setVisible(true);
	initAttribute();
	startGame();
}

void Player::createAnimation()
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCArray* animFrames = CCArray::create();
	char str[100] = {0};
	for(int i = 1; i < 10; i++) 
	{
		sprintf(str, "Rabbit_Run_%02d.png", i);
		CCSpriteFrame *frame = cache->spriteFrameByName(str);
		if(!frame) break;
		animFrames->addObject(frame);
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "Run");
}

void Player::setAnimation(char* name, bool loop)
{
	if(_animationName == name) return;
	_animationName = name;
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	_sprite->stopAllActions();
	if(name == "Stand")
	{
		_sprite->setDisplayFrame(cache->spriteFrameByName("Rabbit_Stand_01.png"));
	}
	else
	{
		CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName("Run");
		CCAnimate *animate = CCAnimate::create(animation);
		CCAction*action;
		if(loop)
		{
			action = CCRepeatForever::create(animate);
		}
		else
		{
			action = animate;
		}
		action->setTag(1);
		_sprite->runAction(action);   
	}
}