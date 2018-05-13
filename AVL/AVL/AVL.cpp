//HW5  AVL Tree
//Due: Saturday (Nov. 18) at 11:59PM


#include <iostream> //to use cout
#include <algorithm> //to use max function such as  i = max(a, b);

using namespace std;

//You need to use the following node class for each node of the AVL tree
class node {
public:
	int value;
	int height;
	int child; //0: this node is a left child of its parent; 1: right child; -1 this node is the tree root
	node * parent;
	node * l_child;
	node * r_child;
	node() {}
	node(int i) { value = i; height = 1; parent = l_child = r_child = nullptr; }

};

class avl_tree {
public:
	node * root;
	avl_tree() {
		root = nullptr;
	}
	void add_node(int i);//You need to implement this.
	void in_order_traversal(node *p);  //provided.
	node * height_adjustment(node *p, int &pattern); //You need to implement this
													 /*
													 This function is invoked by add_node and remove_node.
													 p points to the first node that we need to check for possible height update.  We then need to check possible height update toward root.
													 All nodes whose heights need to be updated will be performed in this function.
													 If no imbalance is detected, the function returns nullptr.
													 If an imbalance is detected, the funciton returns the address of Action Node.
													 In addition, value of pattern will be set to 1, 2, 3, 4 for LL, LR, RL, RR pattern, respectively.
													 */






	void L_Rotate(node *p); //You need to implement this.
							//p points to the node around which the rotation will be performed.

	void R_Rotate(node *p); //You need to implement this.
							//p points to the node around which the rotation will be performed.

	void remove_node(int i);// You need to implement this.
							//Remove the node with value i.  Assume that all node values are distinct.


	node * replace(node * p1);

	/*
	This funciton is invoked by the remove_node.
	p1 points to the node to be removed.  The function returns the first node we need to check for possible height update after a node replcement.

	*/

	int height(node *N);
	int max(int a, int b);
	int getBalance(node *N);
};


