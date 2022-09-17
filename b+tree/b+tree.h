#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <limits.h>
using namespace std;

#define  d_cout(x) cout<<#x<<" "<<(x)<<endl;
enum NodeTtpe {
	t_node,
	t_val
};
template<class T, int M = 3>
struct  _Node
{
	using T_KEY = T;
	_Node()
	{
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		memset(key, 0, sizeof(key));
		memset(child, 0, sizeof(child));
		c_len = 0;
	}
	using _type = _Node<T, M>;

	T     key[M + 1];

	_type* child[M + 1] = { 0 };
	_type* left;
	_type* right ;
	_type* parent;
	int   len = M;
	int   c_len;
	NodeTtpe ty;
	
public:
	virtual ~_Node() {

	}

public:
	virtual void copy(_Node< T, M >*& p)
	{
		p->len = len;
		p->c_len = c_len;
		memcpy(p->child, child, c_len*sizeof(_type*));
		memcpy(p->key, key, c_len * sizeof(_type*));
		p->left = left;
		p->right = right;
		p->parent = parent;
		p->ty = ty;

	}
	virtual bool splitsave(int b,int e,_type* parent)
	{
		if (b > e || e > c_len) return false;
		int c = 0;
		while (b < e)
		{
			child[c] = child[b];
			if (ty == t_node)
			{
				child[c]->parent = parent;
			}
			key[c++] = key[b++];
		
		}
		c_len = c;
		return true;
	}
	virtual void add(_Node< T, M >* p, int idx)
	{

		key[c_len] = p->key[idx];
		child[c_len] = p->child[idx];
		c_len++;
	}
};

template<class T_key, class T_Val, int M = 3>
class Node:public _Node<T_key,M>
{
public:
	using type = Node< T_key, T_Val, M>;
	using _type = _Node<T_Val, M>;

	Node() {
		memset(val, 0, sizeof(val));

	}

	virtual void copy(_Node< T_key, M >*& p)
	{
		_Node<T_key, M>::copy(p);
		type* t = (type*)p;
		memcpy(t->val, val, t->c_len*sizeof(T_Val));

	}
	virtual bool splitsave( int b, int e,_type* parent)
	{
		if (b > e || e > this->c_len) return false;

		int copyb = b;
		int copye = e;
		int k = 0;
		while (b < e)
		{
			val[k++] = val[b++];
		}
		return _Node<T_key, M>::splitsave(copyb, copye, parent);
	}
	virtual void add(_Node< T_key, M >* p,int idx)
	{
		//��������  ��������һ����Node�ڵ�
		type* t = (type*)p;
		val[this->c_len] = t->val[idx];
		_Node<T_key, M>::add(p, idx);

	}
	T_Val val[M+1];
public:
	virtual ~Node() {

	}

};


template<class T_key, class T_Val,int M=3>
class B_Tree
{

