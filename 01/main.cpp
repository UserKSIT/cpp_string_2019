//
//  main.cpp
//  W_1
//
//  Created by Артём on 16/03/2019.
//  Copyright © 2019 Ерошев Артём. All rights reserved.
//

#include <iostream>
#include "numbers.dat"

inline int binary_search(int key){
    int left = 0;
    int right = Size - 1;
    int search = -1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (key == Data[mid]) {
            search = mid;
            break;
        }
        if (key < Data[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }
    return search;
}

int main(int argc, const char * argv[]) {
    //если у нас нечётное число аргументов - error
    if (argc % 3 != 0)
        return -1;
    
    unsigned int result = 0;
    unsigned int current_position = 0;
    unsigned int counter = 1;
    bool flag;
    
    while(counter + 1 < argc){
        result = 0;

        int from = std::atoi(argv[counter]);
        int to = std::atoi(argv[counter + 1]);
        
        //проверка корректности диапазона
        if (to <= from){
            //std::cout << "Incorrect input" << std::endl;
            std::cout << "0" << std::endl;
            return 0;
        }
        
        //поиск начала диапазона
        current_position = binary_search(from);
        if (current_position == -1){
            return 0;
        }
    
        while (Data[current_position] == 1)
            current_position++;
        //проход по диапазону
        while (Data[current_position] <= to && current_position < Size){
            flag = true;
            //перебор делитель до sqrt(Data[i])
            for (unsigned int div = 2; (div * div) - 1 < Data[current_position]; div++){
                if (Data[current_position] % div == 0){
                    flag = false;
                    break;
                }
            }
            if (flag)
                result++;
    
            current_position++;
        }
        counter += 2;
        std::cout << result << std::endl;
    }

    return 0;
}
