#include <iostream>
#include "mymath.hpp"
using namespace std;
double power(double x,int ponement)
{
	int temp = x;
	for (int i = 1;i<ponement;i++)
	{
		if(x!=0)
		{
			x *=temp;
		}else{
			cout << " illegal di_shu " << endl;
			break;
		}
	}
	return x;
}
