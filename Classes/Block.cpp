#include "Block.h"

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
	addChild(lb);
	lb->setPosition(size.width / 2, size.height / 2);

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