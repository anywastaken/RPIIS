/******************************************************************************
    Название:    Set.hpp
    Разработчик: Вашкевич Максим Викторович
    Дата:        18.02.2024
    Описание:    файл содержит определение класса Set, который представляет со-
                 бой множество (всё определение находится в заголовочном файле,
                 поскольку определяемый здесь класс является шаблонным).
******************************************************************************/

#ifndef SET_HPP
#define SET_HPP

#include <cstdlib>
#include <variant>
#include <ostream>

/**
 * @brief Класс-множество.
 *
 * @tparam T - тип элементов множества.
 */
template<typename T>
class Set
{
private:
	std::variant<T, Set> *m_data;
	size_t *m_multiplicity;
	size_t m_size;
	size_t m_capacity;
public:
	/**
	 * @brief Конструктор для класса-множества.
	 */
	Set()
	{
		this->m_size = 0;
		this->m_capacity = 1;
		this->m_data = new std::variant<T, Set>[this->m_capacity];
		this->m_multiplicity = new size_t[m_capacity];
	}
	
	/**
	 * @brief Оператор присваивания для Set.
	 *
	 * @param s присваиваемый объект Set.
	 * @return Set& присвоенный Set.
	 */
	Set &operator=(const Set &s)
	{
		if (this != &s)
		{
			this->m_size = 0;
			this->m_capacity = 0;
			
			delete[] m_data;
			delete[] m_multiplicity;
			
			this->m_data = nullptr;
			this->m_multiplicity = nullptr;
			
			this->m_size = s.m_size;
			this->m_capacity = s.m_capacity;
			
			this->m_data = new std::variant<T, Set>[this->m_capacity];
			this->m_multiplicity = new size_t[this->m_capacity];
			
			for (size_t i = 0; i < this->m_size; i++)
			{
				this->m_data[i] = s.m_data[i];
				this->m_multiplicity[i] = s.m_multiplicity[i];
			}
		}
		return *this;
	}
	
	/**
	 * @brief Вставка элемента множества с определённой кратностью.
	 *
	 * @param value - элемент.
	 * @param count - кратность элемента.
	 */
	void insert(const std::variant<T, Set> &value, size_t count)
	{
		for (size_t i = 0; i < this->m_size; i++)
		{
			if (this->m_data[i] == value)
			{
				this->m_multiplicity[i] += count;
				return;
			}
		}
		
		if (this->m_size == this->m_capacity)
		{
			this->m_capacity = this->m_capacity * 3 / 2 + 1;
			
			auto *dataAux = new std::variant<T, Set>[this->m_capacity];
			auto *multiplicityAux = new size_t[this->m_capacity];
			for (size_t i = 0; i < this->m_size; i++)
			{
				dataAux[i] = this->m_data[i];
				multiplicityAux[i] = this->m_multiplicity[i];
			}
			
			delete[] this->m_data;
			delete[] this->m_multiplicity;
			
			this->m_data = dataAux;
			this->m_multiplicity = multiplicityAux;
		}
		
		this->m_data[this->m_size++] = value;
		this->m_multiplicity[this->m_size - 1] = count;
	}
	
	/**
	 * @brief Кратность определённого элемента множества.
	 *
	 * @param value - элемент.
	 * @return size_t - кратность.
	 */
	size_t getMultiplicity(const std::variant<T, Set> &value)
	{
		for (size_t i = 0; i < this->m_size; i++)
		{
			if (this->m_data[i] == value)
			{
				return this->m_multiplicity[i];
			}
		}
		
		return 0;
	}
	
	/**
	 * @brief Размер массива m_data.
	 *
	 * @return size_t размер.
	 */
	size_t getSize()
	{
		return this->m_size;
	}
	
	/**
	 * @brief Все элементы массива m_data.
	 *
	 * @param destination - динамический массив, куда надо записать m_data.
	 */
	void getElements(std::variant<T, Set> *&destination)
	{
		if (destination != nullptr)
		{
			delete[] destination;
			destination = nullptr;
		}
		
		if (this->m_size != 0)
		{
			destination = new std::variant<T, Set>[this->m_size];
			for (size_t i = 0; i < this->m_size; i++)
			{
				destination[i] = this->m_data[i];
			}
		}
	}
	
	/**
	 * @brief Существует ли элемент в множестве.
	 *
	 * @param value - элемент.
	 * @return true - если элемент найден.
	 * @return false - если нет.
	 */
	bool isFound(const std::variant<T, Set> &value)
	{
		return this->getMultiplicity(value) != 0;
	}
	
	// операторы сравнения (нужны для unit-тестирования)
	template<typename T1>
	friend bool operator==(Set<T1>, Set<T1>);
	
	template<typename T1>
	friend bool operator!=(Set<T1>, Set<T1>);
	
	/**
	 * @brief вывод множества.
	 * 
	 * @tparam T1 - тип хранимых данных.
	 * @return std::ostream& - поток вывода.
	 */
	template<typename T1>
	friend std::ostream & operator<<(std::ostream &, const Set<T1> &);
};

template<typename T>
bool operator==(Set<T> lhs, Set<T> rhs)
{
	for (size_t i = 0; i < lhs.m_size; i++)
	{
		if (rhs.getMultiplicity(lhs.m_data[i]) != lhs.m_multiplicity[i])
		{
			return false;
		}
	}
	for (size_t i = 0; i < rhs.m_size; i++)
	{
		if (lhs.getMultiplicity(rhs.m_data[i]) != rhs.m_multiplicity[i])
		{
			return false;
		}
	}
	return true;
}

template<typename T>
bool operator!=(Set<T> lhs, Set<T> rhs)
{
	return !(lhs == rhs);
}

template<typename T>
std::ostream & operator<<(std::ostream &out, const Set<T> &set)
{
	out << "{ ";
	for (size_t i = 0; i < set.m_size; i++) {
		for (size_t j = 0; j < set.m_multiplicity[i]; j++) {
			try
			{
				T currentElement = std::get<T>(set.m_data[i]);
				out << currentElement;
			}
			catch (const std::bad_variant_access&)
			{
				Set<T> currentElementSet = std::get< Set<T> >(set.m_data[i]);
				out << currentElementSet;
			}
			out << ' ';
		}
	}
	out << "}";
	
	return out;
}

#endif // SET_HPP