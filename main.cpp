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
void PrintVector(const Vector<T>& vector)
{
	for(size_t i = 0; i < vector.Size(); i++)
	{
		std::cout << vector[i] << std::endl;
	}
	std::cout  << "-------------------------------------------------------\n";
}

//template<>
//void PrintVector(const Vector<Vector3>& vector)
//{
//	for(size_t i = 0; i < vector.Size(); i++)
//	{
//		std::cout << vector[i].x <<", "<< vector[i].y <<", "<< vector[i].z <<", " << std::endl;
//	}
//	std::cout  << "-------------------------------------------------------\n";
//}

int main(int, char *[]) {
//	auto m = std::map<
//		int,	float,
//		std::less<int>,
//		logging_allocator<
//			std::pair<const int, float	>
//		>
//	>{};

//	for (int i = 0; i < 5; ++i) {
//		m[i] = static_cast<float>(i);
//	}

	Vector<int> my_vector;
	my_vector.PushBack(100);
	my_vector.PushBack(100);
	my_vector.PushBack(100);

	PrintVector(my_vector);

	return 0;
}
