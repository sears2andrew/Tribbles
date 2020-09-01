/*
 * File:   Transaction.h
 * Author: Tanya Badrljica, Andrew Sears, Rana Hussain
 *
 * Created on February 9, 2019, 11:26 AM
 */

#define TRANSACTION_H
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Transaction
{
    private:
        string cusID, ordID, empID;
        
    public:
        
    //constructor
    Transaction()
    {
        cusID = "";
        ordID = "";
        empID = "";
    }   //end Transaction
    
    //sets
    void setAll(string c, string o, string e){
        cusID = c;
        empID = o;
        ordID = e;
    }
    
    //gets
    string getCusID()
    {
        return cusID;
    }   //end getCusID
    
    string getOrdID()
    {
        return ordID;
    }   //end getOrdID
    
    string getempID()
    {
        return empID;
    }
    
};  //end class Transaction
