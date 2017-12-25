#include "LCMSubscriber.h"
using namespace std;

int main()
{
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