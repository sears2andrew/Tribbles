/*
 * File:   Manager.h
 * Author: Tanya Badrljica, Andrew Sears, Rana Hussain
 *
 * Created on February 24, 2019, 1:21 PM
 */

#define MANAGER_H
#include <iostream>
#include <cstdlib>
#include <string>
#include "Supervisor.h"
using namespace std;

class Manager : public Supervisor
{
    public:
         //constructor
        Manager(string t, string n, string i, string b) : Supervisor(t, n, i, b)
        {
           
        }   //end constructor
        
        virtual double getCommission() 
        {
            return (6.5 * getTotalSales() / 100) + (3 * getBelowSales() / 100);
        }   //end getCommission
        
        
};  //end class Manager