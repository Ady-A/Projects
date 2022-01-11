#include <iostream>
#include <stdlib.h>    
#include <time.h> 

int  main();

class player;

void innit_game(player* player_list, int ppl_qty);

void mafia(int ppl_qty, player* player_list);

void doctor(int ppl_qty, player* player_list);

void detective(int ppl_qty, player* player_list);

void voting(int ppl_qty, player* player_list);

void game();

int alive_mafia(int ppl_qty, player* player_list);

int innocent_alive(int ppl_qty, player* player_list);

void kill_off(int ppl_qty, player* player_list);

void Clear();

class player{
    public: 

    player();
    ~player();

    std::string get_name();
    char get_role();
    int get_votes();
    bool get_is_dead();

    void set_name(std::string name);
    void set_role(char role);
    void set_votes(int votes);
    void set_is_dead(bool is_dead);

    void print_role();

    private:

    std::string name;
    char role;
    int votes;
    bool is_dead;
};

player::player(){
    this->name = " ";
    this->role = 0x00;
    this->votes = 0;
    this->is_dead = false;
}

player::~player(){

}


std::string player::get_name(){
    return name;
}
char player::get_role(){
    return role;
}
int player::get_votes(){
    return votes;
}
bool player::get_is_dead(){
    return is_dead;
}

void player::set_name(std::string name){
    this->name = name;
}
void player::set_role(char role){
    this->role = role;
}
void player::set_votes(int votes){
    this->votes = votes;
}
void player::set_is_dead(bool is_dead){
    this->is_dead = is_dead;
}








void innit_game(player* player_list, int ppl_qty){



    char * p_roles_list = new char[ppl_qty];

    int k{};

    while(k < ppl_qty){

        p_roles_list[k] = 0x09;
        ++k;
        for(int i = 0; i < 4; ++i){
            p_roles_list[k] = 0x01;
            ++k;
        }
        if(k < 6){
            p_roles_list[k] = 0x02;
            ++k;
            p_roles_list[k] = 0x03;
            ++k;
        }

    }


    int rand_element;

    for(int i{}; i<ppl_qty; ++i){

        rand_element = rand()%ppl_qty;


        while(1){
        
        if(p_roles_list[rand_element] < 0x10){
            player_list[i].set_role(p_roles_list[rand_element]);
            p_roles_list[rand_element] = 0x20;
            break;
        } else {
            rand_element = rand()%ppl_qty;
        }
        }


    }

    

        for(int i{}; i<ppl_qty; ++i){
        std::string name;

        if((i)%10 == 0){
            std::cout << i+1 << "st Player, please enter your name: ";
            std::cin >> name;
        } else if((i-1)%10 == 0){
            std::cout << i+1 << "nd Player, please enter your name: ";
            std::cin >> name;
        } else if((i-2)%10 == 0){
            std::cout << i+1 << "rd Player, please enter your name: ";
            std::cin >> name;
        } else {
            std::cout << i+1 << "th Player, please enter your name: ";
            std::cin >> name;
        }

        

        player_list[i].set_name(name);

        std::cout << "You are the ";

        player_list[i].print_role();

        std::cout << std::endl;

        char N = ' ';

        do{


        std::cout << "Please call up the next player and enter (N): ";
        std::cin >> N;

        }while(N != 'N');
        Clear();
    }
    
}

void player::print_role(){
    if(role == 0x01){
        std::cout << "Civilian";
    } else if(role == 0x02){
        std::cout << "Doctor";
    } else if(role == 0x03){
        std::cout << "Detective";
    } else if(role == 0x09){
        std::cout << "Mafia";
    }
}



void Clear()
{
    std::cout << "\x1B[2J\x1B[H";
}

void mafia(int ppl_qty, player* player_list){

    std::cout << "Alive Civilians:" << std::endl;

    for(int i{}; i < ppl_qty; ++i){
        if(player_list[i].get_role() < 0x04){
            std::cout << player_list[i].get_name() << std::endl;
        }
        
    }

    std::string killed_name;
    std::cout << "Please write the name of the person you want to kill(case sensitive): ";
    std::cin >> killed_name;

    for(int i{}; i < ppl_qty; ++i){
        if(player_list[i].get_name() == killed_name){

            player_list[i].set_role(player_list[i].get_role() + 0x20);
        }
        
    }



        

}

void doctor(int ppl_qty, player* player_list){

    std::cout << "Current Civilians:" << std::endl;

    for(int i{}; i < ppl_qty; ++i){

        if(player_list[i].get_is_dead() == false){
        
        std::cout << player_list[i].get_name() << std::endl;
        }
        
    }

    std::string revived_name;
    std::cout << "Please write the name of the person you want to revive(case sensitive): ";
    std::cin >> revived_name;

    for(int i{}; i < ppl_qty; ++i){
        if(player_list[i].get_role() < 0x09){
            if(player_list[i].get_name() == revived_name){

                player_list[i].set_role(player_list[i].get_role() - 0x20);
            
            }
        }
        
    }
}

void detective(int ppl_qty, player* player_list){

    std::cout << "Current Civilians:" << std::endl;

    for(int i{}; i < ppl_qty; ++i){

        if(player_list[i].get_is_dead() == false){
        
        std::cout << player_list[i].get_name() << std::endl;
        }
        
    }

    std::string investigated_name;
    std::cout << "Please write the name of the person you want to investigate(case sensitive): ";
    std::cin >> investigated_name;

    for(int i{}; i < ppl_qty; ++i){
        if(player_list[i].get_name() == investigated_name){



          if(player_list[i].get_role() == 0x09){
              std::cout << player_list[i].get_name() << " is the Mafia";
          } else {
              std::cout << player_list[i].get_name() << " is NOT the Mafia";
          }

          std::cout << std::endl;

           
        }
        
    }
}

