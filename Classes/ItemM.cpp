#include "ItemM.h"
#include "Item.h"
#include "Global.h"


ItemM::ItemM()
{
}

ItemM::~ItemM()
{
}

bool ItemM::init()
{
	if ( !CCLayer::init() )
    {
        return false;
    }
	initItem();
	createNewItem();	
	return true;
}





void ItemM::createNewItem()
{
	if(g_gameScene->isGameOver()) return;
	int type;
	int num = rand()%100;
	CCLOG("num: %d", num);
	if(num > 90) type = 2;
	else if(num > 85) type = 3;
	else if(num > 40) type = 1;
	else type = 0;
	Item *item = Item::create((ITEM_TYPE)type);
	this->addChild(item);
}

void ItemM::createNewItemeEveryTime(float dt)
{
	createNewItem();

}


void ItemM::initItem()
{
	this->unschedule(schedule_selector(ItemM::createNewItemeEveryTime));
	this->schedule(schedule_selector(ItemM::createNewItemeEveryTime),2);
}

void ItemM::restartGame()
{
	this->removeAllChildren();
	createNewItem();
}