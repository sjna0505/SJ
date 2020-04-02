#include <iostream>
#include "mlist.h"
using namespace std;
//------------------------------------------------------------------------------
//IMPORTANT: You are not allowed to remove or add any parameters to any functions.
//NOTE: There can only be at most 2 loops in this file
//------------------------------------------------------------------------------

//Constructor, construct an empty doubly linked list.
MList::MList(){

	ntop = NULL;
	nbottom = NULL;
}

//Destructor, properly clears and deallocates everything of current list.
//simply call the clear function if you have already implemented that.
MList::~MList(){
	clear();
}

//Note: RECURSION --- This function should be implemented using recursion.
//this function properly clears and deallocates everything of current list.
//there should be no loop in this function
void MList::clear(){

	if(ntop == NULL) return;

	else {
		Node* temp = ntop;
		ntop = ntop -> next;
		delete temp;
		clear();
	}
}

//returns a boolean true if the list is empty, false if otherwise.
bool MList::isEmpty(){

	if(ntop == NULL)
		 return true;
	else 
		 return false;
}

/*
	Add or insert a new node with d_item as its data at the top of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_top(Data* d_item){

	if(ntop == NULL){
			ntop = new Node;
			ntop -> nodeData = d_item; 
			ntop -> next = NULL;
			ntop -> prev = NULL;
			nbottom = ntop;
	}

	else{
		 Node* beg = new Node;
		 Node* temp = ntop;
		 ntop -> prev = beg;

		 beg -> nodeData = d_item;
		 beg -> prev = NULL;
		 beg -> next = temp;
		 ntop = beg;
	}
}

/*
	Add or insert a new node with d_item as its data at the bottom of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_bottom(Data* d_item){
	if(ntop == NULL){
		 ntop = new Node;
		 ntop -> nodeData = d_item; 
		 ntop -> next = NULL;
		 ntop -> prev = NULL;
		 nbottom = ntop;
	}
	else{ 

		 Node* end = new Node;
		 Node* temp = nbottom;
		 nbottom -> next = end;

		 end -> nodeData = d_item;
		 end -> next = NULL;
		 end -> prev = temp;
		 nbottom = end;
	}
}

/*
	Delete or remove the top node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_top(){

	if(ntop != NULL){
		 if(ntop == nbottom){
				delete ntop;
				ntop = NULL;
				nbottom = NULL;

		 }
		 else{
			 Node* temp = ntop -> next;
			 delete ntop;
			 temp -> prev = NULL;
			 ntop = temp;
		 }
	}
}

/*
	Delete or remove the bottom node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_bottom(){
	if(nbottom != NULL){
		 if(ntop == nbottom){
				delete ntop;
				nbottom = NULL;
				ntop = NULL;
		 }
		 else{
				Node* temp = nbottom -> prev;
				delete nbottom;
				temp -> next = NULL;
				nbottom = temp;
		 }

	}
}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Search a node in the list that has data with the same name as the parameter.
	If one is found, return the pointer to the node.
	If one is not found, return NULL.
*/
Node* MList::search(Node* start, string name){

	if (start != NULL)
	{
		if(name.compare(start -> nodeData -> name)== 0)
		{
			return start;
		}
		else
		{
			Node * next_node = start -> next;
			return search(next_node,name);
		}
	}
	return NULL;
}


