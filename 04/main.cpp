//
//  main.cpp
//  H/W_3
//
//  Created by Артём on 27/03/2019.
//  Copyright © 2019 Ерошев Артём. All rights reserved.
//
#include "bigint.h"
#include <limits>

void check(int64_t x, int64_t y)
{
    const BigInt bigX = x;
    const BigInt bigY = y;

    if (bigX + bigY != BigInt(x + y))
    {
        std::cout << x << " + " << y << " != " << x + y << " got " << bigX + bigY << '\n';
        std::cout << "BigInt(x + y)" << BigInt(x + y) << std::endl;
        std::cout << "BigX " << bigX << std::endl;
        std::cout << "Bigy " << bigY << std::endl;
    }

    if (bigX - bigY != BigInt(x - y))
    {
        std::cout << x << " - " << y << " != " << x - y << " got " << bigX - bigY << '\n';
        std::cout << "BigInt(x - y)" << BigInt(x - y) << std::endl;
        std::cout << "BigX " << bigX << std::endl;
        std::cout << "Bigy " << bigY << std::endl;
    }
}

int main(int argc, const char* argv[])
{
//    std::cout << "Start" << std::endl;
//    for (long long i = std::numeric_limits<int64_t>::min(); i <= std::numeric_limits<int64_t>::max(); ++i)
//    {
//        for (long long j = std::numeric_limits<int64_t>::min(); j <= std::numeric_limits<int64_t>::max(); ++j)
//        {
//            check(i, j);
//        }
//    }
//    std::cout << "done" << std::endl;

BigInt x = 9223372036854775807;
BigInt y = 9223372036854775807;
    for (long long i = 0; i != 1000000000; i++)
        x += y;
    
BigInt z = x + y;
    if (z == x + y)
    {
        std::cout << "Z - " << z << std::endl;
        std::cout << "X - " << x << std::endl;
        std::cout << "Y - " << y << std::endl;
    }

//std::cout << z << std::endl;

	return 0;
}
