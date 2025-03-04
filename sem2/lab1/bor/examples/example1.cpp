#include "D:\Code\Visual Studio\Projects\bor\include\bor.h"
#include <iostream>

int ex() {
	Bor bor;
	bor.insert("hello");
	bor.insert("world");
	std::cout << bor.search("hello") << std::endl;
	std::cout << bor.search("wor") << std::endl;
	bor.remove("hello");
	std::cout << bor.search("hello") << std::endl;
	return 0;
}