//Swapping node a with node b.
void MList::swapNode(Node* a, Node*b){

	if(a == b)
		 return;

	Node* tempPrevA = a -> prev;
	Node* tempNextA = a -> next;
	Node* tempPrevB = b -> prev;
	Node* tempNextB = b -> next;

	if (a == tempPrevB) {
		a -> prev = b;
		a -> next = tempNextB;

		b -> prev = tempPrevA;
		b -> next = a;

		if(tempPrevA != NULL)
			tempPrevA -> next = b;
		if(tempNextB != NULL)
			tempNextB -> prev = a;
		
	}
	else if (a == tempNextB) {
		a -> prev = tempPrevB;
		a -> next = b;

		b -> prev = a;
		b -> next = tempNextA;

		if(tempNextA != NULL)
			tempNextA -> prev = b;
		if(tempPrevB != NULL)
			tempPrevB -> next = a;
	}
	else {

		a -> prev = tempPrevB;
		a -> next = tempNextB;

		b -> prev = tempPrevA;
		b -> next = tempNextA;

		if(tempPrevA != NULL)
			tempPrevA -> next = b;
		if(tempNextA != NULL)
			tempNextA -> prev = b;
		if(tempPrevB != NULL)
			tempPrevB -> next = a;
		if(tempNextB != NULL)
			tempNextB -> prev = a;
	}
	if(a -> prev == NULL)
		 ntop = a;
	else if(b -> prev == NULL)
		 ntop = b;
	if(a -> next == NULL)
		 nbottom = a;
	else if(b -> next == NULL)
		 nbottom = b;

}

/*
	This function PERMANENTLY deletes a node from the list given a pointer to that node.
	You can assume that the node exists in the list - no need to search for the node.
*/
void MList::deleteNode(Node* a){

	Node* tempPrev = a -> prev;
	Node* tempNext = a -> next;
	delete a;

	if(tempPrev == NULL && tempNext == NULL) {
		ntop = NULL;
		nbottom = NULL;
		return;
	}
	if(tempPrev != NULL)
		 tempPrev -> next = tempNext;
	else{
		 tempNext -> prev = NULL;
		 ntop = tempNext;
	}
	if(tempNext != NULL)
		 tempNext -> prev = tempPrev;
	else{
		 tempPrev -> next = NULL;
		 nbottom = tempPrev;
	}

	return;
}

/*
	Unlike the delete function above, this function does NOT permanently delete the node.
	What you need to do at the last step is to set the node's prev and next pointers to NULL.
	Again, you can assume that the node exists in the list - no need to search for the node.
	Note: this function will be useful
		 when we want to insert the given node later at another position after you remove it from the list.
*/
void MList::removeNode(Node* a){

	if ( a == NULL)
		return;

	Node* tempPrev = a -> prev;
	Node* tempNext = a -> next;

	if(tempPrev == NULL && tempNext == NULL) {
		ntop = NULL;
		nbottom = NULL;
		return;
	}

	if(tempPrev != NULL)
		tempPrev -> next = tempNext;
	else{
		 tempNext -> prev = NULL;
		 ntop = tempNext;
	}
	if(tempNext != NULL)
		 tempNext -> prev = tempPrev;
	else{
		 tempPrev -> next = NULL;
		 nbottom = tempPrev;
	}

	a -> prev = NULL;
	a -> next = NULL;
	return;
}

/*
	Insert node a after node b.
	Note: b can be NULL, Q: what does that mean?
	otherwise, you can assume that b exists in the list.
*/
void MList::insertAfter(Node *a, Node* b){

	if(b == NULL){
		if(ntop == NULL){
			ntop = a;
			ntop -> next = NULL;
			ntop -> prev = NULL;
			nbottom = ntop;
		}
		else {
			ntop -> prev = a;
			a -> prev = NULL;
			a -> next = ntop;
			ntop = a;
		}

	}
	else {
		Node * tempNext = b->next;
		b->next = a;
		a->prev = b;
		a->next = tempNext;
		if(tempNext != NULL)
			tempNext -> prev = a;
		else
			nbottom = a;
	}
	return;
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Implement a SELECTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). if mode = true, sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number if mode = true
		 3). if mode = false, sort by size in ascending order (low->high)
	You can search any online resources available to you (i.e. search 'selection sort')
	to understand the basic idea behind the selection sort algorithm.
	Note: 
		 1). there can only be at most one loop in this function
		 2). this function is private
				see sortByNameSelection and sortBySizeSelection for the calls to this function
