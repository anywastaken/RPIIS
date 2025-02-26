#ifndef SYMMETRICAL_DIFFERENCE_HPP
#define SYMMETRICAL_DIFFERENCE_HPP

#include "Set.hpp"
#include "Tuple.hpp"

/**
 * @brief Симметрическая разность двух множеств.
 *
 * @param a - первое множество.
 * @param b - второе множество.
 * @return Set<T> - симметрическая разность.
 */
template<typename T>
Set<T> symmetricalDifference(Set<T> a, Set<T> b)
{
	Set<T> s;
	
	std::variant< T, Tuple<T>, Set<T> > *aElements = nullptr;
	a.getElements(aElements);
	for (size_t i = 0; i < a.getSize(); i++)
	{
		s.insert(aElements[i],
		         std::abs((int)a.getMultiplicity(aElements[i]) -
		                  (int)b.getMultiplicity(aElements[i])));
	}
	
	std::variant< T, Tuple<T>, Set<T> > *bElements = nullptr;
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

#endif // SYMMETRICAL_DIFFERENCE_HPP