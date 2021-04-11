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

enum IpAddressFilterType
{
	DefaultFiltration,
	FiltrationBySelectedBytes,
};


class IpFilter
{
public:
	IpFilter() = default;
    bool AddIpAddress(const std::string& ipAddressWithOtherData);
	std::list<std::vector<u_int8_t>> GetOriginalList() const;
	void AddFilterParameter(const u_int8_t partNumberAddress, const u_int8_t filterValue);
	void AddFilterParameter(const u_int8_t filterValue);
	void ClearFilterParameters();
	std::list<std::vector<u_int8_t>> GetFilteredList() const;
	void SortAddresses();

private:
	void FilterListBySubString(const u_int8_t filterValue);
	void FilterListByParams();
	std::vector<std::string> Split(const std::string& str, char delimiter);
	std::vector<u_int8_t> ChangeToNumbers(const std::vector<std::string>& ipAddressParts);
private:
	std::list<std::vector<u_int8_t>> m_ipAddressList;
	std::map<u_int8_t, u_int8_t> m_FilterParameters;
	std::list<std::vector<u_int8_t>> m_FilteredIpAddressList;
};

}//IpFiltration

#endif // IPFILTER_H
