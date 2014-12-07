#include "Global.h"

const float SCREEN_WIDTH = 1280;
const float SCREEN_HEIGHT = 720;
const float SCREEN_CX = SCREEN_WIDTH/2;
const float SCREEN_CY = SCREEN_HEIGHT/2;

const char FONT_NAME[] = "arial";

GameScene* g_gameScene = NULL;

CCPoint getRandomPos()
{
	int x = rand()%(int)(SCREEN_WIDTH - 100) + 50;
	int y = rand()%(int)(SCREEN_HEIGHT - 100) + 50;
	return ccp(x, y);
}