int avl_tree::height(node * N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int avl_tree::max(int a, int b)
{
	return (a > b) ? a : b;

}

int avl_tree::getBalance(node * N)
{
	if (N == NULL)
		return 0;
	return height(N->l_child) - height(N->r_child);
}

void avl_tree::add_node(int i)
{
	node * newnode = new node(i);
	node * temp = root;
	node * back = NULL;
	node * ancestor;
	//if tree
	if (root == NULL)
	{
		root = newnode;
		newnode->child = -1;
		return;
	}
	while (temp != NULL)
	{
		back = temp;
		//marking the node which will be out of balance after inserting new node
		// if (temp->child != -1)
		// ancestor = temp;
		if (newnode->value < temp->value)
		{
			temp = temp->l_child;
		}
		else
			temp = temp->r_child;
	}

	//temp is null, back points to parent node to attach newnode to
	//ancestor points to recent out of balance node

	newnode->parent = back;
	if (newnode->value < back->value)
	{
		back->l_child = newnode;
		newnode->child = 0;
	}
	else
	{
		back->r_child = newnode;
		newnode->child = 1;
	}
	int pattern = 0;
	node * action_node = height_adjustment(newnode, pattern);
	node *heightptr = action_node;

	if (pattern == 1)
	{
		R_Rotate(action_node);

	}

	if (pattern == 2)
	{
		L_Rotate(action_node->l_child);
		R_Rotate(action_node);

	}

	if (pattern == 3)
	{

		R_Rotate(action_node->r_child);
		L_Rotate(action_node);

	}
	if (pattern == 4)
	{
		L_Rotate(action_node);

	}

	// root->height = 1 + max(height(root->l_child), height(root->r_child));
	// action_node = action_node->parent;

	// in_order_traversal(action_node);
	while (heightptr != NULL)
	{
		heightptr->height = 1 + max(height(heightptr->l_child), height(heightptr->r_child));
		heightptr = heightptr->parent;
	}


}

node * avl_tree::height_adjustment(node * p, int & pattern)
{
	node * q = p;
	while (q != NULL)
	{
		q->height = 1 + max(height(q->l_child), height(q->r_child));

		q = q->parent;
	}


	node * tempval = p;
	while (p != NULL)
	{
		//p->height = 1 + max(height(p->l_child), height(p->r_child));

		int balance = height(p->l_child) - height(p->r_child);

		//	cout << "Balalnce factor" <<balance<< endl;
		if (balance > 1 && tempval->value < p->l_child->value)

		{
			//	cout << "left left case" << endl;
			pattern = 1;
			return p;


		}


		if (balance > 1 && tempval->value > p->l_child->value)

		{

			//cout << "left right case" << endl;
			pattern = 2;
			return p;

		}

		if (balance < -1 && tempval->value < p->r_child->value)

		{
			//cout << "right left case" << endl;
			pattern = 3;
			return p;

		}


		if (balance < -1 && tempval->value > p->r_child->value)

		{
			//cout << "right right case" << endl;
			pattern = 4;
			return p;

		}

		p = p->parent;
	}
	return nullptr;

}
void avl_tree::L_Rotate(node * p)
{
	node *temp = p->r_child;   //Hold pointer to n's right child
	p->r_child = temp->l_child;      // Move temp 's left child to right child of n
	if (temp->l_child != NULL)      // If the left child does exist
		temp->l_child->parent = p;// Reset the left child's parent
	if (p->parent == NULL)       // If n was the root
	{
		root = temp;      // Make temp the new root
		temp->parent = NULL;   // Root has no parent
	}
	else if (p->parent->l_child == p) // If n was the left child of its' parent
		p->parent->l_child = temp;   // Make temp the new left child
	else               // If n was the right child of its' parent
		p->parent->r_child = temp;// Make temp the new right child
	temp->parent = p->parent;
	temp->l_child = p;         // Move n to left child of temp
	p->parent = temp;         // Reset n's parent
	p->height = max(height(p->l_child), height(p->r_child)) + 1;//updating height
	temp->height = max(height(temp->l_child), height(temp->r_child)) + 1;

}
void avl_tree::R_Rotate(node * p)
{
	node *temp = p->l_child;   //Hold poipter to temp
	p->l_child = temp->r_child;      // Move temp's right child to left child of n
	if (temp->r_child != NULL)      // If the right child does exist
		temp->r_child->parent = p;// Reset right child's parent
	if (p->parent == NULL)       // If p was root
	{
		root = temp;      // Make temp the root
		temp->parent = NULL;   // Root has no parent
	}
	else if (p->parent->l_child == p) // If was the left child of its' parent
		p->parent->l_child = temp;   // Make temp the new left child
	else               // If n was the r_child child of its' parent
		p->parent->r_child = temp;// Make temp the new r_child child
	temp->parent = p->parent;
	temp->r_child = p;         // Move n to right child of temp
	p->parent = temp;         // Reset n's parent
	p->height = max(height(p->l_child), height(p->r_child)) + 1;//updating heights
	temp->height = max(height(temp->l_child), height(temp->r_child)) + 1;
}
void avl_tree::remove_node(int i)
{
	node * back = NULL;
	node * temp;
	node * delNode;//node to delete
	node * storeval;
	temp = root;
	//finding the element
	while (temp != NULL && i != temp->value)
	{
		back = temp;
		if (i < temp->value)
		{
			temp = temp->l_child;
		}
		else
			temp = temp->r_child;
	}

	if (temp == NULL)
	{
		//elememnt not found;
		//	cout << "No element" << endl;
		return;
	}
	else
	{
		if (temp == root) //if deleting node is root
		{
			delNode = root;
			delNode->parent = NULL;
		}
		else
		{
			delNode = temp;
			delNode->parent = back;
		}
	}

	//case 1 : no child or one child
	if (delNode->r_child == NULL)
	{
		if (delNode->parent == NULL) //if root
		{
			root = delNode->l_child;
			storeval = delNode->parent; //saving parent pointer
			free(delNode);
			node * t1 = replace(storeval);
			return;
		}
		else
			if (delNode->parent->l_child == delNode)
				delNode->parent->l_child = delNode->l_child;
			else
				delNode->parent->r_child = delNode->l_child;
		storeval = delNode->parent;
		free(delNode);
		node * t1 = replace(storeval);
		return;
	}

	else //atleast one child exists
	{
		if (delNode->l_child == NULL)
		{
			if (delNode->parent == NULL)
			{
				root = delNode->r_child;
				storeval = delNode->parent;
				free(delNode);
				node * t1 = replace(storeval);
				return;
			}
			else
			{
				if (delNode->parent->l_child == delNode)
				{
					delNode->parent->l_child = delNode->r_child;

				}
				else
					delNode->parent->r_child = delNode->r_child;
				storeval = delNode->parent;
				free(delNode);
				node * t1 = replace(storeval);
				return;
			}

		}

		//deleting nodes with 2 children
		//largest value on the left is used to replace
		temp = delNode->l_child;
		temp->parent = delNode;
		back = delNode;
		while (temp->r_child != NULL)
		{
			back = temp;
			//temp->parent = back;
			temp = temp->r_child;
		}
		delNode->value = temp->value;
		temp->parent = back;
		storeval = back;
		if (back == delNode)
			back->l_child = temp->l_child;
		else
			back->r_child = temp->l_child;
		//storing parent
		free(temp);
		node * t1 = replace(storeval);
		return;

	}

}


node * avl_tree::replace(node * p1)
{
	node * dummy = p1;
	while (dummy != NULL)
	{
		dummy->height = 1 + max(height(dummy->l_child), height(dummy->r_child));

		dummy = dummy->parent;
	}

	node * temp = p1;
	node * heightptr = p1;

	while (p1 != NULL)
	{
		int balance = height(p1->l_child) - height(p1->r_child);


		if (balance > 1 && getBalance(p1->l_child) >= 0)
		{
			R_Rotate(p1);
			return 0;
		}

		if (balance > 1 && getBalance(p1->l_child) <0)
		{
			L_Rotate(p1->l_child);
			R_Rotate(p1);
			return 0;
		}

		if (balance < -1 && getBalance(p1->r_child) <= 0)
		{
			L_Rotate(p1);
			return 0;
		}

		if (balance < -1 && getBalance(temp->r_child)>0)
		{
			R_Rotate(p1->r_child);
			L_Rotate(p1);
			return 0;
		}

		p1 = p1->parent;
	}

	return nullptr;
}
void avl_tree::in_order_traversal(node * p) {
	if (p == nullptr)  return;
	in_order_traversal(p->l_child);
	cout << "value = " << p->value << " " << "height = " << p->height << "   ";
	in_order_traversal(p->r_child);
}


int main() {
	avl_tree t1;
	t1.add_node(45);
	t1.in_order_traversal(t1.root);
	t1.remove_node(45);
	t1.in_order_traversal(t1.root);
	t1.add_node(50);
	t1.add_node(47);
	t1.add_node(30);
	t1.add_node(35);
	t1.in_order_traversal(t1.root);
	t1.remove_node(47);
	t1.in_order_traversal(t1.root);
	getchar();
	getchar();
	return 0;
}



