#include <cstdlib>

#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <map>
#include <chrono>
#include <thread>
#include <syncstream>
#include <mutex>

class Car {
	friend std::ostream &operator<<(std::ostream &out, const Car &car);
public:
	explicit Car(std::string m="Ford", std::string l="", int ml=0) :
        model(std::move(m)),
        license(!l.empty()?std::move(l):(rand()%2?"FOO-":"BAR-") + std::to_string(rand()%999+1)),
        mileage(ml>0?ml:rand()%10000) {}
	~Car() { std::cout << model << " " << license << " deleted" << std::endl; };
	void Read();
	[[nodiscard]] const std::string &GetLicense() const { return license; }
private:
	std::string model;
	std::string license;
	int mileage;
};

void Car::Read()
{
	std::string user_input;
	std::cout << "Enter car information" << std::endl;
	std::cout << "Model: " << std::endl;
	getline(std::cin, model); // replace the following with your own code
	std::cout << "License plate number: " << std::endl;
	getline(std::cin, license); // replace the following with your own code
	std::cout << "Mileage: " << std::endl;
	std::string m;
	getline(std::cin, m); // replace the following with your own code
	mileage = std::stoi(m);
	//model = "Toyota";
	//license = (rand() % 2 ? "NJF-" : "NZF-") + std::to_string(rand() % 999 + 1);
	//mileage = 15000 + rand() % 15000;


}

std::ostream & operator<<(std::ostream & out, const Car & car)
{
	out << "Model: " << car.model << std::endl << "License: " << car.license << std::endl << "Mileage: " << car.mileage << std::endl;

	return out;
}

/*
Modify class Website so that it has member function run() that runs a loop that sleeps for
10 seconds and then prints a list of advertised cars. The loop, and the thread, stops if the
list of cars is empty.
*/

class Website {
public:
	explicit Website(std::string n="carweb.com") : name(std::move(n)) {}
	~Website() { std::cout << name << " deleted" << std::endl; };
#if 0
	void run(std::stop_token st, int interval)
	{
		for (int i = 0; !st.stop_requested() && i < n; ++i)
		{
			std::this_thread::sleep_for(std::chrono::seconds(interval));
			std::cout << i << std::endl;
		}
		if (st.stop_requested())
		{
			std::cout << "Stop requested\n";
		}
		std::cout << "Thread terminated" << std::endl;
	}
#endif
#if 1

	void run(const std::stop_token &st, int interval)
	{
		std::osyncstream outSync(std::cout);

		//if (it->first.expired())
		while (!st.stop_requested())
		{
			auto duration = std::chrono::seconds(interval);
			std::this_thread::sleep_for(duration);

			std::lock_guard<std::mutex> lock(m);

			for (auto it = listing.begin(); it != listing.end(); )
			{
				if (it->first.expired())
				{
					it = listing.erase(it);
				}
				else
				{
					++it;
				}
			}



			if (listing.empty())
			{
				outSync << "Listing has expired" << std::endl;
				return;
			}

			for (auto &v : listing)
			{
				auto c = v.first.lock();
				outSync << v.second << ":" << std::endl << *c; // or << c
			}
		}

	/*
	if (st.stop_requested())
	{
		return;
	}
	*/
	std::cout << name << " end of list" << std::endl;
}


#endif
	void add(const std::weak_ptr<Car> &car, const std::string &dealer)
	{
		std::lock_guard<std::mutex> lock(m);
		listing[car] = dealer;
	}
	// Website.print() removes all sold cars (expired weak_ptr) before printing the listing of
	//cars advertised on the site
#if 0
	void print(std::ostream &out = std::cout)
	{
        out << name << std::endl;
		for (auto it = listing.begin(); it != listing.end(); )
		{
			if (it->first.expired())
			{
				out << "Listing " << it->second << " has expired" << std::endl;
				it = listing.erase(it);
			}
			else
			{
				auto c = it->first.lock();
				out << it->second << ":" << std::endl << *c; // or << c
				++it;
			}
		}
        out << name << " end of list" << std::endl;
	}
	// void remove(const std::weak_ptr<Car> &car) { listing.erase(car); }
#endif
private:
	std::map<std::weak_ptr<Car> , std::string, std::owner_less<std::weak_ptr<Car>>> listing;
	std::string name;
	std::mutex m;
};

