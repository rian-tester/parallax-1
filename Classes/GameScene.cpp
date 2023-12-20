//
// Created by fitra on 12/19/2023.
//

#include "GameScene.h"
#include "MenuScene.h"
#include "BackgroundGameLayer.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
    // scene is an auto release object
    auto scene = Scene::create();

    // layer is an auto release object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GameScene::init()
{
    if( !Layer::init() )
    {
        return false;
    }

    this->initNodes();

    // Register Android back button to event listener
    auto touchListener = EventListenerKeyboard::create();
    touchListener->onKeyReleased =  [](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
    {
        if(keyCode == EventKeyboard::KeyCode::KEY_BACK)
        {
            // Go back to main menu
            Scene* newScene = TransitionMoveInR::create(0.3f, MenuScene::createScene());
            Director::getInstance()->replaceScene(newScene);
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    // Register touch for jump
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    scheduleUpdate();

    return true;
}

void GameScene::initNodes()
{

    Size  visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    this->addChild(this->setupBackgroundLayer(), -1);

    // Setup hero sprite
    heroRun = getRunAnimation();
    playerSprite = Sprite::create();
    playerSprite->setContentSize(visibleSize * 10);
    playerSprite->setPosition(Point(visibleSize.width * 0.2f, visibleSize.height * 0.215f));
    playerSprite->runAction(heroRun);

    // Setup rock sprite (obstacle)
    obstacleSprite = Sprite::createWithSpriteFrameName("obstacle.png");
    obstacleSprite->setContentSize(obstacleSprite->getContentSize() * 4);
    obstacleSprite->setPosition(Point(visibleSize.width, visibleSize.height * 0.18f));

    this->addChild(playerSprite, -1);
    this->addChild(obstacleSprite, -1);
}

BackgroundGameLayer* GameScene::setupBackgroundLayer()
{
    this->backgroundGameLayer = BackgroundGameLayer::create();
    return this->backgroundGameLayer;
}

Action*  GameScene::getRunAnimation()
{
    // Looping from spritesheet for running animation sprites
    auto heroRunAnimation = Animation::create();
    for(int index = 1; index< 7; index++)
    {
        char name[100] = {0};
        sprintf(name, "boyrun_0%i.png",  index);
        auto heroSpriteFrameRun = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        heroRunAnimation->addSpriteFrame(heroSpriteFrameRun);
    }

    // Animation init
    heroRunAnimation->setDelayPerUnit(0.3f / 3.0f);
    heroRunAnimation->setRestoreOriginalFrame(true);
    auto heroAnimate = Animate::create(heroRunAnimation);
    heroRun = RepeatForever::create(heroAnimate);

    return heroRun;
}

Action* GameScene::getJumpAnimation()
{
    // Looping from spritesheet for Jumping animation sprites
    auto heroJumpAnimation = Animation::create();
    for(int index = 1; index < 4; index++)
    {
        char name[100] = {0};
        sprintf(name, "jump_0%i.png", index);
        auto heroSpriteFrameJump = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        heroJumpAnimation->addSpriteFrame(heroSpriteFrameJump);
    }

    // Animation init
    heroJumpAnimation->setDelayPerUnit(0.8f / 3.0f);
    heroJumpAnimation->setRestoreOriginalFrame(true);
    auto heroAnimate = Animate::create(heroJumpAnimation);
    heroJump = RepeatForever::create(heroAnimate);

    return heroJump;
}

void GameScene::setScrollSpeed(int speed)
{

}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    // Callback once Jumping action started
    auto calb = CallFunc::create([this](){
        playerSprite->stopAllActions();
        playerSprite->runAction(getRunAnimation());
        jumping = false;
    });


    // Protection from double jump
    if(!jumping)
    {
        playerSprite->stopAllActions();
        playerSprite->runAction(getJumpAnimation());
        jumping= true;
        auto action = JumpBy::create(1, Point(0, 0), 250, 1);
        auto seq = Sequence::create(action, calb, nullptr);
        playerSprite->runAction(seq);
    }

    return true;

}

void GameScene::update(float dt)
{
    Size  visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // Updating obstacle position
    if(obstacleSprite->getPositionX() <= 0)
    {
        obstacleSprite->setPositionX(visibleSize.width + obstacleSprite->getContentSize().width);
    } else
    {
        obstacleSprite->setPositionX(obstacleSprite->getPositionX() - 400* dt);
    }
}
