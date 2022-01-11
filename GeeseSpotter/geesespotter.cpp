////////////////////////////////////
//  For This File:
// Author: Ady Alhamdan
////////////////////////////////////

#include "geesespotter_lib.h"

void clear_adj_zero(char * board, std::size_t xdim, std::size_t ydim, char * old_board);
bool is_changed(char * board, std::size_t xdim, std::size_t ydim, char * old_board);


char * createBoard(std::size_t xdim, std::size_t ydim){


    long long unsigned int size_of_array {xdim*ydim};
    char * new_array {new char[size_of_array]{0x00}};


    return new_array;
}

void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){

    

    for(int position{}; position < xdim*ydim; position++){

        if(board[position] == 0x09){

            for(int y_shift{-1}; y_shift <= 1; y_shift++){
                for(int x_shift{-1}; x_shift <= 1; x_shift++){


                    int curr_position = position + (y_shift*xdim) + x_shift;

                    int xloc = position % xdim;

                    int yloc = position/xdim;

                    if((xloc + x_shift) >= 0 && (xloc + x_shift) < xdim){

                        if((yloc + y_shift) >= 0 && (yloc + y_shift) < ydim){
                        
                        

                            if(board[curr_position] != 0x09){
                                board[curr_position]++;
                            }
                            
                        }
                        
                    }
                    



                }
            }


        }

    }

}

void hideBoard(char * board, std::size_t xdim, std::size_t ydim){


    for (int k{0}; k < xdim*ydim; ++k){
    board[k] = board[k] | hiddenBit();
    }   

}

void cleanBoard(char * board){


    delete[] board;
    board = nullptr;

}

void printBoard(char * board, std::size_t xdim, std::size_t ydim){
    

    for(int loc{}; loc < xdim*ydim; ++loc){


       
        if( (board[loc] & 0x30) == 0x30){
            std::cout << "M";

        }else if( (board[loc] & hiddenBit()) == hiddenBit()){
            std::cout << "*";

        }else {

            char current_board_display = board[loc];
             current_board_display = current_board_display | 0x30;
            std::cout << current_board_display;

        }


        if((loc + 1)%xdim == 0){
            std::cout << std::endl;
        }
        
    }


}

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){


    int pos = (xdim*(yloc))+xloc;

    char * old_board = new char[xdim*ydim];

    char * old_old_board = new char[xdim*ydim];

    for(int i{}; i < xdim*ydim; ++i){
        old_old_board[i] = board[i];
    }


    if((board[pos]& 0x30) == 0x30){
        return 1;
    } else if(board[pos] < 0x10){
        return 2;
    } else if(board[pos] == 0x29){

        

        for(int i{}; i < xdim*ydim; ++i){
            if(board[i] == 0x29){
            board[i] = board[i] ^ 0x20;
            }
        }

        return 9;

        

    }else if(board[pos] == 0x20){

        board[pos] = board[pos] ^ 0x20;


        while(is_changed(board, xdim, ydim, old_board) == true){

        for(int i{}; i < xdim*ydim; ++i){
        old_old_board[i] = old_board[i];
        }

        for(int i{}; i < xdim*ydim; ++i){
        old_board[i] = board[i];
        }

            
        clear_adj_zero(board, xdim, ydim, old_old_board);


        }


    } else {
        board[pos] = board[pos] ^ 0x20;
    }


    delete[] old_board;
    old_board = nullptr;

    delete[] old_old_board;
    old_old_board = nullptr;
    

    return 0;

}

int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){

    int loc_in_board{};

    loc_in_board = (xdim*(yloc))+xloc;

    if(board[loc_in_board] & 0x30 == 0x30){
        board[loc_in_board] =  board[loc_in_board]^markedBit();

    }else if(board[loc_in_board] & 0x20 == 0x20){
        board[loc_in_board] = board[loc_in_board] | 0x10;

    } else {
        return 2;
    }
    
    return 0;
}
bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){

    bool is_game_won{true};


    for(int pos{}; pos < xdim*ydim; pos++){

    if(board[pos] < 0x39 && board[pos] >= 0x20){
            if (board[pos] != 0x29) {

                is_game_won = false;
            }
    
        }

    }



    return is_game_won;
}

void clear_adj_zero(char * board, std::size_t xdim, std::size_t ydim, char * old_board){

    std::size_t size = xdim*ydim;



    for(std::size_t i{}; i < size; ++i){
            if(board[i] == 0x00){

          

            for(int y_shift{-1}; y_shift <= 1; y_shift++){
                for(int x_shift{-1}; x_shift <= 1; x_shift++){

                    


                    int curr_position = i + y_shift*xdim + x_shift;

                    int xloc = i % xdim;

                    int yloc = i/xdim;


                    if((xloc + x_shift) >= 0 && (xloc + x_shift) < xdim){
                        if((yloc + y_shift) >= 0 && (yloc + y_shift) < ydim){


                            if(board[curr_position] > 0x10){
                                if(board[curr_position] != 0x29){
                            board[curr_position] = board[curr_position] ^ 0x20;
                                }
                            }
                            
                        }
                        
                    }

                }


            }

        }
        
    }



}

bool is_changed(char * board, std::size_t xdim, std::size_t ydim, char * old_board){


    for(std::size_t i{}; i < xdim*ydim; ++i){
        if(board[i] != old_board[i]){
            return true;
        }
    }

    return false;

}
