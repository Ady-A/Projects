////////////////////////////////////
//  For This File:
// Author: Ady Alhamdan
////////////////////////////////////

#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

class Transaction;

    Transaction::Transaction( std::string ticker_symbol,  unsigned int day_date,  
        unsigned int month_date,  unsigned year_date, 
        bool buy_sell_trans,  unsigned int number_shares,  
        double trans_amount ){

    this-> symbol = ticker_symbol;
    this-> day = day_date;
    this-> month = month_date;
    this-> year = year_date;
    if (buy_sell_trans){
      this->trans_type = "Buy";
    }else{
      this->trans_type = "Sell";
    }

    this-> shares = number_shares;
    this->amount = trans_amount;
    this->trans_id = assigned_trans_id;
    ++assigned_trans_id;

        }

    // Destructor
    //
    
    Transaction::~Transaction(){
      
    }


    // Overloaded < operator.
    //
    bool Transaction::operator<( Transaction const &other ){
      if(this->year > other.get_year()){
        return false;
      } else if(this->year < other.get_year()){
        return true;
      }else{
        if(this->month > other.get_month()){
          return false;
        }else if(this->month < other.get_month()){
          return true;
        }else{
          if(this->day > other.get_day()){
            return false;
          }else if(this->day < other.get_day()){
            return true;
          }
        }
      }

      return false;

    }

//2021/11/16
//2021/12/16

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


class History;

	
	History::History(){
    p_head = nullptr;
  }

	// Destructor.
	//
	History::~History(){

    Transaction * curr{p_head};
    Transaction * curr_next{p_head};

    while(curr_next != NULL){

        curr_next = curr->get_next();

        delete curr;
        curr = nullptr;

        curr = curr_next;
        
    }


  }

	// Read the transaction history from file.
	//
	void History::read_history(){

      ece150::open_file();

      

      while(ece150::next_trans_entry()){

        Transaction * ptr = new Transaction(ece150::get_trans_symbol(), ece150::get_trans_day(), ece150::get_trans_month(), 
                                            ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(), 
                                            ece150::get_trans_amount());

      insert(ptr);

        
      }

      ece150::close_file();

  }

	// Insert transaction in linked list.
	//
	void History::insert(Transaction *p_new_trans){

    if(p_head == NULL){
      p_head = p_new_trans;
      p_new_trans->set_next(NULL);
    }else{

      Transaction * curr{p_head};

      while(curr->get_next() != NULL){
        curr = curr->get_next();
      }

      curr->set_next(p_new_trans);
      
      p_new_trans->set_next(NULL);

    }

  }

	// Sort using insertion sort.
	//
	void History::sort_by_date(){

    // Transaction * temp_curr{};
    // Transaction * temp_curr_next{temp_curr->get_next()};
    // Transaction * head_curr{p_head};
    // Transaction * min{};
    // Transaction * p_temp{p_head};

    // p_head = nullptr;

    // while(p_temp != nullptr){
    //   min = p_temp;

    //   while(temp_curr != nullptr){
    //     if(*temp_curr < *min){
    //       temp_curr = min;
    //     }

    //     temp_curr = temp_curr->get_next();

    //   }

    //   temp_curr = p_temp;

    //   temp_curr_next = temp_curr->get_next();

    //   while(temp_curr_next != nullptr){

    //     if(temp_curr == min){
    //       p_temp = temp_curr_next;
    //     } else if(temp_curr_next == min){
    //       temp_curr->set_next(temp_curr_next->get_next());
    //     }

    //     temp_curr = temp_curr->get_next();
    //     temp_curr_next = temp_curr_next->get_next();

    //   }

    //   temp_curr = p_temp;

    //   if(p_head = nullptr){

    //   p_head = min;

    //   p_head->set_next(nullptr);

    //   } else if(p_head != nullptr){
    //     head_curr->set_next(min);
    //     head_curr = head_curr->get_next();
    //   }


    // }


    Transaction * p_sorted{};
    Transaction * p_temp{};
    Transaction * p_insert{};


    p_sorted = p_head;
    p_head = p_head->get_next();
    p_sorted->set_next(nullptr);
    
    

    


    while(p_head != nullptr){
      p_insert = p_head;
      p_head = p_head->get_next();
      p_insert->set_next(nullptr);
      
      
      

      if(*p_insert < *p_sorted){
        p_insert->set_next(p_sorted);
        p_sorted = p_insert;
      } else{
        p_temp = p_sorted;
        while(*p_temp->get_next() < *p_insert && p_temp->get_next() != nullptr){
            p_temp = p_temp->get_next();
        }
        if(p_temp->get_next() == nullptr){
          p_temp->set_next(p_insert);
        } else{
        p_insert->set_next(p_temp->get_next());
        p_temp->set_next(p_insert);
        }
      }
    }

    p_head = p_sorted;
    
  }

	// Update the acb members in the linked list.
	//
	void History::update_acb_cgl(){

    Transaction * curr{p_head};
    Transaction * curr_next{p_head->get_next()};

    curr->set_share_balance(curr->get_shares());
    curr->set_acb(curr->get_amount());
    curr->set_acb_per_share(curr->get_acb() / curr->get_share_balance());
    


    while(curr_next != NULL){
      

      if(curr_next->get_trans_type()){
        curr_next->set_share_balance(curr->get_share_balance() + curr_next->get_shares() );
      } else {
        curr_next->set_share_balance(curr->get_share_balance() - curr_next->get_shares() );
      }

      if(curr_next->get_trans_type()){
        curr_next->set_acb(curr_next->get_amount() + curr->get_acb());
      } else {
        curr_next->set_acb( curr->get_acb() - (curr->get_acb_per_share()*curr_next->get_shares()));
      }

      curr_next->set_acb_per_share(curr_next->get_acb() / curr_next->get_share_balance());
      

      if(curr_next->get_trans_type()){
        curr_next->set_cgl(0);
      } else{
        curr_next->set_cgl(curr_next->get_amount() - (curr_next->get_shares()*curr->get_acb_per_share()));
      }

      curr = curr_next;

      curr_next = curr->get_next();

    }

  }

	// Compute the ACB, and CGL.
	//
	double History::compute_cgl(unsigned int year){

    Transaction * curr{p_head};

    while(curr->get_year() != year){
      curr = curr->get_next();
    }

    Transaction * curr_next{curr->get_next()};

    

    double yearly_cgl;

    while(curr_next->get_year() == year){
      

      yearly_cgl = curr_next->get_cgl() + curr->get_cgl();

      curr = curr_next;
      curr_next = curr->get_next();
    }


    return yearly_cgl;
  }

	// Print the transaction history.
	//
	void History::print(){

   std::cout << "BEGIN TRANSACTION HISTORY" << std::endl;
    
    Transaction * curr{p_head};

      while(curr != NULL){

        curr->Transaction::print();

        curr = curr->get_next();
      }

   std::cout << "END TRANSACTION HISTORY" << std::endl;


  }


Transaction *History::get_p_head() { return p_head; }
