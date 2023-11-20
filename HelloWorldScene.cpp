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

#include "HelloWorldScene.h"
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

USING_NS_CC;

const int grid_pos_x = 0;
const int grid_pos_y = 0;
const int size_of_caro = 64;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    static bool turn = false;
    static std::vector<std::vector<int>> board_number;
    

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto director = Director::getInstance();

    static auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    for (int i = 0; i < 9; i++) {
        std::vector<int> v;
        for (int j = 0; j < 9; j++) {
            v.push_back(-1);
        }
        board_number.push_back(v);
    }
    ////////////////////////-------------------------Check WINNER
    auto checkWinner = [](int row, int col, int temp) -> void {
        board_number[row][col] = temp;
        //int temp = board_number[row][col];

        //////////////-----------Vertical check
        int right_half = 0;
        int left_half = 0;
        for (int i = 1; i < 5; i++) {
            if (row + i > 8 || board_number[row + i][col] != temp) break;
            else right_half++;
        }
        for (int i = 1; i < 5; i++) {
            if (row - i < 0 || board_number[row - i][col] != temp) break;
            else left_half++;
        }
        //if (right_half + left_half >= 4) Director::getInstance()->end();
        if (right_half + left_half >= 4) label->setString(std::to_string(temp) + "win!");

        ///////////----------------Horizontal check
        right_half = 0;
        left_half = 0;
        for (int i = 1; i < 5; i++) {
            if (col + i > 8 || board_number[row][col + i] != temp) break;
            else right_half++;
        }
        for (int i = 1; i < 5; i++) {
            if (col - i < 0 || board_number[row][col - i] != temp) break;
            else left_half++;
        }
        //label->setString(std::to_string(right_half) + std::to_string(left_half));
        //if (right_half + left_half >= 4) Director::getInstance()->end();
        if (right_half + left_half >= 4) label->setString(std::to_string(temp) + "win!");

        ///////////------------Main cross check
        right_half = 0;
        left_half = 0;
        for (int i = 1; i < 5; i++) {
            if (col + i > 8 || row + i > 8 || board_number[row + i][col + i] != temp) break;
            else right_half++;
        }
        for (int i = 1; i < 5; i++) {
            if (col - i < 0 || row - i < 0 || board_number[row - i][col - i] != temp) break;
            else left_half++;
        }
        //if (right_half + left_half >= 4) Director::getInstance()->end();
        if (right_half + left_half >= 4) label->setString(std::to_string(temp) + "win!");

        ///////////------------Secondary cross check
        right_half = 0;
        left_half = 0;
        for (int i = 1; i < 5; i++) {
            if (col + i > 8 || row - i < 0 || board_number[row - i][col + i] != temp) break;
            else right_half++;
        }
        for (int i = 1; i < 5; i++) {
            if (col - i < 0 || row + i > 8 || board_number[row + i][col - i] != temp) break;
            else left_half++;
        }
        //if (right_half + left_half >= 4) Director::getInstance()->end();
        if (right_half + left_half >= 4) label->setString(std::to_string(temp) + "win!");
    };


    
    
    //////////////////////////// 9X9 BUTTON
    int start_pos_x = origin.x + visibleSize.width / 2 - size_of_caro * 4;
    int start_pos_y = origin.y + visibleSize.height / 2 + size_of_caro * 4;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            auto button = ui::Button::create();
            button->loadTextureNormal("normal.png");
            button->setTitleText("Button Text");
            button->setPosition(Vec2(start_pos_x + size_of_caro * j, start_pos_y));
            button->addTouchEventListener([i, j, checkWinner](Ref* sender, ui::Widget::TouchEventType type) {
                auto temp = dynamic_cast<ui::Button*>(sender);
                switch (type)
                {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:
                    //logic win/lose, turn around, send location
                    if(turn) temp->loadTextureDisabled("x.png");
                    else temp->loadTextureDisabled("o.png");
                    //temp->loadTextureDisabled("o.png");
                    temp->setEnabled(false);
                    //text_label << i << "," << j << ";";
                    temp->setTitleText(std::to_string(i) + ";" + std::to_string(j));
                    temp->setTitleColor(Color3B::BLACK);
                    checkWinner(i, j, (turn ? 1 : 0));
                    
                    turn = !turn;

                    //std::cout << "Button 1 clicked" << std::endl;
                    break;
                default:
                    break;
                }
            });
            this->addChild(button, 1);
        }
        start_pos_y -= size_of_caro;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label


    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
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
    auto grid = Sprite::create("grid.png");
    if(grid == nullptr)
    {
        problemLoading("'grid.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        grid->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(grid, 0);
    }
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
