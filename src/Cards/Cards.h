#include <string>
#include <vector>
using namespace std;

#ifndef CARDS_H
#define CARDS_H

class Map; class Hand; class Deck;
class Cards
{
    public:
        //default constructor
        Cards();  
        //constructor
        Cards(string type); 
        //destruct
        ~Cards(); 
        void setCardType(string type);
        string getCardType();
        //cards copy constructor
        Cards(const Cards &initial);
    private:
        //type of each card
        string *cardType;
};

#endif

#ifndef DECK_H
#define DECK_H

class Deck
{
    public:
        //default constructor
        Deck();  
        //destruct
        ~Deck();
        //random card drawer to players hand from remaining deck cards method
        void draw(Hand *currentHand);
        //deck copy constructor
        Deck(const Deck &initial);  
        //cards pointer vector
        vector<Cards *> deckCards;
        //deck of cards initializer method
        void initializeDeck();
        //deck of cards shuffler method
        void shuffleDeck();
};
#endif

#ifndef HAND_H
#define HAND_H

class Hand
{
public:
    //default constructor
    Hand(); 
    //destruct
    ~Hand();
    //hand copy constructor
    Hand(const Hand &initial);
    //cards pointer vector
    vector<Cards *> handCards;
    void setPlayerID(int playerId);
    int getPlayerID();
private:
    int playerID;
};
#endif
