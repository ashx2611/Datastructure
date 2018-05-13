//HW1
//Implement the three member functions of linked_list class: sort, remove_all, and insert
//as described in the code blow
//Due: 11:59pm, Friday, September 8
//Submit a text vesion of your program to blackboard

//Linked List Examples by C-Y (Roger) Chen, Syracuse University
#include <fstream>
#include <iostream>
//#include <time.h>
using namespace std;

ofstream out("data1.txt");

class node {
public:
	int value;
	node * next;
	node() { next = nullptr; }
	node(int k) { value = k; next = nullptr; }
};

class linked_list {
public:
	int num_nodes;
	node * head;
	linked_list() { num_nodes = 0; head = nullptr; }
	void make_random_list(int k);//create a linked list of 
								 //k nodes with values in 0 ..99 randomly

	void new_make_random_list(int k, int m);//create a linked list of 
											//k nodes with values in 0 .. m randomly

	void print(); //Print values of all nodes from head node



	void selection_sort(); //Sort the nodes, based on ascending order of node values


	void bubble_sort();
	void insertion_sort();

};
void linked_list::make_random_list(int k) {
	node * p;
	for (int i = 0; i < k; i++) {
		p = new node(rand() % 100);
		p->next = head;
		head = p;
		num_nodes++;
	}

}

void linked_list::new_make_random_list(int k, int m) {
	node * p;
	for (int i = 0; i < k; i++) {
		p = new node(rand() % m);
		p->next = head;
		head = p;
		num_nodes++;
	}

}



void linked_list::print() {
	node * p = head;
	out << endl;
	while (p != nullptr) {
		out << p->value << " ";
		p = p->next;
	}
}



void linked_list::selection_sort() {

}


void linked_list::bubble_sort() {
	out << "Wrting blah blah";
}

void linked_list::insertion_sort() {

}

int main() {

	//Some examples of tests for your program are given below
	//During grading, other test cases will also be used

	linked_list L1;
	L1.make_random_list(70);
	L1.print();
	L1.bubble_sort();
	L1.print();

	cout << endl;

	linked_list L2;
	L2.make_random_list(70);
	L2.print();
	L2.selection_sort();
	L2.print();

	cout << endl;

	linked_list L3;
	L3.make_random_list(70);
	L3.print();
	L3.insertion_sort();
	L3.print();

	out.close();
	return 0;

}