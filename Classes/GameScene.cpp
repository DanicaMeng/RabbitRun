#include "GameScene.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "DataM.h"
#include "Global.h"

using namespace CocosDenshion;

GameScene::GameScene():
_gameOver(true)
{
}

GameScene::~GameScene()
{
}

bool GameScene::init()
{
	if ( !CCLayer::init() )
    {
        return false;
    }
	srand((unsigned)time(NULL));
	g_gameScene = this;
	_soundBackground = SimpleAudioEngine::sharedEngine();
	_soundBGFile = "bg_music.mp3";
	_soundBackground->preloadBackgroundMusic(_soundBGFile.c_str());
	showMenu();
	showGame();
	return true;
}

void GameScene::startGame()
{
	_gameOver = false;
	// ²¥·Å±³¾°ÒôÀÖ
	_soundBackground->playBackgroundMusic(_soundBGFile.c_str(), true);
	_player->startGame();

	_enemyM = EnemyM::create();
	this->addChild(_enemyM, 3);

}

void GameScene::restartGame()
{
	_soundBackground->playBackgroundMusic(_soundBGFile.c_str(), true);

	_gameOver = false;
	DataM::getInstance()->setScore(0);
	_map->restartGame();
	_player->restartGame();
	_itemM->restartGame();
	_enemyM->restartGame();	
}

void GameScene::showMenu()
{
	MainMenu *menu = MainMenu::create();
	this->addChild(menu, 1000);
}

void GameScene::showGame()
{
	_map = Map::create();
	this->addChild(_map, 0);

	_itemM = ItemM::create();
	this->addChild(_itemM, 1);

	_info = Info::create();
	this->addChild(_info, 4);

	_player = Player::create();
	this->addChild(_player, 2);
}

void GameScene::showGameOver()
{
	_gameOver = true;

	// Í£Ö¹±³¾°ÒôÀÖ
	_soundBackground->stopBackgroundMusic();

	// ²¥·Ågame overÉùÒô
	SimpleAudioEngine *_soundGameOver = SimpleAudioEngine::sharedEngine();
	_soundGameOver->preloadEffect("game_over.mp3");
	_soundGameOver->playEffect("game_over.mp3");

	GameOver *gameOver = GameOver::create();
	this->addChild(gameOver, 1000);
}