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


template <class T, size_t Max>
T getRandom()
{
    static std::random_device device;
    static std::uniform_int_distribution<T> dist(1, Max);
    return dist(device);
}

int main()
{
    const char* fileName = "data.bin";
    std::ofstream file(fileName, std::ios::binary | std::ios::out);
    if (!file)
    {
        std::cerr << "Can't open " << fileName << '\n';
        return 1;
    }
    
    constexpr size_t N = 20;
    uint64_t push = 0;
    for (size_t i = 0; i < N; ++i)
    {
        push = getRandom<uint64_t,2000000000>();
        //std::cout << push << std::endl;
        file.write((char *)&push, sizeof(uint64_t));
    }
    
    return 0;
}
