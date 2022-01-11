////////////////////////////////////
// Author: Ady Alhamdan
////////////////////////////////////


#include <iostream>
#include <cstdlib>
#include <ctime>

int main();

int randomaizor();

void print_cards(int * &my_cards, std::size_t cap);

void game(int * &my_cards, std::size_t cap, int * &dealers_cards, std::size_t dealers_cap);

int* add_card(int * &my_cards, std::size_t cap);



int* add_card(int * &my_cards, std::size_t cap){

    int * my_new_cards = new int[cap + 1]{0};

    for(std::size_t i{}; i<cap; ++i){
        my_new_cards[i] = my_cards[i]; 
    }

    my_new_cards[cap] = randomaizor();

    delete[] my_cards;
    my_cards = nullptr;

    return my_new_cards;

}



void print_cards(int * &my_cards, std::size_t cap){

    for(std::size_t i{}; i<cap -1; ++i){

        if(my_cards[i] != 0){

        std::cout << my_cards[i] << ", "; 
        }
        
    }
    std::cout << my_cards[cap - 1] << std::endl;

}


int total(int* & cards, int cap);

int total(int * &cards, int cap){

    int total{};

    for(int i{}; i<cap; ++i){
        total += cards[i]; 
    }

    return total;
}


int randomaizor(){

    

    int card[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    return card[rand() % 10];

}


void game(int * &cards, std::size_t cap, int * &dealers_cards, std::size_t dealers_cap){

    char hit_or_stand{};

    std::size_t your_cap{cap};
    int * my_cards = new int[21]{};

    for(std::size_t i{}; i < cap; ++i){
        my_cards[i] = cards[i];
    }

    while(hit_or_stand != 'S'){

    std::cout << "Would you like to Hit(H) or Stand(S)?" << std::endl;
    std::cin >> hit_or_stand;

    if(hit_or_stand == 'H'){
        my_cards[your_cap] = randomaizor();
        std::cout << "Your Cards: ";
        ++your_cap;
        print_cards(my_cards, your_cap);
        std::cout << "Your Total: " << total(my_cards, your_cap) << std::endl;
        
        if(total(my_cards, your_cap) > 21){
            std::cout << "Dealer Wins, You lost." << std::endl;
            return;
        }
    } 


}


    std::size_t dealer_cap{dealers_cap};
    int * dealer_cards = new int[21]{};

    for(std::size_t i{}; i < dealer_cap; ++i){
        dealer_cards[i] = dealers_cards[i];
    }

    while(total(dealer_cards, dealer_cap) <= total(my_cards, your_cap)){
        dealer_cards[dealer_cap] = randomaizor();
        std::cout << "Dealer's Cards: ";
        ++dealer_cap;
        print_cards(dealer_cards, dealer_cap);
        std::cout << "Dealer's Total: " << total(dealer_cards, dealer_cap) << std::endl;
    }

    if(total(dealer_cards, dealer_cap) <= 21){
        std::cout << "Dealer Wins, You lost." << std::endl;
    } else{
        std::cout << "You Won!" << std::endl;
    }


     return;

}


int main(){

    char play_again{'Y'};

    while(play_again == 'Y'){

    srand(time(0));

    int your_cap{2};

    int * my_cards = new int[your_cap]{randomaizor(), randomaizor()};

    std::cout << "Welcome To BlackJack!" << std::endl;
    std::cout << "Your Cards: ";
    print_cards(my_cards, your_cap);

    std::cout << "Your Total: " << total(my_cards, your_cap) << std::endl;

    int dealer_cap{1};

    int * dealer_cards = new int[dealer_cap]{randomaizor()};

    
    std::cout << "Dealer's Cards: ";
    print_cards(dealer_cards, dealer_cap); 

    std::cout << "Dealer's Total: " << total(dealer_cards, dealer_cap) << std::endl;


    game(my_cards, your_cap, dealer_cards, dealer_cap);

    std::cout << "Would you like to play again? YES(Y) or NO(N)?" << std::endl;
    std::cin >> play_again;
    
    }


    return 0;
}
