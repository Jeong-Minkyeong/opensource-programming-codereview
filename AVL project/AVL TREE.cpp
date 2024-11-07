#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
	Node(Node* par, int val) {
		this->parent = par;
		this->val;
	}
	
	Node* child;
	Node* parent;
	vector<Node*> childList;
	int val;
	int depth;
	int lion;
};