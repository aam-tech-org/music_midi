#include "MainScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

Scene *MainScene::createScene() {
	return MainScene::create();
}


// on "init" you need to initialize your instance
bool MainScene::init() {
	//////////////////////////////
	// 1. super init first
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label



	// add the label as a child to this layer
//    this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	//auto sprite = Sprite::create("HelloWorld.png");
	/*
	Node* node = Node::create();
	node->setPosition(Point::ZERO);
	this->addChild(node);
	for (int i = 0; i < 100; i++) {
		char name[15];
		memset(name, 0, sizeof(name));
		sprintf(name, "%d.png", i % 10);
		Sprite* sp = Sprite::create("0.png");
		Size size = sp->getContentSize();
		sp->setPosition(Point(size.width / 2, i * size.height * 1.5));
		node->addChild(sp);
	}

	for (int i = 0; i < 100; i++) {
		char name[15];
		memset(name, 0, sizeof(name));
		sprintf(name, "%d.png", i % 10);
		Sprite* sp = Sprite::create("1.png");
		Size size = sp->getContentSize();
		sp->setPosition(Point(20, i * size.height * 1.5));
		node->addChild(sp);
	}

	for (int i = 0; i < 100; i++) {
		char name[15];
		memset(name, 0, sizeof(name));
		sprintf(name, "%d.png", i % 10);
		Sprite* sp = Sprite::create("2.png");
		Size size = sp->getContentSize();
		sp->setPosition(Point(40, i * size.height * 1.5));
		node->addChild(sp);
	}


	for (int i = 0; i < 100; i++) {
		char name[15];
		memset(name, 0, sizeof(name));
		sprintf(name, "%d.png", i % 10);
		Sprite* sp = Sprite::create("3.png");
		Size size = sp->getContentSize();
		sp->setPosition(Point(60, i * size.height * 1.5));
		node->addChild(sp);
	}
*/

	/**/

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("test.plist", "test.pvr.ccz");


	for (int i = 0; i < 100; i++) {
		char name[15];
		memset(name, 0, sizeof(name));
		sprintf(name, "%d.png", i % 10);
		Sprite* sp = Sprite::createWithSpriteFrameName("3.png");
		Size size = sp->getContentSize();
		sp->setPosition(Point(size.width / 2, i * size.height * 1.5));
		this->addChild(sp);
	}

	for (int i = 0; i < 100; i++) {
		char name[15];
		memset(name, 0, sizeof(name));
		sprintf(name, "%d.png", i % 10);
		Sprite* sp = Sprite::createWithSpriteFrameName("2.png");
		Size size = sp->getContentSize();
		sp->setPosition(Point(20, i * size.height * 1.5));
		this->addChild(sp);
	}

	for (int i = 0; i < 100; i++) {
		char name[15];
		memset(name, 0, sizeof(name));
		sprintf(name, "%d.png", i % 10);
		Sprite* sp = Sprite::createWithSpriteFrameName("1.png");
		Size size = sp->getContentSize();
		sp->setPosition(Point(40, i * size.height * 1.5));
		this->addChild(sp);
	}

	for (int i = 0; i < 100; i++) {
		char name[15];
		memset(name, 0, sizeof(name));
		sprintf(name, "%d.png", i % 10);
		Sprite* sp = Sprite::createWithSpriteFrameName("0.png");
		Size size = sp->getContentSize();
		sp->setPosition(Point(60, i * size.height * 1.5));
		this->addChild(sp);
	}

	return true;
}


void HelloWorld::menuCloseCallback(Ref *pSender) {
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
