/*
 * File:   Sales.h
 * Author: Tanya Badrljica, Andrew Sears, Rana Hussain
 *
 * Created on February 24, 2019, 11:57 AM
 */

#define SALES_H
#include <iostream>
#include <cstdlib>
#include <string>
#include "Employee.h"
using namespace std;

class Sales : public Employee
{   
    public:
        double totalSales, belowSales;
        //constructor
        Sales(string t, string n, string i, string b) : Employee(t, n, i, b)
        {
             belowSales = 0;
            totalSales = 0;
            
        }   //end constructor
        
         virtual void setTotalSales(double t)
        {
            totalSales += t;
        }
        
         virtual double getTotalSales() const
        {
            return totalSales;
        }   //end getTotalSales
        
         
              
         virtual double getCommission() 
        {
             return 5 * totalSales / 100;
        }   //end getCommission
            
         virtual void setBelowSales(double t)
        {
            belowSales += t;
        }
        
         virtual double getBelowSales() 
        {
            return belowSales;
        }   //end getTotalSales
         
        virtual string to_String()
        {
            // get the data from the parent
            string msg; //= Employee::to_string();
            
            // append the data that is unique to this class
            msg = getTitle() + ";" + getName() + ";" + getID() + ";" + getBossID() + ";" + "\n" +" Total Sales: " + to_string(getTotalSales());
            return msg;
        }   //end to_string
        
};  //end class Sales
