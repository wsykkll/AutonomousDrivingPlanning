#include <lcm/lcm-cpp.hpp>
#include "LCMSubscriber.h"
#include "LCMHandler.h"
#include <boost/thread.hpp>
#include "stdlib.h"
using namespace boost;

int main(int argc, char *argv[])
{
	CLCMSubscriber lcmsubscriber;
	if (!lcmsubscriber.IsInitialized())
	{
		return -1;
	}
	thread_group gThreadGroup;
	gThreadGroup.create_thread(bind(&CLCMSubscriber::run, &lcmsubscriber));

	gThreadGroup.join_all();
	return 0;
}
