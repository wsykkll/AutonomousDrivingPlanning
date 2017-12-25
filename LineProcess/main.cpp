#include "LCMSubscriber.h"
#include <list>
#include <vector>
using namespace std;

int main()
{
	//vector<int> a;
	//for (int i = 0; i < 10; i++)
	//{
	//	a.push_back(i);
	//}
	//vector<int> b;
	//for (int j = 23; j < 100; j++)
	//{
	//	b.push_back(j);
	//}
	//b.insert(b.begin(), a.begin(), a.end());

	CLCMSubscriber stLcmSubscrber;
	if (!stLcmSubscrber.IsInitialized())
	{
		return -1;
	}
	thread_group stThreadGroup;
	stThreadGroup.create_thread(bind(&CLCMSubscriber::run, &stLcmSubscrber));
	stThreadGroup.join_all();
	return 0;
}