//
//  Matrix.hpp
//  HW_2
//
//  Created by Артём on 25/03/2019.
//  Copyright © 2019 Ерошев Артём. All rights reserved.
//
#pragma once

#include <iostream>
#include <vector>

class Matrix{
public:
    class SubMatrix{
    public:     
        SubMatrix(size_t columns = 0): columns(columns), data(std::vector<int>(columns)){}
        ~SubMatrix(){}
        

        int operator [] (size_t columns) const{
            if (columns >= this->columns)
                throw std::out_of_range("Outside size matrix");
            
            return data[columns];
        }
        int & operator [] (size_t columns){
            if (columns >= this->columns)
                throw std::out_of_range("Outside size matrix");
            
            return data[columns];
        }
        
        
        bool operator == (const SubMatrix & object) const{
            for (int i = 0; i != columns; i++){
                
                if (data[i] != object.data[i])
                    return false;
            }
            
            return true;
        }
        bool operator != (const SubMatrix & object) const{
            return !(*this == object);
        }
        
        
        SubMatrix & operator *= (const int number){
            if (!data.empty()){
                for (int i = 0; i != columns; i++)
                data[i] *= number;
            }
            else
                throw std::out_of_range("Empty Matrix");
            return *this;
        }

        
    private:
        size_t columns;
        std::vector<int> data;
    };


    Matrix(size_t rows = 0, size_t columns = 0): rows(rows), columns(columns), base(std::vector<SubMatrix>(rows)){
        for (size_t i = 0; i != rows; i++)
            base[i] = SubMatrix(columns);
    }
    ~Matrix(){}
    

    const SubMatrix & operator [] (size_t rows) const{
        if (rows >= this->rows)
            throw std::out_of_range("Outside size matrix");
        
        return base[rows];
    }
    SubMatrix & operator [] (size_t rows){
        if (rows >= this->rows)
            throw std::out_of_range("Outside size matrix");
        
        return base[rows];
    }
    

    bool operator == (const Matrix & object) const {
        if (rows == object.rows && columns == object.columns){
            for (int i = 0; i != rows; i++){
                if (!(base[i] == object.base[i]))
                return false;
            }
            return true;
        }
        else
            return false;
    }
    bool operator != (const Matrix & object) const {
        return (!(*this == object));
    }
    
 
    size_t getRows() const {
        return rows;
    }
    size_t getColumns() const {
        return columns;
    }
    
 
    Matrix & operator *= (const int number){
        if (!base.empty()){
            for (int i = 0; i != rows; i++)
            base[i] *= number;
        }
        else
            throw std::out_of_range("Empty Matrix");
        return *this;
    }
    
private:
    size_t rows;
    size_t columns;
    std::vector<SubMatrix>  base;
};
