#pragma once

#include <iostream>

template <class ...Types> struct X;

template <class T>
struct X<T>
{
	void operator()() { std::cout << "Came to X<T>\n"; }
};

template <class T, class ...Types>
struct X<T, Types...>
{
	void operator()() { std::cout << "Came to X<T, Types...>\n"; X<Types...>()(); }
};

template <class ...Types>
void foo()
{
	X<Types...>()();
}

int main()
{
	foo<int>();
	foo<int, double>();
	foo<int, double, char>();
}