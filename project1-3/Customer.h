/*
 * File:   Customer.h
 * Author: Tanya Badrljica, Andrew Sears, Rana Hussain
 *
 * Created on January 31, 2019, 9:29 AM
 */

#define CUSTOMER_H
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Customer
{   
    private:
        string first, last, address, city, state, zipcode, id;
        int count;
    public:
     
    //constructor
    Customer()
    {
        first = "";
        last = "";
        address = "";
        city = "";
        state = "";
        zipcode = "";
        count = 0;
    }   //end Customer
    
    //sets
    void setAll(string a, string b, string c, string d, string e, string f, string g){
        first = b;
        last = c;
        address = d;
        city = e;
        state = f;
        zipcode = g;
        id = a;
    }
    string getId(){
        return id;
    }
    void setNewCust(int s)//
    {
        count = s;
    }   //end setSize
    
    int getNewCust()
    {
        return count;
    }   //end getSize
    
    string getFirst()
    {
        return first;
    }   //end getFirst
    
    string getLast()
    {
        return last;
    }   //end getLast
    
    string getAddress()
    {
        return address;
    }   //end getAddress
    
    string getCity()
    {
        return city;
    }   //end getCity
    
    string getState()
    {
        return state;
    }   //end getState
    
    string getZipcode()
    {
        return zipcode;
    }   //end getZipcode
    
    string to_string()
    {
        string str = id + ";" + first + ";" + last + ";" + address + ";" + city + ";" + state + ";" + zipcode + "\n";
        return str;
    }   //end to_string
    
};  //end class Customer
