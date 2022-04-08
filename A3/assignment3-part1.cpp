#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm> 
using namespace std;

// Classes: Card, Hand, Deck, AbstractPlayer, HumanPlayer, ComputerPlayer, BlackJackGame

// Card does not need a destructor but Hand will (to get rid of the cards).

static int casino_wins = 0;
static int player_wins = 0;

enum Type { CLUBS = 'C', DIAMONDS = 'D', HEARTS = 'H', SPADES = 'S' }; // PDF says to call it a type but I would call it a suit.
enum Rank { ACE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, JACK = 'J', QUEEN = 'Q', KING = 'K' };

class Card
{
    
    Type type;
    Rank rank;

    public:

        Card(Type pType, Rank pRank)
        {
            type = pType;
            rank = pRank;
        }

        int getValue()
        {
            if ( rank=='J' || rank=='Q' || rank=='K' ) return 10;
            else return rank;
        }

        void displayCard()
        {
            if ( rank=='J' || rank=='Q' || rank=='K' ) {char r = rank; cout << r;}
            else cout << rank;
                    
            char t = type;
            cout << t;
            cout << " ";
        }
    
};

class Hand
{
    public:

        vector<Card> vec;

        void add(Card pCard) 
        {
            vec.push_back(pCard);
        }
        void clear()
        {
            vec.clear();
        }
        int getTotal()
        {
            int toReturn = 0;
            int aces = 0;

            // Count all of the aces in the hand and count the total of non-aces.
            for (int index=0;index<vec.size();index++)
            {
                if (vec[index].getValue() == 1) aces += 1;
                else toReturn += vec[index].getValue();
            }

            // If there's no aces just return total of the cards.
            if (aces == 0) return toReturn;
            // If theres at least one ace, check if one of them can be eleven without going over.
            // If there's more than one ace, only one can possibly be eleven cus 11 + 11 > 21.
            else if (11 + (aces-1) + toReturn <= 21) return 11 + (aces-1) + toReturn;
            // Else return as if they're all worth 1.
            else return aces + toReturn ;
        }

        void displayAllCards()
        {
            for (int i=0;i<vec.size();i++) vec[i].displayCard();
        }


};

class Deck: public Hand
{

    // Populates the deck with a given type.
    void populateType(Type pType)
    {
        Rank r;

        for (int i=1;i<11;i++)
        {
            r = static_cast<Rank>(i); // ACE through TEN
            vec.push_back(Card(pType,r));
        }
        r = static_cast<Rank>(74); // Jack
        vec.push_back(Card(pType,r));

        r = static_cast<Rank>(81); // Queen
        vec.push_back(Card(pType,r));

        r = static_cast<Rank>(75); // King
        vec.push_back(Card(pType,r));
    }

    public:

        Deck()
        {
            populate();
        }

        void populate()
        {
            clear();

            Type t; // 67, 68, 72, 83 
            
            t = static_cast<Type>(67);
            populateType(t);

            t = static_cast<Type>(68);
            populateType(t);

            t = static_cast<Type>(72);
            populateType(t);

            t = static_cast<Type>(83);
            populateType(t);

            vec.shrink_to_fit();
        }

        void shuffle()
        {
            unsigned seed = std::chrono::system_clock::now()
                        .time_since_epoch()
                        .count();

            auto rng = std::default_random_engine(seed);

            
            //int randomNumber = rand();

            std::shuffle(std::begin(vec), std::end(vec), rng);
        }

        Card deal()
        {
            Card toReturn = vec[vec.size() - 1];
            vec.pop_back();
            return toReturn;
        }

        Card idealCard(int cpuScore, int playerScore)
        {
            for (int i=0;i<vec.size();i++)
            {
                if ( (vec[i].getValue() + cpuScore == 21) || (vec[i].getValue() + cpuScore < 21 && vec[i].getValue() > playerScore) ) 
                {
                    // take idealCard
                    // take card in the back of the deck
                    // put card in the back of the deck where idealCard was
                    // pop back of the deck out for good
                    // return idealCard

                    Card idealCard = vec[i];
                    Card backOfDeck = vec[vec.size()-1];

                    vec[i] = backOfDeck;
                    vec.pop_back();

                    return idealCard;
                }
            }

            // If we get here just pop the back of the vector as usual.
            // It means there was no single ideal card found.
            return deal();
        }

};

