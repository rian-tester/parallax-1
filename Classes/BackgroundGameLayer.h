//
// Created by fitra on 12/19/2023.
//

#ifndef PROJ_ANDROID_BACKGROUNDGAMELAYER_H
#define PROJ_ANDROID_BACKGROUNDGAMELAYER_H

#include "cocos2d.h"

USING_NS_CC;

class BackgroundGameLayer : public Layer {

public:
    // Destructor
    ~BackgroundGameLayer();

    // Create a layer
    static BackgroundGameLayer* create();

    // Create scene component
    static Scene* scene();

    void setSpeed(int speed);

private:

    virtual bool init(); // initialize the all resources in this layer.

    virtual void update(float dt); // standard Cocos2d layer method

    Sprite* bg1;

    Sprite*  bg2;

    Sprite* ground1;

    Sprite* ground2;

    int speed = 400;
    int bgSpeed = 150;

};


#endif //PROJ_ANDROID_BACKGROUNDGAMELAYER_H
