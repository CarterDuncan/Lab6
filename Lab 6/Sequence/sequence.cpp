//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }
	
	//Destructor
	sequence::~sequence(){
		list_clear(head_ptr);
		head_ptr = NULL;
		tail_ptr = NULL;
		cursor = NULL;
		precursor = NULL;
		many_nodes = 0;
	}
	
	//MODIFICATION MEMBER FUNCTIONS
	void sequence::start(){
		cursor = head_ptr;
	};
	
	void sequence::end(){
		cursor = tail_ptr;
		if (precursor == NULL){
			precursor = head_ptr;
		}
		if(tail_ptr != head_ptr){
			while(precursor->link() != cursor){
				precursor = precursor->link();
			}
		}
	}
	
	void sequence::advance(){
		assert(is_item());
		if(cursor == tail_ptr){
			cursor = NULL;
			precursor = NULL;
			return;
		}
		if(cursor == head_ptr){
			cursor = cursor->link();
			precursor = head_ptr;
			return;
		}
		precursor = cursor;
		cursor = cursor->link();
	}
	
	void sequence::insert(const value_type &entry){
		if(many_nodes <= 1 || cursor == NULL){
			list_head_insert(this->head_ptr, entry);
			cursor = head_ptr;
			if(tail_ptr == NULL){
				tail_ptr = cursor;
			}
		}else{
			list_insert(precursor, entry);
			cursor = precursor->link();
		}
		many_nodes++;
	}
	
	void sequence::attach(const value_type &entry){
		if(cursor == NULL){
			if(head_ptr == NULL){
				list_head_insert(head_ptr, entry);
				tail_ptr = head_ptr;
				cursor = head_ptr;
			}else{
				list_insert(tail_ptr, entry);
				precursor = tail_ptr;
				tail_ptr = tail_ptr->link();
				cursor = tail_ptr;
			}
		}else{
			list_insert(cursor, entry);
			precursor = cursor;
			if(cursor == tail_ptr){
				tail_ptr = tail_ptr->link();
			}
			cursor = precursor->link();
		}
		many_nodes++;
	}
	
	void sequence::operator =(const sequence& source){
		if(this == &source){
			return;
		}
		node *source_h, *source_t, *source_c, *source_p;
		source_h = source.head_ptr;
		source_t = source.tail_ptr;
		source_c = source.cursor;
		source_p = source.precursor;
		list_clear(head_ptr);
		many_nodes = 0;
		list_copy(source.head_ptr, head_ptr, tail_ptr);
		many_nodes = source.many_nodes;
		if(source_c != NULL){
			cursor = list_locate(head_ptr, list_find_node(source_h, source_c));
		}else{
			cursor = NULL;
		}
		if(source_p != NULL){
			precursor = list_locate(head_ptr, list_find_node(source_h, source_p));
		}else{
			precursor = NULL;
		}
	}
	
	
	void sequence::remove_current(){
		assert(is_item());
		if (cursor == head_ptr){
			list_head_remove(head_ptr);
			cursor = head_ptr;
		}else{
			if(cursor == tail_ptr){
				tail_ptr = precursor;
				list_remove(precursor);
				cursor = NULL;
				precursor = NULL;
			}else{
				list_remove(precursor);
				cursor = precursor->link();
			}
		}
		many_nodes--;
	}
	
	sequence::size_type sequence::size() const{
		return many_nodes;
	}
	
	bool sequence::is_item() const{
		if (cursor == NULL){
			return false;
		}
		return true;
	}
	
	sequence::value_type sequence::current() const{
		assert(is_item());
		return cursor->data();
	}

    
}
