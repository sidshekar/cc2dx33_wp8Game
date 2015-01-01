#include "OptionsMenuScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

Scene* OptionsMenu::scene()
{
    Scene *scene = Scene::create();
	OptionsMenu *layer = OptionsMenu::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool OptionsMenu::init()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	scrollingBgLayer = new ScrollingBgLayer(3.0);
	this->addChild(scrollingBgLayer);


	auto nameLabel = Label::createWithBMFont("PixelFont.fnt", "Options Menu");
	nameLabel->setPosition(visibleSize.width/2, visibleSize.height * 0.8);
	this->addChild(nameLabel);
	
	MenuItemImage *presetItem = MenuItemImage::create("_bookgame_UI__resume.png",
														 "_bookgame_UI__resume.png",														  
														  CC_CALLBACK_1(OptionsMenu::reset, this));
	presetItem->setPosition(Vec2(visibleSize.width/2 - visibleSize.width * 0.125,  visibleSize.height * 0.5));
	
	
	MenuItemImage *pmainMenuItem = MenuItemImage::create("_bookgame_UI_mainmenu.png",
															"_bookgame_UI_mainmenu.png",															
															CC_CALLBACK_1(OptionsMenu::mainMenu, this));
	pmainMenuItem->setPosition(Vec2(visibleSize.width/2 + visibleSize.width * 0.125, visibleSize.height * 0.5 ));

	//sound onoff items
    soundOnItem = MenuItemImage::create("_bookgame_UI_soundON.png","_bookgame_UI_soundON.png", this,NULL);
    soundOffItem = MenuItemImage::create("_bookgame_UI_soundOFF.png","_bookgame_UI_soundOFF.png", this,NULL);
    
	bool isPaused = UserDefault::getInstance()->getBoolForKey("tinyBazooka_kSoundPausedKey");
    
    MenuItemToggle* soundToggleItem;
    if(isPaused == false){
        soundToggleItem = MenuItemToggle::createWithTarget(this,menu_selector(OptionsMenu::SoundOnOff),
                                                         soundOnItem, soundOffItem,NULL);
	}else{
        soundToggleItem = MenuItemToggle::createWithTarget(this,menu_selector(OptionsMenu::SoundOnOff),
                                                             soundOffItem, soundOnItem,NULL);
	}
    
    soundToggleItem->setPosition(Vec2(visibleSize.width* 0.5, visibleSize.height * 0.5 ));

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


void OptionsMenu:: mainMenu(Object* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("pop.wav");	
	Scene *mScene = MainMenu::scene();
    Director::getInstance()->replaceScene(mScene);
}


void OptionsMenu::reset(Object* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("pop.wav");	
	UserDefault::getInstance()->setIntegerForKey("bazookaGameHighScore", 0);
    UserDefault::getInstance()->flush();
}
  
void OptionsMenu::SoundOnOff(Object* sender)
{
    MenuItemToggle *toggleItem = dynamic_cast<MenuItemToggle *>(sender);   
	SimpleAudioEngine::getInstance()->playEffect("pop.wav");

    if (toggleItem->selectedItem() == soundOffItem)
    {
        UserDefault::getInstance()->setBoolForKey("tinyBazooka_kSoundPausedKey", true);
        UserDefault::getInstance()->flush();        
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();        
    }
    else if (toggleItem->selectedItem() == soundOnItem)
    {
        UserDefault::getInstance()->setBoolForKey("tinyBazooka_kSoundPausedKey", false);
        UserDefault::getInstance()->flush();        
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }    
}


