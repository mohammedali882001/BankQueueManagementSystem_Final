
#pragma once
#include <string>
#include "Customer.h"
#include <iostream>
#include <deque>
#include <queue>
#include <windows.h>
#include <algorithm>
#include <iomanip> 
using namespace std;

struct compareEventTime
{
    bool operator()(const Customer& lhs, Customer& rhs) const
    {
        return lhs.getArrivalTime() > rhs.getArrivalTime();
    }
};

void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

struct teller
{
    bool isAvailable;
    int tellerNumber;
    int numofserved;
    int availableTime;
    int totalTimeServed;
};

class Bank
{
private:
    deque<Customer> customerDeque;//if ENG:Ahmed want to simulate with VIP(special)
    priority_queue<Customer, vector<Customer>, compareEventTime> customerPriorityQueue;//simulate with arrival time

    int teller_num = 3;
    int currentTime = 0;
    teller* tellers;
    int totalWaitingTime = 0;
    int totalServiceTime = 0;

    teller* findNearestAvailableTeller()
    {
        teller* nearestTeller = nullptr;
        int earliestAvailableTime = INT_MAX;

        for (int i = 0; i < teller_num; i++)
        {
            if (tellers[i].availableTime < earliestAvailableTime)
            {
                nearestTeller = &tellers[i];
                earliestAvailableTime = tellers[i].availableTime;
            }
        }

        return nearestTeller;
    }

    void printHeader() {
        SetColor(12);
        std::cout << std::left << std::setw(20) << "Customer Name"
            << std::setw(15) << "Waiting Time"
            << std::setw(15) << "Service Time"
            << std::setw(15) << "Leave Time"
            << std::setw(30) << "Served with Teller Number"
            << std::setw(15) << "Type"
            << std::endl;
        SetColor(15);
        std::cout << std::string(110, '-') << std::endl;
    }
    void displayCustomerDetails2(Customer c, teller t) {
        string type = (c.getHasVIP()) ? "Special" : "Regular";

        std::cout << std::left << std::setw(20) << c.getName()
            << std::setw(15) << c.getWaitingTime()
            << std::setw(15) << c.getServiceTime()
            << std::setw(15) << c.getLeaveTime()
            << std::setw(30) << t.tellerNumber
            << std::setw(15) << type
            << std::endl;
    }

    void printTellerHeader() {
        SetColor(12);
        std::cout << std::left << std::setw(15) << "Teller Number"
            << std::setw(25) << "Total Time Served"
            << std::setw(30) << "Number of Customers Served"
            << std::endl;
        SetColor(15);
        std::cout << std::string(80, '-') << std::endl;

    }

    void displayTellerDetails2() {
        SetColor(11);
        cout << endl;
        cout << endl;
        cout << "Tellers Details : " << endl;
        SetColor(15);

        printTellerHeader();

        for (int i = 0; i < teller_num; i++) {
            std::cout << std::left << std::setw(15) << tellers[i].tellerNumber
                << std::setw(25) << tellers[i].totalTimeServed
                << std::setw(30) << tellers[i].numofserved
                << std::endl;
        }
    }

    void printBankDataHeader() {
        SetColor(12);
        std::cout << std::left << std::setw(30) << "Total Service Time"
            << std::setw(30) << "Total Waiting Time"
            << std::endl;
        SetColor(15);
        std::cout << std::string(80, '-') << std::endl;
    }

    void displayBankData2() {
        cout << endl;
        SetColor(11);
        cout << "Service and Waiting Details : " << endl;
        SetColor(15);

        printBankDataHeader();

        std::cout << std::left << std::setw(30) << totalServiceTime
            << std::setw(30) << totalWaitingTime
            << std::endl;
    }
    
public:
    Bank()
    {
        tellers = new teller[teller_num];
        for (int i = 0; i < teller_num; ++i)
        {
            tellers[i].isAvailable = true;
            tellers[i].tellerNumber = i + 1;
            tellers[i].numofserved = 0;
            tellers[i].availableTime = 0;
            tellers[i].totalTimeServed = 0;
        }
    }

    ~Bank()
    {
        delete[] tellers;
    }

    void addCustomerToDeque(Customer c)
    {
       
        customerDeque.push_back(c);
        sort(customerDeque.begin(), customerDeque.end(), [](const Customer& a, const Customer& b) {
            return a.getArrivalTime() < b.getArrivalTime();
        });
    }

