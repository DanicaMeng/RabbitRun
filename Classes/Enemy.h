#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

USING_NS_CC;

enum ENEMY_TYPE
{
	EAGLE,			// ӥ 
};

enum MOVETYPE
{
	MOVE_NULL = 0,
	MOVE_ATTACK = 1,
	MOVE_PATROL,
	MOVE_FLYAWAY,
};

enum DIRECTTYPE
{
	DIRECT_LEFT = 1,
	DIRECT_RIGHT = 2,
};

class Enemy : public CCNode
{
public:
	Enemy();
	~Enemy();
	bool init(ENEMY_TYPE type);
	static Enemy* create(ENEMY_TYPE type);
	CCSprite* getSprite(){return _sprite;}

private:
	virtual void update(float dt);
	void setMoveType(MOVETYPE mtype);
	void patrolMove();
	void attack();
	void attackEnd();
	void flyAway();
	void flyAwayEnd();

	void setDirection(CCPoint curPos,CCPoint newPos);
	void setDirection(DIRECTTYPE direct);

	CCSprite *_sprite;
	ENEMY_TYPE _type;
	MOVETYPE _moveType;
	float _parSpeed;
	float _attSpeed;
	CCPoint _attBiginPos;
};

#endif