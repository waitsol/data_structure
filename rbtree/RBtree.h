#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#pragma once
#define IsRed rt->color==red
#define IsBlack rt->color==black
#define showCol(col) #col
enum Color :char
{
	red,
	black
};
class Node {

public:
	Node(int x = 0) :key(x), color(red), left(nullptr), right(nullptr), parent(nullptr) {}

	int key;
	Color color;
	Node *left;
	Node *right;
	Node *parent;
	void show()
	{
		cout << "key = " << key << " color = " << (color?"black":"red") << endl;
	}
};

class RBtree
{
public:
	RBtree() :root(nullptr) {}
	void insert(int v);
	void show()
	{
		queue<Node*> q;
		q.push(root);
		while (q.size())
		{
			auto x = q.front();
			q.pop();
			if (x->left)
				q.push(x->left);
			if (x->right)
				q.push(x->right);
			x->show();
		}

	}
private:
	//×ó×óÆ«ÒÆ  ÓÒÐý
	void LL(Node *t);
	void RR(Node *t);
	void RL(Node *t);
	void LR(Node *t);

	void firdfs(Node *rt);

private:
	Node *root;
};