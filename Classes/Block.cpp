#include "Block.h"
#include "HelloWorldScene.h"

Vector<Block*>* Block::blocks = new Vector<Block*>();

Block* Block::createWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor) {
	Block* b = new Block();
	b->initWithArgs(color, size, label, fontSize, textColor);
	b->autorelease();

	blocks->pushBack(b);
	return b;
}

bool Block::initWithArgs(Color3B color, Size size, std::string label, float fontSize, Color4B textColor) {
	Sprite::init();
	setContentSize(size);
	setAnchorPoint(Vec2::ZERO);
	setColor(color);
	setTextureRect(Rect(0, 0, size.width, size.height));

	Label* lb = Label::create();
	lb->setString(label);
	lb->setSystemFontSize(fontSize);
	lb->setTextColor(textColor);
	lb->setAnchorPoint(Vec2(0.5, 0.5));
	lb->setPosition(size.width / 2, size.height / 2);
	addChild(lb);

	lineIndex = 0;

	return true;
}

void Block::removeBlock() {
	removeFromParent();
	blocks->eraseObject(this);
}

int Block::getLineIndex() {
	return lineIndex;
}

void Block::setLineIndex(int line) {
	lineIndex = line;
}

Vector<Block*>* Block::getBlocks() {
	return Block::blocks;
}

void Block::moveDown() {
	lineIndex--;
	auto size = Director::getInstance()->getVisibleSize();
	runAction(Sequence::create(MoveBy::create(0.25f, Vec2(0, -size.height/HelloWorld::BLOCKS_IN_LINE)), CallFunc::create([this]() {
		if (lineIndex < 0) {
			removeBlock();
		}
	}), NULL));

}