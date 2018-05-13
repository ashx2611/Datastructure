//HW1
//Implement the three member functions of linked_list class: bubble-sort, selection-sort, and insertion-sort.
//as described in the code blow
//Due: 11:59pm, Friday, September 15
//Submit a text vesion of your program to blackboard

//Linked List Examples by C-Y (Roger) Chen, Syracuse University

#include <iostream>
using namespace std;

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
	void print(); //Print values of all nodes from head node

	void reverse(); //Reverse the order of nodes of linked list	
					//void remove_all(int k); //Remove all nodes whose node values are k
					//void insert(int k); //create a new node with value k and insert it to an already sorted list. After the insert, the linked list is still sorted.


					//*********************
					//Implement the following member functions.  

	void bubble_sort(); //Bubble-Sort the nodes, based on ascending order of node values
	void swap(node * leftval, node * rightval); //Function to swap two nodes
	void selection_sort(); //Selection-Sort the nodes, based on ascending order of node values
	void insertion_sort(); //Insert - Sort the nodes, based on ascending order of node values
	
	

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

void linked_list::print() {
	node * p = head;
	cout << endl;
	while (p != nullptr) {
		cout << p->value << " ";
		p = p->next;
	}
	cout << endl;
}

void linked_list::reverse() {
	if (num_nodes <= 1) return;
	node * p1 = head, *p2 = head->next, *p3;
	while (p2 != nullptr) {
		p3 = p2->next;
		p2->next = p1;
		if (p1 == head) p1->next = nullptr;
		p1 = p2;
		p2 = p3;
	}
	head = p1;
}

void linked_list::bubble_sort()
{
	if (head == nullptr || head->next == nullptr)

	{
		cout <<"\n"<< "Only one node present";
		return;
	}
	//Declaring position pointers to track the nodes
	node *currposition;
	node *nextposition;

	
	for (currposition = head; currposition->next != nullptr; currposition = currposition->next)
	{
		for (nextposition = currposition->next; nextposition != nullptr; nextposition = nextposition->next)
		{
			if (currposition->value > nextposition->value)// for acsending order sorting
			{
				swap(currposition, nextposition);
			}
		}
	}

	cout << "\n"<<"The Sorted list using bubblesort method is" << endl;
}

void linked_list::swap(node * leftval, node * rightval)
{
	//function to swap values in linkedlist
	int temp = rightval->value;
	rightval->value = leftval->value;
	leftval->value = temp;
	
}


void linked_list::insertion_sort()
{

	node * temp = head;
	node * currposition = head->next;//node currently compared
	node * prevposition = head;//node previous to current node
	if (head == nullptr || head->next == nullptr)
		return;
	while ( currposition != nullptr )
		
	{
		//if current node is larger than or equal to the elemnt in the assumed sorted list
		//We just move ahead as no sorting is required
		if (prevposition->value <= currposition->value)
		{
			currposition = currposition->next;
			prevposition = prevposition->next;		
			
		}
		else
		{
			//If element is smaller than head 
			if (head->value > currposition->value)
				// the current element will be placed at the start of list
			{
				prevposition->next = currposition->next;
				currposition->next = head;
				head = currposition;
				
			}
			else
			{
				temp = head;
				while (temp->next != nullptr&&temp->next->value < currposition->value)
				{
					temp = temp->next;

				}
				prevposition->next = currposition->next;
				currposition->next = temp->next;
				temp->next = currposition;
			}
		}
		currposition = prevposition->next;
	}

	cout << "\n" << "The Sorted list using insertionsort method is" << endl;
	
}

void linked_list::selection_sort()
{
	//position pointers to track elements in the list
	node * currpositon = head->next;
	node * prevposition = head;
	node * minptr;
	if (head == nullptr || head->next == nullptr)
		return;
	for (prevposition = head; prevposition->next != nullptr; prevposition = prevposition->next)
	{
		minptr = prevposition;
		for (currpositon = prevposition->next; currpositon != nullptr; currpositon = currpositon->next)
		{
			if (currpositon->value < minptr->value)
			{
				minptr = currpositon;
			}
		}
		int temp = minptr->value;
		minptr->value = prevposition->value;
		prevposition->value = temp;


	}
	cout << "\n" << "The Sorted list using selectionsort method is" << endl;

}


int main() {

	//Some examples of tests for your program are given below
	//During grading, other test cases will also be used
	linked_list L1;
	L1.make_random_list(5);
	L1.print();
	L1.bubble_sort();
	L1.print();

	linked_list L2;
	L2.make_random_list(5);
	L2.print();
	L2.selection_sort();
	L2.print();

	linked_list L3;
	L3.make_random_list(5);
	L3.print();
	L3.insertion_sort();
	L3.print();

	getchar();
	getchar();
	return 0;
}