    void addCustomerToPriorityQueue(Customer c)
    {
        customerPriorityQueue.push(c);

    }

    
    void run1()
    {
       
        cout << endl;
        SetColor(11);
        cout << "Customers Details : " << endl;
        SetColor(15);
        printHeader();
        while (!customerPriorityQueue.empty())
        {
            Customer cuurentCustomer = customerPriorityQueue.top();
            

            bool served = false;
            for (int i = 0; i < teller_num; i++)
            {
                if (tellers[i].isAvailable)
                {

                    cuurentCustomer.setWaitingTime(cuurentCustomer.getArrivalTime() - cuurentCustomer.getArrivalTime());
                    cuurentCustomer.setLeaveTime(cuurentCustomer.getArrivalTime() + cuurentCustomer.getServiceTime());
                    displayCustomerDetails2(cuurentCustomer, tellers[i]);
                    tellers[i].isAvailable = false;
                    tellers[i].availableTime = cuurentCustomer.getLeaveTime();
                    tellers[i].numofserved++;

                    tellers[i].totalTimeServed += cuurentCustomer.getServiceTime();

                    totalServiceTime += cuurentCustomer.getServiceTime();
                    totalWaitingTime += cuurentCustomer.getWaitingTime();
                    customerPriorityQueue.pop();
                    served = true;
                    break;
                }

            }

            if (!served)
            {


                teller* nearestTeller = findNearestAvailableTeller();
                nearestTeller->isAvailable = true;
                nearestTeller->numofserved++;
                if (nearestTeller->availableTime < cuurentCustomer.getArrivalTime())
                {
                    cuurentCustomer.setWaitingTime(0);
                }
                else {
                    cuurentCustomer.setWaitingTime(nearestTeller->availableTime - cuurentCustomer.getArrivalTime());

                }
                cuurentCustomer.setLeaveTime(cuurentCustomer.getArrivalTime() + cuurentCustomer.getWaitingTime() + cuurentCustomer.getServiceTime());
                displayCustomerDetails2(cuurentCustomer, *nearestTeller);
                totalServiceTime += cuurentCustomer.getServiceTime();
                totalWaitingTime += cuurentCustomer.getWaitingTime();
                nearestTeller->totalTimeServed += cuurentCustomer.getServiceTime();

                nearestTeller->availableTime = cuurentCustomer.getLeaveTime();
                nearestTeller->isAvailable = false;
                customerPriorityQueue.pop();



            }

        }

        displayTellerDetails2();
        displayBankData2();
    }

    
   

    void run2()
    {
        cout << endl;
        SetColor(11);
        cout << "Customers Details : " << endl;
        SetColor(15);
        printHeader();
        while (!customerDeque.empty())
        {
            Customer cuurentCustomer = customerDeque.front();
            bool served = false;
            for (int i = 0; i < teller_num; i++)
            {
                if (tellers[i].isAvailable)
                {
                    cuurentCustomer.setWaitingTime(cuurentCustomer.getArrivalTime() - cuurentCustomer.getArrivalTime());
                    cuurentCustomer.setLeaveTime(cuurentCustomer.getArrivalTime() + cuurentCustomer.getServiceTime());
                    displayCustomerDetails2(cuurentCustomer, tellers[i]);
                    tellers[i].isAvailable = false;
                    tellers[i].availableTime = cuurentCustomer.getLeaveTime();
                    tellers[i].numofserved++;
                    tellers[i].totalTimeServed += cuurentCustomer.getServiceTime();
                    totalServiceTime += cuurentCustomer.getServiceTime();
                    totalWaitingTime += cuurentCustomer.getWaitingTime();
                    customerDeque.pop_front();
                    served = true;
                    break;
                }
            }

            if (!served)
            {
                teller* nearestTeller = findNearestAvailableTeller();

                bool vipServed = false;
                int indexToRemove = customerDeque.size();  

                for (int i = 0; i < customerDeque.size() && customerDeque[i].getArrivalTime() <= nearestTeller->availableTime; i++)
                {
                    if (customerDeque[i].getHasVIP())
                    {
                        cuurentCustomer = customerDeque[i];
                        nearestTeller->isAvailable = true;
                        nearestTeller->numofserved++;
                        if (nearestTeller->availableTime < cuurentCustomer.getArrivalTime())
                        {
                            cuurentCustomer.setWaitingTime(0);
                        }
                        else {
                            cuurentCustomer.setWaitingTime(nearestTeller->availableTime - cuurentCustomer.getArrivalTime());

                        }
                        cuurentCustomer.setLeaveTime(cuurentCustomer.getArrivalTime() + cuurentCustomer.getWaitingTime() + cuurentCustomer.getServiceTime());
                        displayCustomerDetails2(cuurentCustomer, *nearestTeller);
                        totalServiceTime += cuurentCustomer.getServiceTime();
                        totalWaitingTime += cuurentCustomer.getWaitingTime();
                        nearestTeller->totalTimeServed += cuurentCustomer.getServiceTime();
                        nearestTeller->availableTime = cuurentCustomer.getLeaveTime();
                        nearestTeller->isAvailable = false;

                        
                        indexToRemove = i;
                        vipServed = true;
                        break;
                    }
                }

                
                if (vipServed && indexToRemove != customerDeque.size())
                {
                    customerDeque.erase(customerDeque.begin() + indexToRemove);
                }

                if (!vipServed)
                {
                    nearestTeller->isAvailable = true;
                    nearestTeller->numofserved++;
                    if (nearestTeller->availableTime < cuurentCustomer.getArrivalTime())
                    {
                        cuurentCustomer.setWaitingTime(0);
                    }
                    else {
                        cuurentCustomer.setWaitingTime(nearestTeller->availableTime - cuurentCustomer.getArrivalTime());

                    }
                    cuurentCustomer.setLeaveTime(cuurentCustomer.getArrivalTime() + cuurentCustomer.getWaitingTime() + cuurentCustomer.getServiceTime());
                    displayCustomerDetails2(cuurentCustomer, *nearestTeller);
                   
                    totalServiceTime += cuurentCustomer.getServiceTime();
                    totalWaitingTime += cuurentCustomer.getWaitingTime();
                    nearestTeller->totalTimeServed += cuurentCustomer.getServiceTime();
                    nearestTeller->availableTime = cuurentCustomer.getLeaveTime();
                    nearestTeller->isAvailable = false;
                    customerDeque.pop_front();
                }
            }
        }
        displayTellerDetails2();
        displayBankData2();
    }
};
