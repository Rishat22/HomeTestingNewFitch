#include <iostream>
#include "ip_filter.h"
#include "lib.h"
#include <fstream>
#include <string>

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

void SecondPart()
{
	std::string inputData;
	IpFilter ipFilter;
	while(std::getline(std::cin, inputData))  //input from the file in.txt
	{
		auto bRes = ipFilter.AddIpAddress(inputData);

		if(inputData == "end")
		{
			break;
		}
		if(!bRes)
		{
			cout << "Invalid string format." << endl;
			cout << "Example: text1 \t text2 \t text3 \n" << endl;
		}
	}
	ipFilter.SortAddresses();
	PrintAddressList(ipFilter.GetOriginalList());

	ipFilter.ClearFilterParameters();
	ipFilter.AddFilterParameter(0, 1);
	PrintAddressList(ipFilter.GetFilteredList());

	ipFilter.ClearFilterParameters();
	ipFilter.AddFilterParameter(0, 46);
	ipFilter.AddFilterParameter(1, 70);
	PrintAddressList(ipFilter.GetFilteredList());

	ipFilter.ClearFilterParameters();
	ipFilter.AddFilterParameter(46);
	PrintAddressList(ipFilter.GetFilteredList());
}

int main()
{

	std::cout << "build " << version() << std::endl;
	cout << "Hello World!" << endl;

	cout << "Part 2. Filtering IP addresses." << endl;
	cout << "Enter 'end' to end the input." << endl;


	/* if you want reed from file */
//	std::ifstream in("ip_filter.tsv");
//	std::cin.rdbuf(in.rdbuf());

	SecondPart();

	return 0;
}
