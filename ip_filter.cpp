#include <vector>
#include "ip_filter.h"

namespace IpFiltration
{

bool IpFilter::AddIpAddress(const std::string& ipAddressWithOtherData)
{
	const auto substringsSet = Split(ipAddressWithOtherData, '\t');

	//We ignore other but we need to check the correctness of the data
	if(substringsSet.size() != ADDRESS_WITH_OTHERDATA_PARTS_SIZE)
	{
		return false;
	}
	const auto ipAddressNumParts = ChangeToNumbers(Split(substringsSet.at(0), '.'));
	if(IsCorrectAddress(ipAddressNumParts))
		m_ipAddressList.push_back(ipAddressNumParts);
	return true;
}

std::vector<std::string> IpFilter::Split(const std::string& str, char delimiter)
{
	std::vector<std::string> substringsSet;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(delimiter);
	while(stop != std::string::npos)
	{
		substringsSet.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(delimiter, start);
	}

	substringsSet.push_back(str.substr(start));

	return substringsSet;
}

IpAddress IpFilter::ChangeToNumbers(const std::vector<std::string>& ipAddressParts)
{
	IpAddress ipAddressNumParts;
	for(const auto& ipAddressPart : ipAddressParts)
	{
		ipAddressNumParts.push_back(stoi(ipAddressPart));
	}
	return ipAddressNumParts;
}

IpAddressList IpFilter::GetOriginalList() const
{
	return m_ipAddressList;
}


IpAddressList IpFilter::GetFilteredList() const
{
	return m_FilteredIpAddressList;
}

void IpFilter::AddFilterParameter(const u_int8_t filterValue)
{
	FilterListBySubString(filterValue);
}

void IpFilter::FilterListBySubString(const u_int8_t filterValue)
{
	m_FilteredIpAddressList.clear();
	for(const auto& ipAddress : m_ipAddressList)
	{
		for(const auto& ipAddressPart : ipAddress)
		{
			if(ipAddressPart == filterValue)
			{
				m_FilteredIpAddressList.push_back(ipAddress);
				break;
			}
		}
	}
}

void IpFilter::AddFilterParameter(const u_int8_t partNumberAddress, const u_int8_t filterValue)
{
	m_FilterParameters[partNumberAddress] = filterValue;
	FilterListByParams();
}

void IpFilter::FilterListByParams()
{
	m_FilteredIpAddressList.clear();
	for(const auto& ipAddress : m_ipAddressList)
	{
		auto findAddress = true;
		for(const auto& filterParameter : m_FilterParameters)
		{
			if(ipAddress[filterParameter.first] != filterParameter.second)
			{
				findAddress = false;
				break;
			}
		}
		if(findAddress)
		{
			m_FilteredIpAddressList.push_back(ipAddress);
		}
	}
}

void IpFilter::ClearFilterParameters()
{
	m_FilterParameters.clear();
}

void IpFilter::SortAddresses()
{
	m_ipAddressList.sort(std::greater<IpAddress>());
}

bool IpFilter::IsCorrectAddress(const IpAddress& ipAddress) const
{
	if(ipAddress.size() != ADDRESS_PARTS_SIZE)
	{
		return false;
	}
	return true;
}

} //namespace IpFiltration
