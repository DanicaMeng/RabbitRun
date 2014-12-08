#include "EnemyM.h"
#include "Enemy.h"
#include "Global.h"

EnemyM::EnemyM()
{
}

EnemyM::~EnemyM()
{
}

bool EnemyM::init()
{
	if ( !CCLayer::init() )
    {
        return false;
    }
	initEnemy();
	return true;
}

void EnemyM::createNewEnemy(float dt)
{
	if(g_gameScene->isGameOver()) return;
	Enemy *enemy = Enemy::create(EAGLE);
	this->addChild(enemy);
}

void EnemyM::initEnemy()
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("eagle.plist");

	for(int i = 0; i < 3; i++)
	{
		createNewEnemy(0);
	}
	this->unschedule(schedule_selector(EnemyM::createNewEnemy));
	this->schedule(schedule_selector(EnemyM::createNewEnemy),60);
}

void EnemyM::restartGame()
{
	this->removeAllChildren();
	initEnemy();
}