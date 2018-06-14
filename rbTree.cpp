// rbTree.cpp: 主项目文件。

#include "stdafx.h"
#include <iostream>
#include <string>
#define BLACK 0
#define RED 1

using namespace std;

class rbTree
{
	private:
		struct binaryTree{
			binaryTree *parent;
			binaryTree *leftSon;
			binaryTree *rightSon;
			double key;
			unsigned short color;
		}*root;

		void rbLeftRotate(binaryTree *node){
			binaryTree *y = node->rightSon;
			node->rightSon = y->leftSon;
			if (y->leftSon != nullptr){
				y->leftSon->parent = node;
			}
			y->parent = node->parent;
			if (node->parent == nullptr){
				root = y;
			}
			else if (node == node->parent->leftSon){
				node->parent->leftSon = y;
			}
			else{
				node->parent->rightSon = y;
			}
			y->leftSon = node;
			node->parent = y;
			return;
		}

		void rbRightRotate(binaryTree *node){
			binaryTree *y = node->leftSon;
			node->leftSon = y->rightSon;
			if (y->rightSon != nullptr){
				y->rightSon->parent = node;
			}
			y->parent = node->parent;
			if (node->parent == nullptr){
				root = y;
			}
			else if (node == node->parent->rightSon){
				node->parent->rightSon = y;
			}
			else{
				node->parent->leftSon = y;
			}
			y->rightSon = node;
			node->parent = y;
			return;
		}

