#include <iostream>
#include <map>
#include <vector>
#include "logging_allocator.hpp"
#include "Vector.hpp"

using namespace std;

//struct Vector3
//{
//	float x = 0.0f, y = 0.0f, z  = 0.0f;

//	Vector3() =  default;

//	Vector3(float scalar)
//			: x(scalar), y(scalar), z(scalar)
//	{
//				cout << "Constract\n";
//	}

//	Vector3(float x, float y, float z)
//		: x(x), y(y), z(z)
//	{
//		cout << "Constract\n";
//	}

//	~Vector3()
//	{
//		cout << "Destroy\n";
//	}
//};



template<typename T>
std::ostream& print(std::ostream &out, T const &val) {
  return ( out << val << endl );
}

template<typename T1, typename T2>
std::ostream& print(std::ostream &out, std::pair<T1, T2> const &val) {
  return ( out << val.first << " " << val.second << std::endl );
}

template<template<typename, typename...> class TT, typename... Args>
std::ostream& operator<<(std::ostream &out, TT<Args...> const &cont) {
  for(auto&& elem : cont)
	  print(out, elem);
  out <<"-------------------------------------------------------\n";
  return out;
}


int main(int, char *[]) {
	auto mapWithCustomAllocator = std::map<
			int,	float,
			std::less<int>,
			logging_allocator<
			std::pair< int, float	>
			>
			>{logging_allocator<std::pair< int, float	>>(10)};

	for (int i = 0; i < 5; ++i) {
		mapWithCustomAllocator[i] = static_cast<float>(i);
	}

	cout << mapWithCustomAllocator;

	Vector<int> customVector;
	for (int i = 0; i < 5; ++i) {
		customVector.PushBack(i);
	}

	cout << customVector;

	return 0;
}
