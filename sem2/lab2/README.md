# Лабораторная работа №2. Множества
## Цель работы
- Научиться работать с множествами.
- Научиться разрабатывать алгоритмы выполнения операций над множествами.
## Задачи
- Разработать алгоритм одной из операций над множествами.
- Разработать систему тестов, которые продемонстрировали бы работоспособность реализованного алгоритма.
## Вариант
Мой вариант – вариант 12 [методички](https://drive.google.com/drive/folders/1_xy849HXgTDetxSMlFd0KikTBo8-xalN). Нужно реализовать алгоритм вычисления симметрической разности N множеств.
## Список используемых при решении задачи понятий
- Множество – одно из ключевых понятий математики, представляющее собой набор, совокупность объектов любой природы.
- Элементы множества – объекты, составляющие множество.
- Объект принадлежит множеству тогда и только тогда, когда он является его элементом.
- Говорят, что если объект принадлежит множеству, то существует вхождение этого элемента в множество. Допускается неограниченное количество вхождений
одного объекта в какое-либо множество.
- Например, есть множество _S = {a, b, a, a, c}_. В нём элементы _a_, _b_ и _c_ принадлежат множеству _S_, причём множество _S_ имеет три вхождения элемента _a_ (_S|a|_ = 3) и по одному вхождению элементов _b_ и _c_ (_S|b|_ = _S|c|_ = 1).
- Множеством с кратными вхождениями элементов называют множество _S_ тогда и только тогда, когда существует _x_ такой, что истинно _S|x|_ > 1.
- __Симметрической разностью__ множеств _A_ и _B_ с учётом кратных вхождений элементов будем называть множество _S_ тогда и только тогда, когда для любого _x_ истинно _S|x| = max{A|x|-B|x|, B|x|-A|x|}_. Выражение можно упростить: для любого _x_ истинно _S|x| = |A|x|-B|x||_ (модуль разности кратностей _x_ в множествах A и B).
## Реализация
Поскольку множество может содержать в себе не только обычные элементы, а еще и другие множества, а также кортежи (упорядоченные множества), я создал класс Tuple – кортеж, по сути массив (кортеж также может содержать в себе элементы, множества или другие кортежи). Для реализации кортежа, предоставляющего пользователю возможность хранить кортежи или множества произвольного уровня вложенности, был использован класс __std::variant__.
```C++
template<typename T>
class Tuple
{
private:
	std::variant<T, Set<T>, Tuple> *m_data; // элементы
	size_t m_size;				// размер кортежа
	size_t m_capacity;			// емкость (нужно для 	
						// того, чтобы при
						// помещениии нового
						// элемента не 
						// пересоздавать массив 
						// каждый раз, что
						// увеличит
						// произодительность)
};
```
Конструкторы (по умолчанию, копирования) и оператор присваивания:
```C++
Tuple()
{
	this->m_size = 0;
	this->m_capacity = 1;
	this->m_data = new std::variant<T, Set<T>, Tuple>[this->m_capacity];
}

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

Tuple &operator=(const Tuple &s)
{
	if (this != &s) // проверка на самоприсваивание
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
```
Вставка элемента в кортеж производится так:
```C++
void insert(const std::variant<T, Set<T>, Tuple> &value)
{
	// создаем копию на случай добавления самого себя
	// (м/б случай, когда необходимо расширить m_data,
	// имеющий тот же адрес, что и value.m_data (поскольку это по
	// сути один и тот же объект))
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
```
Операторы сравнения:
```C++
// определены как friend

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
	}
	return true;
}

template<typename T>
bool operator!=(Tuple<T> lhs, Tuple<T> rhs)
{
	return !(lhs == rhs);
}
```
Оператор вывода:
```C++
// определен как friend

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
```
Далее я создал класс Set, представляющий собой множество. Множество представляет собой обычный массив (кортеж), с одним лишь отличием: порядок элементов не важен. В массиве могут храниться обычные элементы, экземпляры класса Set и экземпляры класса Tuple (для этого также был использован класс __std::variant__).
```C++
template<typename T>
class Set
{
private:
	std::variant<T, Tuple<T>, Set> *m_data;
	size_t *m_multiplicity; // кратность i-го элемента m_data.
	size_t m_size;
	size_t m_capacity;
};
```
Конструкторы по умолчанию и коприования, а также оператор присваивания выглядят следующим образом:
```C++
Set()
{
	this->m_size = 0;
	this->m_capacity = 1;
	this->m_data = new std::variant<T, Tuple<T>, Set>[this->m_capacity];
	this->m_multiplicity = new size_t[m_capacity];
}

Set(const Set &other)
{
	this->m_size = other.m_size;
	this->m_capacity = other.m_capacity;
		
	this->m_data = new std::variant<T, Tuple<T>, Set>[this->m_capacity];
	this->m_multiplicity = new size_t[this->m_capacity];
		
	for (size_t i = 0; i < this->m_size; i++)
	{
		this->m_data[i] = other.m_data[i];
		this->m_multiplicity[i] = other.m_multiplicity[i];
	}
}

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
			
		this->m_data = new std::variant<T, Tuple<T>, Set>[this->m_capacity];
		this->m_multiplicity = new size_t[this->m_capacity];
			
		for (size_t i = 0; i < this->m_size; i++)
		{
			this->m_data[i] = s.m_data[i];
			this->m_multiplicity[i] = s.m_multiplicity[i];
		}
	}
	return *this;
}
```
Для реализации также пришлось сделать конструктор копирования и оператор присваивания множества:
```C++
Set(const Set &other)
{
	this->m_size = other.m_size;
	this->m_capacity = other.m_capacity;

	this->m_data = new std::variant<T, Set>[this->m_capacity];
	this->m_multiplicity = new size_t[this->m_capacity];

	for (size_t i = 0; i < this->m_size; i++)
	{
		this->m_data[i] = other.m_data[i];
		this->m_multiplicity[i] = other.m_multiplicity[i];
	}
}

Set &operator=(const Set &s)
{
	if (this != &s) // проверка на самоприсваивание
	{
                // удаление прошлого объекта 
		this->m_size = 0;
		this->m_capacity = 0;
		
		delete[] m_data;
		delete[] m_multiplicity;
			
		this->m_data = nullptr;
		this->m_multiplicity = nullptr;
		
                // создание нового со значениями присваемого
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
```
Вставка элемента в множество выполняется так:
```C++
void insert(const std::variant<T, Tuple<T>, Set> &value, size_t count)
{
	// копия value
	std::variant<T, Tuple<T>, Set> valueCopy = value;

	// увеличение кратности в случае наличия элемента во множестве
	for (size_t i = 0; i < this->m_size; i++)
	{
		if (this->m_data[i] == valueCopy)
		{
			this->m_multiplicity[i] += count;
			return;
		}
	}
	
	if (this->m_size == this->m_capacity)
	{
		// увеличение емкости в случае необходимости
		this->m_capacity = this->m_capacity * 3 / 2 + 1;
			
		auto *dataAux = new std::variant<T, Tuple<T>, Set>[this->m_capacity];
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
	
	// добавление
	this->m_data[this->m_size++] = valueCopy;
	this->m_multiplicity[this->m_size - 1] = count;
}
```
Получение кратности какого-либо объекта относительно множества тривиально и не требует объяснений
```C++
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
```
Также для реализации нужно знать размер массива __m_data__.
```C++
size_t getSize()
{
	return this->m_size;
}
```
Также, иногда нужно получать сами элементы массива __m_data__.
```C++
void getElements(std::variant<T, Tuple<T>, Set> *&destination)
{
	if (destination != nullptr)
	{
		delete[] destination;
		destination = nullptr;
	}
		
	if (this->m_size != 0)
	{
		destination = new std::variant<T, Tuple<T>, Set>[this->m_size];
		for (size_t i = 0; i < this->m_size; i++)
		{
			destination[i] = this->m_data[i];
		}
	}
}
```
Дальше в класс нужно было добавить проверку на принадлежность множеству (элемент принадлежит множеству, если кратность его вхождения отлична от нуля).
```C++
bool isFound(const std::variant<T, Set> &value)
{
	return this->getMultiplicity(value) != 0;
}
```
И последнее, что я добавил – это оператор вывода.
```C++
// friend-функция класса.
template<typename T>
std::ostream & operator<<(std::ostream &out, const Set<T> &set)
{
	out << "{ ";
	for (size_t i = 0; i < set.m_size; i++)
	{
		for (size_t j = 0; j < set.m_multiplicity[i]; j++)
		{
			try
			{
				T currentElement = std::get<T>(set.m_data[i]);
				out << currentElement;
			}
			catch (const std::bad_variant_access &)
			{
				try
				{
					Set<T> currentElementSet = std::get< Set<T> >(set.m_data[i]);
					out << currentElementSet;
				}
				catch (const std::bad_variant_access &)
				{
					Tuple<T> currentElementTuple = std::get< Tuple<T> >(set.m_data[i]);
					out << currentElementTuple;
				}
			}
			out << ' ';
		}
	}
	out << "}";
	
	return out;
}
```
Для расчета симметрической разности от двух аргументов я пользовался определением симметрической разности с учетом кратности вхождений элементов.
```C++
template<typename T>
Set<T> symmetricalDifference2arg(Set<T> a, Set<T> b)
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
```
А для обобщения этой операции на N множеств, я воспользовался свойством ассоциативности. Поскольку данная операция ассоциативна, то при последовательном ее применении на трёх и более множествах результат будет накапливаться.
```C++
template<typename T>
Set<T> symmetricalDifference(Set<T> args[], size_t count)
{
	Set<T> result;
	
	for (size_t i = 0; i < count; i++)
	{
		result = symmetricalDifference2arg(result, args[i]);
	}
	
	return result;
}
```
## Тестирование
Я тестировал программу при помощи unit-тестов, используя фреймворк GoogleTest. Для unit-тестирования пришлось реализовывать операторы сравнения множеств.
```C++
// Операторы определены как friend-функции для класса Set

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
```
Всего я протестировал программу на 12 тестовых примерах, каждый из которых был пройден успешно.
```
Тестовый пример №1:
Входные данные:
3
{ 1 1 2 5 5 5 6 }
{ 2 2 2 4 4 5 5 6 7 }
{ 3 4 7 9 15 }
Выходные данные:
{ 1 1 2 2 3 4 5 9 15 }

Тестовый пример №2:
Входные данные:
2
{ a b c }
{ c a b e e }
Выходные данные:
{ e e }

Тестовый пример №3:
Входные данные:
4
{ }
{ }
{ }
{ }
Выходные данные:
{ }

Тестовый пример №4:
Входные данные:
1
{ 1 2 }
Выходные данные:
{ 1 2 }

Тестовый пример №5:
Входные данные:
2
{ 1 1 6 5 5 5 2 }
{ 2 2 2 5 5 4 4 7 6 }
Выходные данные:
{ 2 2 4 4 1 1 7 5 }

Тестовый пример №6:
Входные данные:
1
{ { 1 2 } }
Выходные данные:
{ { 1 2 } }

Тестовый пример №7:
Входные данные:
2
{ 1 { 1 2 } }
{ { 1 2 } 1 }
Выходные данные:
{ }

Тестовый пример №8:
Входные данные:
2
{ { 1 } }
{ 1 }
Выходные данные:
{ 1 { 1 } }

Тестовый пример №9:
Входные данные:
2
{ 1 { 1 } { 1 { 1 } } }
{ 1 }
Выходные данные:
{ { 1 } { 1 { 1 } } }

Тестовый пример №10:
Входные данные:
2
{ < 1 2 > }
{ < 2 1 > }
Выходные данные:
{ < 1 2 > < 2 1 > }

Тестовый пример №11:
Входные данные:
2
{ < 1 2 > }
{ < 1 2 > }
Выходные данные:
{ }

Тестовый пример №12:
Входные данные:
2
{ A B { C < D { E F } > G } }
{ C { < D { E F } > C G } }
Выходные данные:
{ A B C }
```
Все тесты были успешно пройдены:
![Тесты пройдены](images/unittestspassed.png)
## Вывод
В ходе данной лабораторной работы я:
- Научился работать с множествами
- Научиться разрабатывать алгоритмы выполнения операций над множествами.