#include <iostream>
#include <algorithm>
#include <vector>
#include "RBtree.h"
using namespace std;


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

	//,539,655,93,712,488,810,839,68,28,814,940
	int n;
	cin >> n;
	RBtree rbt;
	while (1)
	{
		rbt.insert(n);
		rbt.show();
		cout << endl;
		cin >> n;
		if (n == -1)
			break;
	}

}
//890 362 741
/*
544
250
682
189
484
612
703
124
241
304
491
604
644
683
853
19
171
236
413
503
638
798
921






*/