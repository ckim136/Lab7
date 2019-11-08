#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "Course.hpp"


using namespace std;

bool cmp(Course i, Course j){return i.day<j.day;}

vector<string> findConflict(vector<Course> &schedule){
    vector<string> conflictSchedule;
for(vector<Course>::const_iterator it = schedule.begin(); it != schedule.end(); ++it){
    for (auto next = it+1; next!=schedule.end(); ++next){
        if (it->day == next->day && (next->start_time <= it->finish_time)) {
            ostringstream conflict{};
            conflict << "CONFLICT: \n";
            conflict << it->title << " " << it->findDay(it->day)<< " " << it->start_time <<" " << it->finish_time << endl;
            conflict << next->title << " " << next->findDay(next->day) << " " << next->start_time <<" " << next->finish_time << endl <<endl;
            conflictSchedule.push_back(conflict.str());
        }
    }
}
return conflictSchedule;
}

/*
 * print schedule - outputs course schedule to the screen
 * @param - add any new parameters you need
 */
void printSchedule(vector<Course> schedule)
{
    sort(schedule.begin(), schedule.end(), cmp);
    copy(schedule.begin(), schedule.end(), ostream_iterator<Course>(cout));
    cout << endl;
    copy(findConflict(schedule).begin(), findConflict(schedule).end(), ostream_iterator<string>(cout));
}

int main () {
    map<string, Course::dayOfWeek > dayFinder;
    dayFinder.insert(make_pair("M",Course::dayOfWeek::MON));
    dayFinder.insert(make_pair("T",Course::dayOfWeek::TUE));
    dayFinder.insert(make_pair("W",Course::dayOfWeek::WED));
    dayFinder.insert(make_pair("R",Course::dayOfWeek::THUR));
    dayFinder.insert(make_pair("F",Course::dayOfWeek::FRI));

    vector<Course> schedule;
    ifstream f("../courses.txt");
    string line;
    string title;
    string day;
    unsigned int start;
    unsigned int finish;
    while (getline(f, line)){
        istringstream is(line);
         is >> title >> day >> start >> finish;
         Course c(title, dayFinder.find(day)->second, start, finish);
         schedule.push_back(c);
    }
   sort(schedule.begin(), schedule.end());
    printSchedule(schedule);


    return 0;
}