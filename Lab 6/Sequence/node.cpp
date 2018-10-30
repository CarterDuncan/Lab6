//
//  test.cpp
//  test
//
//  Created by Carter Duncan on 10/26/18.
//  Copyright © 2018 Santa Clara University. All rights reserved.
//

// FILE: node.cpp
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <iostream>
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
        const node *cursor;
        size_t answer;
        
        answer = 0;
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
            ++answer;
        
        return answer;
    }
    
    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
        head_ptr = new node(entry, head_ptr);
    }
    
    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
        node *insert_ptr;
        
        insert_ptr = new node(entry, previous_ptr->link( ));
        previous_ptr->set_link(insert_ptr);
    }
    
    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
        node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
            if (target == cursor->data( ))
                return cursor;
        
        return NULL;
    }
    
    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
        const node *cursor;
        
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
            if (target == cursor->data( ))
                return cursor;
        
        return NULL;
    }
    
    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
        node *cursor;
        size_t i;
        
        assert (0 < position);
        cursor = head_ptr;
        for (i = 1; (i < position) && (cursor != NULL); i++)
            cursor = cursor->link( );
        
        return cursor;
    }
    
    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
        const node *cursor;
        size_t i;
        
        assert (0 < position);
        cursor = head_ptr;
        for (i = 1; (i < position) && (cursor != NULL); i++)
            cursor = cursor->link( );
        
        return cursor;
    }
    
    void list_head_remove(node*& head_ptr)
    {
        node *remove_ptr;
        
        remove_ptr = head_ptr;
        head_ptr = head_ptr->link( );
        delete remove_ptr;
    }
    
    void list_remove(node* previous_ptr)
    {
        node *remove_ptr;
        
        remove_ptr = previous_ptr->link( );
        previous_ptr->set_link( remove_ptr->link( ) );
        delete remove_ptr;
    }
    
    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
        while (head_ptr != NULL)
            list_head_remove(head_ptr);
    }
    
    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
        head_ptr = NULL;
        tail_ptr = NULL;
        
        // Handle the case of the empty list.
        if (source_ptr == NULL)
            return;
        
        // Make the head node for the newly created list, and put data in it.
        list_head_insert(head_ptr, source_ptr->data( ));
        tail_ptr = head_ptr;
        
        // Copy the rest of the nodes one at a time, adding at the tail of new list.
        source_ptr = source_ptr->link( );
        while (source_ptr != NULL)
        {
            list_insert(tail_ptr, source_ptr->data( ));
            tail_ptr = tail_ptr->link( );
            source_ptr = source_ptr->link( );
        }
    }
	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr){
        head_ptr = tail_ptr = NULL;
        if (start_ptr == NULL)
            return;
        list_head_insert(head_ptr, start_ptr->data());
        tail_ptr = head_ptr;
		if(start_ptr != end_ptr){
			start_ptr = start_ptr->link();
		}
        while(start_ptr != end_ptr && start_ptr != NULL){
            list_insert(tail_ptr, start_ptr->data());
            start_ptr = start_ptr->link();
            tail_ptr = tail_ptr->link();
        }
        return;
    }
    size_t list_occurrences(node* head_ptr, const node::value_type& target){
        size_t count = 0;
		while(head_ptr != NULL){
			if(head_ptr->data() == target)
                count++;
			head_ptr = head_ptr->link();
		}
        return count;
    }
    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position){
        assert(position > 0 && position <= list_length(head_ptr)+1);
        size_t i;
		if(position == 1){
			list_head_insert(head_ptr, entry);
		}else{
			node* tmp;
			tmp = head_ptr;
			for(i=1;i<position-1;i++){
				tmp = tmp->link();
			}
			list_insert(tmp, entry);
		}
        return;
    }
    node::value_type list_remove_at(node*& head_ptr, size_t position){
        assert(position > 0 && position <= list_length(head_ptr));
        size_t i,data;
		if(position == 1){
			data = head_ptr->data();
			list_head_remove(head_ptr);
		}else{
			node* tmp;
			tmp = head_ptr;
			for(i=1;i<position-1;i++){
				tmp = tmp->link();
			}
			data = tmp->data();
			list_remove(tmp);
		}
        return data;
    }
	node* list_copy_segment(node* head_ptr, size_t start, size_t finish){
        assert((1 <= start)&&(start <= finish)&&(finish <= list_length(head_ptr)));
        node *head, *tail;
        head = NULL;
        tail = NULL;
		node *tmp1, *tmp2;
        size_t i;
		tmp1 = head_ptr;
        for(i=1;i<start;i++){
            tmp1 = tmp1->link();
        }
		tmp2 = tmp1->link();
        for(i=start;i<finish;i++){
            tmp2 = tmp2->link();
        }
		list_piece(tmp1, tmp2, head, tail);
        return head;
    }
    void list_remove_dups(node* head_ptr){
        node* current = head_ptr;
        size_t i,j;
        for(i=0;i<list_length(head_ptr);i++)
            for(j=i;j<list_length(head_ptr);j++)
                if(head_ptr->data() == current->data())
                    list_remove(current);
        return;
    }
	void list_print (const node *head_ptr){
		const node *current;
		current = head_ptr;
		if(current == NULL){
			std::cout << std::endl;
		}else{
			while(current != NULL){
				std::cout << current->data();
				if(current->link() != NULL){
					std::cout << ", ";
				}else{
					std::cout << std::endl;
				}
				current = current->link();
			}
		}
        return;
    }
	
	node* list_detect_loop (node* head_ptr){
		node* fast = head_ptr, *slow = head_ptr;
		
		while(fast != NULL && fast->link() != NULL){
			slow = slow->link();
			fast = fast->link()->link();
			if(slow == fast){
				break;
			}
		}
		if(fast == NULL || fast->link() == NULL){
			return NULL;
		}
		slow = head_ptr;
		while(slow != fast){
			slow = slow->link();
			fast = fast->link();
		}
		return fast;
	}
	
	size_t list_find_node(node* head_ptr, const node* target){
		size_t location = 1;
		node *cursor = head_ptr;
		while(cursor != target){
			cursor = cursor->link();
			location++;
		}
		return location;
	}
	
	const size_t list_find_node(const node* head_ptr, const node* target){
		size_t location = 1;
		const node *cursor = head_ptr;
		while(cursor != NULL &&cursor != target){
			cursor = cursor->link();
			location++;
		}
		if(cursor == NULL){
			return 0;
		}
		return location;
	}
	
}
