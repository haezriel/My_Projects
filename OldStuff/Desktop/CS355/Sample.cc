#ifndef Cards_Card_h
#define Cards_Card_h

enum {ACE=1, JACK=11, QUEEN=12, KING=13};
enum {SPADES, CLUBS,DIAMONDS, HEARTS};

struct Card{
	short rank;
	short suit;
	Card(short r=ACE, short s=SPADES) : rank{r}, suit{s} {}
};

class Deck {
private:
	int capacity;
	int numCards;
	Card *cards;
	
	Deck (int n) : capacity {n}, numCards{0}, cards{new Card[n]} {restock;}
public:
	static Deck pokerDeck() {return Deck(52);}
	static Deck pinochleDeck() {return Deck(48);}
	static Deck doublePinochleDeck() {return Deck(96);}
	
	int count() const {return numCards;}
	
	~Deck() {delete[] cards;}
private:
	void restockPoker();
	void restockPinochle(int n);

};

#endif
