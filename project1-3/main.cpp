/*
 *A program to read in and use customer data, orders, transactions, and possible
 * wait list status from a file.
 * Users may choose to add customers, search customers up by last name,
 * search customer up by ID number, add customers to the Rainbow Tribble waiting list,
 * sell a Rainbow Tribble to the next customer in the waiting list, sell Tribbles,  
 * or exit the program.
 * All newly added customers get added to the customer data file.
 * All orders get added to the order file.
 * All transactions are added to the transaction file.
 * Customers are added to the waiting list file if they want a Rainbow Tribble.
 *
 * File:   main.cpp
 * Author: Tanya Badrljica, Andrew Sears, Rana Hussain
 *
 * Created on January 29, 2019, 12:59 PM
 */

//include some standard libraries
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include "Customer.h"
#include "Manager.h"
#include "Transaction.h"
#include "Order.h"
#include <cstdio>
#include <ctime>

using namespace std;

//code given through email
string currentDate()    // StackOverflow code
{    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //express month as string
    string mon;
    int month = tm.tm_mon+1;  // month starts at 0 in the struct
   
    switch(month)
    {
        case 1: mon="Jan"; break;
        case 2: mon="Feb"; break;
        case 3: mon="Mar"; break;
        case 4: mon="Apr"; break;
        case 5: mon="May"; break;
        case 6: mon="Jun"; break;
        case 7: mon="Jul"; break;
        case 8: mon="Aug"; break;
        case 9: mon="Sep"; break;
        case 10:mon="Oct"; break;
        case 11:mon="Nov"; break;
        case 12:mon="Dec"; break;
    }   //end switch
    
    char dateData [10];
    sprintf(dateData,"%02d-%3s-%02d", tm.tm_mday, mon.c_str(), tm.tm_year-100);
    string dater = dateData;
    return dater;
}   //end currentDate

vector<Customer> setCustomer(vector<Customer>customerList,string id, string first, string last, string address, string city, string state, string zip)
{
    //creating a customer object and setting all the customer's information
    //then putting customer object into a vector
    Customer customer;
    customer.setAll(id,first,last,address,city,state,zip);
    customerList.push_back(customer);
    return customerList;
}  //end setCustomer

vector<Customer> setCustomerList()
{
    vector<Customer>customerList;
    int size = 0;
    
    //defining an ifstream object and opening the input file
    ifstream infile("customers.txt", ios::in);
    if(!infile)
    {
        cerr<<"Open file failed.";
        exit(1);
    }
    
    //repeat for each line in file
    //putting the file into a vector
    while (!infile.eof())
    {
       vector<string>data;
       data.clear();
       string datahold;
       //loop for each field and put the data into vector
       for(int i = 0; i < 6; i++)
       {
           getline(infile,datahold, ';');
           data.push_back(datahold);
       }    //end for
       
       getline(infile, datahold);
       //take current customer list and add one to the end
       customerList = setCustomer(customerList, data[0],data[1],data[2],data[3],data[4],data[5],datahold);  
       size++;
    }  //end while
    //close the input file
    infile.close();
    return customerList;
    
}   //end setCustomerList

//checking a given ID string against a customer object vector and returning
//a customer position in the vector
int searchId(vector<Customer>list , string id)
{
    int count = 0,customer = -1;
    string custId;
    
    //loop for each customer object in list
    while(count < list.size())
    {
        //get object id and get rid of extra chars
        custId = list[count].getId();
        id = id.substr(0, 6);
        //if the IDs match
        if(custId == id)
        {
            //track which customer and end loop
            customer = count;
            count = list.size();
        }//end if
        count++;           
    }//end while
    //return which customer on the list matched the ID
    return customer;
}//end searchId

