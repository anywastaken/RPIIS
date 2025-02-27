/******************************************************************************
    Название:    SymmetricalDifference.cpp
    Разработчик: Вашкевич Максим Викторович
    Дата:        18.02.2024
    Описание:    программа получает через консольные параметры имя файла, чита-
                 ет  из него  все множества,  после чего  программа выводит  на
                 стандартный вывод результат выполнения операции симметрической
                 разности для всех этих множеств
******************************************************************************/

#include <iostream>  // std::cout
#include <fstream>   // std::ifstream
#include <cstdlib>   // size_t
#include <string>    // std::string
#include <exception> // std::exception
#include <stack>     // std::stack
#include <cctype>    // isalpha, isdigit

#include "Tuple.hpp"
#include "Set.hpp"
#include "SymmetricalDifference.hpp"

/**
 * @brief Выдаёт количество множеств во входном файле.
 *
 * @param filePath - путь до входного файла.
 * @return size_t - количество множеств.
 */
size_t getSetsCount(std::istream &in)
{
	std::string setsCountStr;
	std::getline(in, setsCountStr);
	
	long long setsCount = 0;
	try
	{
		setsCount = std::stoll(setsCountStr);
		if (setsCount <= 0)
		{
			throw std::exception();
		}
	}
	catch (const std::exception &ex)
	{
		std::cout << "The sets count value is invalid! Please, fix the file."
		             "\n";
		exit(EXIT_FAILURE);
	}
	
	return (size_t)setsCount;
}

/**
 * @brief Ищет ближайшую справа к текущему элементу закрывающую скобку.
 *
 * @param s - строка.
 * @param idx - индекс, начиная с которого рассматривается строка.
 *
 * @return size_t - индекс скобки.
 */
size_t findClosestClosingBrace(const std::string &s, size_t idx)
{
	for (size_t i = idx; i < s.size(); i++)
	{
		if (s[i] == '}')
		{
			return i;
		}
	}
	return std::string::npos;
}

size_t findClosestClosingAngleBracket(const std::string &s, size_t idx)
{
	for (size_t i = idx; i < s.size(); i++)
	{
		if (s[i] == '>')
		{
			return i;
		}
	}
	return std::string::npos;
}

Set<std::string> getSetByString(std::string &, size_t);

Tuple<std::string> getTupleByString(std::string &tupleStr, size_t beginIdx = 0)
{
	Tuple<std::string> t;
	std::string currentValue;
	for (size_t i = beginIdx; i < tupleStr.size(); i++)
	{
		if (tupleStr[i] == ' ')
		{
			if (currentValue == "<")
			{
				t.insert(getTupleByString(tupleStr, i + 1));
				tupleStr.erase(i - 1, findClosestClosingAngleBracket(tupleStr, i) - i + 3);
				i -= 2;
				// i = findKthClosingBrace(setStr, i, level) + 1;
			}
			else if (currentValue == ">")
			{
				return t;
			}
			else if (currentValue == "{")
			{
				t.insert(getSetByString(tupleStr, i + 1));
				tupleStr.erase(i - 1, findClosestClosingBrace(tupleStr, i) - i + 3);
				i -= 2;
			}
			else
			{
				if (!currentValue.empty()) {
					t.insert(currentValue);
				}
			}
			currentValue.clear();
		}
		else
		{
			currentValue.push_back(tupleStr[i]);
		}
	}
	
	if (!currentValue.empty() && currentValue != ">")
	{
		t.insert(currentValue);
	}
	
	return t;
}

/**
 * @brief Переводит строку в множество.
 *
 * @param setStr - множество в виде строки.
 * @param beginIdx - индекс, начиная с которого рассматривается строка.
 *
 * @return Set<int> - множество.
 */
Set<std::string> getSetByString(std::string &setStr, size_t beginIdx = 0)
{
	Set<std::string> s;
	std::string currentValue;
	for (size_t i = beginIdx; i < setStr.size(); i++)
	{
		if (setStr[i] == ' ')
		{
			if (currentValue == "{")
			{
				s.insert(getSetByString(setStr, i + 1), 1);
				setStr.erase(i - 1, findClosestClosingBrace(setStr, i) - i + 3);
				i -= 2;
				// i = findKthClosingBrace(setStr, i, level) + 1;
			}
			else if (currentValue == "}")
			{
				return s;
			}
			else if (currentValue == "<")
			{
				s.insert(getTupleByString(setStr, i + 1), 1);
				setStr.erase(i - 1, findClosestClosingAngleBracket(setStr, i) - i + 3);
				i -= 2;
			}
			else
			{
				if (!currentValue.empty()) {
					s.insert(currentValue, 1);
				}
			}
			currentValue.clear();
		}
		else
		{
			currentValue.push_back(setStr[i]);
		}
	}
	
	if (currentValue == "}")
	{
		return s;
	}
	if (!currentValue.empty())
	{
		s.insert(currentValue, 1);
	}
	
	return s;
}

bool bracketsAreCorrect(const std::string &s)
{
	std::stack<char> balance;
	for (char current : s)
	{
		switch (current)
		{
			case '{':
				balance.push('}');
				break;
			case '<':
				balance.push('>');
				break;
			case '}':
			case '>':
				if (balance.empty() || balance.top() != current)
				{
					return false;
				}
				balance.pop();
				break;
			default:
				break;
		}
	}
	return balance.empty();
}

/**
 * @brief Выдаёт следующее множество, находящееся во входном файле.
 *
 * @param in - поток ввода
 * @return Set<int> - следующее множество.
 */
Set<std::string> getNextSet(std::istream &in)
{
	std::string setStr;
	getline(in, setStr);
	if (setStr.front() != '{' || setStr.back() != '}')
	{
		std::cout << "The set is invalid. Please, fix the file.\n";
		exit(EXIT_FAILURE);
	}
	setStr.erase(setStr.begin());
	setStr.pop_back();
	if (setStr.front() != ' ' || setStr.back() != ' ')
	{
		std::cout << "The set is invalid. Please, fix the file.\n";
		exit(EXIT_FAILURE);
	}
	setStr.erase(setStr.begin());
	setStr.pop_back();
	if (!bracketsAreCorrect(setStr)) {
		std::cout << "The set is invalid. Please, fix the file.\n";
		exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < setStr.size(); i++) {
		if (!isalpha(setStr[i]) && !isdigit(setStr[i]) && setStr[i] != ' ' &&
		    setStr[i] != '}' && setStr[i] != '{' &&
		    setStr[i] != '<' && setStr[i] != '>')
		{
			std::cout << "The set is invalid. Please, fix the file.\n";
			exit(EXIT_FAILURE);
		}
	}
	for (size_t i = 1; i < setStr.size(); i++) {
		if (setStr[i] == '}' || setStr[i] == '>' || setStr[i] == '<' || setStr[i] == '{')
		{
			if (setStr[i - 1] != ' ') {
				std::cout << "The set is invalid. Please, fix the file.\n";
				exit(EXIT_FAILURE);
			}
		}
	}
	Set<std::string> s = getSetByString(setStr);
	return s;
}

int main([[maybe_unused]]int argc, const char *argv[])
{
	const std::string FILE_PATH = argv[1];
	
	Set<std::string> result;
	
	std::ifstream fin(FILE_PATH);
	size_t setsCount = getSetsCount(fin);
	for (size_t i = 0; i < setsCount; i++)
	{
		Set<std::string> currentSet = getNextSet(fin);
		// std::cout << currentSet << '\n';
		
		result = symmetricalDifference(result, currentSet);
	}
	fin.close();
	
	std::cout << result << '\n';
	
	return EXIT_SUCCESS;
}