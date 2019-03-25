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
        //----------------Interface_SubMatrix----------------//
        
        //---------------------Constructor_SubMatrix---------------------//
        SubMatrix(unsigned int columns = 0): columns(columns){
            data = std::vector<int>(columns);
        }
        ~SubMatrix(){}
        
//        friend std::ostream & operator << (std::ostream &, const SubMatrix &);
        
        //---------------------overload_[]---------------------//
        int operator [] (unsigned int columns) const{
            if (columns >= this->columns)
                throw std::out_of_range("Outside size matrix");
            
            return data[columns];
        }
        int & operator [] (unsigned int columns){
            if (columns >= this->columns)
                throw std::out_of_range("Outside size matrix");
            
            return data[columns];
        }
        
        //---------------------overload_==_and_!=---------------------//
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
        
        //---------------------overload_*=---------------------//
        SubMatrix & operator *= (int number){
            if (!data.empty()){
                for (int i = 0; i != columns; i++)
                data[i] *= number;
            }
            else
                throw std::out_of_range("Empty Matrix");
            return *this;
        }

        
    private:
        //----------------State_SubMatrix----------------//
        std::vector<int> data;
        unsigned int columns;
    };
    //----------------Interface_Matrix----------------//
    
    //---------------------Constructor_Matrix---------------------//
    Matrix(unsigned int rows = 0, unsigned int columns = 0): rows(rows), columns(columns){
        base = std::vector<SubMatrix>(rows);
        
        for (unsigned int i = 0; i != rows; i++)
            base[i] = SubMatrix(columns);
    }
    ~Matrix(){}
    
//    friend std::ostream & operator << (std::ostream &, const Matrix &);
    
    //---------------------overload_[]---------------------//
    const SubMatrix & operator [] (unsigned int rows) const{
        if (rows >= this->rows)
            throw std::out_of_range("Outside size matrix");
        
        return base[rows];
    }
    SubMatrix & operator [] (unsigned int rows){
        if (rows >= this->rows)
            throw std::out_of_range("Outside size matrix");
        
        return base[rows];
    }
    
    //---------------------overload_==_and_!=---------------------//
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
    
    //---------------------get_function---------------------//
    unsigned int getRows() const {
        return rows;
    }
    unsigned int getColumns() const {
        return columns;
    }
    
    //---------------------overload_*=---------------------//
    Matrix & operator *= (int number){
        if (!base.empty()){
            for (int i = 0; i != rows; i++)
            base[i] *= number;
        }
        else
            throw std::out_of_range("Empty Matrix");
        return *this;
    }
    
private:
    //----------------State_Matrix----------------//
    unsigned int columns;
    unsigned int rows;
    std::vector<SubMatrix>  base;
};



//---------------------------Output_in_stream---------------------------//
//std::ostream & operator << (std::ostream & flow, const Matrix & object){
//    for (int i = 0; i != object.rows; i++)
//        flow << object.base[i];
//
//    return flow;
//}
//
//std::ostream & operator << (std::ostream & flow, const Matrix::SubMatrix & object){
//    for (const auto current_columns : object.data)
//        flow << current_columns << "    ";
//
//    flow << std::endl;
//
//    return flow;
//}