vector <Customer> addCustomer(vector<Customer>list)
{
    // create a vector to hold customer data to be put into an object
    vector <string> info(6);
    //create a vector that stores the questions to ask when adding a new customer
    vector<string> questions = {"Enter your first name: ",
                                "Enter your last name: ",
                                "Enter your address: ",
                                "Enter your city: ",
                                "Enter your state's abbreviation: ",
                                "Enter your zipcode: "};
    for (int i = 0; i < 6; i++)
    {
        //print out question and store in the corresponding vector slot
        cout << questions[i];
        getline(cin, info[i]);
    }   //end for
    
    bool found = true;
    int id;
    //generate the new ID and sets it to the correct
    while(found == true)
    {
        id = rand() % 1000000;
        for(int l = 0; l <6; l++)
        {
            if(id < 100000)
            {
                id *= 10;
            }   //end if
        }   //end for
        
        //checking to see if this generated ID already exists
        int check = searchId(list, to_string(id));
        if(check == -1)
        {
            found = false;
        }   //end if
    }   // end while
    
    cout << "Here is the new customer ID: " << to_string(id) << endl;
    //add new customer to current list vector
    list = setCustomer(list, to_string(id),info[0],info[1],info[2],info[3],info[4],info[5]);
    //track new customer count in first customer object
    list[0].setNewCust(list[0].getNewCust()+1);
    return list;
    
}//end addCustomer

void searchLast(vector<Customer>list)
{   
    vector<Customer>listData;
    int count = 0, size = 0;
    string input;
    cout << "Enter the last name you would like to search for: ";
    cin >> input;
    
    while(count!=list.size())
    {
        if(!list[count].getLast().compare(input))
        {
            listData.push_back(list[count]);
            size++;
        }   //end if
        count++;
    }   // end while
    
    count = 1;
    if(size == 0)
    {
        cout << "No customers matched that last name." << endl;
    }// end if
    
    else if(size == 1)
    {
        cout << listData[0].getFirst() << " " << listData[0].getLast() << " " << listData[0].getAddress() << endl;
    }  // end else if

    else if(size > 1)
    {
        cout << "Type in the desired customer's number: ";
        for(int i = 0; i < size; i++)
        {
            cout << count << ". " << listData[i].getFirst() << " " << listData[i].getLast() << endl;
            count++;     
        }   //end for
 
        int input;
        cin >> input;
        cout << listData[input-1].getFirst() << " " << listData[input-1].getLast() << " " << listData[input-1].getAddress() << endl;
    }   // end else if

    else
    {
        cout << "Data quantity error." << endl;
    }   // end else
}   // end searchLast

//Adding customers to the Rainbow Tribble waitlist
void rainbowAdd(vector<string>list ,vector<Customer>customerlist)
{
    cout << "Enter your ID number: ";
    string input;
    cin >> input;
    bool goodId = false;
    int checkId = searchId(customerlist, input);
    if(checkId == -1)
    {
        while(goodId == false)
        {
            cout << "Invalid ID. Enter your ID number: ";
            cin >> input;
            checkId = searchId(customerlist, input);
            if(checkId != -1)
                goodId = true;
        }   //end while
    }   //end if
    input = input.substr(0, 6);
    list.push_back(input);
    
    //defining an ofstream object and opening the output file
    ofstream outfile("rainbowList.txt", ios::out);
    for(int i = 0; i < list.size();i++)
    {
        if(list[i].size() > 2)
        {
            outfile << list[i] << endl;
        }   //end if
    }   // end for
    //close the output file
    outfile.close();
}   // end rainbowAdd

