/******************************************************************************
    Название:    SymmetricalDifference.cpp
    Разработчик: Вашкевич Максим Викторович
    Дата:        18.02.2024
    Описание:    программа получает через консольные параметры имя файла, чита-
                 ет  из него  все множества,  после чего  программа выводит  на
                 стандартный вывод результат выполнения операции симметрической
                 разности для всех этих множеств
******************************************************************************/

#include "SymmetricalDifference.hpp"

#include <cstdlib> // size_t

/**
 * @brief Симметрическая разность двух множеств.
 *
 * @param a - первое множество.
 * @param b - второе множество.
 * @return Set<int> - симметрическая разность.
 */
Set<int> symmetricalDifference2arg(Set<int> a, Set<int> b)
{
	Set<int> s;
	
	int *aElements = nullptr;
	a.getElements(aElements);
	for (size_t i = 0; i < a.getSize(); i++)
	{
		s.insert(aElements[i],
		         std::abs((int)a.getMultiplicity(aElements[i]) -
		                  (int)b.getMultiplicity(aElements[i])));
	}
	
	int *bElements = nullptr;
	b.getElements(bElements);
	for (size_t i = 0; i < b.getSize(); i++)
	{
		if (!s.isFound(bElements[i]))
		{
			s.insert(bElements[i],
			         std::abs((int)a.getMultiplicity(bElements[i]) -
			                  (int)b.getMultiplicity(bElements[i])));
		}
	}
	
	delete[] aElements;
	delete[] bElements;
	
	return s;
}

Set<int> symmetricalDifference(Set<int> args[], size_t count)
{
	Set<int> result;
	
	for (size_t i = 0; i < count; i++)
	{
		result = symmetricalDifference2arg(result, args[i]);
	}
	
	return result;
}