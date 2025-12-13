#pragma once
#include <iostream>
#include <concepts>
#include <vector>

template<typename T>
concept Num = std::integral<T> || std::floating_point<T>;

template<Num T>
class NumbersSequence
{
public:
	NumbersSequence(const int& count, const T& min, const T& max, int decimals = 2);
	const std::vector<T>& GetSequence() const;
	T GetSum() const;
	T RoundToDecimals(const T& value);
	bool Equals(const T& a, const T& b) const;
private:
	std::vector<T> sequence;
	T sum = 0;
	int decimals;

	T GenerateRandomNumber(const T& min, const T& max);
	T GenerateValidNumber(const T& min, const T& max);
};

#include "NumbersSequence.tpp"