void voting(int ppl_qty, player player_list[]){

    

    std::string voted_name;

    for(int i{}; i<ppl_qty; ++i){

        if(player_list[i].get_role() < 0x10){
        
            std::cout << "Current Civilians:" << std::endl;

            for(int i{}; i < ppl_qty; ++i){
            
                if(player_list[i].get_is_dead() == false){
            
                    std::cout << player_list[i].get_name() << std::endl;
                }
            }

        std::cout << player_list[i].get_name() << ", please write the name of player you want to vote off(case sensitive): ";
        std::cin >> voted_name;
        Clear();

        for(int k{}; k < ppl_qty; ++k){
        if(player_list[k].get_name() == voted_name){

            player_list[k].set_votes(player_list[k].get_votes() + 1);
           
        }
        }
        
    }
    }

    int max_votes{};
//gotta change it to a tie breaker if there is a tie
    for(int i{}; i<ppl_qty; ++i){
        if(player_list[i].get_votes() > max_votes){
            max_votes = player_list[i].get_votes();
        }
    }

    int voted_player;

    for(int i{}; i<ppl_qty; ++i){
        if(player_list[i].get_votes() == max_votes){
            player_list[i].set_role(0x20);
            player_list[i].set_is_dead(true);
            player_list[i].set_votes(0);

            voted_player = i;
        }
    }

    std::cout << player_list[voted_player].get_name() << " has been voted off." << std::endl;
}

int alive_mafia(int ppl_qty, player* player_list){

    int mafia_qty{};

    for(int i{}; i < ppl_qty; ++i){
        if(player_list[i].get_role() == 0x09){
            ++mafia_qty;
        }
    }

    return mafia_qty;
}

int innocent_alive(int ppl_qty, player* player_list){
    int innocent_qty{};

    for(int i{}; i < ppl_qty; ++i){
        if(player_list[i].get_role() < 0x09){
            ++innocent_qty;
        }
    }

    return innocent_qty;
}

void kill_off(int ppl_qty, player* player_list){


    for(int i{}; i < ppl_qty; ++i){
        if(player_list[i].get_role() > 0x09){
            player_list[i].set_is_dead(true);
        }
    }

}



void game(){

    srand(time(NULL));

    int ppl_qty{};

    std::cout << "Welcome to Mafia!" << std::endl;
    std::cout << "Please Enter the Number of Players: ";
    std::cin >> ppl_qty;

    player* player_list = new player[ppl_qty];
    player* player_list_copy = new player[ppl_qty];
     

    innit_game(player_list, ppl_qty);



    int mafia_qty{1};
    int alive_innocent{4};

    while( (mafia_qty < alive_innocent) && (mafia_qty > 0) ){

        char N;

        do{
        std::cout << "Whenever you are read to proceed to the next night, please enter (N): ";
        std::cin >> N;
        }while(N != 'N');

        Clear();


        for(int i{}; i<ppl_qty; ++i){
            player_list_copy[i].set_name(player_list[i].get_name());
            player_list_copy[i].set_role(player_list[i].get_role());
        }

        


        std::cout << "Everyone, Please go to sleep." << std::endl;

        std::cout << "Mafia, please wake up." << std::endl;
        std::cout << "Whenever you are ready, please enter (N): ";
        std::cin >> N;

        if(N == 'N'){
        mafia(ppl_qty, player_list);
        }

        std::cout << "Whenever you are ready to go back to sleep, please enter (N): ";
        std::cin >> N;

        if(N == 'N'){
            Clear();
        }

        std::cout << "Doctor, please wake up." << std::endl;
        std::cout << "Whenever you are ready, please enter (N): ";
        std::cin >> N;

        if(N == 'N'){
        doctor(ppl_qty, player_list);
        }

        std::cout << "Whenever you are ready to go back to sleep, please enter (N): ";
        std::cin >> N;

        if(N == 'N'){
            Clear();
        }

        std::cout << "Detective, please wake up." << std::endl;
        std::cout << "Whenever you are ready, please enter (N): ";
        std::cin >> N;

        if(N == 'N'){
        detective(ppl_qty, player_list);
        }
        std::cout << "Whenever you are ready to go back to sleep, please enter (N): ";
        std::cin >> N;

        if(N == 'N'){
            Clear();
        }

        kill_off(ppl_qty, player_list);

        for(int i{}; i<ppl_qty; ++i){
            if(player_list_copy[i].get_is_dead() != player_list[i].get_is_dead()){
                std::cout << player_list[i].get_name() << " has been killed off." << std::endl;
            }
        }

        voting(ppl_qty, player_list);
        


        mafia_qty = alive_mafia(ppl_qty, player_list);
        alive_innocent = innocent_alive(ppl_qty, player_list);


    }

    if(mafia_qty >= alive_innocent){
        std::cout << "The Mafia has won!";
    } else {
        std::cout << "All Mafias have been voted off."<< std::endl;  
        std::cout << "Civilians have won!";      
    }
    
}


int main(){

    

    game();
    return 0;
}