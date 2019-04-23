#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int minN_crossing;
set<int> s;

struct TreeNode {
	int index;
	int num_roads;
	int num_cameras;
	bool camera;
	TreeNode * father;
	vector <TreeNode*> children;
	TreeNode() : index(0), num_roads(1), camera(false), father(NULL), num_cameras(0) {}
	TreeNode(const int & root_index) : index(root_index), father(NULL), num_roads(1), camera(true), num_cameras(0) {}
	TreeNode(int & index, TreeNode * father) : index(index), father(father), num_roads(1), camera(false), num_cameras(0) {}
};

class Tree {
public:
	int size;
	TreeNode * root;

	Tree() : root(NULL), size(0) {}
	Tree(const int & root_index) : root(new TreeNode(root_index)), size(1) { }

	~Tree();

	void deleteSubTree(TreeNode * node);
	TreeNode * addNode(TreeNode * father, int & index);
	void preorder(TreeNode * n);
};

Tree::~Tree() {
	deleteSubTree(root);
	size = 0;
}

void Tree::deleteSubTree(TreeNode * node) {
	vector<TreeNode*>::iterator it = node->children.begin();
	while (it != node->children.end()) {
		deleteSubTree(*it);
		it++;
	}
	delete(node);
}

TreeNode * Tree::addNode(TreeNode * father, int & index) {
	TreeNode * newNode = new TreeNode(index, father);
	father->children.push_back(newNode);
	father->num_roads++;
	size++;
	return newNode;
}

void Tree::preorder(TreeNode * n) {
	vector<TreeNode*>::iterator it = n->children.begin();

	while (it != n->children.end()) {
		if ((*it)->father->camera == false && (*it)->num_roads >= minN_crossing) {
			(*it)->camera = true;
			s.insert((*it)->index);
		}
		else if ((*it)->father->camera == false && (*it)->father->num_cameras == 3) {
			(*it)->camera = true;
			s.insert((*it)->index);
		}
		else ((*it)->num_cameras) = (*it)->father->num_cameras + 1;
		
		preorder(*it);
		it++;
	}
}

int main() {
	int counter = 1;
        int n;
	cin >> n >> minN_crossing;
	
	int f, ch;

	Tree t(1);
	TreeNode ** tmp = new TreeNode*[n+1];

	while (counter < n) {
		cin >> f >> ch;
		if (f == 1) {
			tmp[ch] = t.addNode(t.root, ch);
		}
		else {
			tmp[ch] = t.addNode(tmp[f], ch);
		}
		counter++;
	}

	t.preorder(t.root);

	cout << "1" << " ";

	auto i = s.begin();
	while (i != s.end()) {
		cout << (*i) << " ";
		i++;
	}

	return 0;
}
