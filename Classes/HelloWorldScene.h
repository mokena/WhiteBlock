#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:
	int lineCount;
	bool showEnd;
	bool timerRunning;
	long startTime;
	Size visibleSize;
	Node* gameLayer;
	Label* timerLabel;

	void addStartLine();
	void addEndLine();
	void addNormalLine(int lineIndex);
	void startGame();
	void moveDown();

	void startTimer();
	void stopTimer();

public:
	static const int BLOCKS_IN_LINE = 4;

    static cocos2d::Scene* createScene();

    virtual bool init();

	virtual void update(float dt);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
