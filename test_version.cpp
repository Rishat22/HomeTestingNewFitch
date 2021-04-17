#define BOOST_TEST_MODULE test_version

#include "lib.h"
#include "ip_filter.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
	BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_CASE(test_result_emptyList_size)
{
	using namespace IpFiltration;
	std::list<std::string> inputData;
	IpFilter ipFilter;
	BOOST_CHECK(inputData.size() == ipFilter.GetOriginalList().size());
}

BOOST_AUTO_TEST_CASE(test_result_sortList_size)
{
	using namespace IpFiltration;
	std::list<std::string> inputData
	{
		"192.168.1.0	0	0",
		"200.100.1.1	0	0",
		"200.111.1.0	0	0",
		"1.1.1.1	0	0",
		"0.0.0.0	0	0",
	};
	IpFilter ipFilter;
	for(const auto& inputLine : inputData)
	{
		ipFilter.AddIpAddress(inputLine);
	}
	ipFilter.SortAddresses();
	BOOST_CHECK(inputData.size() == ipFilter.GetOriginalList().size());
}

BOOST_AUTO_TEST_CASE(test_check_sortList)
{
	using namespace IpFiltration;
	std::list<std::string> inputData
	{
		"192.168.1.0	0	0",
		"200.100.1.1	0	0",
		"200.111.1.0	0	0",
		"1.1.1.1	0	0",
		"0.0.0.0	0	0",
	};
	IpFilter ipFilter;
	for(const auto& inputLine : inputData)
	{
		ipFilter.AddIpAddress(inputLine);
	}
	std::list<std::vector<u_int8_t>> sortedList
	{
		{200, 111, 1, 0},
		{200, 100, 1, 1},
		{192, 168, 1, 0},
		{1, 1, 1, 1},
		{0, 0, 0, 1}

	};
	ipFilter.SortAddresses();
	BOOST_CHECK(sortedList == ipFilter.GetOriginalList());
}

}
