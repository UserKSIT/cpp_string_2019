//
//  main.cpp
//  W_1
//
//  Created by Артём on 16/03/2019.
//  Copyright © 2019 Ерошев Артём. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "numbers.dat"



int main(int argc, const char * argv[]) {
    //если у нас нечётное число аргументов - error
    if (argc % 3 != 0){
        //std::cout << "Incorrect input" << std::endl;
        return -1;
    }
    
    std::vector<int> turn;
    //сохряняем диапазоны
    for (int i = 1; i < argc; ++i)
    {
        turn.push_back(std::atoi(argv[i]));
    }
    
    std::vector<int>::const_iterator from = turn.begin();
    std::vector<int>::const_iterator to = turn.begin();
    to++;
    
    unsigned int res = 0;
    unsigned int i = 0;
    bool flag;
    
    while(from != turn.end()){
        res = 0;
        //проверка корректности диапазона
        if (*to <= *from){
            //std::cout << "Incorrect input" << std::endl;
            std::cout << "0" << std::endl;
            return 0;
        }
        //поиск начала диапазона
        for (i = 0; (Data[i] != *from) && (i < Size); i++)
            if (Data[i] > *from){
                //std::cout << "Don't exist this number" << std::endl;
                std::cout << "0" << std::endl;
                return 0;
            }
        //проход по диапазону
        while (Data[i] <= *to){
            flag = true;
            //перебор делитель до sqrt(Data[i])
            for (unsigned int j = 2; (j * j) - 1 < Data[i]; j++){
                if (Data[i] % j == 0 && Data[i] != 2){
                    flag = false;
                    break;
                }
            }
            if (flag){
                std::cout << Data[i] << std::endl;
                res++;
            }
            i++;
        }
        from += 2;
        to += 2;
        std::cout << res << ' ';
    }
    return 0;
}
