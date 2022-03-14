#include <iostream>
#include <algorithm>
#include <vector>
#include "RBtree.h"
using namespace std;
#pragma once

class node {
	
public:
	node(int x = 0) :data(x), heigth(0), left(NULL), right(NULL) {}

	int data;
	int heigth;
	node *left;
	node *right;
};

class AVL
{
public:
	//插入
	void insert(node *&rt,int v);
	//左左偏移  右旋
	void LL(node *&t);
	void RR(node *&t);
	void RL(node *&t);
	void LR(node *&t);

	/*node* GetMaxVal(node *rt);
	node* GetMinVal(node *rt);*/
	int  GetHeight(node *rt);
	void firdfs(node *rt);


};
void AVL::firdfs(node *rt)
{
	queue< node*> q;
	q.push(rt);
	while (q.size())
	{
		auto x = q.front();
		q.pop();
		if (x->left)
			q.push(x->left);
		if(x->right)
			q.push(x->right);
		cout << x->data << endl;

	}



}
void AVL::LL(node *&t)
{
	cout << "val " << t->data << "LL" << endl;
	node *p = t->left;
	t->left = p->right;
	p->right = t;
	t->heigth = max(GetHeight(t->left), GetHeight(t->right)) + 1;
	p->heigth = max(GetHeight(p->left), GetHeight(p->right)) + 1;
	t = p;

}

void AVL::RR(node *&t)
{
	cout << "val " << t->data << "RR" << endl;
	node *p = t->right;
	t->right = p->left;
	p->left = t;
	t->heigth = max(GetHeight(t->left), GetHeight(t->right)) + 1;
	p->heigth = max(GetHeight(p->left), GetHeight(p->right)) + 1;
	t = p;

}
void AVL::RL(node *&t)
{
	LL(t->right);
	RR(t);
}
void AVL::LR(node *&t)
{
	RR(t->left);
	LL(t);
}
void AVL::insert(node *&rt,int v)
{
	if (rt == NULL)
	{
		rt = new node(v);
		cout << v << "插入成功\n";
	}
	else if (rt->data > v)
	{
		cout << v << "进入左节点\n";
		insert(rt->left, v);
		if (GetHeight(rt->left) - GetHeight(rt->right) > 1)
		{
			if (rt->left->data > v)
				cout << "LL" << endl,LL(rt);
			else
				cout <<v<< "LR"<<"  root"<< rt->data<< endl, LR(rt);
		}

	}
	else if (rt->data < v)
	{
		cout << v << "进入右节点\n";
		insert(rt->right, v);
		if (GetHeight(rt->right) - GetHeight(rt->left) > 1)
		{
			cout << GetHeight(rt->right) << GetHeight(rt->left);
			if (rt->right->data > v)
				cout << "rl" << endl, RL(rt);
			else
				cout <<v<<"  "<< "rr" << endl, RR(rt);
		}
	}



	rt->heigth = max(GetHeight(rt->left), GetHeight(rt->right)) + 1;
	cout << rt->data << " " << rt->heigth << endl;
}
int AVL::GetHeight(node *t)
{
	if (t == NULL)
		return -1;
	return t->heigth;
}


int main()
{
	//avl rbt;
	//node *node = nullptr;
	//rbt.insert(node,10);
	//rbt.insert(node, 8);
	//rbt.insert(node, 9);
	//rbt.insert(node, 7);
	//

	//rbt.insert(node, 8);
	//cout << endl;
	//rbt.firdfs(node);


	RBtree rbt;
	rbt.insert(10);
	rbt.insert(9);
	rbt.insert(11);
	rbt.insert(7);
	rbt.show();

	cout << endl;
	rbt.insert(8);
	rbt.show();
	cout << endl;
	rbt.insert(6);
	rbt.show();
	cout << endl;
	rbt.insert(5);
	rbt.show();
}

