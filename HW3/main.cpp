#include <iostream>
#include <fstream>      // file handling
#include <algorithm>    // sort
#include <vector>       // vector

using namespace std;

// Variable declaration used in functions

const int MAX_SIZE = 100;           //  Max. size of array or max no. of empoyees in input file

string inputFile  = "datafile.in";  //  Input File

string name[MAX_SIZE],      //  Name of employee
       temp;                // Temporary variable

int i,                        // for looping variable(temporary)
    totalEmployees;           // Total Emplyees data in input file
float hrsWorked[MAX_SIZE],    // Hours worked
      rateOfPay[MAX_SIZE],    // Rate of Pay
      age[MAX_SIZE],          // Age of employee
      basePay[MAX_SIZE],      // Base Pay of employee
      tax[MAX_SIZE],          // Tax
      netPay[MAX_SIZE];       // Net Pay = Pay - Tax

void ReadInput();
void DisplayInput();
void FindBasePay();
void FindTax();
void FindNetPay();
void OldYoungEmployee();
void MostPaidTaxEmployee();
void SortAlphabatically();
void SortNetPay();

int main()
{
    cout << "\n \t\t Misor Coroperation Payroll\n" << endl;
    ReadInput();
    DisplayInput();
    FindBasePay();
    FindTax();
    FindNetPay();

    // Display all calculated details of employee
    cout << "\n\t EMPLOYEE'S BASE PAY, TAX AND NET PAY DETAILS\n" << endl;
    cout << "NAME \t"
         << "HOURS WORKED \t"
         << "RATE OF PAY \t"
         << "AGE \t"
         << "BASE PAY \t"
         << "TAX \t"
         << "NET PAY \n"
         << endl;

    for(i = 0; i < totalEmployees; i++)
    {
        cout << name[i] << "\t"
             << hrsWorked[i] << "\t"
             << rateOfPay[i] << "\t"
             << age[i] << "\t"
             << basePay[i] << "\t"
             << tax[i] << "\t"
             << netPay[i] << endl;
    }

    OldYoungEmployee();
    MostPaidTaxEmployee();
    SortAlphabatically();
    SortNetPay();

    cout << "\n \t\t PAYROLL PROCESS IS COMPLETE \n";

    return 0;
}

/**
 *  Reading input details from file
 */

void ReadInput()
{
    ifstream inFile;
    inFile.open(inputFile.c_str());

    i = totalEmployees = 0; // Initializing values to 0

    while(getline(inFile, name[i], '\n'))   // Reading employee Name
    {
        if(inFile.eof())    // Break if end of file
            break;

        inFile >> hrsWorked[i] >> rateOfPay[i] >> age[i];   // Reading other details
        i++;
        getline(inFile, temp, '\n');    // Reading empty space(temporary).
    }
    totalEmployees = i; // Setting total employees in file

    inFile.close();
}

/**
 *  Display employee details on console
 */

void DisplayInput()
{
    cout << "\n\t DISPLAYING DETAILS OF EMPLOYEE \n" << endl;

    for(i = 0; i < totalEmployees; i++)
    {
        cout << "Name: "<< name[i] << "\t"
             << "Hours Worked: " << hrsWorked[i] << "\t"
             << "Rate of Pay: " << rateOfPay[i] << "\t"
             << "Age: " << age[i] << endl;
    }
}

/**
 *  Calculating base pay of all employees
 */

void FindBasePay()
{
    float overtimeRate = 1.5,
          overtimePay;

    int minHrs = 40,
        extraHrs = 0;

    for(i = 0; i < totalEmployees; i++)
    {
        extraHrs = hrsWorked[i] - minHrs;   // Finding extra hrs of employee
        overtimePay = (overtimeRate * rateOfPay[i]) * extraHrs;  // Calculating pay of extra hrs.
        basePay[i] = (rateOfPay[i] * minHrs) + overtimePay; // Calculating base pay
    }
}

/**
 *  Calculating tax of all employees
 */

void FindTax()
{
    int oldTaxRate = 50,    // Tax rate of older than 55 age in %
        youngTaxRate = 10;  // Tax rate of younger than 55 age in %

    int oldAge = 55;    // Min. age of old employee

    for(i = 0; i < totalEmployees; i++)
    {
        if(age[i] >= oldAge)
            tax[i] = (oldTaxRate * basePay[i]) / 100;
        else
            tax[i] = (youngTaxRate * basePay[i]) / 100;
    }
}

/**
 *  Calculating net pay of all employees
 */

