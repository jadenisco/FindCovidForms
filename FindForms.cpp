//
// FindForms.cpp
//
// Created by John DeNisco on 9/28/22.
//
//  
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;
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

typedef struct FormInfo {
    string volunteer_number;
    string dateAsString;
} FormInfoDef;

typedef struct VolMonDayYear {
    string volNum;
    string month;
    string day;
    string year;
} VolMonDayYearDef;

// Test Values
static FormInfo formInfo[] = {{"350", "6/10/21"}};
////                            {"450", "12345678"},
////                            {"john", "11/1/2021"},
////                            {"350", "11/35/2021"},
////                            {"345", "14/18/2021"},
////                            {"100085", "06/00/2021"},
////                            {"123", "04/11"},
////                            {"0725", "6/11/2022"},
////                            {"342", "1/9/2022"}
////                            };
static int formInfoIndex = 0;

// GetVol
// Returns the Volunteer Number.
// 
// returns 0, if the function fails

static int GetVol(VolMonDayYear *volMonDayYear) {

// Keep trying until we get a valid input
    while(true) {
        int volNum = 0;
        string volAsString;
        char sbuf[64];

#ifdef CONSOLE_INPUT
        cout << "\nPlease the volunteer number: "; 
        cin >> volAsString;
#else
        volAsString = formInfo[formInfoIndex].volunteer_number;
#endif
        cout << "Vol as String: " << volAsString << "\n";

        try {
            volNum = stoi(volAsString);
        }
        catch(exception &err) {
            cout << err.what() << "\n";
            cout << "The volunteer number '" << volAsString << "' is not valid, Please enter a valid number.\n";

            formInfoIndex++;
            continue;
        }

        volMonDayYear->volNum = volAsString;
        cout << "Volunteer Number: " << volNum << "\n";
        return(volNum);
    }
}

// GetDate
// Takes a pointer to a date, returns the date in the date structure.
// 
// returns false, if the parse failed

static bool GetDate(tm *date) {

// Keep trying until we get a valid input
    while(true) {
        string dateAsString;

#ifdef CONSOLE_INPUT
        cout << "\nPlease enter a date (mm/dd/yy): "; 
        cin >> dateAsString;
#else
        dateAsString = formInfo[formInfoIndex].dateAsString;
#endif

        cout << "Date as String: " << dateAsString << "\n";
        istringstream ss(dateAsString);
        ss >> get_time(date, "%D");

        if (ss.fail()) {
            cout << "The date " << dateAsString << " is not valid, Please enter a valid date.\n";
            formInfoIndex++;
        }
        else {
            cout << put_time(date, "Parsed Date: %D") << '\n';
            return(true);
        }
    }
}

static void GetInfo(VolMonDayYear *volMonDayYear) {
    tm date = {};
    char sbuf[64];
    int volNum = 0;

    if(GetDate(&date)) {
        strftime(sbuf, sizeof(sbuf), "%b", &date);
        volMonDayYear->month = string(sbuf);
        volMonDayYear->month[0] = tolower(volMonDayYear->month[0]);
        cout << "MONTH: " << volMonDayYear->month << "\n";
        strftime(sbuf, sizeof(sbuf), "%d", &date);
        volMonDayYear->day = string(sbuf);
        cout << "DAY: " << volMonDayYear->day << "\n";
        strftime(sbuf, sizeof(volMonDayYear->year), "%Y", &date);
        volMonDayYear->year = string(sbuf);
        cout << "YEAR: " << volMonDayYear->year << "\n";
    }

    if((volNum = GetVol(volMonDayYear)) != 0) {
        cout << "VOL NUM: " << volMonDayYear->volNum << "\n";
    }
}

static void ParseDir(const fs::path& pathToScan, int level = 0) {

    for(const auto& entry : fs::directory_iterator(pathToScan)) {
        cout << "L: " << level << setw(1) << "";
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_directory()) {
            cout << setw(level * 3) << "" << "D: " << filenameStr << "\n";
            ParseDir(entry, level +1 );
        } else if ( entry.is_regular_file()) {
            cout << setw(level * 3) << "" << "F: " << filenameStr << "\n";
        } else {
            cout << setw(level * 3) << "" << " [?]" << filenameStr << "\n"; 
        }
    }
} 

int main(int argc, const char * argv[]) {

#ifdef CONSOLE_INPUT
    while(true) {
#else
    for(formInfoIndex=0; formInfoIndex < sizeof(formInfo)/sizeof(FormInfo); formInfoIndex++) {
#endif
        VolMonDayYear volMonDayYear;

        GetInfo(&volMonDayYear);
        ParseDir(adult_volunteer_root_dir);
    }

    return 0;
}
