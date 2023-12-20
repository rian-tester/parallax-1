//
// Created by fitra on 12/19/2023.
//

#include "BackgroundGameLayer.h"
#include "cocos2d.h"

BackgroundGameLayer::~BackgroundGameLayer()
{

}

BackgroundGameLayer* BackgroundGameLayer::create()
{
    BackgroundGameLayer* layer = new BackgroundGameLayer();
    layer->init();
    return layer;
}

bool BackgroundGameLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }

    Size  visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    bg1 = Sprite::createWithSpriteFrameName("background.png");
    bg1->setContentSize(Size(visibleSize.width * 1.5, visibleSize.height));
    bg1->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg1, -1);

    bg2 = Sprite::createWithSpriteFrameName("background.png");
    bg2->setContentSize(Size(visibleSize.width * 1.5, visibleSize.height));
    bg2->setPosition(Point(visibleSize.width * 3/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg2, -2);

    ground1 = Sprite::createWithSpriteFrameName("ground.png");
    ground1->setName("ground1");

    ground2 = Sprite::createWithSpriteFrameName("ground.png");
    ground2->setName("ground2");

    ground1->setContentSize(Size(visibleSize.width * 1.5,  visibleSize.height/4));
    ground1->setPosition(Point(visibleSize.width / 2 + origin.x, origin.y));
    this->addChild(ground1, -1);

    ground2->setContentSize(Size(visibleSize.width * 1.5,  visibleSize.height/4));
    ground2-> setPosition(Point(visibleSize.width * 3/2 + origin.x, origin.y));
    this->addChild(ground2, -1);

    scheduleUpdate();

    return true;
}

void BackgroundGameLayer::update(float dt)
{
    Size  visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // Manual parallax
    // Created by updating the background and ground position every frame with certain speed
    // Background and foreground have different speed
    // Once sprite position pass left screen border it will spawn again behind the other sprite

    if(ground1->getPositionX() <= -visibleSize.width * 0.4)
    {
        ground1->setPositionX(visibleSize.width * 3/2 - origin.x);

    } else
    {
        ground1->setPositionX(ground1->getPositionX() - speed * dt);
    }

    if(ground2->getPositionX() <= -visibleSize.width*0.4 )
    {
        ground2->setPositionX(visibleSize.width*3/2-origin.x);

    }else
    {
        ground2->setPositionX(ground2->getPositionX()-speed*dt);
    }


    if(bg1->getPositionX() <= -visibleSize.width * 0.75)
    {
        bg1->setPositionX(visibleSize.width * 3/2 - origin.x);

    } else
    {
        bg1->setPositionX(bg1->getPositionX() - bgSpeed * dt);
    }

    if(bg2->getPositionX() <= -visibleSize.width * 0.75)
    {
        bg2->setPositionX(visibleSize.width * 3/2 - origin.x);

    } else
    {
        bg2->setPositionX(bg2->getPositionX() - bgSpeed * dt);
    }
}