//
// FindForms.cpp
//
// Created by John DeNisco on 9/28/22.
//
//  
//

#include <iostream>
#include <string>

using namespace std;

// Local Definitions
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

static FormInfo formInfo[] = {{"450", "12345678"},
                            {"350", "11/18/2021"},
                            {"123", "04/11"},
                            {"0725", "6/11/2022"},
                            {"342", "1/9/2022"}
                            };
static int formInfoIndex = 0;

int main(int argc, const char * argv[]) {
    int x;

    cout << "Hello World!\n";
    cout << "Enter a Number: ";

#ifdef CONSOLE_INPUT
    cin >> x;
#else
    x = 10;
#endif

    cout << "The number is: " << x;
    return 0;
}
