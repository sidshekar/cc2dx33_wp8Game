#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "OptionsMenuScene.h"
#include <spine/spine-cocos2dx.h>
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Scene* MainMenu::scene(){
    auto scene = Scene::create();
	auto layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init(){
    
	//check if background music needs to be played
	bool isPaused = UserDefault::getInstance()->getBoolForKey("tinyBazooka_kSoundPausedKey");
	
	if(isPaused == true)	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}else{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();	
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	scrollingBgLayer = new ScrollingBgLayer(3.0);
	this->addChild(scrollingBgLayer);
	auto nameLabel = Label::createWithBMFont("PixelFont.fnt", "Ms.tinyBazooka");
	nameLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height * 0.8));
	this->addChild(nameLabel);

	//actions
	
	MoveBy* moveUp =MoveBy::create( 1, Vec2(0, 20));
    EaseSineInOut *easeUp = EaseSineInOut::create(moveUp);	
	auto easeDown = easeUp->reverse();
	auto sequence = dynamic_cast<ActionInterval*>(Sequence::create(easeUp,easeDown, nullptr));
	nameLabel->runAction(RepeatForever::create(sequence));	

	//spine instead of extension namespace
	auto skeletonNode = spine::SkeletonAnimation::createWithFile("player.json", "player.atlas", 1.0f); //Or can use spine::SkeletonAnimation* skelettonNode instead of auto
	//order of parameters is changed
	skeletonNode->addAnimation(0,"runCycle",true,0);
	skeletonNode->setPosition(Vec2(visibleSize.width * .125 , visibleSize.height * 0.2 - skeletonNode->getContentSize().height/2));
	addChild(skeletonNode);
	
	auto pPlayItem = MenuItemImage::create("_bookgame_UI_play.png",
														 "_bookgame_UI_play.png",														  
														  CC_CALLBACK_1(MainMenu::playGame, this)); //callback instead of schedule_selector. Also delegate is inside callback
	pPlayItem->setPosition(Vec2(visibleSize.width/2,  visibleSize.height * 0.5));
	
	
	auto pOptionsItem = MenuItemImage::create("_bookgame_UI_options.png",
															"_bookgame_UI_options.png",															
															CC_CALLBACK_1(MainMenu::optionsScene, this));
	pOptionsItem->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.5 ));


    // create menu, it's an autorelease object
	auto pMenu = Menu::create(pOptionsItem,pPlayItem, nullptr);
	pMenu->setPosition(Vec2(0,0));// Or use Vec2::Zero
    this->addChild(pMenu, 10);	
	
	auto newHighScoreLabel = Label::createWithBMFont("PixelFont.fnt", "CURRENT HIGH SCORE");
    newHighScoreLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.15));
    this->addChild(newHighScoreLabel, 10);
    newHighScoreLabel->setScale(0.5);        

	auto highScoreLabel = Label::createWithBMFont("PixelFont.fnt", "0");
    highScoreLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.1));
    this->addChild(highScoreLabel, 10);
    highScoreLabel->setScale(0.5);     
	
	int highScore = UserDefault::getInstance()->getIntegerForKey("bazookaGameHighScore");
    char scoreTxt[100];
    sprintf(scoreTxt, "%d", highScore);
    highScoreLabel->setString(scoreTxt);
	this->scheduleUpdate();
	return true;
}


void MainMenu::update(float dt)
{
	scrollingBgLayer->update();
}


void MainMenu:: playGame(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("pop.wav");	
	Scene *mScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(mScene);
}


void MainMenu::optionsScene(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("pop.wav");	
	Scene *mScene = OptionsMenu::scene();
    Director::getInstance()->replaceScene(mScene);
}

  
