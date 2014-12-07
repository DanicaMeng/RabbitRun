#include "MainMenu.h"
#include "Global.h"
#include "DataM.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

bool MainMenu::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 200)) )
    {
        return false;
    }

	CCLabelTTF *title = CCLabelTTF::create("Rabbit Run", FONT_NAME, 70);
	title->setPosition(ccp(SCREEN_CX, SCREEN_HEIGHT - 80));
	this->addChild(title);

	CCMenuItemFont::setFontName(FONT_NAME);
	CCMenuItemFont::setFontSize(50);

	char* text[] = {"Score", "Power", "Effect",
				   "+10", "+20%", "--",
	               "+20", "+40%", "grow up",
				   "+10", "+0", "lose weight",
	               "+0", "+0","hiding"};
	for(int i = 0; i < 15; i++)
	{
		CCLabelTTF *label = CCLabelTTF::create(text[i], FONT_NAME, 50);
		label->setPosition(ccp(400 + i%3*300, 550 - i/3*85));
		this->addChild(label);
	}
	char* img[] = {"cabbage.png", "carrot.png", "carrot_ice.png", "carrot_sterlth.png"};
	for(int i = 0; i < 4; i++)
	{
		CCSprite *sprite = CCSprite::create(img[i]);
		sprite->setScale(0.2f);
		sprite->setPosition(ccp(250, 450 - i*80));
		this->addChild(sprite);
	}
	CCMenuItemFont *startGame = CCMenuItemFont::create("Play", this, menu_selector(MainMenu::startGame));
	startGame->setColor(ccc3(0, 255,51));
	startGame->setPositionX(-90);

	CCMenuItemFont *exitGame = CCMenuItemFont::create("Exit", this, menu_selector(MainMenu::exitGame));
	exitGame->setColor(ccc3(255, 0, 0));
	exitGame->setPositionX(110);

	CCMenu *menu = CCMenu::create(startGame, exitGame, NULL);
	menu->setPositionY(120);
	menu->setTouchPriority(-201);
	this->addChild(menu);

	this->setTouchPriority(-200);
	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

	return true;
}

void MainMenu::startGame(CCObject* sender)
{
	this->removeFromParent();
	g_gameScene->startGame();
}

void MainMenu::exitGame(CCObject* sender)
{
	DataM::purge();
	CCDirector::sharedDirector()->end();
}