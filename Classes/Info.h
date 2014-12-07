#ifndef __INFO_H__
#define __INFO_H__

#include "cocos2d.h"

USING_NS_CC;

class Info : public CCLayer
{
public:
	Info();
	~Info();
	bool init();
	CREATE_FUNC(Info);
	void updateScore(int score);
	void updatePower(float power);

private:
	CCLabelTTF *_score;
	CCProgressTimer *_power;
};

#endif