	using type = Node< T_key, T_Val, M>;
	using _type = _Node<T_key, M>;
public:
	B_Tree():m_sqt(nullptr),m_root(nullptr){}
	void view()
	{
		_type * t = m_sqt;
		while (t != nullptr)
		{
			for (int i = 0; i < t->c_len; i++)
			{
				cout << t->key[i] << " ";
			}
			t = t->right;
			cout << " | ";
		}
		cout << endl;
	}
	~B_Tree()
	{
		
	/*	_type * t = m_sqt;
		while (t != nullptr)
		{
			for (int i = 0; i < t->c_len; i++)
			{
				cout << t->key[i] << " ";
			}
			auto tt = t;
			t = t->right;
			cout << " | ";
			delete tt;
		}*/
	
	}
public:
	bool Insert(pair<T_key, T_Val> p)
	{
		if (m_root == nullptr)
		{
			m_root = new type;
			m_root->ty = t_val;
		}

		return _insert(m_root, p);

	}
	bool Delete(T_key key)
	{
		if (m_root == nullptr)
		{
			return true;
		}

		return _delete(m_root, key);

	}
	bool search(T_key k)
	{
		if (m_root == nullptr)
		{
			return false;
		}

		pair<T_key, T_Val> p;
		p.first = k;
		return _insert(m_root,p,true);

	}
	bool check()
	{
		if (m_root->c_len > 0)
		{
			return _check(m_root, m_root->key[m_root->c_len - 1]);

		}
		return true;
	}
	
private:
	bool _check(_type *p, T_key k)
	{
		if (p == nullptr)
			return true;

		if (p->key[p->c_len - 1] != k)
		{
			cout << "?" << endl;
			return false;
		}
		if ((p->right&&p->right->left != p))
		{
			cout << "?" << endl;
			return false;
		}
		for (int i = 0; i < p->c_len; i++)
		{
			cout << p->key[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < p->c_len; i++)
		{
			if (!_check(p->child[i], p->key[i]))
				return false;
			if (p->child[i] && p->child[i]->parent != p)
			{
				return false;
			}
		}
		return true;
	}
private:
	bool _insert(_Node< T_key, M >* root, pair<T_key, T_Val> p,bool bSearch=false)
	{
		
		if (root->ty==t_node)
		{
			for (int i =  0; i < root->c_len; i++)
			{
				if (p.first == root->key[i]) return bSearch;
				if (p.first < root->key[i])
				{

					return _insert(root->child[i], p);
				}
			}
			return _insert(root->child[root->c_len - 1], p);

		}
		else {
			type *t = (type*)root;
			for (int i = t->c_len - 1; i >= 0; i--)
			{
				if (p.first == root->key[i]) return bSearch;
			}
			//���Ѳ�
			if (bSearch)
			{
				return false;
			}
			for (int i = t->c_len - 1; i >= 0; i--)
			{
				if (p.first > t->key[i])
				{

					t->key[i + 1] = p.first;
					t->val[i + 1] = p.second;
					t->c_len++;

					_adjust(t,i + 2);
					return true;
				}
				t->key[i + 1] = t->key[i];
				t->val[i + 1] = t->val[i];
			
			}
			t->key[0] = p.first;
			t->val[0] = p.second;
			t->c_len++;

			_adjust(t,0);
			
			if (m_sqt == nullptr)
			{
				m_sqt = t;
				m_sqt->ty = t_val;
				resetparent(m_sqt->parent,m_sqt, nullptr, p.first, p.first);
			}
		}
		//һ����false
		return bsearch;
	}
	bool _delete(_Node< T_key, M >* root, T_key key)
	{

		if (root->ty == t_node)
		{
			auto iter = lower_bound(root->key, root->key + root->c_len, key);
			if (iter != nullptr)
			{
				return _delete(root->child[iter - root->key], key);
			}
			return true;

		}
		else {
			type *t = (type*)root;

			auto iter = lower_bound(root->key, root->key + root->c_len, key);
			if (iter == nullptr || *iter != key)
			{
				return false;
			}
			int idx = iter - root->key;
			for (int i = idx; i < root->c_len - 1; i++)
			{
				t->child[i] = t->child[i + 1];
				t->key[i] = t->key[i + 1];
				t->val[i] = t->val[i + 1];
			}
			t->c_len--;
			_adjust(t, idx, false);
			return true;

		}
		//һ����false
		return false;
	}
	//����2�ǲ����idx
	bool _adjust(_Node< T_key, M > *p, int idx, bool add = true)
	{
		if (add)
		{
			if (idx == p->c_len)
			{
				_reset(p->parent, p->key[idx - 2], p->key[idx - 1]);

			}
		}
		else {
			if (idx == p->c_len)
			{
				
				_reset(p->parent, p->key[idx], p->c_len == 0 ? p->key[0] : p->key[idx - 1], p->c_len == 0);

			}
		}
		if (p->c_len > p->len)
		{
			//copy
			_type *div = nullptr;
			if (p->ty == t_node)
			{
				div = new _type;
			}
			else {
				div = new type;
			}
			p->copy(div);

			int divlen = p->c_len / 2;
			//���� �����������ӽڵ�
			p->splitsave(0, divlen, p);
			div->splitsave(divlen, div->c_len, div);

			_type* rnode = p->right;

			p->right = div;
			div->left = p;
			if (rnode)
				rnode->left = div;
			//���¸��ڵ�key
			resetparent(p->parent, p, div, p->key[p->c_len - 1], div->key[div->c_len - 1]);

		}
		else if (p->c_len < M/2 )
		{
			int ln = p->left ? p->left->c_len : 0;
			int rn = p->right ? p->right->c_len : 0;
			if (ln + rn == 0)
			{
				return true;
			}//rn!=0��ʵҲ���Ƿ�ֹ�ҽڵ��ǿ� �Ǿͺ����ڵ�ϲ�
			_type* lnode = p->left;
			_type*  rnode = p->right;
			//��ǰ�ڵ���û��������
			if (p->c_len == 0)
			{
				if (lnode)
					lnode->right = p->right;
				if (rnode)
					rnode->left = lnode;
				return true;

			}
		

			else if ((ln > rn&&rn != 0)||!p->left)
			{
				d_cout(rn + p->c_len);

			
				//���ұߺϲ� ��߿���һ�� ��κϲ��˴���len�Ͳ�����
				if (rn + p->c_len > p->len)
					return true;
				if (rnode == nullptr)
					return true;
				//���ݺϲ�
				int pn = p->c_len;
				for (int j = 0; j < rn; j++)
				{
					p->add(rnode, j);
				}
				//�����ӽڵ� ��Ϊɾ���Ǵ��µ��� ���� ����ά�������keyֵ
				if (rnode->ty == t_node)
				{
					for (int j = 0; j < rn; j++)
					{
						rnode->child[j]->parent = p;
					}
				}
				//���ҽڵ�  
				p->right = rnode->right;
				if (rnode->right)
					rnode->right->left = p;


				//�����ڵ�
				_type *pp = p->parent;
				p->parent = rnode->parent;
				//�ҽڵ�һ�������� ��Ϊɾ��������ڵ�
				if (!_resetchild(rnode->parent, rnode, p))
				{
					return false;
				}
			
				if (pn ==0 || !_delkey(pp, p->key[pn - 1]))
				{
					return false;
				}
			
				_delete(rnode);
			
			}
			else {
				d_cout(ln + p->c_len);
				if (ln + p->c_len > p->len)
					return true;
				if (lnode == nullptr)
					return true;
				int pn = p->c_len;
				//���ݺϲ�
				
				for (int j = 0; j < p->c_len; j++)
				{
					lnode->add(p, j);
				}
				//�����ӽڵ�
				if (lnode->ty == t_node)
				{
					for (int j = 0; j < p->c_len; j++)
					{
						p->child[j]->parent = lnode;
					}
				}
				//���ҽڵ�  
				lnode->right = p->right;
				if (p->right)
					p->right->left = lnode;
				//�����ڵ�
				_type *lp = lnode->parent;

				lnode->parent = p->parent;
				//
				if (!_resetchild(p->parent, p, lnode))
				{
					return false;
				}

				if (ln ==0 || !_delkey(lp, lnode->key[ln - 1]))
				{
					return false;
				}
				_delete(p);

			}
			

		}

		return true;
	}

	//���del�����true�ʹ��� ���滻 ���ֱֵ��ɱ��
	void _reset(_Node< T_key, M >* p, T_key src, T_key des,bool del=false)
	{
		if (p == nullptr)
			return;
		for (int i = p->c_len - 1; i >= 0; i--)
		{
			if (p->key[i] == src)
			{
				p->key[i] = des;
				//�����ɾ�� �Ǵ������ľ��Ǳ�ɾ����
				if (del)
				{
					for (int j = i; j < p->c_len - 1; j++)
					{
						p->key[j] = p->key[j + 1];
						p->child[j] = p->child[j + 1];
					}
					p->c_len--;
					i--;
				}
				
				if (i == p->c_len - 1)
				{
					//�����ɾ�����������һ������
					if (del)
					{

						_reset(p->parent, src, p->c_len == 0 ? p->key[0] : p->key[p->c_len - 1], p->c_len == 0);
					}
					else {
						_reset(p->parent, src, des);

					}

					return;
				}
				break;
			}
		}
	}
	//�ɵ����ڵ�key 
	bool _delkey(_Node< T_key, M >* root, T_key key)
	{

		auto iter = lower_bound(root->key, root->key + root->c_len, key);
		if (iter == nullptr)
			return true;//�п�����֮ǰreset�ɵ���
		if (*iter != key)
		{
			return false;
		}
		int idx = iter - root->key;
		if (idx + 1 != root->c_len)
		{
			for (int i = idx; i < root->c_len; i++)
			{
				root->child[i] = root->child[i + 1];
				root->key[i] = root->key[i + 1];

			}
		}
		root->c_len--;
		//�����ɾ��ͬ�� ���� ɾ����idx�ݹ��ж�
		return _adjust(root, idx,false);
	}
	
	bool _resetchild(_Node< T_key, M >* root, _Node< T_key, M >* src, _Node< T_key, M >* dec)
	{
		for (int i = 0; i < root->c_len; i++)
		{
		
			if (root->child[i] ==src)
			{
				root->child[i] = dec;
				return true;
			}
		}
		return false;
	}
protected:
	void _delete(_type*&p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
	void resetparent(_type *&parent, _type* f1, _type* f2, T_key k1, T_key k2)
	{
		if (parent == nullptr)
		{
			parent = new _type;
			m_root = parent;
			if (f1)
			{
				parent->child[0] = f1;
				parent->key[0] = k1;
				parent->c_len++;
				f1->parent = parent;

			}
			if (f2)
			{
				parent->child[1] = f2;
				parent->key[1] = k2;
				parent->c_len++;
				f2->parent = parent;
			}
			parent->ty = t_node;
		}
		else {
	
			_nodevecinsert(parent,f1, f2,k1,k2);
			_adjust(parent, -1);
		}
	}
	void _nodevecinsert(_type *&p, _type* f1, _type* f2, T_key k1, T_key k2)
	{
	
		auto &t = *p;


		for (int i = p->c_len - 1; i >= 0; i--)
		{
			if (k2 == p->key[i])
			{
				p->child[i] = f2;
			}

			if (k1 > p->key[i])
			{
				p->key[i + 1] = k1;
				p->child[i + 1] = f1;
				p->c_len++;
				return;
			}
			p->key[i + 1] = p->key[i];
			p->child[i + 1] = p->child[i];
		}
		p->key[0] = k1;
		p->child[0] = f1;
		p->c_len++;
	}
private:

	_type* m_sqt;
	_type* m_root;
};