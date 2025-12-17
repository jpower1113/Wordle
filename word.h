//
// Created by Jake Power on 2/23/24.
//
#ifndef WORDLE_WORD_H
#define WORDLE_WORD_H
#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <fstream>
#include<ctime>
#include "player.h"
using namespace std;
class Word {
    friend class Player;
public:
    Word();
    bool openFile(const char*);
    string getDailyWord();
    string setDailyWord();
    string setWord(string );
    string getWord();
    void PlayGame();
    bool Compare();
    void lookForLetter();

private:
    string word;
    vector <string> guessedWords;
    Player *nameList;
    string dailyWord;
    int maxSize,current,sz,index;
    vector <char> guessedLetters;
    vector <char> correctLetters;

    bool getValidWord(string s)
    {
        ifstream file;
        //cin.get();
        //cin.clear();
        string guess;
        if(s.length()!=5)
        {
            return false;
        }
        else {
            if(openFile("sgb-words.txt"))
            {
                file.open("sgb-words.txt");
                for (size_t i = 0; i <5770; i++)
                {
                    getline(file, guess);
                    if(guess == s)
                    {
                        return true;
                    }
                }

            }
        }
        return false;
    }
    void Randomize()
// COMPILER-SPECIFIC: sets the random number generator's seed.
    {
        unsigned int seed = unsigned(clock());
        srand(seed);

    }
    string toLower(string s)
    {
        for(int i=0;i<s.length();i++)
        {
            s[i] = tolower(s[i]);
        }
        return s;
    }
    void DisplayRules()
    {
        cout<<"How To Play\n"
              "Guess the word in 6 tries.\n"
              "Each guess must be a valid 5-letter word.\n"
              "The color of the letters will change to show how close your guess is to the word.\n"
              "If a letter is in green it means it is found in the word and is in the right spot.\n"
              "If a letter is in yellow it means it is found in the word but is in the wrong spot (letters that are yellow may occur multiple times in the word and might refer to a 'green' letter.\n"
              "No change in color means a letter is not in the word in any spot.\n"
              "1 guess  = 5000 points, 2 guesses = 2500 points, 3 guesses = 1000 points, 4 guesses = 500 points, 5 guesses = 250 points, and 6 guesses = 100 points\n";

    }
    void Grow()
    {
        ++maxSize;
        ++current;
        Player *newList = new Player[maxSize];
        if (nameList) { // Only copy if nameList is not nullptr
            for (int i = 0; i < maxSize - 1; i++) {
                newList[i] = nameList[i];
            }
            delete[] nameList;
        }
        nameList = newList;
    }
    bool changeUsername(int count)
    {
        string name;
        string temp;
        if(count ==0)
        {
            maxSize++;
            cout<<"\nPlease enter a new username: ";
            cin>>name;
            nameList[current].setName(name);

        }
        else if(count != 0)
        {
            cout << "Would you like to change your username(y/n)?: ";
            if (KeepPlaying() == 'n')
            {
                getDailyWord();
                return true;
            }
            cout << "\nPlease enter a new username: ";
            cin>>temp;
            if (newName(temp))
            {
                current = maxSize - 1;
                Grow();

            }
            name = temp;
            nameList[current].setName(name);
            getNewDaily();
        }
        return true;
    }
    bool newName(string name)
    {
        for(int i = 0;i<=maxSize;i++)
        {
            if(nameList[i].name==name)
            {
                current = i;
                cout<<"Welcome back "<<nameList[i].getName()<<", as a reminder your score is "<<nameList[i].getScore()<<endl;
                nameList[current].score = nameList[i].score;
                return false;
            }
        }
            return true;
    }
    bool getNewDaily()
    {
        cout<<"Would you like to use the same word as the last player?";
        if (KeepPlaying() == 'y')
        {
            return true;
        }
        getDailyWord();
        return false;

    }
    bool exportScore()
    {
        fstream file;
        file.open("HighScoresSheet.txt",fstream::out | fstream::trunc);
        if(!file)
        {
            return false;
        }
        for(int i=0;i<maxSize;i++)
        {
            file<<setw(15)<<fixed<<left<<nameList[i].getName()<<"\t\t"<<setw(15)<<fixed<<right<<nameList[i].getScore()<<endl;
        }
        file.close();
        return true;

    }
    char KeepPlaying()
    {
        char ans;
        cin >>ans;
        while(ans !='y' && ans != 'n')
        {
            cout<<"Please enter a valid ans(y/n): ";
            cin>>ans;
        }
        return tolower(ans);

    }
};

#endif //WORDLE_WORD_H
