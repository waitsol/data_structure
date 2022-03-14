#include "RBtree.h"
void RBtree::firdfs(Node *root)
{
	if (root)
		cout << root->key << " ";
	if (root->left)
		firdfs(root->left);
	else
		cout << "L" << " ";
	if (root->right)
		firdfs(root->right);
	else
		cout << "R" << " ";

}
void RBtree::LL(Node *g)
{
	cout << "val " << g->key << "LL" << endl;
	Node *p = g->left;
	Node *x = p->left;
	
	g->parent->left = p;
	p->parent = g->parent;

	g->left = p->right;
	if (p->right)
		p->right->parent = g;

	p->right = g;
	g->parent = p;





//	t = p;

}

void RBtree::RR(Node *g)
{
	Node *p = g->left;
	Node *x = p->right;
	
	p->right = x->left;
	if (x->left)
		x->left->parent = p;

	x->left = p;
	p->parent = x;

	g->left = x;
	x->parent = g;

	//t = p;
}
void RBtree::RL(Node *t)
{
	LL(t->right);
	RR(t);
}
void RBtree::LR(Node *t)
{
	RR(t->left);
	LL(t);
}
void RBtree::insert(int v)
{
	if (root == nullptr)
	{
		root = new Node(v);
		root->color = black;
		return;
	}

	Node *cur = root;
	Node *parent = nullptr;
	while (cur)
	{
		if (v > cur->key)
		{
			parent = cur;
			cur = cur->right;
		}
		else if (v < cur->key)
		{
			parent = cur;
			cur = cur->left;
		}
		else
			break;//存在了
	}

	cur = new Node(v);
	cur->parent = parent;
	if (parent->key < v)
		parent->right = cur;
	else
		parent->left = cur;



	while (parent&&parent->color == red)
	{
		Node *gparent = parent->parent; //祖父的颜色一定是黑色
		if (gparent->left == parent)  //左子树
		{
			//如果 右节点是红色 直接变颜色
			Node *uncle = gparent->right;
			if (uncle&&uncle->color == red)
			{
				uncle->color=parent->color = black;
				gparent->color = red;
				cur = gparent;
				parent = gparent->parent;
			}
			else//uncle 不存在或者为黑色
			{
				if (cur == parent->right)
				{
					printf("%p %p", parent, gparent->left);
					RR(gparent);
					LL(gparent);
					cur->color = black;
					//左右旋转 左是p 又是gp  所以不为空
					cur->left->color = cur->right->color = red;
				}
				else
				{
					LL(gparent);
					parent->color = black;
					//左右旋转 左是p 又是gp  所以不为空
					parent->left->color = parent->right->color = red;
				}
			

			}

		}
		else 
		{
			//如果 左节点是红色 直接变颜色
			Node *uncle = gparent->left;
			if (uncle&&uncle->color == red)
			{
				uncle->color = parent->color = black;
				gparent->color = red;
				cur = gparent;
				parent = gparent->parent;
			}
			else//uncle 不存在或者为黑色
			{
				if (cur == parent->left)
				{
					LL(gparent->right);
					RR(gparent);
					cur->color = black;
					//左右旋转 左是p 又是gp  所以不为空
					cur->left->color = cur->right->color = red;
				}
				else {
					RR(gparent);
						parent->color = black;
					//左右旋转 左是p 又是gp  所以不为空
					parent->left->color = parent->right->color = red;
				}
				
			}

		}
	}
	
	if (parent == nullptr)
	{
		cur->color = black;
	}
}

