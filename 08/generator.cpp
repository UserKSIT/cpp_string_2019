//
//  generator.cpp
//  Thread_sort
//
//  Created by Артём on 01/05/2019.
//  Copyright © 2019 Ерошев Артём. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <random>
#include <limits>


template <class T>
T getRandom()
{
    static std::random_device device;
    static std::uniform_int_distribution<T> dist(1);
    return dist(device);
}

int main()
{
    const char* fileName = "data.bin";
    std::ofstream file(fileName, std::ios::binary);
    if (!file)
    {
        std::cerr << "Can't open " << fileName << '\n';
        return 1;
    }
    
    constexpr size_t N = 20;
    unsigned long long push = 0;

    for (size_t i = 0; i < N; ++i)
    {
        push = getRandom<unsigned long long>();
    
        file.write(reinterpret_cast<char *>(&push), sizeof(unsigned long long));
    }
    
    return 0;
}
