//
// Created by Jake Power on 2/25/24.
//
#include "player.h"

Player::Player()
{
    score =0;
    name = " ";
}
void Player::setName(string temp)
{
    name = temp;
    //return name;

}
string Player::getName() const
{return name;}
int Player::calculateScore(int val) {
    int temp;
    if (val == 1) {
        temp = 5000;
    } else if (val == 2) {
        temp = 2500;
    } else if (val == 3) {
        temp = 1000;
    } else if (val == 4) {
        temp = 500;
    } else if (val == 5) {
        temp = 250;
    }
    else if( val ==6)
    {
        temp = 100;
    }
    else {
        temp = 0;
    }
    cout << "Your score for the round is " << temp<< endl;
    return temp;
}
void Player::addScore(int val)
{
    score +=val;
}
int Player::getScore() const
{ return score;}