//HW2: Sparse Matrix Operation -- Applicaiton of 2-D linked lists  
//by C-Y (Roger) Chen
//Due:  11:59pm, Wed. September 27
//Implement the following three member functions for the class my_matrix:
//add_node, operator+, operator*
//Do not change the main function and the my_matrix::print function

#include <iostream>
#include <vector>
using namespace std;

class node {
public:
	int value;
	int r_position;
	int c_position;
	node * r_next;
	node * c_next;
	node() { value = -9999; r_position = c_position = -1; r_next = c_next = nullptr; }
	node(int v, int r, int c) { value = v; r_position = r; c_position = c; r_next = c_next = nullptr; }

};
class my_matrix {
public:
	int num_rows;
	int num_cols;
	vector<node *> r_vec;
	vector<node *> c_vec;


	my_matrix() {}
	my_matrix(int r, int c);
	//Initialize a matrix of rows and c cols.

	my_matrix(int r, int c, int n, int k);
	//Initializa a matrix of r rows, c cols, n nodes, with values randomly in - (k-1) ... (k-1);
	void print(); //print value, r_position, and c_position of all matrix elements in row-oriented manner


				  //Implement the following three member functions:
	
	void add_node(int v, int r, int c);
	//Create a new node with value v at row r and col c.
	//If there already exists an element at this position, then just update the node
	//value at this position to v, and do not create a new node.

	my_matrix operator+(my_matrix M);//matrix addition

	my_matrix operator*(my_matrix M); //matrix multiplication


};

my_matrix::my_matrix(int r, int c) {
	num_rows = r;
	num_cols = c;
	r_vec.resize(r, nullptr);
	c_vec.resize(c, nullptr);
}


my_matrix::my_matrix(int r, int c, int n, int k) {
	num_rows = r;
	num_cols = c;
	r_vec.resize(r, nullptr);
	c_vec.resize(c, nullptr);
	for (int i = 0; i < n; i++) {
		int vv = rand() % (2 * k - 1) - (k - 1);
		int rr = rand() % r;
		int cc = rand() % c;
		add_node(vv, rr, cc);
		
	}
	
	
}



void my_matrix::print() {
	cout << endl;
	cout << "Printing" << endl;
	for (int i = 0; i < num_rows; i++) {
		node * p = r_vec[i];
		cout << endl;
		while (p != nullptr) {
			cout << p->value << " " << p->r_position << " " << p->c_position << "  ";
			p = p->r_next;
		}
	}
}

