#ifndef NUMBERSSEQUENCE_TPP
#define NUMBERSSEQUENCE_TPP

#include "NumbersSequence.h"
#include <random>

template<Num T>
NumbersSequence<T>::NumbersSequence(const int& count, const T& min, const T& max, int decimals) : 
	decimals(decimals)
{
	sequence.resize(count);

	for (int i = 0; i < count; ++i)
	{
		T randomNumber = GenerateValidNumber(min, max);
		sequence[i] = randomNumber;
		sum += randomNumber;
	}
}

template<Num T>
const std::vector<T>& NumbersSequence<T>::GetSequence() const
{
	return sequence;
}

template<Num T>
T NumbersSequence<T>::GetSum() const
{
	return sum;
}

template<Num T>
T NumbersSequence<T>::GenerateRandomNumber(const T& min, const T& max)
{
	static std::random_device rd;
	static std::mt19937 generator(rd());

	if constexpr (std::is_integral_v<T>)
	{
		std::uniform_int_distribution<T> dist(min, max);
		return dist(generator);
	}
	else if constexpr (std::is_floating_point_v<T>)
	{
		std::uniform_real_distribution<T> dist(min, max);

		return RoundToDecimals(dist(generator));
	}
}

template<Num T> T NumbersSequence<T>::RoundToDecimals(const T& value)
{
	T aux = value;

	if (decimals < 0)
		return aux;

	T factor = static_cast<T>(std::pow(10, decimals));
	aux = std::round(aux * factor) / factor;
	return aux;
}

template<Num T>
bool NumbersSequence<T>::Equals(const T& a, const T& b) const
{
	if (decimals < 0)
		return a == b;

	T factor = static_cast<T>(std::pow(10, decimals));

	return std::round(a * factor) == std::round(b * factor);
}

template<Num T>
T NumbersSequence<T>::GenerateValidNumber(const T& min, const T& max)
{
	T value;

	do
	{
		value = GenerateRandomNumber(min, max);
	} while (sum + value < 0);

	return value;
}

#endif // NumbersSequence.tpp