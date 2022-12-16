#pragma once

#ifndef STRING_CONVERTER
#define STRING_CONVERTER
#include <iostream>
std::string Stos(System::String^ s) //convert to string
{
	using namespace System::Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	std::string os(chars);
	return os;
}

System::String^ stoS(std::string& os) //convert to String
{
	System::String^ s;
	s = gcnew System::String(os.c_str());
	return s;
}
System::String^ stoS(const char* os) //convert to String
{
	System::String^ s;
	s = gcnew System::String(os);
	return s;
}
#endif

