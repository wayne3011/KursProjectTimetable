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
std::string UTF8to1251(std::string const& utf8)
{
    std::string s1251;
    for (int i = 0; i < utf8.size(); ++i)
    {
        int b1 = (unsigned char)utf8[i];
        if ((b1 >> 5) == 6)
        {
            int b2 = (unsigned char)utf8[i + 1];
            if ((b1 == 208) && (b2 >= 144 && b2 <= 191))
            {
                s1251 += (char)(b2 + 48);
            }
            else if ((b1 == 209) && (b2 >= 128 && b2 <= 143))
            {
                s1251 += (char)(b2 + 112);
            }
            else if ((b1 == 208) && (b2 == 129))
            {
                s1251 += (char)(b2 + 39);
            }
            else if ((b1 == 209) && (b2 == 145))
            {
                s1251 += (char)(b2 + 39);
            }
            ++i;
        }
        else if ((b1 >> 7) == 0)
        {
            s1251 += b1;
        }
    }
    return s1251;
}
#endif

