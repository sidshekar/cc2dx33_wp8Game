#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "OptionsMenuScene.h"
#include <spine/spine-cocos2dx.h>
#include "SimpleAudioEngine.h"

CCScene* MainMenu::scene(){
    auto scene = CCScene::create();
	auto layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init(){
    
	//check if background music needs to be played
	bool isPaused = CCUserDefault::sharedUserDefault()->getBoolForKey("tinyBazooka_kSoundPausedKey");
	
	if(isPaused == true)	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}else{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();	
	}
	
	Size visibleSize = CCDirector::getInstance()->getVisibleSize();
    Vec2 origin = CCDirector::getInstance()->getVisibleOrigin();


	CCLOG("Hello CCLOG");

	scrollingBgLayer = new ScrollingBgLayer(3.0);
	this->addChild(scrollingBgLayer);

	auto nameLabel = LabelBMFont::create("Ms.tinyBazooka","PixelFont.fnt");
	nameLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height * 0.8));
	this->addChild(nameLabel);


	//actions

	
	MoveBy* moveUp =MoveBy::create( 1, Vec2(0, 20));
    EaseSineInOut *easeUp = EaseSineInOut::create(moveUp);	
	auto easeDown = easeUp->reverse();
	auto sequence = (ActionInterval*)Sequence::create(easeUp,easeDown, NULL);
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
	auto pMenu = Menu::create(pOptionsItem,pPlayItem, NULL);
	pMenu->setPosition(Vec2(0,0));// Or use Vec2::Zero
    this->addChild(pMenu, 10);	
	
	auto newHighScoreLabel = LabelBMFont::create("CURRENT HIGH SCORE", "PixelFont.fnt");
    newHighScoreLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.15));
    this->addChild(newHighScoreLabel, 10);
    newHighScoreLabel->setScale(0.5);        

	auto highScoreLabel = LabelBMFont::create("0", "PixelFont.fnt");
    highScoreLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.1));
    this->addChild(highScoreLabel, 10);
    highScoreLabel->setScale(0.5);     
	
	int highScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("bazookaGameHighScore");
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
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");
	
	CCScene *mScene = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(mScene);
}


void MainMenu::optionsScene(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");
	
	Scene *mScene = OptionsMenu::scene();
    CCDirector::sharedDirector()->replaceScene(mScene);
}

  
