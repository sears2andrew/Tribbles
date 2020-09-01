/*
 * File:   Employee.h
 * Author: Tanya Badrljica, Andrew Sears, Rana Hussain
 *
 * Created on February 24, 2019, 11:21 AM
 */

#define EMPLOYEE_H
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Employee
{   
    private:
        string title, name, id, bossID;
        
    public:
        //constructor
        Employee()
        {
            title = "";
            name = "";
            id = "";
            bossID = "";
        }   //end Employee
        
        //constructor
        Employee(string t, string n, string i, string b)
        {
            title = t;
            name = n;
            id = i;
            bossID = b;
        }
        
        virtual double getCommission()
        {
            
        }
        
        virtual void setTotalSales(double n)
        {
            
        }
        
        virtual double getTotalSales()const
        {
            
        }
        
        virtual void setBelowSales(double n)
        {
            
        }
        
        virtual double getBelowSales()const
        {
            
        }
     
        
        //sets
        void setTitle(string t)
        {
            title = t;
        }   //end setTitle
        
        void setName(string n)
        {
            name = n;
        }   //end setName
        
        void setID(string i)
        {
            id = i;
        }   //end setSalesID
        
        void setBossID(string b)
        {
            bossID = b;
        }   //end setBossID
        
        //gets
        string getTitle()
        {
            return title;
        }   //end getTitle
        
        string getName()
        {
            return name;
        }   //end getName
        
        string getID()
        {
            return id;
        }   //end getSalesID
        
        string getBossID()
        {
            return bossID;
        }   //end getBossID
        
        virtual string to_String()
        {
            string str = title + ";" + name + ";" + id + ";" + bossID + ";" + "\n";
            return str;
        }   //end to_string
        
};  //end class Employee