void FindNetPay()
{
    for(i = 0; i < totalEmployees; i++)
    {
        netPay[i] = basePay[i] - tax[i];
    }
}

/**
 *  Finding Oldest and youngest employees in list
 */

void OldYoungEmployee()
{
    int oldEmployee,    //  Storing index value of oldest age employee
        youngEmployee;  //  Storing index value of youngest age employee

    oldEmployee = youngEmployee = 0;    // Inititalizing index to 0

    for(i = 1; i < totalEmployees; i++)
    {
        if(age[i] > age[oldEmployee])   // Finding oldest employee
            oldEmployee = i;

        if(age[i] < age[youngEmployee]) // Finding youngest employee
            youngEmployee = i;
    }

    // Displaying oldest and youngest employee

    cout << "\n\t YOUNGEST AND OLDEST EMPLOYEES \n" << endl
         << " Youngest Employees\n" << endl;

    for(i = 0; i < totalEmployees; i++)
    {
        if(age[i] == age[youngEmployee])
        {
            cout << "Name: " << name[i] << "\t"
                 << "Age: " << age[i] << endl;
        }
    }

    cout << "\n Oldest Employees\n" << endl;

    for(i = 0; i < totalEmployees; i++)
    {
        if(age[i] == age[oldEmployee])
        {
            cout << "Name: " << name[i] << "\t"
                 << "Age: " << age[i] << endl;
        }
    }
}

/**
 *  Finding employees who paid maximum tax
 */

void MostPaidTaxEmployee()
{
    int maxTax = 100;   // Set value of max tax. You can change max tax here.

    cout << "\n\t EMPLOYEES WHO PAID TAX MORE THAN " << maxTax << ".\n" << endl;

    for(i = 0; i < totalEmployees; i++)
    {
        if(tax[i] > maxTax) // Display details if tax > maxtax
        {
            cout << "Name: " << name[i] << "\t"
                 << "Tax Paid: " << tax[i] << endl;
        }
    }
}

/**
 *  Sorting names of employee alphabetically
 */

void SortAlphabatically()
{
    vector<string> sortedArray; // String array

    // Copying employee names in sortedArray

    for(i = 0; i < totalEmployees; i++)
    {
        sortedArray.push_back(name[i]);
    }

    // sorting array using sort function of algorithem header file

    sort(sortedArray.begin(), sortedArray.end());

    cout << "\n\t SORTING EMPLOYEE DETAILS ALPHABATICALLY \n" << endl;

    cout << "NAME \t"
         << "HOURS WORKED \t"
         << "RATE OF PAY \t"
         << "AGE \t"
         << "BASE PAY \t"
         << "TAX \t"
         << "NET PAY \n"
         << endl;

    for(i = 0; i < totalEmployees; i++)
    {
        for(int j = 0; j < totalEmployees; j++)
        {
            // Matches value of name with sorted array and displays result
            if(sortedArray[i] == name[j])
            {
                cout << name[j] << "\t"
                     << hrsWorked[j] << "\t"
                     << rateOfPay[j] << "\t"
                     << age[j] << "\t"
                     << basePay[j] << "\t"
                     << tax[j] << "\t"
                     << netPay[j] << endl;
            }
        }
    }

}

/**
 *  Sorting net pay of employees
 */

void SortNetPay()
{
    vector<float> sortedArray;

    // Copying employee names in sortedArray

    for(i = 0; i < totalEmployees; i++)
    {
        sortedArray.push_back(netPay[i]);
    }

    // sorting array using sort function of algorithem header file

    sort(sortedArray.begin(), sortedArray.end());

    cout << "\n\t SORTING EMPLOYEE DETAILS w.r.t. NET PAY \n" << endl;
    cout << "NAME \t"
         << "HOURS WORKED \t"
         << "RATE OF PAY \t"
         << "AGE \t"
         << "BASE PAY \t"
         << "TAX \t"
         << "NET PAY \n"
         << endl;

    for(i = 0; i < totalEmployees; i++)
    {
        cout << sortedArray[i] << endl;
        for(int j = 0; j < totalEmployees; j++)
        {
            // Matches value of net pay with sorted array and displays result
            if(sortedArray[i] == netPay[j])
            {
                cout << name[j] << "\t"
                     << hrsWorked[j] << "\t"
                     << rateOfPay[j] << "\t"
                     << age[j] << "\t"
                     << basePay[j] << "\t"
                     << tax[j] << "\t"
                     << netPay[j] << endl;
            }
        }

    }
}
