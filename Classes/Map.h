#ifndef __MAP_H__
#define __MAP_H__

#include "cocos2d.h"

USING_NS_CC;

class Map : public CCLayer
{
public:
	Map();
	~Map();
	bool init();
	CREATE_FUNC(Map);
	void restartGame();
	void createStoneAndTree();

private:
	CCSprite *_bg;
};

#endif