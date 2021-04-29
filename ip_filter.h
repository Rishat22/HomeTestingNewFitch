#ifndef IPFILTER_H
#define IPFILTER_H
#include <iostream>
#include <list>
#include <vector>
#include <map>

namespace IpFiltration
{
const size_t ADDRESS_PARTS_SIZE = 4;
const size_t ADDRESS_WITH_OTHERDATA_PARTS_SIZE = 3;

using IpAddress = std::vector<u_int8_t>;
using IpAddressList = std::list<IpAddress>;

class IpFilter
{
public:
	IpFilter() = default;
    bool AddIpAddress(const std::string& ipAddressWithOtherData);
	IpAddressList GetOriginalList() const;
	void AddFilterParameter(const u_int8_t partNumberAddress, const u_int8_t filterValue);
	void AddFilterParameter(const u_int8_t filterValue);
	void ClearFilterParameters();
	IpAddressList GetFilteredList() const;
	void SortAddresses();

private:
	void FilterListBySubString(const u_int8_t filterValue);
	void FilterListByParams();
	std::vector<std::string> Split(const std::string& str, char delimiter);
	IpAddress ChangeToNumbers(const std::vector<std::string>& ipAddressParts);
	bool IsCorrectAddress(const IpAddress& ipAddress) const;
private:
	IpAddressList m_ipAddressList;
	std::map<u_int8_t, u_int8_t> m_FilterParameters;
	IpAddressList m_FilteredIpAddressList;
};

}//IpFiltration

#endif // IPFILTER_H
