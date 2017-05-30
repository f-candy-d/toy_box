#include <iostream>
#include <iomanip>
#include <vector>
#include "ring_buffer.h"

void log_buff(const toy_box::ring_buffer<int>& buff)
{
	std::cout << "--------------------------------" << '\n';
	std::cout << "capacity -> " << buff.capacity() << '\n';
	std::cout << "count -> " << buff.count() << '\n';
	std::cout << "index -> ";
	for(size_t i = 0; i < buff.capacity(); ++i)
	{
			std::cout << std::setfill('_') << std::setw(3) << i << "|";
	}
	std::cout << "\ndata  -> ";
	// for(auto itr = buff.begin(); itr != buff.end(); ++itr)
	for(size_t i = 0; i < buff.count(); ++i)
	{
		// std::cout << std::setfill('_') << std::setw(3) << *itr << "|";
		std::cout << std::setfill('_') << std::setw(3) << buff[i] << "|";
	}
	std::cout << "\n--------------------------------" << '\n';
}

int main(int argc, char const *argv[])
{

	toy_box::ring_buffer<int> buff(4);
	log_buff(buff);

	std::cout << "push_back(1)" << '\n';
	std::cout << "push_front(2)" << '\n';
	std::cout << "push_back(3)" << '\n';
	buff.push_back(1);
	buff.push_front(2);
	buff.push_back(3);
	log_buff(buff);

	std::cout << "push_back(4)" << '\n';
	std::cout << "push_back(5)" << '\n';
	std::cout << "push_back(6)" << '\n';
	buff.push_back(4);
	buff.push_back(5);
	buff.push_back(6);
	log_buff(buff);

	std::cout << "push_front(7)" << '\n';
	std::cout << "push_front(8)" << '\n';
	buff.push_front(7);
	buff.push_front(8);
	log_buff(buff);

	std::cout << "pop_back()" << '\n';
	std::cout << "pop_back()" << '\n';
	std::cout << "pop_front()" << '\n';
	buff.pop_back();
	buff.pop_back();
	buff.pop_front();
	log_buff(buff);

	std::cout << "front -> " << buff.front() << '\n';
	std::cout << "back -> " << buff.back() << '\n';


	return 0;
}
