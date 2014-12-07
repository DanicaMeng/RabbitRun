#ifndef __ENEMY_M_H__
#define __ENEMY_M_H__

#include "cocos2d.h"

USING_NS_CC;

class EnemyM : public CCLayer
{
public:
	EnemyM();
	~EnemyM();
	bool init();
	CREATE_FUNC(EnemyM);
	void restartGame();

private:
	void initEnemy();
	void createNewEnemy(float dt);
};

#endif