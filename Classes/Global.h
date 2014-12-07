#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "GameScene.h"
#include "cocos2d.h"

USING_NS_CC;

extern const float SCREEN_WIDTH;
extern const float SCREEN_HEIGHT ;
extern const float SCREEN_CX;
extern const float SCREEN_CY;

extern const char FONT_NAME[];

extern GameScene* g_gameScene;

extern CCPoint getRandomPos();

#endif