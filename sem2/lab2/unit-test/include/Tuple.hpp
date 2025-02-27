#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <variant>
#include <ostream>

#include "Set.hpp"

template<typename T>
class Set;

/**
 * @brief Класс-кортеж.
 *
 * @tparam T - тип элементов кортежа.
 */
template<typename T>
class Tuple
{
private:
	std::variant<T, Set<T>, Tuple> *m_data;
	size_t m_size;
	size_t m_capacity;
public:
	/**
	 * @brief Конструктор для класса-множества.
	 */
	Tuple()
	{
		this->m_size = 0;
		this->m_capacity = 1;
		this->m_data = new std::variant<T, Set<T>, Tuple>[this->m_capacity];
	}
	
	/**
	 * @brief Конструктор копирования для Tuple.
	 *
	 * @param other копируемый объект Other.
	 */
	Tuple(const Tuple &other)
	{
		this->m_size = other.m_size;
		this->m_capacity = other.m_capacity;
		
		this->m_data = new std::variant<T, Set<T>, Tuple>[this->m_capacity];
		
		for (size_t i = 0; i < this->m_size; i++)
		{
			this->m_data[i] = other.m_data[i];
		}
	}
	
	/**
	 * @brief Оператор присваивания для Tuple.
	 *
	 * @param s присваиваемый объект Tuple.
	 * @return Set& присвоенный Tuple.
	 */
	Tuple &operator=(const Tuple &s)
	{
		if (this != &s)
		{
			this->m_size = 0;
			this->m_capacity = 0;
			
			delete[] m_data;
			
			this->m_data = nullptr;
			
			this->m_size = s.m_size;
			this->m_capacity = s.m_capacity;
			
			this->m_data = new std::variant<T, Set<T>, Tuple>[this->m_capacity];
			
			for (size_t i = 0; i < this->m_size; i++)
			{
				this->m_data[i] = s.m_data[i];
			}
		}
		return *this;
	}
	
	/**
	 * @brief Вставка элемента кортежа.
	 *
	 * @param value - элемент.
	 */
	void insert(const std::variant<T, Set<T>, Tuple> &value)
	{
		std::variant<T, Set<T>, Tuple> valueCopy = value;
		
		if (this->m_size == this->m_capacity)
		{
			this->m_capacity = this->m_capacity * 3 / 2 + 1;
			
			auto *dataAux = new std::variant<T, Set<T>, Tuple>[this->m_capacity];
			for (size_t i = 0; i < this->m_size; i++)
			{
				dataAux[i] = this->m_data[i];
			}
			
			delete[] this->m_data;
			
			this->m_data = dataAux;
		}
		
		this->m_data[this->m_size++] = valueCopy;
	}
	
	template<typename T1>
	friend bool operator==(Tuple<T1>, Tuple<T1>);
	
	template<typename T1>
	friend bool operator!=(Tuple<T1>, Tuple<T1>);
	
	/**
	 * @brief Вывод кортежа.
	 * @tparam T1 тип хранимых данных
	 * @return поток вывода.
	 */
	template<typename T1>
	friend std::ostream & operator<<(std::ostream &, const Tuple<T1> &);
};

template<typename T>
bool operator==(Tuple<T> lhs, Tuple<T> rhs)
{
	if (lhs.m_size == rhs.m_size)
	{
		for (size_t i = 0; i < lhs.m_size; i++)
		{
			if (lhs.m_data[i] != rhs.m_data[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

template<typename T>
bool operator!=(Tuple<T> lhs, Tuple<T> rhs)
{
	return !(lhs == rhs);
}

template<typename T>
std::ostream & operator<<(std::ostream &out, const Tuple<T> &tuple)
{
	out << "< ";
	for (size_t i = 0; i < tuple.m_size; i++)
	{
		try
		{
			T currentElement = std::get<T>(tuple.m_data[i]);
			out << currentElement;
		}
		catch (const std::bad_variant_access &)
		{
			try
			{
				Set<T> currentElementSet = std::get< Set<T> >(tuple.m_data[i]);
				out << currentElementSet;
			}
			catch (const std::bad_variant_access &)
			{
				Tuple<T> currentElementTuple = std::get< Tuple<T> >(tuple.m_data[i]);
				out << currentElementTuple;
			}
		}
		out << ' ';
	}
	out << ">";
	
	return out;
}

#endif // TUPLE_HPP