//
// Created by fitra on 12/19/2023.
//

#ifndef PROJ_ANDROID_MENUSCENE_H
#define PROJ_ANDROID_MENUSCENE_H

#include  "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class MenuScene : public Layer {

public:
    CREATE_FUNC(MenuScene);

    static Scene* createScene();

    virtual bool init();

private:

    void initNodes(); // initialize the sprites in our game.

    void initControllers();

    ui::Button* playButton;


    void clickPlayButton(Ref* sender);

};


#endif //PROJ_ANDROID_MENUSCENE_H
