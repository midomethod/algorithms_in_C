// Filename: linkedlist.cpp
// 
// Contains the class linkedlistist that represents a linked list
// 
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020

#include "linkedlistfunc.h"
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
using namespace std;

// Default constructor sets head and tail to null
LinkedList :: LinkedList()
{
	head = NULL;
}

// Insert(int val): Inserts the int val into list, at the head of the list. Note that there may be multiple copies of val in the list.
// Input: Int to insert into the linked list
// Output: Void, just inserts new Node
// Simply calls recursive function
void LinkedList :: insert(int val)
{
	Node *to_add = new Node; // creates new Node
	to_add->data = val; // sets the data to hold input val
	
    to_add->next = head; // make to_add point to existing head
    head = to_add; // set head to to_add
}

// find(int val): Finds a Node with data "val"
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Just a wrapper to recursive function
Node* LinkedList :: find(int val)
{
    return find(val, head); // just call recursive function
}

// find(int val, Node* curr): Finds a Node with data "val", at list starting from curr
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node in the list containing val
Node* LinkedList :: find(int val, Node *curr)
{
    if (curr == NULL) // base case, list is empty
        return NULL;
    if (curr->data == val) // curr node has val
        return curr;
    else
        return find(val, curr->next); // recursive call to list starting from next node
}

// deleteNode(int val): Delete a Node with data val, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, only the first Node in the list is deleted.
Node* LinkedList :: deleteNode(int val)
{
    return deleteNode(val, NULL, head); // recursive call. We set prev to NULL, and curr to head
}

// deleteNode(int val, Node* prev, Node* curr): Delete a Node with data val  from the list starting *with* curr. prev stores pointer of previous node, to aid deletion
// Note that we cannot delete curr, so we only look at the list after that. If no node is found, return NULL.
// Input: int to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, only the first Node in the list is deleted.
Node* LinkedList :: deleteNode(int val, Node *prev, Node* curr)
{
    if (curr == NULL) // base case, val not found, no more list left
        return NULL;
    if (curr->data == val) // val is found! Now for the case analysis
    {
        if (prev == NULL) // prev was supposed to be pointer of previous node. Since prev is NULL, curr is the head
            head = head->next; // delete head
        else
            prev->next = curr->next; // delete curr from the list, by "skipping" over curr
        return curr; // returning node with val
    }
    return deleteNode(val, curr, curr->next); // proceed one step in the list
}

// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void LinkedList :: deleteList()
{
    deleteList(head);
}


// deleteList(curr): Deletes every Node of list starting from curr to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list starting from curr
void LinkedList :: deleteList(Node *curr)
{
    if (curr == NULL) // base case, empty list
        return; 
    Node *nextNode = curr->next; // store next node
    delete(curr); // delete current node
    deleteList(nextNode); // recursive call
}

// Prints list in order
// Input: None
// Output: string that has all elements of the list in order
string LinkedList :: print()
{
    string to_return = print(head);
    if (to_return.length() > 0) // non-empty string, has extra space at end
        to_return.pop_back(); // delete last character
    return to_return;
}

// print(Node *curr): Prints list in order, starting from curr
// Input: None
// Output: string that has all elements of the list in order
string LinkedList :: print(Node *curr)
{
    if(curr == NULL) // base case, empty list
        return ""; // return empty string
    return to_string(curr->data) + " " + print(curr->next);
}

// Computes the length of the linked list
// Input: None
// Output: Int, length of list
int LinkedList :: length()
{
    return length(head); // recursive call
}

// length(Node *curr): Computes the length of the linked list, starting from curr
// Input: None
// Output: Int, length of list
int LinkedList :: length(Node *curr)
{
    if (curr == NULL) // base case
       return 0;
    return 1+length(curr->next); // recursive call
}

bool LinkedList :: palindrome()
{
    Node* curr = head;
    bool palindrome = true;
    int i;
    int j;
    Node* target1;
    Node* target2;
    int numiteration = length()/2;


    for(i=0; i<numiteration; i++)
    {
        curr=head;

        for(j=0; j<i; j++)
        {
            curr=curr->next;
        }
        target1=curr;

        curr=head;

        for(j=0; j<length()-i-1; j++)
        {
            curr=curr->next;
        }
        target2=curr;

        if(target1->data != target2->data){
            palindrome = false;
        }

    }

    return palindrome;

}

Node* LinkedList :: deleteLast(int val)
{
    int iOfLast;
    int i=0;
    Node* curr=head;
    Node* ptOfLast;

    while(curr!=NULL)
    {
        if(curr->data==val)
        {
            iOfLast=i;
            ptOfLast=curr;
        }
        curr=curr->next;
        i++;
    }

    curr=head;
    //Move to the spot one before iOfLast, 1 3 4 5 3 6, <-for 3, ioflast would be 4 and we would like tomove to the 5 which is 3 nexts
    for(i=0;i<iOfLast-1;i++)
    {
        curr=curr->next;
    }

    //Now, make thisone->next point to 
    if(curr->next->next!=NULL)
        {
            curr->next=curr->next->next;
        }
    else
    {
        curr->next=NULL;
    }
    free(ptOfLast);

    return ptOfLast;
}

void LinkedList :: dedup()
{
    int target;
    int i=0;
    int j;
    Node* curr;
    Node* dummy;



    while(i<length())
    {
        //This level assumes ith elemnt of linklist IS the first instance, then removes dupes
        curr=head;

        //Find value of first occurance
            for(j=0;j<i;j++)
            {
                curr=curr->next;
            }
        target=curr->data;
        //printf("\tCP1:\n\tTarget: %d\n\ti: %d\n",target,i);

        while(curr!=NULL)
        {
            //printf("\tCP2\n");
            if(curr->next==NULL)
            {
                break;
            }
            if(curr->next->data==target)
            {
                dummy=curr->next->next;
                free(curr->next);
                curr->next=dummy;
                //printf("DELETED\n");
            }
            else
            {
                curr=curr->next;
            }
        }


        i++;
    }

    return;
}

// Rotating is easy
void LinkedList :: rotate(int val)
{
    Node *curr;
    Node *dummy;

    for(int i = 0; i<val; i++){
        curr = head;
        while(curr->next->next != NULL)
        {
            curr=curr->next;
        }

        dummy=curr->next;
        curr->next = NULL;

        dummy->next=head;
        head = dummy;
    }
    return;
}

void LinkedList :: reverse(int val)
{
    Node* curr;
    Node* target1;
    Node* target2;
    int dummyVal;
    int i;
    int j;


    curr = head;
    for(i=0; i<val/2; i++)
    {
        curr=head;

        for(j = 0; j<i; j++)
        {
            curr=curr->next;
        }
        target1 = curr;

        curr = head;
        for(j = 0; j<val-i-1; j++)
        {
            curr=curr->next;
        }
        target2 = curr;
        
            dummyVal = target1->data;
            target1->data=target2->data;
            target2->data=dummyVal;
        
    }

    return;
}
