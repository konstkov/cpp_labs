
#include <iostream>

#include "Counter.h"
#include "InheritedObserver.h"
#include "LimitedCounter.h"
#include "OverflowCounter.h"

int main(int argc, char** argv) {
	LimitedCounter lc(0, 5);
	OverflowCounter oc(5, 9);

	//Add three observers called “red”, “green”, “blue” to the main function.

	std::string red_name ("red");
	std::string green_name ("green");
	std::string blue_name ("blue");

	InheritedObserver red(red_name);
	InheritedObserver green(green_name);
	InheritedObserver blue(blue_name);

	// “Red” and “Blue” observe limited counter (lc)
	lc.attach(&red);
	lc.attach(&blue);

	// “Green” observes overflow counter (of)
	oc.attach(&green);

	std::cout << oc << std::endl;
	UseCounter(oc, 5);
	std::cout << oc << std::endl; // should display zero
	UseCounter(oc, -1);
	std::cout << oc << std::endl; // should display 9
	oc.dec();
	std::cout << oc << std::endl; // should display 8

	std::cout << lc << std::endl; // should display 0
	lc.inc();
	std::cout << lc << std::endl; // should display 1
	lc.dec();
	std::cout << lc << std::endl; // should display 0
	for(int i = 0; i < 10; ++i) lc.inc();
	std::cout << lc << std::endl; // should display 5
	UseCounter(lc, -9);
	std::cout << lc << std::endl; // should display 0

	return 0;
}

// you need to implement this function
void UseCounter(Counter& ctr, int num)
{
	if (num > 0) while (num--)
	{
		ctr.inc(); // A negative value decrements counter and positive value increments counter.
	}
	else if (num < 0) while (num++)
	{
		ctr.dec();
	}
}