#include "GameOver.h"
#include "Global.h"
#include "GameScene.h"
#include "DataM.h"

GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

bool GameOver::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 200)) )
    {
        return false;
    }
	
	DataM::getInstance()->saveHighScore();

	CCLabelTTF *title = CCLabelTTF::create("Game Over", FONT_NAME, 90);
	title->setPosition(ccp(SCREEN_CX, SCREEN_HEIGHT - 100));
	this->addChild(title);
	
	char s[128];
	sprintf(s, "High Score: %d", DataM::getInstance()->getHighScore());
	CCLabelTTF *highScore = CCLabelTTF::create(s, FONT_NAME, 80);
	highScore->setAnchorPoint(ccp(0.5f, 0.5f));
	highScore->setPosition(ccp(SCREEN_CX, SCREEN_HEIGHT - 250));
	highScore->setColor(ccc3(255,245, 0));

	this->addChild(highScore);

	sprintf(s, "Score: %d", DataM::getInstance()->getScore());
	CCLabelTTF *scoreShow = CCLabelTTF::create(s, FONT_NAME, 80);
	scoreShow->setAnchorPoint(ccp(0.5f, 0.5f));
	scoreShow->setPosition(ccp(SCREEN_CX, SCREEN_HEIGHT - 380));
	scoreShow->setColor(ccc3(255,245, 0));
	this->addChild(scoreShow);

	

	CCSprite *_eagle_catch = CCSprite::createWithSpriteFrameName("eagle_dive_left.png");
	_eagle_catch->setPosition(ccp(275, SCREEN_HEIGHT - 260));
	_eagle_catch->setScale(0.9f);
	this->addChild(_eagle_catch,1);

	CCSprite *_rabbit_catched = CCSprite::create("rabbit_catched.png");
	_rabbit_catched->setPosition(ccp(220, SCREEN_HEIGHT - 350));
	_rabbit_catched->setScale(0.25f);
	this->addChild(_rabbit_catched,2);

	CCMenuItemFont::setFontName(FONT_NAME);
	CCMenuItemFont::setFontSize(50);

	CCMenuItemFont *restartGame = CCMenuItemFont::create("Replay", this, menu_selector(GameOver::restartGame));
	restartGame->setColor(ccc3(0, 255,51));
	restartGame->setPositionX(-70);
	CCMenuItemFont *exitGame = CCMenuItemFont::create("Exit", this, menu_selector(GameOver::exitGame));
	exitGame->setColor(ccc3(255, 0, 0));
	exitGame->setPositionX(130);

	CCMenu *menu = CCMenu::create(exitGame, restartGame, NULL);
	menu->setPositionY(220);
	menu->setTouchPriority(-201);
	this->addChild(menu);

	

	this->setTouchPriority(-200);
	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);
	
	return true;
}

void GameOver::restartGame(CCObject* sender)
{
	this->removeFromParent();
	g_gameScene->restartGame();
}

void GameOver::exitGame(CCObject* sender)
{
	DataM::purge();
	CCDirector::sharedDirector()->end();
}