void setOrder(int quantity, string id,string empid)
{
    vector<Order> orderData;
    //create vector to hold corresponding values to order quantities
    vector<string> cost = {"9.50", "16.15", "25.88", "28.15", "30.00"};
    //defining an ifstream object and opening the input file
    ifstream orderinfile("orders.txt", ios::in);
    if(!orderinfile)
    {
        cerr<<"Open file failed.";
        exit(1);
    }
    
    string holder, tempid, tempdate, tempnum, tempcost;
    //loop for each line in file and set customer data to an order object
    while (!orderinfile.eof())
    {
        Order order;
        getline(orderinfile,tempid, ';');
        getline(orderinfile,tempdate, ';');
        getline(orderinfile,tempnum, ';');
        getline(orderinfile,tempcost);
        order.setAll(tempid,tempdate,tempdate,tempcost);
        orderData.push_back(order);
    }   //end while
    
    //close the input file
    orderinfile.close();
    Order order;
    //create customer transaction number and store new
    //info in order data object
    
    holder = "00000" + to_string(stod(orderData[orderData.size()-1].getID())+1);
    string orderNum = holder.substr(holder.length() - 6, holder.length());
    order.setAll(orderNum,currentDate(),to_string(quantity),cost[quantity-1]);
    orderData.push_back(order);
    
    vector<Transaction> transactionData;
    //defining an ifstream object and opening the input file
    ifstream infile("transactions.txt", ios::in);
    if(!infile)
    {
        cerr<<"Open file failed.";
        exit(1);
    }
    
    //loop for each line in file and
    //set data into transaction objects
    while (!infile.eof())
    {
        Transaction transaction;
        getline(infile, tempid, ';');
        getline(infile, tempnum, ';');
        getline(infile, holder);
        transaction.setAll(tempid,tempnum,holder);
        transactionData.push_back(transaction);
    }   //end while
    
    //set new data into transaction object
    Transaction transaction;
    transaction.setAll(id,orderNum,empid);
    transactionData.push_back(transaction);
    infile.close();
    //open both output files and print formated data
    //by looping through the length of the vector
    //defining ofstream objects and opening the output files
    ofstream outfile("transactions.txt", ios::out);
    ofstream orderoutfile("orders.txt", ios::out);
    for(int i = 0; i < transactionData.size();i++)
    {
        if(i != transactionData.size()-2)
        {
            outfile << transactionData[i].getCusID() << ";" << transactionData[i].getOrdID() << endl;
            orderoutfile << orderData[i].getID() << ";" << orderData[i].getDate() << ";" << orderData[i].getNum() << ";" << orderData[i].getCost() << endl;
        }   //end if
    }   //end for
            
    //close the output files
    orderoutfile.close();
    outfile.close();
}   //end setOrder


//Selling a Rainbow Tribble to a customer
void rainbowSell(vector<Customer>list, vector<string>waitlist)
{
    string temp = waitlist[0];
    int customer = searchId(list, temp);
   
    if(customer == list.size() -1 + list[0].getNewCust() || temp.length() != 6)
    {
        cout << "\nThere are no customers in the waiting list." << endl;
    }   //end if
    
    else
    {
        cout << list[customer].getFirst() << " " << list[customer].getLast() << " 1 sold @ $9.50" << endl;
   
        cout << "Enter 0 to confirm, 1 to exit: ";
        int input;
        cin >> input;
        bool done = false;
        while(done == false)
        {
            if(input == 0)  //confirmation 0 or 1 exit
            {
                setOrder(1,list[customer].getId(),"000000");
                //defining an ofstream object and opening the output file
                ofstream outfile("rainbowList.txt", ios::out);
                for(int i = 1; i < waitlist.size();i++)
                {
                    outfile << waitlist[i] << endl;
                }   //end for

                //close the output file
                outfile.close();
                cout << "Confirmed." << endl;
                done = true;
            }   //end if

            else if(input == 1)
            {
                done = true;
            }   //end else if
        }   //end while
    }   //end else
}   //end rainbowSell

//Rainbow Tribble menu
void rainbow(vector<Customer>list)
{
    //defining an ifstream object and opening the input file
    ifstream infile("rainbowList.txt", ios::in);
    if(!infile)
    {
        cerr<<"Open file failed.";
        exit(1);
    }
    string id;
    vector<string>waitlist;
    //read in the waitlist data into a vector
    while(!infile.eof())
    {
        getline(infile,id);
        id = id.substr(0, 6);
        waitlist.push_back(id);
    }   //end while
    //close the input file
    infile.close();
    
    cout << "\nEnter the number corresponding with your choice: " << endl
            << "1.)Add a customer to the waiting list." << endl
            << "2.)Sell a Rainbow Tribble to the next customer on the waiting list." << endl;
    int input;
    cin >> input;
    //based on user inputs, call methods
    switch(input)
    {
        case 1: rainbowAdd(waitlist,list);
        break;
        case 2: rainbowSell(list, waitlist);
        break;
    }   //end switch
}   //end rainbow

