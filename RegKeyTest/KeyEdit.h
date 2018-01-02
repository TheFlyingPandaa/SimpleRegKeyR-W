#ifndef KEYEDIT_H
#define KEYEDIT_H

#include <ctime>

using namespace System;
using namespace System::Security::Permissions;
using namespace Microsoft::Win32;

public ref class KeyEdit
{
public:
	KeyEdit();
	~KeyEdit();

	void createKey();
	void removeKey();

	void keyPeek();


private:

	String ^ subKeyName;

	RegistryKey ^ regKey;
	RegistryKey ^ testSettings;

};


#endif