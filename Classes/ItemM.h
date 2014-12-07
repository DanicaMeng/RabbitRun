#ifndef __ITEM_M_H__
#define __ITEM_M_H__

#include "cocos2d.h"

USING_NS_CC;

class ItemM : public CCLayer
{
public:
	ItemM();
	~ItemM();
	bool init();
	CREATE_FUNC(ItemM);
	void createNewItem();
	void createNewItemeEveryTime(float dt);
	void deleteItemEveryTime(float dt);
	void restartGame();

private:
	void initItem();
	//void createNewItem();
};

#endif