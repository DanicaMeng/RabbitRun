#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "Map.h"
#include "ItemM.h"
#include "EnemyM.h"
#include "Player.h"
#include "Info.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

class GameScene : public CCLayer
{
public:
	GameScene();
	~GameScene();
    virtual bool init();  
    CREATE_FUNC(GameScene);
	void startGame();
	void restartGame();
	void showGameOver();
	bool isGameOver(){return _gameOver;}
	Map* getMap(){return _map;}
	ItemM* getItemM(){return _itemM;}
	EnemyM* getEnemyM(){return _enemyM;}
	Player* getPlayer(){return _player;}
	Info* getInfo(){return _info;}

private:
	void showMenu();
	void showGame();
	
	bool _gameOver;
	Map *_map;
	ItemM *_itemM;
	EnemyM *_enemyM;
	Player *_player;
	Info *_info;
	SimpleAudioEngine *_soundBackground;
	string _soundBGFile;
};
#endif