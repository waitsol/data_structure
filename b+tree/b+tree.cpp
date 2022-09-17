// b+tree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "b+tree.h"
#include<vector>
#include <time.h>
#include <unordered_set>
#include <fstream>
#include <set>
#include <random>
#include <set>
#define M 10
#define debug 0
#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif // WIN32
inline INT64 GetTickCountEx()
{
#ifndef WIN32
	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
#else
	return GetTickCount64();
#endif // !WIN32

}



void shuffle(vector<int> &v)
{
	srand(time(0));
	int n = v.size();
	for (int i = 0; i < n; i++)
	{
		swap(v[i], v[rand() % n]);
	}
}
vector<int> Stringsplit(const string& str, const char split )
{
	vector<int> res;
	if (str == "")        return res;
	//在字符串末尾也加入分隔符，方便截取最后一段
	string strs = str + split;
	size_t pos = strs.find(split);

	// 若找不到内容则字符串搜索函数返回 npos
	while (pos != strs.npos)
	{
		string temp = strs.substr(0, pos);
		if(temp.size()>0)
			res.push_back(atoi(temp.c_str()));
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(split);
	}
	return res;
}

void test(vector<int> &s)
{
	B_Tree<int, int, M> b;
	unordered_set<int> us(s.begin(), s.end());
	auto begin = GetTickCountEx();
	for(auto &x:s)
	{
		b.Insert(make_pair(x,1));
		if (!b.check())
		{
			cout << x << endl;
			ofstream ofs("debug.txt");
			for (auto xx : s)
			{
				ofs << xx << " ";
			}

			exit(-2);
		}
	}
	for (auto &x : us)
	{
		b.Delete(x);
		if (!b.check())
		{
			cout << x << endl;
			ofstream ofs("debug.txt");
			for (auto xx : s)
			{
				ofs << xx << " ";
			}

			exit(-3);
		}
	}

	//b.view();
	auto e = GetTickCountEx();

	cout << (e - begin) << endl;
}
int debugtxt()
{

	ifstream ifs("debug.txt");
	vector<int> v1, v2;
	set<int> s1;
	const int len = 100 * 4;
	v1.reserve(len);
	int x = 0;
	while (ifs >> x)
	{
		v1.push_back(x);
		s1.emplace(x);
	}
	cout << s1.size() << endl;
	
	test(v1);
	return 0;
}
void check(vector<int>&v)
{
	set<int> s(v.begin(), v.end());
	int i = 0;
	for (auto x :  s)
	{
		if (x != i)
		{
			return;
		}
		i++;
	}
	cout << s.size() << endl;
	
}
void load(vector<int>* v)
{
	ifstream ifs("text.txt");
	string s;
	getline(ifs, s, '\n');
	v[0] = Stringsplit(s, ',');
	check(v[0]);
	getline(ifs, s, '\n');
	v[1] = Stringsplit(s, ',');
	check(v[1]);
	ifs.close();
}

void debigdel()
{
	B_Tree<int, int, M> b;
	vector<int> v;
	vector<int> vec[2];
#if debug
	load(vec);
#endif // debug
	ofstream ofs("text.txt");

	default_random_engine e(time(0));
	uniform_int_distribution<int> u(0, INT_MAX);

	for (int i = 0; i < 5000; i ++ )
	{
		v.push_back(u(e));
	}
	shuffle(v);
#if debug
	v = vec[0];
#endif // debug

	for (auto &x : v)
	{
		cout << x << ", ";
		ofs << x << ",";
	}
	auto begin = GetTickCountEx();
	for (auto &x : v)
	{

		cout << "add  " << x << endl;
		b.Insert(make_pair(x, 1));
		if (!b.check())
		{
			cout << x << endl;
			ofstream ofs("debug.txt");
			for (auto xx : v)
			{
				ofs << xx << " ";
			}

			exit(-4);
		}
	}
	cout << endl;
	cout << endl;
	b.check();
	b.view();
	shuffle(v);
#if debug
	v = vec[1];
#endif // debug
	ofs << endl;
	for (auto &x : v)
	{
		cout << x << ", ";
		ofs << x << ",";
	}
	cout << endl;
	ofs << endl;
	ofs.close();

	for (auto &x : v)
	{
		int y = x;
		cout << "delete x = " << x << endl;
		if (!b.Delete(y))
		{
			exit(-7);
		}
		if (!b.check())
		{
			cout << x << endl;
		/*	ofstream ofs("debug.txt");
			for (auto xx : v)
			{
				ofs << xx << " ";
			}
*/
			exit(-5);
		}
		b.view();
	}

	b.view();
	auto ee = GetTickCountEx();

	cout <<"run time "<< (ee - begin) << endl;
}
int main()
{


	freopen("in.txt", "w", stdout);
	int ii = 10000;
	while (ii--)
	{
		debigdel();

	}

	return 0;
	//return debugtxt();

	default_random_engine e(time(0));
	uniform_int_distribution<int> u(0, 500);

	vector<int> v1, v2;
	const int len = 20*1;
	v1.reserve(len);
	v2.reserve(len);
	for (int i = 0; i < len; i++)
	{
		v1.push_back(i);
		v2.push_back(u(e));
	}
	for (int i = 0; i < 1000; i++)
	{
		v2.clear();

		for (int j = 0; j < len; j++)
		{
			
			v2.push_back(u(e));
		}
	//	test(v1);
		test(v2);
		cout << endl;

	}

	
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
