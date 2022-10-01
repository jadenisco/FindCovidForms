//
// FindForms.cpp
//
// Created by John DeNisco on 9/28/22.
//
//  
//

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdio.h>

using namespace std;

// Local Definitions, these should go in a header file
//#define MGH
//#define CONSOLE_INPUT

#if MGH
static String vol_root_dir = "//Cifs2/voldept$";
static String? pet_volunteer_dir = vol_root_dir + "/.Volunteer Files/Pet Therapy";
#else
static string vol_root_dir = "/Users/jdenisco/Developer/Windows/testroot";
static string pet_volunteer_root_dir;
#endif

static string adult_volunteer_root_dir = vol_root_dir + "/.Volunteer Files/ADULT MEDICAL AND NONMEDICAL";
static string junior_volunteer_root_dir = vol_root_dir + "/.Volunteer Files/JUNIOR MEDICAL AND NONMEDICAL/Active JR Volunteers";
static string path = adult_volunteer_root_dir;

struct FormInfo {
    string volunteer_number;
    string dateAsString;
};

// Test Values
static FormInfo formInfo[] = {{"450", "12345678"},
                            {"350", "11/35/2021"},
                            {"345", "14/18/2021"},
                            {"100085", "06/00/2021"},
                            {"123", "04/11"},
                            {"0725", "6/11/2022"},
                            {"342", "1/9/2022"}
                            };
static int formInfoIndex = 0;

// Takes a pointer to a date, the date obtained will be returned in this structure.
// returns false, if the parse failed
static bool GetDate(tm *date) {
    string dateAsString = formInfo[formInfoIndex++].dateAsString;

    cout << "Date as String: " << dateAsString << "\n";
    istringstream ss(dateAsString);
    ss >> get_time(date, "%D");

    if (ss.fail()) {
        std::cout << "The date is not valid, Please enter a valid date.\n";
        return(false);
    }
    else {
        std::cout << put_time(date, "Parsed Date: %D") << '\n';
        return(true);
    }
}

static void GetInfo() {
    char sbuf[64];
    string month;
    string day;
    
    for(formInfoIndex=0; formInfoIndex < sizeof(formInfo)/sizeof(FormInfo);) {
        tm date = {};

        if(GetDate(&date)) {
            strftime(sbuf, sizeof(sbuf), "%b", &date);
            string month(sbuf);
            cout << "MONTH: " << month << "\n";
            strftime(sbuf, sizeof(sbuf), "%d", &date);
            string day(sbuf);
            cout << "DAY: " << day << "\n";
            strftime(sbuf, sizeof(sbuf), "%Y", &date);
            string year(sbuf);
            cout << "YEAR: " << year << "\n";
        }
    }
}

int main(int argc, const char * argv[]) {
    int x;

    GetInfo();

    cout << "Enter a Number: ";
#ifdef CONSOLE_INPUT
    cin >> x;
#else
    x = 10;
#endif

    cout << "The number is: " << x << "\n";
    return 0;
}
