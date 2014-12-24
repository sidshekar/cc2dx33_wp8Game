#include "OptionsMenuScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

Scene* OptionsMenu::scene()
{
    Scene *scene = CCScene::create();
	OptionsMenu *layer = OptionsMenu::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool OptionsMenu::init()
{
    Size visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    Vec2 origin = CCDirector::sharedDirector()->getVisibleOrigin();

	scrollingBgLayer = new ScrollingBgLayer(3.0);
	this->addChild(scrollingBgLayer);


	LabelBMFont *nameLabel = LabelBMFont::create("Options Menu","PixelFont.fnt");
	nameLabel->setPosition(visibleSize.width/2, visibleSize.height * 0.8);
	this->addChild(nameLabel);
	
	MenuItemImage *presetItem = MenuItemImage::create("_bookgame_UI__resume.png",
														 "_bookgame_UI__resume.png",														  
														  CC_CALLBACK_1(OptionsMenu::reset, this));
	presetItem->setPosition(ccp(visibleSize.width/2 - visibleSize.width * 0.125,  visibleSize.height * 0.5));
	
	
	MenuItemImage *pmainMenuItem = MenuItemImage::create("_bookgame_UI_mainmenu.png",
															"_bookgame_UI_mainmenu.png",															
															CC_CALLBACK_1(OptionsMenu::mainMenu, this));
	pmainMenuItem->setPosition(Vec2(visibleSize.width/2 + visibleSize.width * 0.125, visibleSize.height * 0.5 ));



	//sound onoff items
    soundOnItem = MenuItemImage::create("_bookgame_UI_soundON.png","_bookgame_UI_soundON.png", this,NULL);
    soundOffItem = MenuItemImage::create("_bookgame_UI_soundOFF.png","_bookgame_UI_soundOFF.png", this,NULL);
    
	bool isPaused = CCUserDefault::sharedUserDefault()->getBoolForKey("tinyBazooka_kSoundPausedKey");
    
    MenuItemToggle* soundToggleItem;
    if(isPaused == false){
        soundToggleItem = MenuItemToggle::createWithTarget(this,menu_selector(OptionsMenu::SoundOnOff),
                                                         soundOnItem, soundOffItem,NULL);
	}else{
        soundToggleItem = MenuItemToggle::createWithTarget(this,menu_selector(OptionsMenu::SoundOnOff),
                                                             soundOffItem, soundOnItem,NULL);
	}
    
    soundToggleItem->setPosition(ccp(visibleSize.width* 0.5, visibleSize.height * 0.5 ));




    // create menu, it's an autorelease object
	Menu* pMenu = Menu::create(pmainMenuItem, presetItem,soundToggleItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
    this->addChild(pMenu, 10);

	this->scheduleUpdate();

	return true;

}

void OptionsMenu::update(float dt)
{
	scrollingBgLayer->update();
}


void OptionsMenu:: mainMenu(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");
	
	CCScene *mScene = MainMenu::scene();
    CCDirector::sharedDirector()->replaceScene(mScene);
}


void OptionsMenu::reset(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");
	
	CCUserDefault::sharedUserDefault()->setIntegerForKey("bazookaGameHighScore", 0);
    CCUserDefault::sharedUserDefault()->flush();
}
  
void OptionsMenu::SoundOnOff(CCObject* sender)
{
    CCMenuItemToggle *toggleItem = (CCMenuItemToggle *)sender;
   
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");

    if (toggleItem->selectedItem() == soundOffItem)
    {
        CCUserDefault::sharedUserDefault()->setBoolForKey("tinyBazooka_kSoundPausedKey", true);
        CCUserDefault::sharedUserDefault()->flush();
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        
    }
    else if (toggleItem->selectedItem() == soundOnItem)
    {
        CCUserDefault::sharedUserDefault()->setBoolForKey("tinyBazooka_kSoundPausedKey", false);
        CCUserDefault::sharedUserDefault()->flush();
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }    
}


