/*
 * File:   SuperSales.h
 * Author: Tanya Badrljica, Andrew Sears, Rana Hussain
 *
 * Created on February 24, 2019, 1:05 PM
 */

#define SUPERSALES_H
#include <iostream>
#include <cstdlib>
#include <string>
#include "Sales.h"
using namespace std;

class SuperSales : public Sales
{
    public:
        
        //constructor
        SuperSales(string t, string n, string i, string b) : Sales(t, n, i, b)
        {
            
        }   //end constructor
       
        virtual double getCommission() 
        {
            return 6.5 * getTotalSales() / 100;
        }   //end getCommission
        
        
        
};  //end class SuperSales