class AbstractPlayer: public Hand
{
    public:

        virtual bool isDrawing(Hand pPlayer) const = 0;

        bool isBusted()
        {
            if (getTotal() > 21) return true;
            else return false;
        }
};

class HumanPlayer: public AbstractPlayer
{
    public:

        virtual bool isDrawing(Hand pPlayer) const
        {
            //Card c = vec[1];

            // First case for when player busts and is forced to stop or when you get exactly 21 and are forced to stop.
            if (pPlayer.getTotal() >= 21) return false;

            char answer;

            cout << "Would you like to draw (y/n): " << endl;
            cin >> answer;

            if (answer == 'y') return true;
            else if (answer =='n') return false;
            else {cout << "This is an invalid choice, try again." << endl; return isDrawing(pPlayer);}
        }

        void announce(int competitorScore)
        {
            if (getTotal() > 21 && competitorScore > 21) {cout << "Push." << endl;}
            else if (getTotal() > 21 && competitorScore <= 21) { casino_wins++ ;cout << "Player busts. \nCasino Wins." << endl;}
            else if (getTotal() <= 21 && competitorScore > 21) { player_wins++; cout << "Player wins." << endl;}
            else if ( getTotal() > competitorScore ) { player_wins++; cout << "Player wins." << endl;}
            else if ( getTotal() == competitorScore ) {cout << "Push." << endl;}
            else { casino_wins++; cout << "Player busts. \n Casino Wins." << endl;}
        }

};

class ComputerPlayer: public AbstractPlayer
{
    public: 

        virtual bool isDrawing(Hand pPlayer) const
        {
            
            if (pPlayer.getTotal() >= 21) return false;
            else if (pPlayer.getTotal() <= 16) return true;
            else return false;

        }
};

class BlackJackGame
{

    Deck m_deck = Deck();
    ComputerPlayer m_casino;

    public:

        void play()
        {
            m_deck.populate();
            m_deck.shuffle();
            m_casino.clear();

            HumanPlayer m_player;
            m_deck.shuffle();


            m_casino.add(m_deck.deal());

            cout << "Casino: ";
            m_casino.displayAllCards();
            cout << "[" << m_casino.getTotal() << "]" << endl;

            m_player.add(m_deck.deal());
            m_player.add(m_deck.deal());

            cout << "Player: ";
            m_player.displayAllCards();
            cout << "[" << m_player.getTotal() << "]" << endl;

            while (m_player.isDrawing(m_player)) 
            // Ok look, I have to have m_player as param because there would be no other way to access it due to the fact that this is
            // a const function. But I also use the same object m_player in order to access the function in the class with the dot operator.
            {
                m_player.add(m_deck.deal());
                cout << "Player: ";
                m_player.displayAllCards();
                cout << "[" << m_player.getTotal() << "]" << endl;

            }

            if ( m_player.isBusted() ) { m_player.announce(m_casino.getTotal()); return ; }

            while (m_casino.isDrawing(m_casino))
            {
                //cout << "inside casino" << endl;

                // if win rate < 55 pc then call a function which returns an ideal card from the deck
                // else get any card
                if ( ( (double) casino_wins) / ( (double) (casino_wins+player_wins)) < 0.55) 
                    m_casino.add(m_deck.idealCard(m_casino.getTotal(),m_player.getTotal()));
                else m_casino.add(m_deck.deal());;

                cout << "Casino: ";
                m_casino.displayAllCards();
                cout << "[" << m_casino.getTotal() << "]" << endl;
            }

            m_player.announce(m_casino.getTotal());

        }
};

int main()
{
    cout << "\tWelcome to the Comp322 Blackjack game!" << endl << endl;

    BlackJackGame game;

    bool playAgain = true;
    char answer = 'y';
    while (playAgain)
    {
        game.play();

        cout << "Would you like another round? (y,n): ";
        cin >> answer;
        playAgain = (answer == 'y' ? true : false);
    }

    cout << "Game over!";
    return 0;
}