#include<iostream>
using namespace std;
typedef struct Node* ptr;
ptr root = NULL;
int COUNT = 10;
struct Node {
	int data;
	ptr left;
	ptr right;
};
void print(ptr root, int space) {
	if (root == NULL)
		return;
	space += COUNT;
	print(root->right, space);
	cout << endl;
	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->data << "\n";
	print(root->left, space);
}
void BST(int x) {
	ptr loc = root, insert = root;
	if (root == NULL) {
		root = new Node;
		root->data = x;
		root->left = NULL;
		root->right = NULL;
	}
	else {
		while (loc != NULL && loc->data != x)
		{
			insert = loc;
			if (x > loc->data) {
				loc = loc->right;
			}
			else {
				loc = loc->left;
			}
		}
		if (loc != NULL) {
			cout << "има го" << endl;
		}
		else {
			loc = new Node;
			loc->data = x;
			loc->left = NULL;
			loc->right = NULL;
			if (x > insert->data) {
				insert->right = loc;
			}
			else {
				insert->left = loc;
			}
		}
	}
}
void righOfTheLefts(ptr& father, ptr& fatherToRemove, ptr help, ptr& toReplace) {
	toReplace = new Node;
	bool list = false;
	if (help->left == NULL && help->right == NULL) {
		toReplace->data = help->data;
		toReplace->left = NULL;
		toReplace->right = fatherToRemove->right;
		delete help;
		help = NULL;
	}
	else {
		while (help->right != NULL) {
			fatherToRemove = help;
			help = help->right;
		}
		if (help->left == NULL) {
			list = true;
		}
		if (list && fatherToRemove == root) {
			toReplace->data = help->data;
			fatherToRemove->left = NULL;
			delete help;
			help = NULL;
		}
		else if (list) {
			toReplace->data = help->data;
			fatherToRemove->right = NULL;
			toReplace->left = father->left;
			toReplace->right = father->right;
			delete help;
			help = NULL;
		}
		else {
			fatherToRemove->left = help->left;
			toReplace->data = help->data;
			toReplace->left = help->left;
			toReplace->right = help->right;
			delete help;
			help = NULL;
		}
	}
}
void leftOfTheRights(ptr& father, ptr& help, ptr& toReplace) {
	toReplace = new Node;
	bool list = false;
	while (help->left != NULL) {
		father = help;
		help = help->left;
	}
	if (help->right == NULL) {
		list = true;
	}
	if (list && father == root) {
		toReplace->data = help->data;
		father->right = NULL;
		delete help;
		help = NULL;
	}
	else if (list) {
		toReplace->data = help->data;
		toReplace->left = NULL;
		toReplace->right = NULL;
		father->left = NULL;
		father->right == NULL;
		delete help;
		help = NULL;
	}
	else {
		father->left = help->right;
		toReplace->data = help->data;
		toReplace->right = help->right;
		toReplace->left = help->left;
		delete help;
		help = NULL;
	}
	cout << "TOREPLACE + " << toReplace->data << endl;
}
void cutNode(int x) {
	ptr loc = root, father = root, toReplace = NULL, toRemove = NULL;
	while (loc != NULL && loc->data != x) {
		father = loc;
		if (x > loc->data) {
			loc = loc->right;
		}
		else {
			loc = loc->left;
		}
	}
	if (loc == NULL) {
		cout << "there isnt" << endl;
	}
	else {
		toRemove = loc;
		if (loc->left == NULL && loc->right == NULL) {
			delete loc;
			loc = NULL;
			if (x > father->data) {
				father->right = NULL;
			}
			else {
				father->left = NULL;
			}
		}
		else if (loc->left != NULL) {
			if (x > root->data && father == root) {
				righOfTheLefts(father->right, loc, loc->left, toReplace);
			}
			else if (x < root->data) {
				righOfTheLefts(father->left, loc, loc->left, toReplace);
			}
			else {
				righOfTheLefts(father, loc, loc->left, toReplace);
			}
			cout << "toReplace = " << toReplace->data << endl;
			//toReplace->left = loc->left;
			//toReplace->right = loc->right;
			if (x > father->data) {
				father->right = toReplace;
			}
			else if (x < father->data) {
				father->left = toReplace;
			}
			else {
				root = toReplace;
			}
			//delete loc;
			//loc = NULL;
		}
		else if (loc->right != NULL) {
			leftOfTheRights(loc, loc->right, toReplace);
			toReplace->left = loc->left;
			toReplace->right = loc->right;
			if (x > father->data) {
				father->right = toReplace;
			}
			else if (x < father->data) {
				father->left = toReplace;
			}
			else {
				root = toReplace;
			}
			delete loc;
			loc = NULL;
		}
	}
}
int main() {
	setlocale(LC_ALL, "BULGARIAN");
	int x;
	int arr[15] = { 20,9,3,1,8,14,11,16,44,33,21,34,58,52,61 };
	for (int i = 0; i < 15; i++) {
		BST(arr[i]);
	}
	print(root, 10);
	cout << "Enter 5 numbers for removing from tree" << endl;
	for (int i = 0; i < 5; i++) {
		cin >> x;
		cutNode(x);
		print(root, 10);
	}
	return 0;
}