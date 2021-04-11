#include <iostream>
#include "ip_filter.h"
#include "lib.h"

using namespace std;
using namespace IpFiltration;

void PrintAddressList(const std::list<std::vector<u_int8_t>>& ipAddressList)
{
	std::cout << std::endl;
	for(const auto& ipAddress : ipAddressList)
	{
		for(const auto& ipAddressPart : ipAddress)
		{

			std::cout << to_string(ipAddressPart);
			std::cout << ".";
		}
		std::cout << std::endl;
	}
}

int main()
{
	std::cout << "build " << version() << std::endl;
	cout << "Hello World!" << endl;

	cout << "Part 2. Filtering IP addresses." << endl;
	cout << "Enter 'end' to end the input." << endl;
	IpFilter ipFilter;
	while (true)
	{
		std::string inputData;
		getline(cin, inputData);
		if(inputData == "end")
		{
			break;
		}

		auto bRes = ipFilter.AddIpAddress(inputData);

		if(!bRes)
		{
			cout << "Invalid string format." << endl;
			cout << "Example: text1 \t text2 \t text3 \n" << endl;
		}
	}


	ipFilter.SortAddresses();
	PrintAddressList(ipFilter.GetOriginalList());

	ipFilter.AddFilterParameter(0, 1);
	PrintAddressList(ipFilter.GetFilteredList());

	ipFilter.AddFilterParameter(46, 70);
	PrintAddressList(ipFilter.GetFilteredList());

	ipFilter.AddFilterParameter(46);
	PrintAddressList(ipFilter.GetFilteredList());

	return 0;
}
