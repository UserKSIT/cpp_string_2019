//
//  bigint.h
//  H/W_3
//
//  Created by Артём on 27/03/2019.
//  Copyright © 2019 Ерошев Артём. All rights reserved.
//

#include <iostream>
#include <cmath>

class BigInt{
public:
	BigInt(long long number = 0): size(1), range(size + 101), sign(1), value(new int[range])
	{
    	if (number < 0) 
		{
        	sign = -1;
        	number = abs(number);
    	} 


        size_t i = 0;
        if (number != 0)
        {
			while(number)
			{
				value[i] = static_cast<int>(number % base);
				number /= base;
				i++;
			}
        	size = i;
        }

            
    	for (size_t cleaning = i; cleaning != range; cleaning++)
        	value[cleaning] = 0;
       
	}

	BigInt(const BigInt & copied): size(copied.size), range(copied.range), sign(copied.sign), value(new int[range])
	{
		std::copy(copied.value, copied.value + copied.range, value);
	}
    
	BigInt & operator = (const BigInt & copied)
	{
		if (*this == copied)
			return *this;
		
		int* ptr_copied = new int[copied.range];
		delete [] value;
		value = ptr_copied;

		range = copied.range;
		size = copied.size;
		sign = copied.sign;
		

		std::copy(copied.value, copied.value + range, value);
		return *this;
	}

	BigInt(BigInt && moved): size(moved.size), range(moved.range), sign(moved.sign), value(moved.value)
	{
		moved.value = nullptr;
		moved.size = 0;
		moved.range = 0;
		moved.sign = 0;
	}

	BigInt & operator = (BigInt && moved)
	{
		if (*this == moved)
			return *this;

		delete [] value;

		value = moved.value;
		size = moved.size;
		range = moved.range;
		sign = moved.sign;

		moved.value = nullptr;
		moved.size = 0;
		moved.range = 0;
		moved.sign = 0;

		return *this;
	}

	~BigInt(){delete [] value;}

	BigInt & operator += (const BigInt & addend)
	{
        if (addend.size > range)
        {
    		int* new_ptr_value = new int[addend.size + 100];

            std::copy(value, value + range, new_ptr_value);
            delete [] value;
            value = new_ptr_value;

            range = addend.size + 100;
            for(size_t i = size; i != range; i++)
                value[i] = 0;
        }


		size_t it1 = 0, it2 = 0;
		int sum = 0;
        
		while (it1 != size || it2 != addend.size) {
			if (it1 != size) 
			{
				sum += value[it1];
			} 
			else 
			{
				value[size++] = 0;
				it1 = size - 1;
			}
            
			if (it2 != addend.size) 
			{
	            sum += addend.value[it2++];
			}
            
			value[it1] = sum % base;
			++it1;
			sum /= base;
		}
        
		if (sum) 
			value[size++] = 1;

		return *this;
	}

	BigInt operator + (const BigInt & addend) const
	{
		BigInt tmp = *this;
        
		if (sign == 1 && addend.sign == 1)
			tmp += addend;
		if (sign == 1 && addend.sign == -1)
			tmp -= addend;
		if (sign == -1 && addend.sign == 1)
			tmp -= addend;
		if (sign == -1 && addend.sign == -1)
			tmp += addend;

		return tmp;
	}

	BigInt & operator -= (const BigInt & subtrahend)
	{
		size_t it1 = 0, it2 = 0;
        int dif = 0;
        
    	while (it1 != size || it2 != subtrahend.size) 
    	{
	        if (it1 != size) 
	        {
	            dif += value[it1++];
	        }

	        if (it2 != subtrahend.size) 
	        {
	            dif -= subtrahend.value[it2++];
	        }

	        if (dif < 0) 
	        {
				if (size > 1)
	            	value[it1 - 1] = dif + base;
				else
					value[it1 - 1] = abs(dif);
				
	            dif = -1;
	        } 
	        else 
	        {
	            value[it1 - 1] = dif % base;
	            dif /= base;
	        }
    	}

    	if (dif < 0)
    	 	sign *= -1;
        if (size == 1 && value[0] == 0)
            sign = 1;

    	 return *this;
	}

	BigInt operator - (const BigInt & subtrahend) const
	{
		BigInt tmp = *this;

		if (sign == 1 && subtrahend.sign == 1)
			tmp -= subtrahend;
		if (sign == 1 && subtrahend.sign == -1)
			tmp += subtrahend;
		if (sign == -1 && subtrahend.sign == 1)
			tmp += subtrahend;
		if (sign == -1 && subtrahend.sign == -1)
			tmp -= subtrahend;

		return tmp;
	}

	int compare(const BigInt &compared) const //0 this == compared || -1 this < compared || 1 this > compared
	{
		if (sign == 1 && compared.sign == -1) 
			return 1;
		if (sign == -1 && compared.sign == 1) 
			return -1;

		int check = 1;
		if (sign == -1 && compared.sign == -1) 
			check = -1;

		if (size < compared.size) 
			return -1 * check;
		if (size > compared.size) 
			return check;

		for (size_t i = size; i > 0; --i) 
		{
			if (value[i-1] < compared.value[i-1]) 
				return -1 * check;
			if (value[i-1] > compared.value[i-1]) 
				return check;
		}

		return 0; // ==
	}

	bool operator < (const BigInt & compared) const
	{
		return compare(compared) == -1;
	}

	bool operator <= (const BigInt & compared) const
	{
		int result = compare(compared);

		return result == 0 || result == -1;
	}

	bool operator > (const BigInt & compared) const
	{
		return compare(compared) == 1;
	}

	bool operator >= (const BigInt & compared) const
	{
		int result = compare(compared);

		return result == 0 || result == 1;
	}

	bool operator == (const BigInt & compared) const
	{
		return compare(compared) == 0;
	}

	bool operator != (BigInt const & compared) const
	{
		return !(*this == compared);
	}

	friend std::ostream & operator << (std::ostream & flow, const BigInt & object)
	{
		if (object.sign == -1)
			flow << '-';
		for (size_t i = object.size - 1; i != -1; i--)
			flow << object.value[i];
		return flow;
	}


	BigInt operator -() const
	{
		BigInt x = *this;
		if (x.size != 1 && x.value[0] != 0)
			x.sign *= -1;

		return x;	
	}


private:
	size_t size;
	size_t range;
	int sign;

	static const int base = 1000000000;

	int* value;
};
