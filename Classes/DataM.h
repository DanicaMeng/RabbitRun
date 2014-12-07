#ifndef __DATA_M_H__
#define __DATA_M_H__

#include "cocos2d.h"

USING_NS_CC;

class DataM : public CCObject
{
public:
	DataM();
	~DataM();
	static DataM* getInstance();
	static void purge();
	bool init();
	void setScore(int value);
	void addScore(int value);
	int getScore();
	int getHighScore();
	void setPower(float value);
	void saveHighScore();

private:
	int _score;
	int _highScore;
	int _power;
};
#endif