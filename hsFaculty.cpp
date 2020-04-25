
/**
    hsFaculty.cpp
    Declaration file for the class hsFaculty.
*/

#include "hsFaculty.h"
#include "systemControl.h"
#include "cstdlib"
#include "string"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;


hsFaculty::hsFaculty() {
	User();
}

hsFaculty::hsFaculty(const User& source) {
	setID(source.getID());
	setName(source.getUserName());
	setPassword(source.getPassword());
}

hsFaculty::hsFaculty(const hsFaculty& source) {
	setID(source.getID());
	setName(source.getName());
	setPassword(source.getPassword());
}

hsFaculty hsFaculty::operator=(const hsFaculty& source) {
	setID(source.getID());
	setName(source.getName());
	setPassword(source.getPassword());
	return *this;
}

bool hsFaculty::operator==(const hsFaculty& source) {
	if (getID() == source.getID() && getName() == source.getName() && getPassword() == source.getPassword())
		return true;
	else return false;
}


void hsFaculty::viewSchedule(schedule my_schedule)
{
    my_schedule.printSchedule();
}


void hsFaculty::editSchedule(schedule my_schedule)
{
    int choice;
    //ask if user wants to add dates or remove dates & enters those functions
    cout << "Enter 1 if you wish to add a date, or 2 if you wish to remove one: ";
    cin >> choice;
    while (choice != 1 && choice != 2) {
        cout << "Invalid input.\n";
        cout << "Enter 1 if you wish to add a date, or 2 if you wish to remove one: ";
        cin >> choice;
    }
    
    if (choice == 1) addDates(my_schedule);
    else removeDates(my_schedule);
}


void hsFaculty::addDates(schedule my_schedule)
{
    // adds new dates to semester schedule
    string date;
    cout << "Enter the date: ";
    cin >> date;

    my_schedule.setDate(date);
}

void hsFaculty::removeDates(schedule my_schedule)
{
    //removes dates from semester schedule
}

void hsFaculty::removeAvailableTimes(schedule my_schedule)
{
    
}

void hsFaculty::showStats(coronaInfo& nationalStats, Statistics& stats) const
{
    User::showStats(nationalStats); // displays base class function first
    cout << "Patients Registered:\t\t" << stats.getPatientCount() << endl;
    cout << "Flu like Symptoms:\t\t" << stats.getFluCount() << "  /  " << stats.getFluPercent() << endl;
    cout << "# of Patients with Coronavirus:\t\t" << stats.getCoronaCount() << "  /  " << stats.getCoronaPercent() << endl;
    cout << "# of Patients who saught Counseling:\t" << stats.getCounselingCount() << "  /  " << stats.getCounselingPercent() << endl;
}

void hsFaculty::updateRecord(schedule schedule, User faculty, Statistics& statSet, const systemControl& sys)
{
    User patient;
	bool another = false;

    cout << endl;
    
    do
    {
		int id;
		string fileName, notes;
		ofstream o_stream;
		stringstream s_stream;
		bool checked = false;
		bool counselling, flu, tested_corona, positive_corona;

        do
        {

            cout << "\nEnter Patient ID: #";
            cin >> id;
        
            patient.setID(id);
        
            if (!sys.verifyUser(patient))
            {
                cout << "\nError: Patient not found.\n\n";
            }
            else
            {
                checked = true;
        
                s_stream << id;
                fileName = s_stream.str();
        
                o_stream.open(fileName, std::ios::app);
        
                if (!o_stream.is_open())
                {
                    checked = false;
                    cout << "\nError: Could not open file.\n\n";
                }
            }
        } while (!checked);
    
            // Printing Patient & Appointment details to Record
        o_stream << "==========================================================================\n\n";
        o_stream << "Patient Name: " << patient.getUserName();
        o_stream << "\t\t\t\tID: #" << patient.getID();
        o_stream << "\n\nPractitioner Seen: " << faculty.getUserName();
        o_stream << "\t\t\tApt: "; // << schedule.printAppt();
    
        cout << "\n----------------------------------\n\n";
        cout << "\tEnter: 1 for Yes, 0 for No.\n\n";
        cout << "----------------------------------\n\n";
    
            // Input Counselling
        cout << "Patient seen for counselling services: ";
        o_stream << "\n\nPatient seen for counselling services: ";
        cin >>  counselling;
    
            if (counselling)
            {
                o_stream << "YES";
                statSet.incrementCounselingCount();
            }
            else
            {
                o_stream << "NO";
            }
    
    
            // Input Flu Like Symptoms
        cout << "\nPatient showed flu like symptoms: ";
        o_stream << "\n\nPatient showed flu like symptoms: ";
        cin >>  flu;
        
            if (flu)
            {
                o_stream << "YES";
                statSet.incrementFluCount();
            }
            else
            {
                o_stream << "NO";
            }
    
            // Input Tested for Coronavirus
        cout << "\nPatient was tested for the Coronavirus: ";
        o_stream << "\nPatient was tested for the Coronavirus: ";
        cin >> tested_corona;
    
            if (tested_corona)
            {
                o_stream << "YES";
            }
            else
            {
                o_stream << "NO";
            }
    
            // Input TESTED POSITIVE for Coronavirus
        cout << "\nPatient TESTED POSITIVE for the Coronavirus: ";
        o_stream << "\nPatient TESTED POSITIVE for the Coronavirus: ";
        cin >> positive_corona;
    
            if (positive_corona)
            {
                o_stream << "YES";
                statSet.incrementCoronaCount();
            }
            else
            {
                o_stream << "NO";
            }
    
            // Allow faculty to enter notes
        cout << "\nNotes: ";
        o_stream << "\n\nNotes:\n\n\t";
        cin.ignore();
        getline(cin,notes);
        o_stream << notes;
        o_stream << "\n\n==========================================================================\n";
    
            // Closing stream
        o_stream.close();
    
        if (!o_stream.is_open())
        {
            cout << "\nWriting Complete: Information written to record.";
        }
        
        cout << "\n\nWould you like to enter another? ( 1 = YES  |  0 = NO )\n";
        cin >> another;
		
		cout << endl << endl;
        
    } while (another);
}

void hsFaculty::viewRecord(const systemControl &sys)
{
    User patient;
    bool another = false;
    bool answer = false;

    cout << endl;

    do
    {
		int ID;
		string fileName;
		ifstream i_stream;
		stringstream s_stream;
		bool checked = false;

        do
        {
		
            cout << "\nEnter Patient ID to view: #";
            cin >> ID;
           
            patient.setID(ID);
            
            if (!sys.verifyUser(patient))
            {
                cout << "\nError: Patient not found.\n";
            }
            else
            {
                checked = true;
           
                s_stream << ID;
                fileName = s_stream.str();
           
                i_stream.open(fileName);
           
                if (!i_stream.is_open())
                {
                    checked = false;
                    cout << "\nError: Could not open file.\n";
                }
            }
            
            cout << "\nWould you like to exit? ( 1 = YES  |  0 = NO )  ";
            cin >> answer;
                
            if (answer) { return; }
                
        } while (!checked);
    
        cout << endl << i_stream.rdbuf();
    
        i_stream.close();
        
        cout << "\n\nWould you like to view another? ( 1 = YES  |  0 = NO )  ";
        cin >> another;
		cout << endl;
        
    } while (another);
}

