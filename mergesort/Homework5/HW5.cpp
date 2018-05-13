//HW5 CSE674
//Due: Sunday (Nov. 5) at 11:59PM
//Referrred to geeksforgeeks and careercup.com/question?id=15421981 for pseudocode
//You need to implement the following three functions
////void merge_sort(node * p, int i);
//void merge(node * p1, int i1, node * p2, int i2);
//void merge_sort(vector<int> &V);
//Read the requirements stated below.


#include <iostream>
#include <list>
#include <vector>
#include <assert.h> 
using namespace std;

class node {
public:
	int value;
	node * next;
	node() { next = nullptr; }
	node(int i) { value = i; next = nullptr; }
};


class linked_list {
public:
	int num_nodes;
	node * head;
	linked_list() { num_nodes = 0; head = nullptr; }
	void make_list(int k, int m);
	void print();

	//****************************************************************************************************************************************
	void merge_sort(node * p, int i);//Sort the portion (i nodes) of linked list beginning at the node pointed by p.
									 //You will implement the algoeithm using a recursive approach.
									 //In-place merge sort is required; that is, you are not allowed to create a separate linked list, etc. to perform sorting.
	void merge(node * p1, int i1, node * p2, int i2);
	//*******************************************************************************************************************************************
	//You need to also implement the following merge funciton, which
	//merges two already sorted porttion of linked list beginning at nodes pointed by p1 and p2, with sizes being i1 nodes and i2 nodes, respectively.
	//Assume that these two portions are adjacent.
	//That is, the last node of the first portion is immediately followed by the first node of the second portion.

};


void linked_list::make_list(int k, int m) {
	for (int i = 0; i < k; i++) {
		node * p = new node(rand() % m);
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
void printListdummy(node *head) {
	//cout << "printing list inside printlist" << endl;
	node* current = head;
	while (current != NULL) {

		printf("%d ", current->value);
		current = current->next;
	}
	printf("\n");

}

void linked_list::merge_sort(node * p, int i)
{
	//if linkedlist is empty or has just one node then return
	if (i == 0 || i == 1)
		return;
	node * lefthead = p;
	node * righthead = nullptr;
	int midpoint = i / 2;
	int rightlistlen = i - midpoint;
	//determining position of list two head after splitting
	int j = 0;
	righthead = p;
	while (j != midpoint)
	{
		righthead = righthead->next;
		j++;
	}
	merge_sort(lefthead, midpoint);
	merge_sort(righthead, rightlistlen);
	merge(lefthead, midpoint, righthead, rightlistlen);
}

void linked_list::merge(node * p1, int i1, node * p2, int i2)
{
	if (p1 == p2)
		return;
	node * currentptr = head;
	while (currentptr->next != p2)
	{
		currentptr = currentptr->next;
	}
	//prev pointer to list 2
	node *l2_ptr = currentptr;
	currentptr = head;
	int l1_count = 0;
	int l2_count = 0;
	if (p1->value < p2->value)
	{
		p1 = p1->next;
		l1_count++;
	}
	else {
		//Initially swapping only values
		swap(p1->value, p2->value);
		//adjusting pointers of linkedlist
		if (p1->next != p2)
		{
			l2_ptr->next = p2->next;
			p2->next = p1->next;
			p1->next = p2;
			p2 = l2_ptr->next;
			p1 = p1->next;
			l2_count++;
		}
		else
		{
			p1 = p1->next;
			p2 = p2->next;
			l2_count++;
		}
	}


	while (l1_count < i1 && l2_count < i2)
	{
		currentptr = head;
		while (currentptr->next != p2)
		{
			currentptr = currentptr->next;
		}
		l2_ptr = currentptr;
		currentptr = head;
		while (currentptr->next != p1)
		{
			currentptr = currentptr->next;
		}
		node *l1_ptr = currentptr;
		if (p1->value < p2->value)
		{
			p1 = p1->next;
			l1_count++;
		}
		else
		{
			l2_ptr->next = p2->next;
			l1_ptr->next = p2;
			p2->next = p1;
			p2 = l2_ptr->next;
			l2_count++;
		}
	}
}





void make_random_vector(vector<int> &V, int k, int m) {
	for (int i = 0; i < k; i++) V.push_back(rand() % m);
}

int min(int x, int y)
{
	return (x< y) ? x : y;
}

void merge(vector<int> &V, int l, int m, int r)
{
	int i, j, k;
	int sizen1 = m - l + 1;
	int sizen2 = r - m;

	//creating temporary vectors 
	vector<int> left_vec;
	vector<int> right_vec;

	//copying elements to vector
	for (int i = 0; i < sizen1; i++)
	{
		left_vec.push_back(V[l + i]);

	}

	for (int j = 0; j < sizen2; j++)
	{
		right_vec.push_back(V[m + 1 + j]);

	}

	//merging temp vector to V[l...r]
	i = 0; j = 0; k = l;
	while (i < sizen1 && j < sizen2)
	{
		if (left_vec[i] < right_vec[j])
		{
			V[k] = left_vec[i];
			i++;

		}
		else
		{
			V[k] = right_vec[j];
			j++;
		}
		k++;
	}

	while (i < sizen1)
	{
		V[k] = left_vec[i];
		i++;
		k++;
	}
	while (j < sizen2)
	{
		V[k] = right_vec[j];
		j++;
		k++;
	}

}
//***********************************************************************************************************************
void merge_sort(vector<int> &V)
//Using iterative (i.e., non_recursive) approach to implement merge sort.

//***********************************************************************************************************************
{
	//storing size of vector
	int size = V.size();
	int currentsize;
	int leftstart;
	for (currentsize = 1; currentsize < size; currentsize = 2 * currentsize)
	{
		for (leftstart = 0; leftstart < size; leftstart = leftstart + 2 * currentsize)
		{
			int mid = leftstart + (currentsize - 1);
			if (mid >= V.size())
			{
				mid = V.size() - 1;
			}

			int rightend = leftstart + ((2 * currentsize) - 1);
			if (rightend >= V.size())
			{
				rightend = V.size() - 1;
			}
			merge(V, leftstart, mid, rightend);

		}
	}
}
int main()
{

	vector<int> V;
	make_random_vector(V, 50, 40);
	cout << endl;
	for (size_t i = 0; i < V.size(); i++) cout << V[i] << " ";
	merge_sort(V);
	cout << endl;
	for (size_t i = 0; i < V.size(); i++) cout << V[i] << " ";
	linked_list L1;
	L1.make_list(30, 20);
	L1.print();
	L1.merge_sort(L1.head, L1.num_nodes);
	L1.print();

	getchar();
	getchar();
	return 0;
}