void orders(vector<Customer> list)
{
    vector<string> select = {"1 Tribble - $9.50", "2 Tribbles - $16.15",
     "3 Tribbles - $25.88", "4 Tribbles - $28.15", "5 Tribbles - $30.00"};
    string id;
    int quantity;
    
    //get customer data
    cout << "Enter your customer ID: ";
    cin >> id;
    bool goodId = false;
    int checkId = searchId(list,id);
    if(checkId == -1)
    {
        while(goodId == false)
        {
            cout << "Invalid ID. Enter your ID number: ";
            cin >> id;
            checkId = searchId(list,id);
            if(checkId != -1)
                goodId = true;
        }   //end while
    }   //end if
    
    cout << "Enter the quantity (1-5): ";
    cin >> quantity;
    //ask for customer confirmation
    int temp = searchId(list,id);
    cout << "Confirmation: Customer name: " << list[temp].getFirst() << " " << list[temp].getLast() << ". Quantity = " <<select[quantity-1] << endl;
    
    bool done = false;
    while(done == false)
    {
        cout << "Enter 0 to confirm, 1 to exit: ";
        int input;
        cin >> input;
        //check user input for valid data.
        //if confirming:
        if(input == 0)
        {
            cout << "Confirmed." << endl;
            //set new customer transaction data
            setOrder(quantity, id, "000000");
            done = true;
        }   //end if
        
        else if(input == 1)
        {
            done = true;
        }   //end else if
    }   //end while
}   //end orders

//sets employee sales totals
void setCommission(vector<Employee*>empList)
{
    //defining an ifstream object and opening the input file
    ifstream infile("transactions.txt", ios::in);
    if(!infile)
    {
        cerr<<"Open file failed.";
        exit(1);
    }   //end if
    
    string cusid, salesid, orderid;
    vector<Transaction> transactionData;
    while (!infile.eof())
    {
        Transaction transaction;
        getline(infile, cusid, ';');
        getline(infile, salesid, ';');
        getline(infile, orderid);
        transaction.setAll(cusid,salesid,orderid);
        transactionData.push_back(transaction);
    }   //end while
    //close the input file
    infile.close();
    
    //defining an ifstream object and opening the input file
    ifstream orderinfile("orders.txt", ios::in);
    if(!orderinfile)
    {
        cerr<<"Open file failed.";
        exit(1);
    }   //end if
    
    string burn, total;

    while(!orderinfile.eof())
    {
        getline(orderinfile, orderid, ';');
        getline(orderinfile, burn, ';');
        getline(orderinfile, burn, ';');
        getline(orderinfile, total);
        int managerpos = 0;
        for(int g =0; g<empList.size(); g++)
        {
            if(!empList[g]->getTitle().compare("Manager"))
            {
                managerpos = g;
                g = empList.size();
            }   //end if
        }   //end for
        
        for(int l = 0; l < transactionData.size(); l++)
        {   
            //match transaction and order data
            if(transactionData[l].getOrdID().substr(0,6) == orderid.substr(0,6))
            {
                for(int m = 0; m < empList.size(); m++)
                {
                    //match transaction employee id's with employee vector
                    if(empList[m]->getID() == transactionData[l].getTempID())
                    {
                        empList[m]->setTotalSales(atof(total.c_str()));
                        //add to total manager back commisions
                        if(empList[m]->getTitle().compare("Manager") && transactionData[l].getTempID().compare("000000"))
                        {
                            empList[managerpos]->setBelowSales(atof(total.c_str()));
                        }   //end if
                        
                        for(int p =0; p<empList.size(); p++)
                        {
                            //add to supervisor back commissions
                            if(empList[m]->getBossID() == empList[p]->getID() && !empList[p]->getTitle().compare("Supervisor"))
                            {
                                empList[p]->setBelowSales(atof(total.c_str()));
                                p = empList.size();
                            }   //end if
                        }   //end for   
                        m = empList.size();
                    }   //end if
                }   //end for
                l = transactionData.size();
            }   //end if        
        }   //end for
    }   //end while  
    
    //close the input file
    orderinfile.close();
}   //end setCommission

