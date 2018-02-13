#include <iostream>
#include <fstream>

int main(void)
{
	std::ifstream file;
	/* ate: At End */
	file.open("hello.txt", std::ios::ate|std::ios::binary);

	if (file.fail())
	{
		std::cerr << "Opening a file has failed.\n";
		return 1;
	}

	char *memblock = nullptr;
	/* tellg() and tellp() */
	std::streamsize size = file.tellg();

	/* Allocating */
	memblock = new char[size];
	file.seekg(0, std::ios::beg);
	file.read(memblock, size);

	std::cout << "Size: " << size << std::endl;
	std:: cout << "Contents: " << memblock << std::endl;
	
	/* Deallocating */
	delete memblock;

	file.close();

	return 0;	
}

