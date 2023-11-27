/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Start.h"
#include "MT.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include "Node.h"

USING_NS_CC;


Scene* Start::createScene()
{
    return Start::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Start::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto director = Director::getInstance();

    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    
    auto closeItem = MenuItemImage::create(
                                           "item.png",
                                           "item.png",
                                           CC_CALLBACK_1(Start::callNormal, this));
    
    auto monte = MenuItemImage::create("item.png", "item.png", CC_CALLBACK_1(Start::callMonte, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + closeItem->getContentSize().height/2 + 250;
        closeItem->setPosition(Vec2(x,y));
    }

    if (monte == nullptr ||
        monte->getContentSize().width <= 0 ||
        monte->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + monte->getContentSize().height / 2 + 450;
        monte->setPosition(Vec2(x, y));
    }
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, monte, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label_14 = Label::createWithTTF("MT", "fonts/Marker Felt.ttf", 24);
    if (label_14 == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label_1 on the center of the screen
        label_14->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label_14->getContentSize().height - 250));

        // add the label_1 as a child to this layer
        this->addChild(label_14, 1);
    }

    auto label_12 = Label::createWithTTF("Normal", "fonts/Marker Felt.ttf", 24);
    if (label_12 == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label_1 on the center of the screen
        label_12->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label_12->getContentSize().height - 450));

        // add the label_1 as a child to this layer
        this->addChild(label_12, 1);
    }
    auto label_13 = Label::createWithTTF("Caro 9x9", "fonts/Marker Felt.ttf", 24);
    if (label_13 == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label_1 on the center of the screen
        label_13->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label_13->getContentSize().height));

        // add the label_1 as a child to this layer
        this->addChild(label_13, 1);
    }
    /*
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label


    // add "Start" splash screen"
    auto sprite = Sprite::create("Start.png");
    if (sprite == nullptr)
    {
        problemLoading("'Start.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
    */
    ////////////// BOARD
    
    
    return true;
}


void Start::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void Start::callMonte(Ref* pSender) {
    auto mont = MT::createScene();
    Director::getInstance()->replaceScene(mont);
}

void Start::callNormal(Ref* pSender) {
    auto norm = HelloWorld::createScene();
    Director::getInstance()->replaceScene(norm);
}
