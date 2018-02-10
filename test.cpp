//#include <iostream>

enum simple_enum {A, B};

enum complex_enum {C=1, D=-3};

template <typename T>
#pragma template
class TEMPLATE {
	T internals;
};


void test()
{
//	std::cout << "Test from executable" << std::endl;
}

int main()
{
	int a = 0;
	complex_enum v = C;
	TEMPLATE<int> i;
	while(1);
}
