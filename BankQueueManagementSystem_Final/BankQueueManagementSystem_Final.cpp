
#include <iostream>
#include "Bank.h"
using namespace std;


int main()
{

    Bank b1;
    

    int typeOfSimulation;
    SetColor(10);
    cout << "Enter Type Of The Simulation That You Want To Do It In The Bank" << endl;
    SetColor(12);
    cout << "Simulation With Normal Customers ? Press 1" << endl;
    cout << "Simulation With Spacial Customers ? Press 2" << endl;
    cin >> typeOfSimulation;
    switch (typeOfSimulation)
    {
    case 1:
    {
        int numOfCusromers;
        SetColor(10);
        cout << "Enter Number of Customers that You Want to Simulate : ";
        SetColor(15);
        cin >> numOfCusromers;
        for (int i = 0; i < numOfCusromers; i++)
        {
            string name;
            int arrivalTime, serviceTime;
            char vip;
            SetColor(8);
            cout << "Enter Details of Customer " << i + 1 << ":" << endl;
            SetColor(10);
            cout << "Name : ";
            SetColor(15);
            cin >> name;
            SetColor(10);
            cout << "Arrival Time : ";
            SetColor(15);
            cin >> arrivalTime;
            SetColor(10);
            cout << "Service Time : ";
            SetColor(15);
            cin >> serviceTime;

            Customer customer(name, arrivalTime, serviceTime);
            b1.addCustomerToPriorityQueue(customer);


        }
        b1.run1();
    }
    break;
    case 2:
    {
        int numOfCusromers;
        SetColor(10);
        cout << "Enter Number of Customers that You Want to Simulate : ";
        SetColor(15);
        cin >> numOfCusromers;
        for (int i = 0; i < numOfCusromers; i++)
        {
            string name;
            int arrivalTime, serviceTime;
            char vip;
            SetColor(8);
            cout << "Enter Details of Customer " << i + 1 << ":" << endl;
            SetColor(10);
            cout << "Name : ";
            SetColor(15);
            cin >> name;
            SetColor(10);
            cout << "Arrival Time : ";
            SetColor(15);
            cin >> arrivalTime;
            SetColor(10);
            cout << "Service Time : ";
            SetColor(15);
            cin >> serviceTime;
            bool isVIP;
            SetColor(10);
            cout << "Are you Special customer y|n : ";
            SetColor(15);
            cin >> vip;
            if (vip == 'y')
            {
                isVIP = true;
            }
            else {
                isVIP = false;
            }

            Customer customer(name, arrivalTime, serviceTime, isVIP);
            b1.addCustomerToDeque(customer);


        }
        b1.run2();
    }

    break;

    }


}