void my_matrix::add_node(int value, int row, int col)
{
	//initializing location pointers
	node *lead = new node(value, row, col);
	node *pre_point_r = nullptr;
	node *point_r = nullptr;
	node *pre_point_c = nullptr;
	node *point_c = nullptr;
	//Delete node if value=0
	if (value == 0)
	{
		node *lead = new node(value, row, col);
		node *pre_point_r = nullptr;
		node *point_r = nullptr;
		node *pre_point_c = nullptr;
		node *point_c = nullptr;
		pre_point_r = r_vec[row];		
	if (pre_point_r == nullptr)return;
		if(pre_point_r->r_next==nullptr&&(pre_point_r->r_position == row && pre_point_r->c_position == col))
			//if head node
		{
				r_vec[row] = nullptr;
				free(pre_point_r);
				return;
			
		}
		//traverse the linklist to find the node
		while (pre_point_r != NULL)
		{
			
			
			if (pre_point_r->c_position == col && pre_point_r->r_position == row)
			{
				if (point_r != nullptr)
				{
					point_r->r_next = pre_point_r->r_next;
					free(pre_point_r);
					return;
				}

			}
			point_r = pre_point_r;
			pre_point_r = pre_point_r->r_next;			
			
		}	
		
		//Logic for column pointers
		pre_point_c = c_vec[col];
		if (pre_point_c == nullptr)return;
		if (pre_point_c->c_next == nullptr && (pre_point_c->r_position == row && pre_point_c->c_position == col))

		{
			c_vec[col] = nullptr;
			free(pre_point_c);
			return;

		}
	
	}
//if value is not zero, add a node		
	//logic for rowpointers
	{
		if (r_vec[row] == NULL)//for headnode
			r_vec[row] = lead;
		
		else
		{//traversing the linkedlist to add the node
			pre_point_r = r_vec[row];
			while ((pre_point_r->r_next != NULL) && (pre_point_r->c_position < col))
			{
				point_r = pre_point_r;
				pre_point_r = pre_point_r->r_next;
			}
			if (pre_point_r->c_position > col)
			{
				lead->r_next = pre_point_r;
				if (r_vec[row] == pre_point_r)
				{
					r_vec[row] = lead;
				}
				else {
					point_r->r_next = lead;
				}

			}
			if (pre_point_r->c_position == col)
			{
				pre_point_r->value = value;
			}

			if (pre_point_r->c_position < col && pre_point_r->r_next == nullptr)
			{
				pre_point_r->r_next = lead;
			}
		}
		//logic for column pointers
			if (c_vec[col] == NULL)
				c_vec[col] = lead;
			else
			{
				pre_point_c = c_vec[col];
				while ((pre_point_c->c_next != NULL) && (pre_point_c->r_position<col))
				{
					point_c= pre_point_c;
					pre_point_c = pre_point_c->c_next;
				}
				if (pre_point_c->r_position>row)
				{
					lead->c_next = pre_point_c;
					if (c_vec[col] == pre_point_c)
					{
						c_vec[col] = lead;
					}
					else {
						point_c->c_next = lead;
					}

				}
				if (pre_point_c->r_position == row)
				{
					pre_point_c->value = value;
				}

				if (pre_point_c->r_position < row && pre_point_c->c_next == nullptr)
				{
					pre_point_c->c_next = lead;
				}

			}		
	}
}


my_matrix  my_matrix:: operator+(my_matrix M)
{
	node * p = nullptr;
	node *q = nullptr;
	my_matrix Mtemp(this->num_rows, this->num_cols);
	
	for (int i = 0; i < num_rows; i++)
	
	{
		int sum = 0;
		for (int j = 0; j < num_cols; j++)
		{
			if (r_vec[i] != nullptr)
			{
				p = r_vec[i];
				while (p!=NULL)
				
				{
					if (p->r_position == i && p->c_position == j)//adding data when co-ordinates match
						sum = sum + p->value;
					p = p->r_next;

				}
			}
			if (M.r_vec[i] != NULL)
			{
				q = M.r_vec[i];
				while (q != NULL)
				{
					if (q->r_position == i && q->c_position == j)
					
						sum = sum + q->value;
						q = q->r_next;
					
				}
			}
			
			if (sum != 0)
				Mtemp.add_node(sum, i, j);// adding to the matrix
			sum = 0;
		}
		
	}
	
	return Mtemp;
}


my_matrix  my_matrix:: operator*(my_matrix M)
{

	node * p = nullptr;
	node *q = nullptr;
	my_matrix Mtemp(this->num_rows, this->num_cols);
	if (this->num_cols != M.num_rows)
	{
		cout << "Invalid data" << endl;
		return Mtemp;
	}
	for (int i = 0; i < num_rows; i++)
	{
		if (r_vec[i] != NULL) {
			for (int j = 0; j < num_cols; j++)
			{

				int sum = 0;
				p = r_vec[i];
				
					while (p != NULL)
					{
						q = M.c_vec[j];
						while (q != NULL)
						{
							if (p->r_position == q->c_position)
								sum = sum + (p->value*q->value);
							q = q->c_next;

						}
						p = p->r_next;
					}
				
				if (sum != 0)
					Mtemp.add_node(sum, i, j);
				sum = 0;
			}
		}
	}
	return Mtemp;
}



 
int main() {
	my_matrix M1(7, 5, 11, 8), M2(7, 5, 10, 8), M3(7, 5), M4(5, 6, 13, 9), M5(7, 6);
	M1.print();
	M2.print();
	M3 = M1 + M2;
	M3.print();
	M1.print();
	M4.print();
	M5 = M1 * M4;
	M5.print();
	getchar();
	getchar();
	return 0;
}

