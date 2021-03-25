// MemAllocateTest [C++14]
#include <iostream>
#include <vector>

constexpr std::size_t kb = 1024;
constexpr std::size_t mb = 1024 * 1024;
constexpr std::size_t gb = 1024 * 1024 * 1024;

constexpr std::size_t reservesize{ gb * 16 };

void showsize(const std::size_t size) {
	std::cout << "[ "
		<< size      / gb << " GB | "
		<< size % gb / mb << " MB | "
		<< size % mb / kb << " KB | "
		<< size % kb      << " B ]"
		<< std::endl;
}

void __fastcall func(bool flag = false) {
	std::vector<std::uint8_t> vec;
	if(flag) vec.reserve(reservesize);
	std::size_t vecCapacity{ 0 };

	std::size_t i = 0;
	try {
		while (i < reservesize) {
			vec.push_back(i % 256);
			if (vec.capacity() != vecCapacity) {
				vecCapacity = vec.capacity();
				std::cout << "(vector re-located) new capacity: " << vecCapacity << std::endl;
			}
			++i;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cout << "(vector re-located): " << e.what() << std::endl;
	}
	showsize(i);

	std::cout << "Press ENTER to end this step..." << std::endl;
	std::cin.ignore();
}

int main() {
	std::cout << "Press ENTER to run step ONE..." << std::endl;
	std::cin.ignore();
	func(false);

	std::cout << "Press ENTER to run step TWO..." << std::endl;
	std::cin.ignore();
	func(true);

	std::cout << "Press ENTER to run step THREE..." << std::endl;
	std::cin.ignore();

	std::vector<std::uint8_t> vec;
	std::size_t vecCapacity{ 0 };

	std::size_t i = 0;
	try {
		while (i < reservesize) {
			vec.push_back(i % 256);
			if (vec.capacity() != vecCapacity) {
				vecCapacity = vec.capacity();
				std::cout << "(vector re-located) new capacity: " << vecCapacity << std::endl;
			}
			++i;
		}
	}
	catch (const std::bad_alloc& e) {
		std::cout << "(vector re-located): " << e.what() << std::endl;
	}
	showsize(vec.capacity());

	std::cout << "Press ENTER to use clear()..." << std::endl;
	std::cin.ignore();
	vec.clear();
	showsize(vec.capacity());

	std::cout << "Press ENTER to use resize(4096)..." << std::endl;
	std::cin.ignore();
	vec.resize(4096);
	showsize(vec.capacity());

	std::cout << "Press ENTER to use shrink_to_fit()..." << std::endl;
	std::cin.ignore();
	vec.shrink_to_fit();
	showsize(vec.capacity());

	std::cout << "Press ENTER to close programm..." << std::endl;
	std::cin.ignore();

	return 0;
}

