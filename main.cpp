#include <bits/stdc++.h>

#include "Range.h"

using namespace std;



int main ()
{
	auto y = rg::range(0.5, 2.1, 0.1);

	//cout << y.begin_ << "   " << y.end_ << "  " << y.step_ << endl;

	for(auto x : y)
	{
		cout << x << endl;
	}


	return 0;
}