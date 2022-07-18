
#ifndef _DAYOFYEAR_H
#define _DAYOFYEAR_H
#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<string>
#include<cstring>
using namespace std;


namespace SetofDays{
   

    class DayofYearSet{
        public :
        
          
          class DayofYear{ /* inner class DayofYear */
            public:
            
            int getDay() const; 
            int getMonth() const;
            void setDay(int _day);
            void setMonth(int _month); 
            private:
                int day;
                int month;
        };
        
        DayofYearSet();
        DayofYearSet(const vector<DayofYear>&v); /* Use vector's elements to create a new DayofYearSet */
        DayofYearSet(int day1, int month1, int day2, int month2);
        DayofYearSet(int day, int month);
        /* For any class that uses pointers and the new operator, it is 
         safest to define your own copy constructor, overloaded =, and a destructor. */
        DayofYearSet(const DayofYearSet& Obj); /* Copy constructor */
        DayofYearSet& operator =(const DayofYearSet& Obj); /* Assignment operator */
        ~DayofYearSet();
        
        friend ostream& operator<<(ostream &os, const DayofYearSet& Obj); /* Print DayofYearSet details */
        friend ostream& operator<<(ostream &os, const DayofYearSet::DayofYear& Obj); /* Prints one of DayofYearSet elements */
        bool operator==(const DayofYearSet& Obj) const;  /* Checks if two sets are equal */
        bool operator!=(const DayofYearSet& Obj) const; /* Checks if two sets are not equal */
        const DayofYearSet operator+(const DayofYearSet& Obj) const; /* Returns the union set  */
        const DayofYearSet operator-(const DayofYearSet& Obj) const; /* Returns the difference set. */
        const DayofYearSet operator^(const DayofYearSet& Obj) const; /* Returns the intersection set. */
        const DayofYearSet operator!() const; /* Returns the complement set. */
        DayofYear& operator[](int index); /* Returns the element at given position. */
        
     
        void add(int _day, int _month); /* Adds an element to the set. */
        void remove(int index);     /* Removes an element from the set. */
        void write_to_file(string file_name) const; /* Write DayofYearSet to file */
        bool isValidInput(int _day, int _month) const;
        /* It checks if a date which is given for add function is a valid date or not */
        /* It also checks the repetition whether given input date is exist in the DayofYearSet or not */
        
        int getSize() const; /* Returns the number of elements. */
        static int TotalNumberofObjects(); /* Returns the total number of DayOfYear objects alive in all the Sets */
        static void AddNewObject(int number); /* Add new objects to total number of active DayofYear objects */
        static void RemoveObject(int number); /* Remove objects from active DayofYear objects */
        private:
            int capacity; /* Capacity dynamical DayOfYear object */
            DayofYear *d;
            static int totalObjects ;
    };

}

#endif