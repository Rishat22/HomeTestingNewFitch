#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>
#include <utility>

template <typename T>
class Vector
{
public:
	Vector()
	{
		ReAlloc(2);
	}

	~Vector()
	{
		Clear();
		::operator delete( m_Data, m_Capacity * sizeof (T) );
	}

	void Clear()
	{
		for(size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();
	}

	void PushBack(const T& value)
	{
		if(m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity /2);

		m_Data[m_Size] = value;
		m_Size++;
	}

	void PushBack(const T&& value)
	{
		if(m_Size >= m_Capacity)
			ReAlloc(m_Capacity + m_Capacity /2);

		m_Data[m_Size] = std::move(value);
		m_Size++;
	}

	const T& operator[](const size_t index) const
	{
		if(index >= m_Size)
		{
			//assert
		}
		return m_Data[index];
	}

	T& operator[](const size_t index)
	{
		if(index >= m_Size)
		{
			//assert
		}
		return m_Data[index];
	}

	size_t Size() const { return m_Size; }

private:
	void ReAlloc(const size_t newCapacity)
	{
		T* newBlock = (T*)::operator new( newCapacity * sizeof (T) );

		if(newCapacity < m_Size)
				m_Size = newCapacity;

		for(size_t i = 0; i < m_Size; i++)
			newBlock[i] = std::move(m_Data[i]);

		for(size_t i = 0; i < m_Size; i++)
			m_Data[i].~T();

		::operator delete( m_Data,m_Capacity * sizeof (T));
		m_Data = newBlock;
		m_Capacity = newCapacity;
	}
private:
	T* m_Data = nullptr;
	size_t m_Size = 0;
	size_t m_Capacity = 0;
};

#endif // VECTOR_H
