#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>
#include <utility>

template <typename T>
class Vector
{
	using iterator = Vector<T>;
	using const_iterator = Vector<const T>;
	using reverse_iterator =  Vector<T>;
	using const_reverse_iterator =  Vector<const T>;

public:
	Vector()
	{
		ReAlloc(2);
	}
	~Vector();

	void Clear();
	void PushBack(const T& value);
	void PushBack(const T&& value);
	const T& operator[](const size_t index) const;
	T& operator[](const size_t index);
	size_t Size() const;
	bool Empty() const;

	/* Iterators */
	iterator			begin() { return iterator(&m_Data[0]); }
	iterator			end() { return iterator(&m_Data[m_Size]); }
	const_iterator	cbegin(){ return const_iterator(&m_Data[0]);}
	const_iterator	cend(){ return const_iterator(&m_Data[m_Size]);}
	reverse_iterator	rbegin(){ return reverse_iterator(&m_Data[m_Size - 1]);}
	reverse_iterator	rend(){ return reverse_iterator(&m_Data[-1]);}
	const_reverse_iterator	crbegin(){ return const_reverse_iterator(&m_Data[m_Size - 1]);}
	const_reverse_iterator	crend(){ return const_reverse_iterator(&m_Data[-1]);}

private:
	void ReAlloc(const size_t newCapacity);
private:
	T* m_Data = nullptr;
	size_t m_Size = 0;
	size_t m_Capacity = 0;
};

template<typename T>
Vector<T>::~Vector()
{
	Clear();
	::operator delete( m_Data, m_Capacity * sizeof (T) );
}

template<typename T>
void Vector<T>::Clear()
{
	for(size_t i = 0; i < m_Size; i++)
		m_Data[i].~T();
}

template<typename T>
void Vector<T>::PushBack(const T& value)
{
	if(m_Size >= m_Capacity)
		ReAlloc(m_Capacity + m_Capacity /2);

	m_Data[m_Size] = value;
	m_Size++;
}

template<typename T>
void Vector<T>::PushBack(const T&& value)
{
	if(m_Size >= m_Capacity)
		ReAlloc(m_Capacity + m_Capacity /2);

	m_Data[m_Size] = std::move(value);
	m_Size++;
}

template<typename T>
const T& Vector<T>::operator[](const size_t index) const
{
	if(index >= m_Size)
	{
		//assert
	}
	return m_Data[index];
}

template<typename T>
T& Vector<T>::operator[](const size_t index)
{
	if(index >= m_Size)
	{
		//assert
	}
	return m_Data[index];
}

template<typename T>
size_t Vector<T>::Size() const
{
	return m_Size;
}

template<typename T>
bool Vector<T>::Empty() const
{
	return m_Size == 0;
}

template <typename T>
void Vector<T>::ReAlloc(const size_t newCapacity)
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

#endif // VECTOR_H
