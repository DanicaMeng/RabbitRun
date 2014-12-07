#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"

USING_NS_CC;

class GameOver : public CCLayerColor
{
public:
	GameOver();
	~GameOver();
	bool init();
	CREATE_FUNC(GameOver);

private:
	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event){return true;}
	void restartGame(CCObject* sender);
	void exitGame(CCObject* sender);
};

#endif