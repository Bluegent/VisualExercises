#include <gtest/gtest.h>
#include <unordered_map>
#include <map>
#include <sstream>
#include <iostream>
#include <chrono>
#include <string_view>
#include <stdint.h>
#include <ve/Helper/Math.hpp>


class BenchMarker
{
private:
    std::string name;
    std::chrono::steady_clock::time_point start;
public:
    BenchMarker(const std::string& name)
        : name{ name }
        , start{ std::chrono::steady_clock::now() }
    {

    }

    ~BenchMarker()
    {
        auto end = std::chrono::steady_clock::now();
        std::cout << name << " took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " msec\n";
    }

};

const size_t count = 1000000;
const size_t length = 10;

std::vector<const char*> makeStrings(const size_t amount, const size_t length)
{
    std::stringstream ss;
    ss << "Generating " << count << " strings of length " << length;
    std::vector<const char*> strings;
    {
        BenchMarker benchmarker(ss.str());
        strings.reserve(amount);
        for (size_t i = 0; i < amount; ++i)
        {
            char* str = new char[length];
            for (size_t j = 0; j < length; ++j)
            {
                str[j] = ve::getRandom('a', 'z');
            }
            strings.emplace_back(str);
        }
    }
    return strings;
}


void free(const std::vector<const char*>& vec)
{
    for (auto& str : vec)
    {
        delete[] str;
    }
}



template <class MapType>
void benchmarkMap(const std::string& msg)
{
    std::cout << "Benchmarking variant: " << msg << "\n";
    auto strings = makeStrings(count, length);
    std::string notContained("aaaaa");
    MapType map;
    {
        BenchMarker marker("Insertion");
        for (const auto& str : strings)
        {
            map.emplace(str, 0);
        }
    }

    {
        BenchMarker marker("Find and access (contained key)");
        for (const auto& str : strings)
        {
            (void)map.find(str)->second;
        }
    }

    {
        BenchMarker marker("Find uncontained key");
        for (size_t i = 0; i < strings.size(); ++i)
        {
            (void)map.find(notContained);
        }
    }
    std::cout << "-----------------------\n";
    free(strings);

}

TEST(Benchmark, BenchmarkMap)
{
    //benchmarkMap<std::unordered_map<std::string_view, int>>("unordered_map<string_view,int>");
    //benchmarkMap<std::unordered_map<std::string, int>>("unordered_map<string,int>");

    //benchmarkMap<std::map<std::string_view, int>>("map<string_view,int>");
    //benchmarkMap<std::map<std::string, int>>("map<string,int>");

}


struct LPoint
{
public:
    uint64_t val;
    LPoint(int32_t _x, int32_t _y)
    {
        val = (uint64_t)(((uint64_t)_x & 0xFFFFFFFF) | (((uint64_t)_y) << 32));
    }
    LPoint(uint64_t l)
    {
        val = l;
    }
    inline int32_t  getX()
    {
        return (int32_t)(val & 0xFFFFFFFF);
    }
    inline int32_t getY()
    {
        return (int32_t)(val >> 32);
    }
};


struct PPoint
{
public:
    int32_t x, y;
    PPoint(int32_t x, int32_t y)
        : x{ x }
        , y{ y }
    {
    }
    inline int32_t getX()
    {
        return x;
    }
    inline int32_t getY()
    {
        return y;
    }
};

const size_t pointCount = 1;// = 100000000;

template <typename PointType>
int64_t createAndGetPoints(const std::string & name)
{
    int64_t sum = 0;
    BenchMarker marker(name);
    for (size_t i = 0; i < pointCount; ++i)
    {
        PointType point(i, i);
        sum+= point.getX();
        sum+= point.getY();
    }
    return sum;
}

int64_t createAndGetPointsNoGet(const std::string& name)
{
    int64_t sum = 0;
    BenchMarker marker(name);
    for (size_t i = 0; i < pointCount; ++i)
    {
        PPoint point(i, i);
        sum += point.x;
        sum += point.y;
    }
    return sum;
}

TEST(Benchmark, TestPoints)
{
    /*
    ASSERT_NE(0l, createAndGetPoints<LPoint>("LPoint"));
    ASSERT_NE(0l, createAndGetPoints<PPoint>("PPoint"));
    ASSERT_NE(0l, createAndGetPointsNoGet("PPointDirectAccess"));
    */
}