/*
 * File:   Supervisor.h
 * Author: Tanya Badrljica, Andrew Sears, Rana Hussain
 *
 * Created on February 24, 2019, 1:12 PM
 */

#define SUPERVISOR_H
#include <iostream>
#include <cstdlib>
#include <string>
#include "SuperSales.h"
using namespace std;

class Supervisor : public SuperSales
{    
        public:
        //constructor
        Supervisor(string t, string n, string i, string b) : SuperSales(t, n, i, b)
        {
           
        }   //end constructor
        
       
        
        virtual double getCommission() 
        {
            return (6.5 * getTotalSales() / 100) + (3 * getBelowSales() / 100);
        }   //end getCommission
        
        
};  //end class Supervisor
