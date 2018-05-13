//Prims Algorithm Implementation//
//10/25/2017

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
class e_node { //stands for edge node
public:
	int nb;//the neighbor of a currently considered node
	int weight; //weight of the edge to the above neighbor
	e_node() {}//constructor
};
class rt_node { //rt stands for routing table
public:
	int cost;  //cost to a node
	int from;  //the from node to this node
	int checked;
	int h_pos; //the postion in heap for this node
	rt_node() { from = -1;  cost = 9999;  checked = 0; }
};

class h_node { //stands for heap_node
public:
	int id;
	int cost;
	h_node() { id = -1; cost = 9999; }
	h_node(int i, int j) { id = i; cost = j; }
	bool operator<(h_node h) { return (cost < h.cost); }
};

void set_up(vector<rt_node> &rt, vector<h_node> & heap, int &start); //Insert the souce node to heap and update rt and heap accordingly
void heap_adjust_up(vector<rt_node> &rt, vector<h_node> & heap, int &n);
void heap_adjust_down(vector<rt_node> & rt, vector<h_node> & heap);
void heap_op(vector<vector<e_node> > & graph, vector<rt_node> & rt, vector<h_node> &heap);

int main() {

	ifstream in("text1.txt");
	int start;

	int n, e; //n: num of nodes ; e: num of edges
	in >> n >> e;
	vector<e_node> ve;
	vector<vector<e_node> > graph(n, ve);
	e_node e1;
	e_node e2;
	int min = 999;
	int n1, n2, w;
	for (int i = 0; i < e; i++) {
		in >> n1 >> n2 >> w;
		e1.nb = n2;
		e1.weight = w;
		//checking for the minimum weight and setting its associated node as start
		if (min > w)
		{
			min = w;
			start = n1;
		}
		e2.nb = n1;
		e2.weight = w;
		//creating bidirectional graph
		graph[n1].push_back(e1);
		graph[n2].push_back(e2);
	}
	in.close();
	vector<rt_node> rt(n); //rt stands for routing table
	vector<h_node> heap(n);
	set_up(rt, heap, start);
	heap_op(graph, rt, heap);

	for (int i = 0; i < n; i++) {
		//if (rt[i].from != i)
		{

			cout << rt[i].from << " " << i << " " << rt[i].cost << endl;
		}

	}
	getchar();
	getchar();
	return 0;
}


void set_up(vector<rt_node> &rt, vector<h_node> & heap, int &start) {

	rt[start].from = start;
	rt[start].cost = 0;
	for (size_t i = 0; i < heap.size(); i++) {
		heap[i].id = i;
		rt[i].h_pos = i;
	}
	heap[start].id = 0;
	heap[0].id = start;
	heap[0].cost = 0;
	rt[0].h_pos = start;
	rt[start].h_pos = 0;
	for (size_t i = 0; i < heap.size(); i++) {
		heap[i].id = i;
		rt[i].h_pos = i;
	}
}



void heap_adjust_down(vector<rt_node> & rt, vector<h_node> & heap)
{
	int N = rt.size();
	for (int v = 0; v < N; v++)
	{
		if (v != 0 && (heap[v].cost < heap[v - 1].cost))
		{
			h_node temp = heap[v];
			heap[v] = heap[v - 1];
			heap[v - 1] = temp;
		}
	}
}

void heap_adjust_up(vector<rt_node> & rt, vector<h_node> & heap, int &n)
{
	int N = rt.size();
	for (int v = 0; v < N; v++)
	{
		if (v != 0 && (heap[v].cost < heap[v - 1].cost))
		{
			h_node temp = heap[v];
			heap[v] = heap[v - 1];
			heap[v - 1] = temp;
			//update info in routing table
			for (int rt_pos = 0; rt_pos < rt.size(); rt_pos++)
			{
				if (heap[v].id == rt_pos)
				{
					rt[rt_pos].h_pos = v;
				}
				if (heap[v - 1].id == rt_pos)
				{
					rt[rt_pos].h_pos = v - 1;
				}
			}
		}
	}
}

//function to check if edge from node exists
bool isValidEdge(vector<vector<e_node>> & graph, int m, int edge)
{
	vector<e_node> ve = graph[m];
	vector<e_node>::iterator itr = graph[m].begin();
	while (itr != graph[m].end())
	{
		if ((*itr).nb == edge)
		{
			return true;
		}
		++itr;
	}

	return false;
}

int getWeightToNodeAtIndex(vector<e_node> & node, int idx)
{
	vector<e_node>::iterator itr = node.begin();
	while (itr != node.end())
	{
		if ((*itr).nb == idx)
		{
			return (*itr).weight;
		}
		++itr;
	}
	return -1;
}

void heap_op(vector<vector<e_node>> & graph, vector<rt_node> & rt, vector<h_node> &heap)
{
	int N = rt.size();
	for (int count = 0; count < N; count++) // Find shortest path for all node
	{
		// Get mininum distance vertex
		int min = 9999, min_index;

		for (int v = 0; v < N; v++)
		{
			if (rt[v].checked == 0 && rt[v].cost <= min)
			{
				min = rt[v].cost;
				min_index = v;
			}
		}

		rt[min_index].checked = 1;

		heap_adjust_down(rt, heap);


		// Updating cost value of adjacent vertices 
		for (int v = 0; v <N; v++)

		{
			//update the routing table only when a valid edge exists and the current weight of the node is smaller than the value 
			//in routing table
			if ((!rt[v].checked && isValidEdge(graph, min_index, v) && ((getWeightToNodeAtIndex(graph[min_index], v))< rt[v].cost)))
			{
				rt[v].cost = (getWeightToNodeAtIndex(graph[min_index], v));

				rt[v].from = min_index;
				heap[v].cost = rt[v].cost;
				heap_adjust_up(rt, heap, v);
			}
		}
	}
}

