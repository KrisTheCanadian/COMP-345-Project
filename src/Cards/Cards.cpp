#include "Cards.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
    
    //->Cards constructors
    
    //Default constructor
    Cards::Cards()
    {
        cardType = new string("");
    }
    
    //Card constructor with a type parameter
    Cards::Cards(string type) {
        *cardType = type;
    }
    
    //Copy constructor
    Cards::Cards(const Cards &initial)
    {
        cardType = new string(*initial.cardType);
    }
    
    void Cards::setCardType(string type)
    {
        *cardType = type;
    }
    
    string Cards::getCardType()
    {
        return *cardType;
    }
    
    //Destructor
    Cards::~Cards()
    {
        delete cardType;
    }
    
    //->Deck constructors
    //Default constructor
    Deck::Deck()
    {
    }
    
    //Destructor
    Deck::~Deck()
    {
        for (auto card : deckCards)  {
            delete card;
        }
        deckCards.clear();
    }
    
    //copy constructor
    Deck::Deck(const Deck &initial)
    {
        for (auto &&temp : initial.deckCards) {
            deckCards.push_back(new Cards(*temp));
        }
    }
    
    //draw card from the deck of cards
    void Deck::draw(Hand *currentHand)
    {
        if (deckCards.empty())
        {
            cout << "The deck is currenttly empty." << endl;
        }
        else
        {
            //add last deck card to user's hand
            currentHand->handCards.push_back(deckCards.back());
            //removes card from the deck of cards after it has been drawn for hand
            deckCards.pop_back();                               
        }
    }
    
    //initialize the deck of cards
    void Deck::initializeDeck()
    {
        vector<string> cardTypes = {"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"};
        
        for (int i = 0; i < cardTypes.size(); i++)
        {
            Cards *card = new Cards();
            card->setCardType(cardTypes[i]);
            for (int j = 0; j < 6; j++) {
                deckCards.push_back(card);
            }
        }
        //shuffle the cards
        shuffleDeck();
    }
    
    //method shuffling the deck of cards
    void Deck::shuffleDeck()
    {
        mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
        shuffle(std::begin(deckCards), std::end(deckCards), rng);
    };
    
    //->player hand constructors
    
    //Default constructor
    Hand::Hand(){
    };
    
    //Copy construct
    Hand::Hand(const Hand &initial)
    {
        for (auto &&temp : initial.handCards) {
            handCards.push_back(new Cards(*temp));
        }
    };
    
    
    //Destruct
    Hand::~Hand()
    {
        for (auto card : handCards) {
            delete card;
        }
        handCards.clear();
    }
    
    void Hand::setPlayerID(int playerId) {
        playerID = playerId;
    }
    
    int Hand::getPlayerID() {
        return playerID;
    }
