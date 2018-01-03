#include <iostream>
#include <windows.h>
#include "KeyEdit.h"


int main()
{
	KeyEdit keyEdit;
	bool temp = keyEdit.keyPeek();
	int x;
	if (temp != false)
	{
		while (x != 4) {
			std::cin >> x;
			std::cin.ignore();
			switch (x)
			{
			case 1:
				keyEdit.createKey();
				x = 0;
				break;
			case 2:
				keyEdit.removeKey();
				x = 0;
				break;
			case 3:
				keyEdit.keyPeek();
				x = 0;
				break;
			default:
				//x = 0;
				break;
			}
		}
	}
	else
	{
		std::cout << "expired" << std::endl;

	}

	//keyEdit.createKey();
	//keyEdit.removeKey();

	

	return 0;
}