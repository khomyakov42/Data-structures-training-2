#include "List.h"
#include <cstdio>
using namespace std;

int main(){
	hmw::list<int> l;
	l.push_front(1);
	hmw::list<int>::iterator itr = l.begin();
	int x = *(itr);
	//l.push_back(2);
	//l.pop_back();
	//l.pop_front();
}