*/
void MList::sortSelection(Node* start, bool mode){

	if (start == NULL)
	return;
	Node * minNode = start;
	Node * curNode = start->next;
	Node * tempNext = start->next;
	while(curNode != NULL)
	{
	if(mode){
		string minstring = minNode -> nodeData -> name;
		if( minstring.compare(curNode -> nodeData -> name) > 0 )
			minNode = curNode;
	}
	else{
		if(minNode -> nodeData -> size > curNode -> nodeData -> size)
			minNode = curNode;
	}
	curNode = curNode -> next;
	}
	swapNode(start,minNode);
	sortSelection(tempNext,mode);

	return;
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Implement an INSERTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). we are trying to sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number.
	You can search any online resources available to you (i.e. search 'insertion sort')
	to understand the basic idea behind the insertion sort algorithm.
	The gif from the wikipedia page of this algorithm is the easiest to understand in my opinion
	Link: https://en.wikipedia.org/wiki/Insertion_sort
	Note: 
		 1). there can only be at most one loop in this function
		 2). this function is private, see sortByNameInsertion for the call to this function
*/
void MList::sortInsertion(Node* start){
	if (start == NULL)
	return;
	Node * curNode = ntop;
	Node * prevNode = NULL;
	Node * tempNext = start -> next;
	while(curNode != start){
	string curString = curNode -> nodeData -> name;
	if( curString.compare(start -> nodeData -> name) > 0)
	{
		removeNode(start);
		insertAfter(start,prevNode);
		break;
	}
	else
				prevNode = curNode;
		curNode = curNode -> next; 
	}
	sortInsertion(tempNext);
	return;
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the top.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, do

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):

		folder1 file1(0) folder2 file2(0)

	There should be no loop in this function
	See printBtT function for the call to this function.
	This function is private
*/
void MList::traverseToTop(Node* n, string delim){
	if (n != NULL)
	{
		if(n -> nodeData -> isFolder) {
			cout<<n -> nodeData -> name<<delim;
		}
		else {
			cout<<n -> nodeData -> name<<"("<<n -> nodeData -> size<<")"<<delim;
		}
		Node * next_node = n -> prev;
		traverseToTop(next_node,delim);
	}
	return;
}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the bottom.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, do

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):

		folder1 file1(0) folder2 file2(0)

	There should be no loop in this function
	See printTtB function for the call to this function.
	This function is private
*/
void MList::traverseToBottom(Node* n,string delim){
	if (n != NULL)
	{
		if(n -> nodeData -> isFolder) {
			cout<<n -> nodeData -> name<<delim;
		}
		else {
			cout<<n -> nodeData -> name<<"("<<n -> nodeData -> size<<")"<<delim;
		}
		Node * next_node = n -> next;
		traverseToBottom(next_node,delim);
	}
	return;
}

//------------------------------------------------------------------------------
//FUNCTIONS BELOW ARE COMPLETE, PLEASE DON'T CHANGE ANYTHING HERE
//------------------------------------------------------------------------------

//getting the pointer to the top node.
Node* MList::top(){
	return ntop;
}

//getting the pointer to the bottom node.
Node* MList::bottom(){
	return nbottom;
}

//call traverseToBottom to print all item in the list from bottom node to top node
//the list of items is separated by a given delimiter
void MList::printBtT(string delim){
	//create a temp pointer to hold bottom
	Node* tmp = nbottom;
	traverseToTop(tmp,delim);
}

//call traverseToBottom to print all item in the list from top node to bottom node
//the list of items is separated by a given delimiter
void MList::printTtB(string delim){
	Node* tmp = ntop;
	traverseToBottom(tmp,delim);
}

//call sortSelection function, mode = true = sort by name
//public member
void MList::sortByNameSelection(){
	bool mode = true;
	Node *tmp = ntop;
	sortSelection(tmp,mode);
}

//call sortSelection function, mode = false = sort by size
//public member
void MList::sortBySizeSelection(){
	bool mode = false;
	Node *tmp = ntop;
	sortSelection(tmp,mode);
}

//call sortInsertion function
//public member
void MList::sortByNameInsertion(){
	Node *tmp = ntop;
	sortInsertion(tmp);
}
