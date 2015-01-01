#include "HUDLayer.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
HUDLayer::HUDLayer()
{
	visibleSize = Director::getInstance()->getVisibleSize();  
	
	//moved the score label to the center
	scoreLabel = Label::createWithBMFont("PixelFont.fnt", "Score: 0");
	scoreLabel->setPosition(Vec2(visibleSize.width * 0.50, visibleSize.height * 0.9));
	this->addChild(scoreLabel, 10);
    scoreLabel->setScale(0.5);


	MenuItemImage*pauseItem = MenuItemImage::create("_bookgame_UI__pause.png",
														 "_bookgame_UI__pause.png", this,
														 menu_selector(HUDLayer::pauseGame));
    
	pauseItem->setPosition(Vec2(visibleSize.width - pauseItem->getContentSize().width/2,
								visibleSize.height- pauseItem->getContentSize().height/2));
	
	
	pauseMenu = Menu::create(pauseItem, nullptr);
	pauseMenu->setPosition(Vec2::ZERO);
	this->addChild(pauseMenu);

}

HUDLayer::~HUDLayer(void)
{

}

void HUDLayer::pauseGame(Object* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("pop.wav");
	
	HelloWorld* helloWorld = dynamic_cast<HelloWorld*> (this->getParent());

	if(!helloWorld->gameOver)
	{
		pauseMenu->setTouchEnabled(false);

		MenuItemImage* resumeItem = MenuItemImage::create("_bookgame_UI__resume.png",
														  "_bookgame_UI__resume.png", this,
														  menu_selector(HUDLayer::resumeGame));
    
		resumeItem->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height* 0.5));	
		resumeMenu = Menu::create(resumeItem, NULL);
		resumeMenu->setPosition(Vec2::ZERO);
		this->addChild(resumeMenu);	
		helloWorld->gamePaused();
	}
}

void HUDLayer::resumeGame(Object* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("pop.wav");	
	pauseMenu->setTouchEnabled(true);
	this->removeChild(resumeMenu);
	HelloWorld* helloWorld = (HelloWorld*)this->getParent();
	helloWorld->gameResumed();
}

void HUDLayer::updateScore(int score)
{
	char scoreTxt[100];
	sprintf(scoreTxt, "Score: %d", score);
	scoreLabel->setString(scoreTxt);
}