/*
 * File:   Order.h
 * Author: Tanya Badrljica, Andrew Sears, Rana Hussain
 *
 * Created on February 9, 2019, 11:15 AM
 */

#define ORDER_H
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Order
{
    private:
        string id, date, num, cost;
        
    public:
    
    //constructor
    Order()
    {
        id = "";
        date = "";
        num = "";
        cost = "";
    }   //end Order
    
    //sets
    void setAll(string i, string d, string n, string c){
        id = i;
        date = d;
        num = n;
        cost = c;
    }
    //gets
    string getID()
    {
        return id;
    }   //end getID
    
    string getDate()
    {
        return date;
    }   //  end getDate
    
    string getNum()
    {
        return num;
    }   //end getNum
    
    string getCost()
    {
        return cost;
    }   //end getCost

    string to_string()
    {
        string str = id + ";" + date + ";" + num + ";" + cost + "\n";
        return str;
    }   //end to_string
    
};  //end class Order
