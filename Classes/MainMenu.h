#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "cocos2d.h"

USING_NS_CC;

class MainMenu : public CCLayerColor
{
public:
	MainMenu();
	~MainMenu();
    virtual bool init();  
    CREATE_FUNC(MainMenu);

private:
	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event){return true;}
	void startGame(CCObject* sender);
	void exitGame(CCObject* sender);
};
#endif