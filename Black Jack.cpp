#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;
class Card {
public:
    string suit;
    string rank;
    int value;
    Card(string r, string s, int v) : rank(r), suit(s), value(v) {}
};
class Deck {
private:
    vector<Card> cards;
public:
    Deck() {
        string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
        int values[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };
        for (int s = 0; s < 4; s++) {
            for (int r = 0; r < 13; r++) {
                cards.push_back(Card(ranks[r], suits[s], values[r]));
            }
        }
        srand(time(0));
    }
    Card drawCard() {
        int index = rand() % cards.size();
        Card drawnCard = cards[index];
        cards.erase(cards.begin() + index);
        return drawnCard;
    }
};
class Player {
public:
    vector<Card> hand;
    int score;
    Player() : score(0) {}
    void draw(Deck& deck) {
        Card newCard = deck.drawCard();
        hand.push_back(newCard);
        score += newCard.value;
        if (score > 21) {
            for (Card& card : hand) {
                if (card.rank == "A" && card.value == 11) {
                    card.value = 1;
                    score -= 10;
                    break;
                }
            }
        }
    }
    void showHand() {
        for (Card card : hand) {
            cout << card.rank << " of " << card.suit << "  ";
        }
        cout << "(Score: " << score << ")\n";
    }
};
int main() {
    Deck deck;
    Player player, dealer;
    player.draw(deck);
    player.draw(deck);
    dealer.draw(deck);
    dealer.draw(deck);
    cout << "Your hand: ";
    player.showHand();
    cout << "Dealer's hand: " << dealer.hand[0].rank << " of " << dealer.hand[0].suit << " and [Hidden]\n";
    string choice;
    while (player.score < 21) {
        cout << "Hit or Stand? (h/s): ";
        cin >> choice;
        if (choice == "h") {
            player.draw(deck);
            cout << "Your hand: ";
            player.showHand();
        }
        else break;
    }
    if (player.score > 21) {
        cout << "You busted! Dealer wins.\n";
        return 0;
    }
    cout << "Dealer's hand: ";
    dealer.showHand();
    while (dealer.score < 17) {
        dealer.draw(deck);
        cout << "Dealer draws...\n";
        dealer.showHand();
    }
    if (dealer.score > 21 || player.score > dealer.score) {
        cout << "You win!\n";
    }
    else if (player.score < dealer.score) {
        cout << "Dealer wins!\n";
    }
    else {
        cout << "It's a tie!\n";
    }
    return 0;
}
