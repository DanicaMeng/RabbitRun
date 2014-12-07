#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "item.h"
#include <string>

USING_NS_CC;
using namespace std;

class Player : public CCLayer
{
public:
	Player();
	~Player();
	bool init();
	CREATE_FUNC(Player);
	CCSprite* getSprite(){return _sprite;}
	void eatItem(ITEM_TYPE type);
	void die();
	void hit();
	bool isSterlth(){return _sterlth;}
	void startGame();
	void restartGame();

private:
	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);
    virtual void ccTouchCancelled(CCTouch *touch, CCEvent *event);
	virtual void update(float dt);
	void initAttribute();
	void reducePower(float dt);
	void unsterlth(float dt);
	void setAnimation(char* name, bool loop = true);
	void createAnimation();

	CCPoint _touchPos;
	CCSprite* _sprite;
	float _speed;
	float _power;
	bool _sterlth;
	float _scale;
	string _animationName;
};

#endif