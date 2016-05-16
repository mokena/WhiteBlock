#include "HelloWorldScene.h"
#include "Block.h"


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	lineCount = 20;
	showEnd = false;
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	startGame();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* t, Event* e) {
		auto blocks = Block::getBlocks();

		for (auto it = blocks->begin(); it != blocks->end(); it++) {
			if ((*it)->getLineIndex() == 1 && (*it)->getBoundingBox().containsPoint(t->getLocation())) {
				if ((*it)->getColor() == Color3B::BLACK) {
					(*it)->setColor(Color3B::GRAY);
					moveDown();
				}
				else if ((*it)->getColor() == Color3B::MAGENTA) {
					moveDown();
					showEnd = true;
				}
				else {
					MessageBox("Failed!", "Game Over");
				}
				break;
			}
		}

		return false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
    return true;
}

void HelloWorld::addStartLine() {
	Block* startLine = Block::createWithArgs(Color3B::YELLOW, Size(visibleSize.width, visibleSize.height / BLOCKS_IN_LINE), "", 20, Color4B::BLACK);
	addChild(startLine);
	int lineIndex = 0;
	startLine->setLineIndex(lineIndex);
	startLine->setPosition(0, lineIndex*visibleSize.height / BLOCKS_IN_LINE);
}

void HelloWorld::addEndLine() {
	lineCount--;
	Block* endLine = Block::createWithArgs(Color3B::MAGENTA, visibleSize, "Game Over", 40, Color4B::BLACK);
	addChild(endLine);
	int lineIndex = 4;
	endLine->setLineIndex(lineIndex);
	endLine->setPosition(0, lineIndex*visibleSize.height / BLOCKS_IN_LINE);
}

void HelloWorld::addNormalLine(int lineIndex) {
	//srand(time(NULL));
	int black = rand() % BLOCKS_IN_LINE;
	Size size = Size(visibleSize.width / BLOCKS_IN_LINE - 1, visibleSize.height / BLOCKS_IN_LINE - 1);
	for (int i = 0; i < BLOCKS_IN_LINE; i++) {
		Block* b = Block::createWithArgs(i == black ? Color3B::BLACK : Color3B::WHITE, size, "", 20, Color4B::BLACK);
		addChild(b);
		b->setPosition(i*visibleSize.width / BLOCKS_IN_LINE, lineIndex*visibleSize.height / BLOCKS_IN_LINE);
		b->setLineIndex(lineIndex);
	}
	lineCount--;
}

void HelloWorld::startGame() {
	addStartLine();
	addNormalLine(1);
	addNormalLine(2);
	addNormalLine(3);	
}

void HelloWorld::moveDown() {
	CCLOG("line count %d", lineCount);
	if (lineCount > 0) {
		addNormalLine(4);
	}
	else if(lineCount == 0) {
		addEndLine();
	}
	
	if (!showEnd) {
		auto bs = Block::getBlocks();
		for (auto it = bs->begin(); it != bs->end(); it++) {
			(*it)->moveDown();
		}
	}
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
