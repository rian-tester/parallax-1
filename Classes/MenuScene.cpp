//
// Created by fitra on 12/19/2023.
//

#include "MenuScene.h"
#include "GameScene.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    auto scene = Scene::create();

    auto layer = MenuScene::create();

    scene->addChild(layer);

    return scene;
}

bool MenuScene::init()
{
    if( !Layer::init() )
    {
        return false;
    }

    this->initNodes();
    this->initControllers();

    // Register Android back button to event listener
    auto touchListener = EventListenerKeyboard::create();
    touchListener->onKeyReleased =  [](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
    {
        if(keyCode == EventKeyboard::KeyCode::KEY_BACK)
        {
            // Quit the game
            Director::getInstance()->end();
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    // Audio setup on game playing
    auto  userdefaults = cocos2d::UserDefault::getInstance();
    auto id = userdefaults->getIntegerForKey("audio");
    if (AudioEngine::getState(id) != AudioEngine::AudioState::PLAYING)
    {
        id = AudioEngine::play2d("music/music_ingame.mp3", true, 1.f);
        AudioEngine::resume(id);
    }

    userdefaults->setIntegerForKey("audio", id);

    return true;
}

void MenuScene::initNodes()
{
    Size  visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // Background creation and positioning
    auto bg = Sprite::createWithSpriteFrameName("background.png");
    bg->setContentSize(visibleSize);
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, -1);

    // Foreground creation and positioning
    auto ground = Sprite::createWithSpriteFrameName("ground.png");
    ground->setContentSize(Size(visibleSize.width,  visibleSize.height/4));
    ground->setPosition(Point(visibleSize.width/2 + origin.x, origin.y));
    this->addChild(ground, -1);

    // Logo creation and positioning
    auto logo = Sprite::createWithSpriteFrameName("logo.png");
    logo->setContentSize(Size(visibleSize.width / 2, visibleSize.height / 4));
    logo->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.7 + origin.y));
    this->addChild(logo, -1);


}

void MenuScene::initControllers()
{
    Size screenSize = Director::getInstance()->getWinSize();

    // Play button setup
    playButton = ui::Button::create(
            "startButton.png",
            "startButtonDn.png",
            "startButtonDn.png",
            ui::AbstractCheckButton::TextureResType::PLIST
            );
    playButton->setPosition(Point(screenSize.width * 0.5f,  screenSize.height  * 0.3f));
    playButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch(type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->clickPlayButton(sender);
                break;
            default:
                break;
        }
    });


    this->addChild(playButton, -1);

}

void MenuScene::clickPlayButton(Ref* sender)
{
    // Go to game scene
    Scene* newScene = TransitionMoveInR::create(0.3f, GameScene::createScene());
    Director::getInstance()->replaceScene(newScene);
}

