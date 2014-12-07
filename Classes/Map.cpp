#include "Map.h"
#include "Global.h"

const int STORE_MIN_NUM = 1;		// 石头最少个数 
const int STORE_MAX_NUM = 5;		// 石头最多个数 
const int TREE_MIN_NUM = 1;			// 树最少个数 
const int TREE_MAX_NUM = 5;			// 树最多个数

Map::Map()
{
}

Map::~Map()
{
}

bool Map::init()
{
	if ( !CCLayer::init() )
    {
        return false;
	}
	_bg = CCSprite::create("game_map.png");
	_bg->setAnchorPoint(ccp(0, 0));
	this->addChild(_bg);
	createStoneAndTree();
	
	return true;
}

void Map::createStoneAndTree()
{
	for(int i = 0; i < rand()%STORE_MAX_NUM + STORE_MIN_NUM; i++)
	{
		char name[16];
		sprintf(name, "stone-%d.png", rand()%3+1);
		CCSprite* stone = CCSprite::create(name);
		stone->setPosition(getRandomPos());
		_bg->addChild(stone);
	}

	for(int i = 0; i < rand()%TREE_MAX_NUM + TREE_MIN_NUM; i++)
	{
		CCSprite* tree = CCSprite::create("tree.png");
		tree->setPosition(getRandomPos());
		_bg->addChild(tree);
	}
}

void Map::restartGame()
{
	_bg->removeAllChildren();
	createStoneAndTree();
}