vector<Employee*> setSales()
{
    vector<Employee*> salesTeam;
    //defining an ifstream object and opening the input file
    ifstream infile("salesStaff.txt", ios::in);
    if(!infile)
    {
        cerr<<"Open file failed.";
        exit(1);
    }   //end if
    
    while (!infile.eof())
    {
        vector<string> dataHolder;
        dataHolder.clear();
        for(int i = 0; i<4; i++)
        {
            string temp;
            getline(infile, temp, ';');
            dataHolder.push_back(temp);
        }   //end for
        
        //burn the new line character
        string burn;
        getline(infile,burn);
        
        string type = dataHolder[0];
        Employee *employee;
        bool hit = false;
        //set data acording to employee type
        if(!type.compare("Sales"))
        {
            employee = new Sales(dataHolder[0],dataHolder[1],dataHolder[2],dataHolder[3]);
            hit = true;
        }   //end if
        
        else if(!type.compare("SuperSales"))
        {
            employee = new SuperSales(dataHolder[0],dataHolder[1],dataHolder[2],dataHolder[3]);
            hit = true;
        }   //end else if
        
        else if(!type.compare("Supervisor"))
        {
            employee = new Supervisor(dataHolder[0],dataHolder[1],dataHolder[2],dataHolder[3]);
            hit = true;
        }   //end else if
        
        else if(!type.compare("Manager"))
        {
            employee = new Manager(dataHolder[0],dataHolder[1],dataHolder[2],dataHolder[3]);
            hit = true;
        }   //end else if
        
        if(hit = true)
        {
            salesTeam.push_back(employee);
        }   //end if
        
    }   //end while
    //close the input file
    infile.close();
    return salesTeam;
}

vector<Customer> menuMain(vector<Customer>list)
{
    int input;
    string temp;
    do{
        //opening messages
        cout << "\nEnter the number corresponding with your choice: " << endl
             << "1.)Add a customer." << endl
             << "2.)Look up a customer by last name." << endl
             << "3.)Look up a customer by ID number." << endl
             << "4.)Rainbow Tribbles." << endl
             << "5.)Customer Sale." << endl
             << "6.)Sales Report." << endl
             << "7.)Exit." << endl;
        cin >> input;
        cin.ignore();
        
        //based on user inputs, call methods
        switch(input)
        {
            case 1: list = addCustomer(list);
            break;
            case 2: searchLast(list);
            break;
            case 3: cout << "Enter your ID number: ";
                cin >> temp;
                input = searchId(list, temp);
                if(input == -1)
                {
                    cout << "No customers matched that ID.\n";
                }
                else
                {
                    cout << list[input].getFirst() << " " << list[input].getLast() << " " << list[input].getAddress() << endl;
                }   //end else
            break;
            case 4: rainbow(list);
            break;
            case 5: orders(list);
            break;
            case 6: cout << "                    --SALES REPORT--\n";
                    cout << "Staff Member          Total Sales         Commission" << endl;
                    cout << "____________          ___________         __________" << endl;
                    vector<Employee*> empList = setSales();
                
                    setCommission(empList);

                    for(int k = 0; k < empList.size()-1; k++)
                    {
                        int base = empList[k]->getCommission();
                        int decimal = empList[k]->getCommission()*100;
                        decimal = decimal % 100;
                        int round = empList[k]->getCommission()*1000;
                        round = round %10;
                        if (round >= 5){
                            decimal++;
                        }
                        if(decimal < 10)
                        {
                            cout << empList[k]->to_String() << " $" << base << ".0" << decimal  << endl;
                        }   //end if
                        
                        else if(base > 99)
                        {
                            cout << empList[k]->to_String() << "$" << base << "." << decimal  << endl;
                        }   //end if
                        
                        else
                        {
                            cout << empList[k]->to_String() << " $" << base << "." << decimal  << endl;
                        }   //end else
                    }   //end for
            break;
        }   //end switch
        
    }while(input!=7);   //end do while   
    return list;
}   //end menuMain

void setFile(vector<Customer>list)
{
    //defining an ofstream object and opening the output file
    ofstream  outfile("customers.txt", ios::out);
    
    for(int i = 0; i < list.size();i++)
    {
        if(i != list.size()-list[0].getNewCust()-1)
        {
            outfile<<list[i].to_string();
        }   //end if
    }   //end for
    //close the output file
    outfile.close();
}   //end setFile

int main(int argc, char** argv)
{
    vector<Customer>customerList = setCustomerList();
    //initializes the vector with current data from the customer data file
    customerList = setCustomerList();
    customerList = menuMain(customerList);
    setFile(customerList);  //calling the setFile method

    return 0;
}   //end main