class Dealer {
	friend std::ostream &operator<<(std::ostream &out, const Dealer &dealer);
public:
	explicit Dealer(std::string name_ = "John Doe") : name(std::move(name_)) {};
	~Dealer() { std::cout << name << " deleted" << std::endl; };
	void buy();
	void sell();
	//void add(Car *car) {
	void add(const std::shared_ptr<Car> &car)
	{
        cars.push_back(car);
        for (const auto &site : sites) site->add(car, name);
	}
	void add_site(const std::shared_ptr<Website> &w) {
        sites.push_back(w);
    }
private:
	std::string name;
	std::vector<std::shared_ptr<Car>> cars;
	std::vector<std::shared_ptr<Website>> sites;
};

void Dealer::buy()
{	// when we do a->buy() we make the pointer to Dealer object call
	// its member function buy  which dynamically creates a pointer to car object
	// and then uses that pointer to object to call Car class member functions (read() and add())
	// It says " dealer “owns” a car – has a shared_ptr to the car ".
	// Class Dealer has a private data member std::vector<Car *> cars and whenever
	// we call add(car) we are adding ptr to car object to a vector
	// Instead, we need to create a vector of shared pointers and make a car object a shared pointer with make_shared
	// and add those instead

	// Car *car = new Car;
	auto car = std::make_shared<Car>();
	car->Read();
	add(car);
}

void Dealer::sell()
{
	std::cout << *this; // print my list of cars
	std::cout << "Enter license of car you want to buy: " << std::flush;

	std::string license;
	std::cin >> license;
	auto ci = std::find_if(cars.begin(), cars.end(), [&license](const std::shared_ptr<Car> &c) {return license == c->GetLicense(); });
	if (ci != cars.end()) {
        // modify code so that you don't need to remove a sold car from the website
		//for (auto site : sites) site->print(ci);
		cars.erase(ci);
	}
}


std::ostream & operator<<(std::ostream & out, const Dealer & dealer)
{
	out << dealer.name << "'s cars for sale" << std::endl;
	for (const auto &car : dealer.cars) out << *car;
	out << "End of " << dealer.name << "'s cars listing" << std::endl;

	return out;
}

/* ---------------------- */



void car_sales()
{
	std::cout << "Car sales started" << std::endl;

	const auto wa = std::make_shared<Website>("www.autos.com");
	const auto wb = std::make_shared<Website>("www.bilar.com");

	const auto a = std::make_shared<Dealer>("Alan Aldis");
	const auto b = std::make_shared<Dealer>("Bill Munny");

	{ // inner scope to make some if the pointers go out of scope before the function ends.
        //auto *wc = new Website("www.cars.com");
		const auto wc = std::make_shared<Website>("www.cars.com");

		const auto c = std::make_shared<Dealer>("Casey Ball");

		const auto ca = std::make_shared<Car>();
		const auto cb = std::make_shared<Car>();

		// DEALERS: a, b, c
		// WEBSITES: wa, wb, wc
		// CARS: ca, cb

		a->add_site(wa);
		a->add_site(wb);
		b->add_site(wb);
		b->add_site(wc);
		c->add_site(wa);
		c->add_site(wb);
		c->add_site(wc);

		a->buy();
		a->buy();
		a->buy();

		a->buy();

		b->buy();
		b->buy();
		b->buy();

		c->buy();

		c->add(ca);
		c->add(cb);


		/*wa->print();
		wb->print();
		wc->print();*/

		std::cout << *a << *b << *c << std::endl;

		/*Change car_sales() so that it asks user to select the dealer
		 *from which to buy a car or to exit
		program in a loop*/

		/*Change the program so that after initial setup
		 (filling of the lists) a thread is started for each
		website. Remove all calls to print functions from the main.*/


		std::jthread w1([wa](const std::stop_token &stoken){wa->run(stoken, 10); });
		std::jthread w2([wb](const std::stop_token &stoken){wb->run(stoken, 10); });
		std::jthread w3([wc](const std::stop_token &stoken){wc->run(stoken, 10); });




		while (true)
		{
			std::string user_input;
			std::cout << "Please select a dealer from which you want to buy a car "
		       "(type a, b or c) or 'stop' to exit the program in a loop:" << std::endl;

			getline(std::cin, user_input);

			if (user_input=="a")
			{
				a->sell();
			}

			else if (user_input=="b")
			{
				b->sell();
			}
			else if (user_input=="c")
			{
				c->sell();
			}



			/*Call sell() of selected dealer or stop loop and wait for the other thread(s)
			to finish if user selected to exit program.*/

			else if (user_input=="stop") // exit program in a loop
			{
				w1.request_stop();
				w2.request_stop();
				w3.request_stop();
				break;
			}
		}

		std::cout << *a << *b << *c << std::endl;


	}

	std::cout << "Car sales ended" << std::endl;

}

int main(int argc, char **argv) {

	srand(time(nullptr));

	car_sales();

	return 0;
}


