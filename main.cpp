#include <iostream>
#include "Container.hpp"

int main(void)
{
	Container<float> container;

	for(int32_t i = 0; i < 10; ++i)
	{
		container.Append(utils::rand<float>(1, 100));
	}

	std::cout << container << std::endl;
	container.BubbleSort();
	std::cout << container << std::endl;

	return EXIT_SUCCESS;
}
