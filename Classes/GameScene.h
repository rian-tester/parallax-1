//
// Created by fitra on 12/19/2023.
//

#ifndef PROJ_ANDROID_GAMESCENE_H
#define PROJ_ANDROID_GAMESCENE_H

#include "cocos2d.h"
#include "BackgroundGameLayer.h"

USING_NS_CC;

class GameScene : public Layer {

public:
    CREATE_FUNC(GameScene);

    static Scene* createScene();

    virtual bool init();

private:

    void initNodes(); // initialize the sprites in our game.

    virtual void update(float dt); // standard Cocos2d layer method

    virtual bool onTouchBegan(Touch* touch, Event* event);

    BackgroundGameLayer* backgroundGameLayer;

    BackgroundGameLayer* setupBackgroundLayer();

    void setScrollSpeed(int speed);

    Sprite* playerSprite;
    Sprite* obstacleSprite;

    Action* heroRun;
    Action* heroJump;

    Action* getRunAnimation();
    Action* getJumpAnimation();

    bool jumping;



};


#endif //PROJ_ANDROID_GAMESCENE_H