		void rbInsertFixUp(binaryTree *node){
			binaryTree *y;
			if ((node == root) || (node->parent == root)){
				if (node == root){
					node->color = BLACK;
				}
				return;
			}
			while (node->parent->color == RED){
				if (node->parent == node->parent->parent->leftSon){
					y = node->parent->parent->rightSon;
					unsigned int flag = 0;
					if (y != nullptr){
						if (y->color == RED){
							flag++;
						}
					}
					if (flag){
						node->parent->color = BLACK;
						y->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else{
						if (node == node->parent->rightSon){
							node = node->parent;
							rbLeftRotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						rbRightRotate(node->parent->parent);
					}
				}
				else{
					y = node->parent->parent->leftSon;
					unsigned int flag = 0;
					if (y != nullptr){
						if (y->color == RED){
							flag++;
						}
					}
					if (flag){
						node->parent->color = BLACK;
						y->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else{
						if (node == node->parent->leftSon){
							node = node->parent;
							rbRightRotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						rbLeftRotate(node->parent->parent);
					}
				}
				if ((node == root) || (node->parent == root)){
					if (node == root){
						node->color = BLACK;
					}
					return;
				}
			}
			return;
		}

		void rbDeleteFixUp(binaryTree *node, binaryTree *ifNull){
			binaryTree *temp;
			if (node == nullptr){
				if (ifNull == nullptr){
					return;
				}
				temp = new(binaryTree);
				temp->parent = ifNull;
				temp->color = BLACK;
				node = temp;
				if (ifNull->leftSon == nullptr){
					ifNull->leftSon = temp;
				}
				else{
					ifNull->rightSon = temp;
				}
			}
			while ((node != root) && (node->color == BLACK)){
				if (node == node->parent->leftSon){
					binaryTree *w = node->parent->rightSon;
					binaryTree *wLeftSon, *wRightSon;
					if (w->color == RED){
						w->color = BLACK;
						node->parent->color = RED;
						rbLeftRotate(node->parent);
						w = node->parent->rightSon;
					}
					if (w->leftSon == nullptr){
						wLeftSon = new(binaryTree);
						wLeftSon->parent = w;
						wLeftSon->color = BLACK;
						w->leftSon = wLeftSon;
					}
					if (w->rightSon == nullptr){
						wRightSon = new(binaryTree);
						wRightSon->parent = w;
						wRightSon->color = BLACK;
						w->rightSon = wRightSon;
					}
					if ((w->leftSon->color == BLACK) && (w->rightSon->color == BLACK)){
						w->color = RED;
						node = node->parent;
					}
					else{
						if (w->rightSon->color == BLACK){
							w->leftSon->color = BLACK;
							w->color = RED;
							if (wLeftSon != nullptr){
								delete(wLeftSon);
								wLeftSon = w->leftSon = nullptr;
							}
							if (wRightSon != nullptr){
								delete(wRightSon);
								wRightSon = w->rightSon = nullptr;
							}
							rbRightRotate(w);
							w = node->parent->rightSon;
						}
						if (w->leftSon == nullptr){
							wLeftSon = new(binaryTree);
							wLeftSon->parent = w;
							wLeftSon->color = BLACK;
							w->leftSon = wLeftSon;
						}
						if (w->rightSon == nullptr){
							wRightSon = new(binaryTree);
							wRightSon->parent = w;
							wRightSon->color = BLACK;
							w->rightSon = wRightSon;
						}
						w->color = w->parent->color;
						w->parent->color = BLACK;
						w->rightSon->color = BLACK;
						if (wLeftSon != nullptr){
							delete(wLeftSon);
							wLeftSon = w->leftSon = nullptr;
						}
						if (wRightSon != nullptr){
							delete(wRightSon);
							wRightSon = w->rightSon = nullptr;
						}
						rbLeftRotate(node->parent);
						node = root;
					}
					if (wLeftSon != nullptr){
						delete(wLeftSon);
						wLeftSon = w->leftSon = nullptr;
					}
					if (wRightSon != nullptr){
						delete(wRightSon);
						wRightSon = w->rightSon = nullptr;
					}
				}
				else{
					binaryTree *w = node->parent->leftSon;
					binaryTree *wLeftSon, *wRightSon;
					if (w->color == RED){
						w->color = BLACK;
						node->parent->color = RED;
						rbRightRotate(node->parent);
						w = node->parent->leftSon;
					}
					if (w->leftSon == nullptr){
						wLeftSon = new(binaryTree);
						wLeftSon->parent = w;
						wLeftSon->color = BLACK;
						w->leftSon = wLeftSon;
					}
					if (w->rightSon == nullptr){
						wRightSon = new(binaryTree);
						wRightSon->parent = w;
						wRightSon->color = BLACK;
						w->rightSon = wRightSon;
					}
					if ((w->rightSon->color == BLACK) && (w->leftSon->color == BLACK)){
						w->color = RED;
						node = node->parent;
					}
					else{
						if (w->leftSon->color == BLACK){
							w->rightSon->color = BLACK;
							w->color = RED;
							if (wLeftSon != nullptr){
								delete(wLeftSon);
								wLeftSon = w->leftSon = nullptr;
							}
							if (wRightSon != nullptr){
								delete(wRightSon);
								wRightSon = w->rightSon = nullptr;
							}
							rbLeftRotate(w);
							w = node->parent->leftSon;
						}
						if (w->leftSon == nullptr){
							wLeftSon = new(binaryTree);
							wLeftSon->parent = w;
							wLeftSon->color = BLACK;
							w->leftSon = wLeftSon;
						}
						if (w->rightSon == nullptr){
							wRightSon = new(binaryTree);
							wRightSon->parent = w;
							wRightSon->color = BLACK;
							w->rightSon = wRightSon;
						}
						w->color = w->parent->color;
						w->parent->color = BLACK;
						w->leftSon->color = BLACK;
						if (wLeftSon != nullptr){
							delete(wLeftSon);
							wLeftSon = w->leftSon = nullptr;
						}
						if (wRightSon != nullptr){
							delete(wRightSon);
							wRightSon = w->rightSon = nullptr;
						}
						rbRightRotate(node->parent);
						node = root;
					}
					if (wLeftSon != nullptr){
						delete(wLeftSon);
						wLeftSon = w->leftSon = nullptr;
					}
					if (wRightSon != nullptr){
						delete(wRightSon);
						wRightSon = w->rightSon = nullptr;
					}
				}
			}
			node->color = BLACK;
			if (temp != nullptr){
				if (temp == temp->parent->leftSon){
					temp->parent->leftSon = nullptr;
				}
				else{
					temp->parent->rightSon = nullptr;
				}
				delete(temp);
				temp = nullptr;
			}
			return;
		}

		string rbGetPrintTree(binaryTree *node){
			string lson, rson;
			if (node->leftSon != nullptr){
				lson = rbGetPrintTree(node->leftSon);
			}
			if (node->rightSon != nullptr){
				rson = rbGetPrintTree(node->rightSon);
			}
			return ("(" + lson + ", " + to_string(node->key) + ", " + rson + ")");
		}

	public:
		rbTree(){
			root = nullptr;
		}

		~rbTree(){
			//Nothing...
		}

		void rbInsert(double key){
			binaryTree *x, *y;
			binaryTree *newNode = new(binaryTree);
			newNode->key = key;
			newNode->color = RED;
			newNode->leftSon = nullptr;
			newNode->rightSon = nullptr;
			y = nullptr;
			x = root;
			while (x != nullptr){
				y = x;
				if (newNode->key < x->key){
					x = x->leftSon;
				}
				else{
					x = x->rightSon;
				}
			}
			newNode->parent = y;
			if (y == nullptr){
				root = newNode;
				root->color = BLACK;
			}
			else if (newNode->key < y->key){
				y->leftSon = newNode;
			}
			else{
				y->rightSon = newNode;
			}
			rbInsertFixUp(newNode);
			return;
		}

		void rbDelete(binaryTree *node){
			binaryTree *x, *y;
			if ((node->leftSon == nullptr) || (node->rightSon == nullptr)){
				y = node;
			}
			else{
				x = node->rightSon;
				while (x->leftSon != nullptr){
					x = x->leftSon;
				}
				y = x;
			}
			if (y->leftSon != nullptr){
				x = y->leftSon;
			}
			else{
				x = y->rightSon;
			}
			if (x != nullptr){
				x->parent = y->parent;
			}
			if (y->parent == nullptr){
				root = x;
			}
			else if (y == y->parent->leftSon){
				y->parent->leftSon = x;
			}
			else{
				y->parent->rightSon = x;
			}
			if (y != node){
				node->key = y->key;
			}
			if (y->color == BLACK){
				if (x == nullptr){
					rbDeleteFixUp(x, y->parent);
				}
				else{
					rbDeleteFixUp(x, nullptr);
				}
			}
			delete(y);
			y = nullptr;
			return;
		}

		unsigned short rbSearch(double key, unsigned short ifDelete){
			binaryTree *now = root;
			if (root == nullptr){
				return 0;
			}
			while (key != now->key){
				if (key < now->key){
					now = now->leftSon;
				}
				else{
					now = now->rightSon;
				}
				if (now == nullptr){
					return 0;
				}
			}
			if (ifDelete){
				rbDelete(now);
			}
			return 1;
		}

		string rbPrintTree(){
			string lson, rson;
			if (root != nullptr){
				if (root->leftSon != nullptr){
					lson = rbGetPrintTree(root->leftSon);
				}
				if (root->rightSon != nullptr){
					rson = rbGetPrintTree(root->rightSon);
				}
				return ("(" + lson + ", " + to_string(root->key) + ", " + rson + ")");
			}
			return "( )";
		}
};

int main(){
	rbTree searchTree;
	unsigned short flag;
	char opt;
	double key;
	do{
		cin >> opt;
		switch (opt)
		{
		case 'I':
			cin >> key;
			searchTree.rbInsert(key);
			cout << "DONE" << endl;
			break;
		case 'S':
			cin >> key;
			flag = searchTree.rbSearch(key, 0);
			if (flag){
				cout << "YES" << endl;
			}
			else{
				cout << "NO" << endl;
			}
			break;
		case 'D':
			cin >> key;
			flag = searchTree.rbSearch(key, 1);
			if (flag){
				cout << "DONE" << endl;
			}
			else{
				cout << "NONE" << endl;
			}
			break;
		case 'P':
			cout << searchTree.rbPrintTree() << endl;
			break;
		default:
			;
		}
	} while (opt != 'E');
	return 0;
}