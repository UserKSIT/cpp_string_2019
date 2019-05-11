//
//  main.cpp
//  Thread_sort
//
//  Created by Артём on 01/05/2019.
//  Copyright © 2019 Ерошев Артём. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <algorithm>


constexpr size_t Mb = 1024*1024;
constexpr size_t read_value = (8 * Mb - sizeof(std::thread) * 2);
constexpr size_t MAXSIZE = read_value / sizeof(uint64_t);

using typeNumber = uint64_t;

size_t counter = 0;
std::vector<std::string> file_list;

void sort_(std::vector<typeNumber>::iterator begin_, std::vector<typeNumber>::iterator end_)
{
    std::sort(std::forward<std::vector<typeNumber>::iterator>(begin_), std::forward<std::vector<typeNumber>::iterator>(end_));
}


void quick_sort(std::vector<typeNumber>& buffer_)
{
    auto mid = buffer_.begin();
    size_t shift = buffer_.size() / 2;
    std::advance(mid, shift);
    
    std::thread worker_1(sort_, buffer_.begin(), mid);
    std::thread worker_2(sort_, mid, buffer_.end());
    
    worker_1.join();
    worker_2.join();
    
    return;
}

bool writeFile(std::vector<typeNumber>& buffer_)
{
    std::string fileName = "/Users/artem/Desktop/Programing/Techoatom/C++/Thread_sort/Thread_sort/semi_result" + std::to_string(counter) + ".bin";
    std::ofstream file(fileName, std::ios::binary);
    
    if (!file)
    {
        std::cerr << "Can't open " << fileName << '\n';
        return false;
    }
    counter++;
    
    file.write(reinterpret_cast<char *> (buffer_.data()), read_value);
    
    file_list.push_back(fileName);
    
    return true;
}

bool fileMerge()
{
    std::ifstream file_1;
    std::ifstream file_2;
    std::ofstream result_file;
    
    std::string name_1;
    std::string name_2;
    std::string result_name;
    
    while (file_list.size() >= 2)
    {
        name_1 = file_list.back();
        file_list.pop_back();
        name_2 = file_list.back();
        file_list.pop_back();
        
        file_1.open(name_1, std::ios::binary);
        file_2.open(name_2, std::ios::binary);
        
        result_name = "/Users/artem/Desktop/Programing/Techoatom/C++/Thread_sort/Thread_sort/s_result" + std::to_string(counter) + ".bin";
        counter--;
        
        result_file.open(result_name, std::ios::binary);
        if (!result_file)
        {
            std::cerr << "Can't open " << result_name << '\n';
            
            std::string name;
            while(!file_list.empty())
            {
                name = file_list.back();
                file_list.pop_back();
                std::remove(name.c_str());
            }
            
            return false;
        }
        
        typeNumber number_1 = 0, number_2 = 0;
        if (!file_1.eof() && !file_2.eof())
        {
            file_1.read(reinterpret_cast<char *>(&number_1), sizeof(typeNumber));
            file_2.read(reinterpret_cast<char *>(&number_2), sizeof(typeNumber));
        }
        else
            return false;
        
        while(!file_1.eof() && !file_2.eof())
        {
            if(number_1 < number_2)
            {
                result_file.write(reinterpret_cast<char *>(&number_1), sizeof(typeNumber));
                file_1.read(reinterpret_cast<char *>(&number_1), sizeof(typeNumber));
            }
            else
            {
                result_file.write(reinterpret_cast<char *>(&number_2), sizeof(typeNumber));
                file_2.read(reinterpret_cast<char *>(&number_2), sizeof(typeNumber));
            }
        }
        
        
        while(!file_1.eof())
        {
            file_1.read(reinterpret_cast<char *>(&number_1), sizeof(typeNumber)/sizeof(char));
            
            result_file.write(reinterpret_cast<char *>(&number_1), sizeof(typeNumber)/sizeof(char));
        }

        while(!file_2.eof())
        {
            file_2.read(reinterpret_cast<char *>(&number_2), sizeof(typeNumber)/sizeof(char));
            
            result_file.write(reinterpret_cast<char *>(&number_2), sizeof(typeNumber)/sizeof(char));
        }
        
        file_list.push_back(result_name);
        
        file_1.close();
        file_2.close();
        result_file.close();
        
        std::remove(name_1.c_str());
        std::remove(name_2.c_str());
    }
    
    return true;
}



int main()
{
    std::vector<typeNumber> buffer_(MAXSIZE);
    
    const char* fileName = "/Users/artem/Desktop/Programing/Techoatom/C++/Thread_sort/Thread_sort/data.bin";
    std::ifstream file(fileName, std::ios::binary);
    if (!file)
    {
        std::cerr << "Can't open " << fileName << '\n';
        return 1;
    }
    
    while (!file.eof())
    {
        file.read(reinterpret_cast<char *> (buffer_.data()), read_value);
        
        if(file.good())
        {
            quick_sort(buffer_);
            writeFile(buffer_);
        }
    }
    
    fileMerge();
    
    return 0;
}
