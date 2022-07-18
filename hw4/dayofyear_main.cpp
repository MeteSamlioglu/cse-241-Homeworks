#include<iostream>
#include"dayofyear.h"


using namespace std;

void test1(const SetofDays::DayofYearSet& s1, const SetofDays::DayofYearSet& s2){
    using SetofDays::DayofYearSet;
    cout<<"-----------Test1----------------"<<endl;
    cout<<"Set1 Elements"<<s1<<"Set2 Elements"<<s2<<endl;
    cout<<"Is s1=s2 :?";
    if(s1 == s2) 
        cout<<"Yes"<<endl;
    else if(s1 != s2)
        cout<<"No"<<endl;
    
    DayofYearSet union_set = s1 + s2 ; 
    cout<<"Union set(s1 U s2)  "<<union_set<<endl;
    DayofYearSet intersection = s1 ^ s2;
    cout<<"Intersection set(s1 ^ s2)"<<intersection<<endl;
    DayofYearSet difference = s1 - s2;
    cout<<"Difference set(s1 - s2)"<<difference<<endl;
    cout<<"De Morgan Rule";
    cout<<endl<<"Is !(s1 + s2) == (!s1^!s2) ? true = ";
    if(!(s1 + s2) == (!s1^!s2)) 
        cout<<"True !"<<endl;
    else
        cout<<"False"<<endl;
    
    cout<<endl<<"Is !(s1 + s1) == (!s1^!s1) ? true = ";
    if(!(s1 + s1) == (!s1^!s1)) 
        cout<<"True !"<<endl;
    else
        cout<<"False"<<endl;

    intersection.write_to_file("intersection1.txt"); /* You can write any set to file */
    cout<<"--------------------------------"<<endl;
}

void test2(const SetofDays::DayofYearSet s1, const SetofDays::DayofYearSet s2 ){
    using SetofDays::DayofYearSet;
    cout<<endl<<"-----------Test2----------------"<<endl;
    cout<<"Set 1 "<<s1<<"Set 2"<<s2;
    
    cout<<endl<<"De morgan rule check :";
    cout<<"Is !(s1 + s2) == (!s1^!s2) ? true = ";
    if(!(s1 + s2) == (!s1^!s2)) 
        cout<<"True !"<<endl;
    else
        cout<<"False"<<endl;
    DayofYearSet union_set = s1 + s2 ; 
    cout<<"Union set(s1 U s2) "<<union_set<<endl;
    DayofYearSet intersection = s1 ^ s2;
    cout<<"Intersection set(s1 ^ s2)"<<intersection<<endl;
    DayofYearSet difference = s1 - s2;
    cout<<"Difference set(s1 - s2)"<<difference<<endl;
    if(s1 == s2)
        cout<<"Sets are equal"<<endl;
    else
        cout<<"Sets are not equal"<<endl;
    

    union_set.write_to_file("union1.txt");
    
    cout<<"-----------------------------"<<endl; 
}
void testIncorrectInputs(){
    using SetofDays::DayofYearSet;
    cout<<"Incorrect input test"<<endl;
    DayofYearSet d1(30,13);
    DayofYearSet d2(5, 12, 5, 12);
    DayofYearSet d3(30,2);
}
void testComplement(const SetofDays::DayofYearSet s1){
    using SetofDays::DayofYearSet;
    DayofYearSet complement = !s1;
    cout<<complement;
}

int main(){

    using SetofDays::DayofYearSet;
    DayofYearSet Dates1(12,11, 9,2);
    DayofYearSet Dates2(4, 12, 1, 1);
    test1(Dates1, Dates2); // Test my first initilialized sets */
    cout<<"The total number of DayOfYear objects alive in all sets: " <<Dates1.TotalNumberofObjects()<<endl;
    /* Modify Sets */
    Dates1.add(4, 12);
    Dates1.add(1, 1);
    Dates1.remove(1); /* Delete the element at index 1  which is Day: 9 Month: 2*/
    Dates2.add(15, 11);
    Dates2.add(3,4);
    cout<<endl<<"After modification"<<endl;
    test1(Dates1, Dates2);
    
    /* ------------------------------------------- */
    DayofYearSet Dates3(Dates1); /* Copy constructor works */
    DayofYearSet Dates4(Dates2);
    Dates3.add(6,2);
    Dates3.add(10,11);
    Dates4.remove(0); /* Remove first index element which is Day 4, Month 12 */
    cout<<endl<<"Does Dates3 set equal Dates 3 ";
    if(Dates3 == Dates3)
        cout<<"True";
    else
        cout<<"False";

    test2(Dates3,Dates4);
    cout<<endl<<"The total number of DayOfYear objects alive in all sets: " <<Dates1.TotalNumberofObjects()<<endl;

    test1(Dates1, Dates3);
    
    cout<<"Dates1[0] element : "<<Dates1[0];
    Dates1.remove(0); /* Remove first index of Dates1 set, check global DateofYear objects count */
    cout<<"Old Dates1[0] removed, new Dates1[0] element : "<<Dates1[0];

    cout<<endl<<"The total number of DayOfYear objects alive in all sets: " <<Dates1.TotalNumberofObjects()<<endl;
    
    testIncorrectInputs();

    /* testComplement has too many outputs, therefore i made it comment line, but it works */
    //testComplement(Dates1);  
    
    /* All the functions works as expected */
    /* I used vector parameter constructor as a return value of operator overloading functions, it would be more efficient in that way */


    return 0;
}


