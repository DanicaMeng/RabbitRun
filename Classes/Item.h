#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

USING_NS_CC;

enum ITEM_TYPE
{
	CARROT,				// ���ܲ� 
	CABBAGE,			// �ײ� 
	STERLTH_CARROT,		// ������ܲ� 
	ICE_CARROT,         // ���ܲ�
};

class Item : public CCNode
{
public:
	Item();
	~Item();
	bool init(ITEM_TYPE type);
	static Item* create(ITEM_TYPE type);
	void removeSprite(float dt);
	CCSprite* getSprite(){return _sprite;}

private:
	virtual void update(float dt);
	void deleteItem();
	CCSprite *_sprite;
	ITEM_TYPE _type;
	int _score;
	bool _eat;
};

#endif