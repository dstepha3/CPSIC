
#pragma once

/**
    hsFaculty.h
    Declaration file for class hsFaculty
*/

#ifndef HSFACULTY_H
#define HSFACULTY_H

#include "User.h"

/**
    @author Daniel Stephan dstepha3@kent.edu
*/

class hsFaculty: private User
{
public:
    
    /**
     Displays the schedule.
     
     @param Schedule An instance of the current schedule
     */
    void viewSchedule(schedule);
    
    /**
     Allows user to add additional dates to semester schedule or
     Allows user to remove dates from semester schedule or
     
     @param schedule An instance of the current schedule
     */
    void editSchedule(schedule);
    
    /**
     Remove available times to semester schedule
     
     @param schedule An instance of the currant schedule
     */
    void removeAvailableTimes(schedule);
    
    /**
     Displays current statistics of Coronavirus cases in Ohio & USA.
     Displays Coronavirus related statistics of HS Facility.
     
     @param Statistics
     */
    void showStats(statistics);

private:
    /**
     Adds additional dates to semester schedule
     
     @param Schedule An instance of the current schedule
     */
    void addDates(schedule);
    
    /**
     removes dates from semester schedule
     
     @param Schedule An instance of the current schedule
     */
    void removeDates(schedule);
   
};

#endif