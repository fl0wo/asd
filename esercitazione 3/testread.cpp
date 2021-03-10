#include <cstdio>
#include<iostream>
#include <sstream>
#include <chrono>

std::chrono::time_point<std::chrono::steady_clock> hClock()
{
    return std::chrono::steady_clock::now();
}

std::uint32_t TimeDuration(std::chrono::time_point<std::chrono::steady_clock> Time)
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(hClock() - Time).count();
}


void Benchmark(const char* Name, std::string &str, void(*func)(std::string &str))
{
    auto time = hClock();
    for (int i = 0; i < 100; ++i)
    {
        func(str);
        str.clear();
    }
    std::cout<<Name<<" took: "<<TimeDuration(time) / 100<<" nano-seconds.\n";
}

void unlocked_bench(std::string &str)
{
    char c = '0';
    while((c = getchar()) && (c != -1 && c != '\n' && c != '\r'))
    {
        str += c;
    }
}

void getchar_bench(std::string &str)
{
    char c = '0';
    while((c = getchar())  && (c != -1 && c != '\n' && c != '\r'))
    {
        str += c;
    }
}

void getline_bench(std::string &str)
{
    std::cin.getline(&str[0], str.size());
}

void scanf_bench(std::string &str)
{
    scanf("%[^\n]100s", &str[0]);
}

void fgets_bench(std::string &str)
{
    fgets(&str[0], str.size(), stdin);
}

void cinread_bench(std::string &str)
{
	std::cin.read(&str[0], str.size());
}

int main()
{
    std::string str;
    str.reserve(100);

    Benchmark("getchar_unlocked", str, unlocked_bench);
    Benchmark("getchar", str, getchar_bench);
    Benchmark("getline", str, getline_bench);
    Benchmark("scanf", str, scanf_bench);
    Benchmark("fgets", str, fgets_bench);
    Benchmark("cinread", str, cinread_bench);

    return 0;
}
