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

using typeNumber = uint64_t;

class AsyncSort final
{
private:
    //We allocate 4Mb buffer, because quick sort may require O(n) memory
    static constexpr size_t MAXSIZE = (4*1024*1024) / sizeof(typeNumber);
    
    size_t counter;
    
    std::vector<std::string> file_list;
    std::vector<typeNumber> buffer_;
    
    void quick_sort()
    {
        auto mid = buffer_.begin();
        size_t shift = buffer_.size() / 2;
        std::advance(mid, shift);
        
        std::thread worker_1(&AsyncSort::sort_, buffer_.begin(), mid);
        std::thread worker_2(&AsyncSort::sort_, mid, buffer_.end());
        
        std::inplace_merge(buffer_.begin(), mid, buffer_.end());
        
        worker_1.join();
        worker_2.join();
        
        return;
    }
    
    bool writeFile()
    {
        std::string fileName = "semi_result" + std::to_string(counter) + ".bin";
        std::ofstream file(fileName, std::ios::binary);
        
        if (!file)
        {
            std::cerr << "Can't open " << fileName << '\n';
            return false;
        }
        counter++;
        
        file.write(reinterpret_cast<char *> (buffer_.data()), buffer_.size() * sizeof(typeNumber));
        
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
            
            result_name = "s_result" + std::to_string(counter) + ".bin";
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
    
public:
    AsyncSort()
    :counter(0),
    buffer_(MAXSIZE)
    {}
    
    AsyncSort(const AsyncSort &) = delete;
    AsyncSort(AsyncSort &&) = delete;
    

    void process(std::ifstream & file)
    {
        while (!file.eof())
        {
            for (size_t i = 0; i != MAXSIZE; i++)
            {
                if (file.read(reinterpret_cast<char *>(&buffer_[i]), sizeof(uint64_t)).eof())
                {
                    while(i != MAXSIZE)
                    {
                        buffer_[i++] = 0;
                    }
                    break;
                }
            }
            quick_sort();
            writeFile();
        }
        fileMerge();
    }
    
    static void sort_(std::vector<typeNumber>::iterator left, std::vector<typeNumber>::iterator right)
    {
        if (right - left <= 1)
            return;
    
        typeNumber mid = *(left + (right - left) / 2);
        std::vector<typeNumber>::iterator yetLeft = left, yetRight = right - 1;
    
        while (yetLeft <= yetRight)
        {
            while (*yetLeft < mid) yetLeft++;
            while (*yetRight > mid) yetRight--;
                
            if (yetLeft <= yetRight)
            {
                std::swap(*yetLeft, *yetRight);
                yetLeft++;
                yetRight--;
            }
        }
    
        if (left < yetRight)
            sort_(left, yetRight + 1);
        if (yetLeft < right)
            sort_(yetLeft, right);
    }
};


int main()
{
    std::string fileName = "data.bin";
    std::ifstream file(fileName, std::ios::binary);
    if (!file)
    {
        std::cerr << "Can't open " << fileName << '\n';
        return 1;
    }
    
    AsyncSort machine;
    machine.process(file);
    
    return 0;
}
