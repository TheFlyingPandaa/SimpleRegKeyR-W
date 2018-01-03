#include "KeyEdit.h"
#include <iostream>
#include <string>
KeyEdit::KeyEdit()
{
	//std::cout << "thinking emoji" << std::endl;

	this->subKeyName = "PandaKeys";
}

KeyEdit::~KeyEdit()
{
} 

bool KeyEdit::keyPeek() {

	if (Registry::CurrentUser->OpenSubKey(this->subKeyName) != nullptr)
	{
		regKey = Registry::CurrentUser->CreateSubKey(this->subKeyName);
		String ^ dayString;
		String ^ monthString;
		String ^ yearString;

		
		if (regKey->OpenSubKey("dateKeys", true) != nullptr)
		{
			//std::cout << "wop" << std::endl;
			testSettings = regKey->OpenSubKey("dateKeys", true);
			//testSettings = testSettings->OpenSubKey("month");

			dayString = testSettings->GetValue("day")->ToString();
			monthString = testSettings->GetValue("month")->ToString();
			yearString = testSettings->GetValue("year")->ToString();

			//Console::WriteLine(dynamic_cast<String^>(testSettings->GetValue("day")->ToString()));
			//Console::WriteLine(dynamic_cast<String^>(testSettings->GetValue("month")->ToString()));
			//Console::WriteLine(dynamic_cast<String^>(testSettings->GetValue("year")->ToString()));
		}

		time_t now = time(0);
		 
		std::string day_String = "00";
		std::string month_String = "00";
		std::string year_String = "0000";

		for (size_t i = 0; i < dayString->Length; i++)
		{
			day_String[i] = dayString[i];
		}
		for (size_t i = 0; i < monthString->Length; i++)
		{
			month_String[i] = monthString[i];
		}
		for (size_t i = 0; i < yearString->Length; i++)
		{
			year_String[i] = yearString[i];
		}

		int dayParsed = std::stoi(day_String);
		int monthParsed = std::stoi(month_String);
		int yearParsed = std::stoi(year_String);

		tm *ltm = localtime(&now);

		int year = 1900 + ltm->tm_year;
		int month = 1 + ltm->tm_mon;
		int day = ltm->tm_mday + 1;
		
		
		if (day != dayParsed)
		{
			regKey = nullptr;

			return true;
		}
		else
		{
			return false;
		}
		
		//regKey->Close();

	}
	else
	{
		Console::WriteLine("No Key to print");
		return false;
	}

}

void KeyEdit::createKey() {
	// Create a subkey named Test9999 under HKEY_CURRENT_USER.
	RegistryKey ^ rk = nullptr;
	rk = Registry::CurrentUser->OpenSubKey(this->subKeyName);
	//Calling close on system keys is shit. they never close

	if (rk == nullptr)
	{
		//std::cout << "OHHOHH SPAGHEIIT" << std::endl;
		regKey = Registry::CurrentUser->CreateSubKey(this->subKeyName);

		std::cout << "Key created" << std::endl;

		time_t now = time(0);



		tm *ltm = localtime(&now);

		int year = 1900 + ltm->tm_year;
		int month = 1 + ltm->tm_mon;
		int day = ltm->tm_mday;

		//std::string smash;

		//smash = year + "/" + month + "/" + day;

		// Create two subkeys under HKEY_CURRENT_USER\Panda.
		//regKey->CreateSubKey("TestName")->Close(); 


		if (regKey->OpenSubKey("dateKeys") == nullptr)
		{
			testSettings = regKey->CreateSubKey("dateKeys");


			// Create data for the TestSettings subkey.
			testSettings->SetValue("year", year);
			testSettings->SetValue("month", month);
			testSettings->SetValue("day", day);
			//testSettings->Close();
			std::cout << "SubKey created" << std::endl;
			// Print the information from the Test9999 subkey.
			Console::WriteLine("There are {0} subkeys under ", this->subKeyName, regKey->SubKeyCount.ToString());
			array<String^>^subKeyNames = regKey->GetSubKeyNames();
			for (int i = 0; i < subKeyNames->Length; i++)
			{
				RegistryKey ^ tempKey = regKey->OpenSubKey(subKeyNames[i]);
				Console::WriteLine("\nThere are {0} values for {1}.", tempKey->ValueCount.ToString(), tempKey->Name);
				array<String^>^valueNames = tempKey->GetValueNames();
				for (int j = 0; j < valueNames->Length; j++)
				{
					Console::WriteLine("{0,-8}: {1}", valueNames[j], tempKey->GetValue(valueNames[j])->ToString());

				}
			}
		}

	}
	else
	{
		Console::WriteLine("Key in place");
	}
	//rk->Close();
} 

void KeyEdit::removeKey() {

	// Delete the ID value.
	//testSettings = regKey->OpenSubKey("dateKeys", true);
	//testSettings->DeleteValue("id");

	// Verify the deletion.
	//Console::WriteLine(dynamic_cast<String^>(testSettings->GetValue("id", "ID not found.")));
	//testSettings->Close();
	
	// Delete or close the new subkey.
	if (Registry::CurrentUser->OpenSubKey(this->subKeyName) != nullptr)
	{
		Console::Write("\nDelete newly created re gistry key? (Y/N) ");
		std::string te;
		std::cin >> te;
		if (te == "Y")//Char::ToUpper(Convert::ToChar(Console::Read())) == 'Y')
		{
			Registry::CurrentUser->DeleteSubKeyTree(this->subKeyName);
			Console::WriteLine("Key del");
			//Console::WriteLine("\nRegistry key {0} deleted.", regKey->Name);
		}
	}
	else
	{
		std::cout << "No Sub Key to delete" << std::endl;
	}
}