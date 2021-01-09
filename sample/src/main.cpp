#include <iostream>
#include <array>

#include <Windows.h>
	

void test1()
{
}

int main()
{
	int choice;
	do {
		printf("Choose test, 0 to exit: ");
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			test1();
			break;
		case 2:
			test2();
			break;
		}
	} while (choice != 0);

	return 0;
}
