#include <iostream>
#include <windows.h>
#include "KeyEdit.h"


int main()
{
	KeyEdit keyEdit;
	
	int x;

	while (x != 4) {
		std::cin >> x;

		switch (x)
		{
		case 1:
			keyEdit.createKey();
			break;
		case 2:
			keyEdit.removeKey();
			break;
		case 3:
			keyEdit.keyPeek();
			break;
		default:
			break;
		}
	}

	//keyEdit.createKey();
	//keyEdit.removeKey();

	

	return 0;
}