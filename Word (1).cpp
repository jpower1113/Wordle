//
// Created by Jake Power on 2/23/24.
//
#include "Word.h"
#include <ctime>
#include <cstdlib>		// for rand(), srand()
#include <string>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
using namespace std;
Word::Word( ) {
    word = " ";
    dailyWord = " ";
    index= sz= maxSize =current = 0;
    nameList = new Player[1];
}
bool Word::openFile(const char * name)
{
    ifstream file;
    file.open(name);
    if(!file)
    {
        return false;
    }
    else
        return true;
}
string Word::setDailyWord()
{
    Randomize();
    string daily;
    while(openFile("Five-LetterWords.txt"))
    {
        
        ifstream file("Five-LetterWords.txt");
        int r = rand() % 2314;
        for(size_t i = 0;i<r;i++)
        {
            getline(file,daily);
        }
        file.close();
        
        return daily;
    }
    cout<<"try again"<<endl;
    return " ";

}
string Word::getDailyWord()
{
   dailyWord= setDailyWord();
   return dailyWord;
}
string Word::setWord(string s)
{
    while(!getValidWord(s))
    {
        cout<<"Please enter a valid 5 letter word\n";
        cin>>s;
    }
    word = s;
    return word;
}
string Word::getWord()
{
    return word;
}
bool Word::Compare()
{
    if(word==dailyWord)
    {
        return true;
    }
    return false;
}
void Word::PlayGame()
{

    Player p;
    string s,temp,name;
    int index = 0;
    cout<<"Welcome to my Wordle game!\n";
    char ANS;
    getDailyWord();
    do {
        word = " ";
        int count =0;
        if(index != 0)
        {
            for(int i =0;i<50;i++)
            {
                cout<<endl;
            }
        }
        changeUsername(index);
        while (count != 6 && !Compare()) {
            count++;
            cin.clear();
            cout << "\nPlease enter guess #" << count << ", press 1 to display the rules, press 2 to display your total score, press 3 to display ALL letters guessed, or press 4 to display guessed letters that are found in the Wordle   \n";
            cin >> s;
            temp = toLower(s);
            while (temp == "1")
            {
                DisplayRules();
                if (count > 1) {
                    cout << "\nYour guess for guess #" << count - 1 << " is: ";
                    lookForLetter();
                }
                cout << "\nPlease enter guess #" << count << endl;
                cin >> s;
                temp = toLower(s);
            }
            while (temp == "2")
            {
                cout<<"Your total score is "<<nameList[current].score<<endl;
                if (count > 1) {
                    cout << "\nYour guess for guess #" << count - 1 << " is: ";
                    lookForLetter();
                }
                cout << "\nPlease enter guess #" << count << endl;
                cin >> s;
                temp = toLower(s);
            }
            while (temp == "3")
            {
                cout<<"The letters you have guessed so far are: ";
                for(int i=0;i<sz;i++)
                {
                    
                    cout<<guessedLetters[i]<<", ";
                }
                cout<<endl;
                cout << "\nPlease enter guess #" << count << endl;
                cin >> s;
                temp = toLower(s);
            }
            while (temp == "4")
            {
                cout<<"The letters you have guessed so far that are found in the Wordle: ";
                for(int i=0;i<correctLetters.size();i++)
                {
                    cout<<correctLetters[i]<<", ";
                }
                cout<<endl;
                cout << "\nPlease enter guess #" << count << endl;
                cin >> s;
                temp = toLower(s);
            }
            setWord(temp);
            lookForLetter();

        }
        if (Compare()) {
            cout << "\nYou got it! ";
        } else {
            cout << "\nUnfortunately, that is all of your guesses. \n";
            cout << "The word is " << dailyWord << endl;
            count = 7;
        }

        nameList[current].score += nameList[current].calculateScore(count);
        cout<<"\nWould you like to play again(y/n)? ";
        ANS = KeepPlaying();
        index++;
    }while( ANS !='n');
    cout<<"\nThanks for playing ";
    exportScore();
    cout<<"Check the HighScoresSheet.txt to view your scores!"<<endl;
}
void Word::lookForLetter() {
    bool found[5];
    bool correct[5];
    for (int i = 0; i < word.length(); ++i)
    {
        found[i] = false;
        correct[i] = false;
        if (word[i] == dailyWord[i]) {
            correct[i] = true;
            found[i] = true;
        }
    }
    // Second pass: check for correct letters in wrong positions
    bool wordMatch[5];
    for (int i = 0; i < word.length(); ++i) { //correct = t,f,f,f,f ;found = t,f,f,f ,t ;wordMatch = f,f,t,f,f
        wordMatch[i] = false;
        if (!correct[i]) {
            for (int j = 0; j < dailyWord.length(); ++j) {

                if (!found[j] && word[i] == dailyWord[j]) {
                    found[j] = true;
                    wordMatch[i] = true;
                    break;
                }
            }
        }
    }
    for (int i = 0; i <word.length() ; i++) {
        if(correct[i])
        {
            cout << GREEN << word[i] << RESET;
        }
        else if(wordMatch[i])
        {
            cout << YELLOW << word[i] << RESET;

        }
        else
        {
            cout<<word[i];
        }

    }
    //I need to iterate through the word, put all unique letters into a vector 
    for(int i =0;i<5;i++)
    {
        if (find(guessedLetters.begin(), guessedLetters.end(), word[i]) == guessedLetters.end()) 
        {
            sz++;
            guessedLetters.push_back(word[i]);
        }
    }
    for(int i =0;i<5;i++)
    {
        if(correct[i] || wordMatch[i])
        {
            if (find(correctLetters.begin(), correctLetters.end(), word[i]) == correctLetters.end()) {
                correctLetters.push_back(word[i]);
            }
        }
    }
    
    cout<<endl;
}