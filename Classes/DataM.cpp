#include "DataM.h"
#include "Global.h"

static DataM *s_SharedDataM = NULL;

DataM::DataM():
_score(0),
_highScore(0)
{
}

DataM::~DataM()
{
}

DataM* DataM::getInstance()
{
    if (!s_SharedDataM)
    {
        s_SharedDataM = new DataM();
        s_SharedDataM->init();
    }

    return s_SharedDataM;
}

void DataM::purge()
{
	if (s_SharedDataM)
	{
		delete s_SharedDataM;
		s_SharedDataM = NULL;
	}
}

bool DataM::init()
{
	_highScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("HighScore", 0);
	return true;
}

void DataM::setScore(int value)
{
	_score = value;
	g_gameScene->getInfo()->updateScore(_score);
}

void DataM::addScore(int value)
{
	_score += value;
	if(_score > _highScore)
	{
		_highScore = _score;
	}
	g_gameScene->getInfo()->updateScore(_score);
}

int DataM::getScore()
{
	return _score;
}
	
int DataM::getHighScore()
{
	return _highScore;
}

void DataM::setPower(float value)
{
	_power = value;
	g_gameScene->getInfo()->updatePower(_power);
}

void DataM::saveHighScore()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("HighScore", _highScore);
	CCUserDefault::sharedUserDefault()->flush();
}