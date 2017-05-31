#include <iostream>
#include <iomanip>
#include <vector>
#include "ring_buffer.h"

void log_buff(const toy_box::ring_buffer<int>& buff)
{
	std::cout << "------------------------------------------" << '\n';
	std::cout << "capacity  -> " << buff.capacity() << '\n';
	std::cout << "count     -> " << buff.count() << '\n';
	std::cout << "          index  -> ";
	for(size_t i = 0; i < buff.capacity(); ++i)
	{
			std::cout << std::setfill('_') << std::setw(3) << i << "|";
	}
	std::cout << "\n virtual memory  -> ";
	for(auto itr = buff.begin(); itr != buff.end(); ++itr)
	{
		std::cout << std::setfill('_') << std::setw(3) << *itr << "|";
	}
	std::cout << "\nphysical memory  -> ";
	for(auto itr = buff.pmbegin(); itr != buff.pmend(); ++itr)
	{
		std::cout << std::setfill('_') << std::setw(3) << *itr << "|";
	}
	std::cout << "\n------------------------------------------" << '\n';
}

int main(int argc, char const *argv[])
{
	std::cout << "\n[ toy_box::ring_buffer class tutorial ]\n" << '\n';

	std::cout << "constructor(4)" << '\n';
	toy_box::ring_buffer<int> buff(4);
	log_buff(buff);

	std::cout << "push_back(1)" << '\n';
	std::cout << "push_back(2)" << '\n';
	std::cout << "push_back(3)" << '\n';
	buff.push_back(1);
	buff.push_back(2);
	buff.push_back(3);
	log_buff(buff);

	std::cout << "push_front(4)" << '\n';
	std::cout << "push_front(5)" << '\n';
	buff.push_front(4);
	buff.push_front(5);
	log_buff(buff);

	std::cout << "front() -> " << buff.front() << '\n';
	std::cout << "back() -> " << buff.back() << '\n';
	std::cout << "full() -> " << buff.full() << '\n';

	std::cout << "pop_back()" << '\n';
	buff.pop_back();
	log_buff(buff);

	std::cout << "pop_front()" << '\n';
	buff.pop_front();
	log_buff(buff);

	std::cout << "shrink(2)" << '\n';
	buff.shrink(2);
	log_buff(buff);

	std::cout << "clean_up()" << '\n';
	buff.clean_up();
	log_buff(buff);

	std::cout << "empty() -> " << buff.empty() << '\n';

	std::cout << "expand(8)" << '\n';
	std::cout << "push_back(1)" << '\n';
	std::cout << "push_back(2)" << '\n';
	std::cout << "push_back(3)" << '\n';
	buff.expand(8);
	buff.push_back(1);
	buff.push_back(2);
	buff.push_back(3);
	log_buff(buff);

	std::cout << "buffer[0] -> " << buff[0] << '\n';
	std::cout << "buffer[1] -> " << buff[1] << '\n';
	std::cout << "buffer[2] -> " << buff[2] << '\n';
	std::cout << "buffer[3] -> " << buff[3] << '\n';

	return 0;
}
