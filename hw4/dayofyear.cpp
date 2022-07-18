#include<iostream>
#include<cstdlib>
#include"dayofyear.h"
using namespace std;



namespace SetofDays{

    int DayofYearSet::totalObjects = 0;

    DayofYearSet::DayofYearSet()
        :capacity(0)
    { }

    DayofYearSet::DayofYearSet(int day, int month)
        :capacity(0)
    {
        add(day, month);
    }

    DayofYearSet::DayofYearSet(int day1, int month1, int day2, int month2)
        :capacity(0)
    {   
        add(day1, month1);
        add(day2, month2);

    }
    
    DayofYearSet::DayofYearSet(const vector<DayofYear>&v)
        :capacity(v.size())
    {
        
        d = new DayofYear[capacity];
        
        for(int i = 0 ; i <getSize(); i++){
            d[i].setDay(v[i].getDay());
            d[i].setMonth(v[i].getMonth());
            AddNewObject(1);
        }
    }


    DayofYearSet::DayofYearSet(const DayofYearSet& Obj) /* Copy Constructor */
        :capacity(Obj.capacity)
    {
        d = new DayofYear[getSize()];
        for(int i = 0 ; i < getSize(); i++ ){
            d[i].setDay(Obj.d[i].getDay());
            d[i].setMonth(Obj.d[i].getMonth());
            AddNewObject(1);
        }
  
    }
    DayofYearSet::~DayofYearSet(){
        if(capacity>0){ /* To prevent deleting uninitialized dynamical arrays */
            RemoveObject(getSize());
            delete[] d;
        }
    }

    DayofYearSet& DayofYearSet::operator=(const DayofYearSet& Obj) /* Assignment operator */
    {
        if(capacity != Obj.capacity){
            delete[] d;
            d = new DayofYear[Obj.capacity];
        }
        capacity = Obj.capacity;
        for(int i = 0; i < capacity; i++){
            d[i].setDay(Obj.d[i].getDay());
            d[i].setMonth(Obj.d[i].getMonth());
            AddNewObject(1);
        }
        
        return *this;
    }
    bool DayofYearSet::operator==(const DayofYearSet& Obj) const{
        bool isFound = false, isEqual = true;

        for(int i = 0 ; i < getSize(); i++){
            isFound = false;
            for(int j = 0; j < Obj.getSize(); j++){
                if(( Obj.d[j].getDay() == d[i].getDay()) && (Obj.d[j].getMonth() == d[i].getMonth()))
                    {
                        isFound = true;
                        break;
                    }
            }
            if(isFound != true){
                isEqual = false;
                break;
            }
        }
        if( (isEqual == true) && (getSize()==Obj.getSize()))
            return true;
        else 
            return false;
    } 
    bool DayofYearSet::operator!=(const DayofYearSet& Obj) const{
        bool isEqual = false;
        if(*this == Obj)
            isEqual = true;
        else 
            isEqual = false;
        if(isEqual == true)
            return false;
        else
            return true;
    }
 const DayofYearSet DayofYearSet::operator+(const DayofYearSet& Obj)const{ /* Return union set */
      
  vector<DayofYear>union_set;
        bool check = false;
        int size_of_union = 0, vector_index = 0;
        /* First we need to determine size of union set */
        
        for(int i = 0; i < getSize(); i++) 
            size_of_union++;
        
        for(int i = 0; i < Obj.getSize(); i++){
            check = false;
            for(int j = 0; j <getSize(); j++){
                if(( d[j].getDay() == Obj.d[i].getDay() ) && ( d[j].getMonth() == Obj.d[i].getMonth() )){
                    check = true;
                    break;
                }
            }
             if(check == false)
                size_of_union++;
        }
        union_set.resize(size_of_union); /* Set the  vector's size accordingly */
        for(int i = 0 ; i < getSize(); i++){
            union_set[i].setDay(d[i].getDay());
            union_set[i].setMonth(d[i].getMonth()); 
        }
        vector_index = getSize();
        for(int i = 0; i < Obj.getSize(); i++){
            for(int j = 0; j <getSize(); j++){
                check = false;
                if(( d[j].getDay() == Obj.d[i].getDay() ) && ( d[j].getMonth() == Obj.d[i].getMonth() )){
                    check = true;
                    break;
                }
            }
            if(check == false){
                union_set[vector_index].setDay(Obj.d[i].getDay());
                union_set[vector_index].setMonth(Obj.d[i].getMonth()); 
                vector_index++;
            }
        }
        
        return DayofYearSet(union_set);
      
    }
    const DayofYearSet DayofYearSet::operator-(const DayofYearSet& Obj) const{  /* A difference B */
        vector<DayofYear>difference;   
        DayofYearSet::DayofYear a;
        bool check = false;

        for(int i = 0; i < getSize(); i++){
            check = false ;
            for(int j = 0 ; j < Obj.getSize(); j++){
                if( (d[i].getDay()==Obj.d[j].getDay() ) && (d[i].getMonth()==Obj.d[j].getMonth() ) ){
                    check = true;
                    break;
                }
            }
            if( check == false){
                a.setDay(d[i].getDay());
                a.setMonth(d[i].getMonth());
                difference.push_back(a);
            }
        }
        
        return DayofYearSet(difference);
    }
    const DayofYearSet DayofYearSet::operator^(const DayofYearSet& Obj) const{ /* Interection */
        vector<DayofYear>intersection;
        DayofYearSet::DayofYear r;
        bool check = false;
        for(int i = 0 ; i < getSize(); i++){
            check = false;
            for(int j = 0 ; j < Obj.getSize() ; j++ ){
                if( (d[i].getDay()==Obj.d[j].getDay() ) && (d[i].getMonth()==Obj.d[j].getMonth() ) ){
                    check = true;
                    break;
                }
            }
            if(check == true){
                r.setDay(d[i].getDay());
                r.setMonth(d[i].getMonth());
                intersection.push_back(r);
            }
        }
    
        return DayofYearSet(intersection);
    }
    const DayofYearSet DayofYearSet::operator!() const{ /* Complement --> All days except days inside of the DayofYearSet */ 
        bool check = false;
        vector<DayofYear>complement;
        DayofYearSet::DayofYear a;
        int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; 

        for(int i = 1 ; i <= 12 ; i++){
            for(int k = 1 ; k <= months[ i - 1] ; k++){
                a.setDay(k);
                a.setMonth(i);
                complement.push_back(a);
            }
        }
        for(auto i = complement.begin(); i != complement.end(); i++){
            for(int j = 0 ; j < getSize(); j++){
                if( ( d[j].getMonth() == i->getMonth()) && ( d[j].getDay() == i->getDay()) ){
                    complement.erase(i);
                    i--;
                    break;
                }
            }
        }
        return DayofYearSet(complement);
    }
    DayofYearSet::DayofYear& DayofYearSet::operator[](int index){
        if(index>=getSize()){
            cerr<<"Your index does not exist in DayofYearSet!"<<endl;
            exit(0);
        }
        return d[index];
    }
    ostream& operator<<(ostream &os, const DayofYearSet& Obj){ /* Prints all the elements inside of DayofYearSet obj */

        os<<endl;
        for(int i = 0 ; i < Obj.getSize() ; i++){
            if(Obj.d[i].getDay()<10)
                os<<'0'<<Obj.d[i].getDay()<<".Day ";
            else
                os<<Obj.d[i].getDay()<<".Day ";
        
            if(Obj.d[i].getMonth()<10)
                os<<'0'<<Obj.d[i].getMonth()<<".Month"<<endl;
            else
                os<<Obj.d[i].getMonth()<<".Month"<<endl;
        }
        return os;
    }
    ostream& operator<<(ostream &os, const DayofYearSet::DayofYear& Obj){ /* Prints given index of DayofYearSet */
           if(Obj.getDay()<10)
                os<<'0'<<Obj.getDay()<<".Day ";
            else
                os<<Obj.getDay()<<".Day ";
        
            if(Obj.getMonth()<10)
                os<<'0'<<Obj.getMonth()<<".Month"<<endl;
            else
                os<<Obj.getMonth()<<".Month"<<endl;
        
        return os;
    }
    void DayofYearSet::AddNewObject(int number){
        totalObjects+=number;
    }

    void DayofYearSet::RemoveObject(int number){
        totalObjects-= number;
    }

    int DayofYearSet::TotalNumberofObjects(){
        return totalObjects;
    }
    
    void DayofYearSet::add(int _day, int _month){ /* Add an element at the last index of Set */
        int initial_capacity = getSize();
        if(isValidInput(_day, _month)==true){
            if(initial_capacity==0){ /* For uninitialized array */
                capacity++;
                d = new DayofYear[capacity];
                d[0].setDay(_day);
                d[0].setMonth(_month);        
            }
            else if(initial_capacity > 0 ){
                DayofYearSet copy(*this);    
                initial_capacity = this->getSize();
                delete [] d; 
                capacity = initial_capacity + 1;
                d = new DayofYear[capacity];
                for(int i = 0; i < initial_capacity  ; i++)
                {
                    d[i].setDay(copy.d[i].getDay());
                    d[i].setMonth(copy.d[i].getMonth());
                }
                    d[initial_capacity].setDay(_day);
                    d[initial_capacity].setMonth(_month);
            }
            RemoveObject(initial_capacity);
            AddNewObject(capacity);
        }
    }
    void DayofYearSet::remove(int index){ /* Remove an element at given index from Set */
        int initial_capacity = getSize(), counter = 0;
        
        if(index>=capacity)
            cerr<<"Error! : Your index's value is greater than Set's capacity "<<endl;
        else{
            DayofYearSet copy(*this);
            delete [] d;
            capacity = initial_capacity - 1;
            d = new DayofYear[capacity];
            
            for(int i = 0 ; i < initial_capacity ; i++)
            {
                if(index != i){
                    d[counter].setDay(copy.d[i].getDay());
                    d[counter].setMonth(copy.d[i].getMonth());
                    counter++;
                }
            }
            RemoveObject(1);
        }
    }
    
    bool DayofYearSet::isValidInput(int _day, int _month) const
    {
        bool isValidMonth = false, isValidDay = false, isDateExist = false;
        int counter = 0;
        int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; 
        
        if( _month > 0 && _month <=12){
            isValidMonth = true;
            for(counter = 0 ; counter < 12; counter++){
                if(_month == counter + 1)
                    break;
            }
            if( months[counter]>= _day)
                isValidDay = true;
            else{
                isValidDay = false;
                cerr<<"Error: Your input date is not a valid date ! "<<endl;
            }
        }
        else{
            cerr<<"Error: Your input date is not a valid date !"<<endl;
            isValidMonth = false;
        }
        if(getSize() >= 0){
            for(int i = 0 ; i <getSize(); i++){
                if(d[i].getDay()==_day && d[i].getMonth()==_month){
                    isDateExist = true; /* The given date is exist in our Set */
                    cerr<<"Error: Date is exist in DayofYearSet! "<<endl;
                    break;
                }                       /* Return false */
            }
        }
        else
            isDateExist = false; 
        

        if(isValidDay == true && isValidMonth == true && isDateExist ==false)
            return true;
        else
            return false;
    
    
    }
 
    int DayofYearSet::getSize() const{ /* Return current capacity of dynamical array */
        return capacity ;
    }

    void DayofYearSet::write_to_file(string file_name) const
    {
        string str ="Your DayOfYearSet is copied successfully ";
        ofstream file(file_name);
        auto index = 0;
        decltype(str) warning = "The file could not open !";
        if(file.is_open())
        {
            for(index = 0 ; index < getSize(); index++){
                if(d[index].getDay()<10)
                    file<<'0'<<d[index].getDay()<<".Day ";
                else
                    file<<d[index].getDay()<<".Day ";
            
                if(d[index].getMonth()<10)
                    file<<'0'<<d[index].getMonth()<<".Month"<<endl;
                else
                    file<<d[index].getMonth()<<".Month"<<endl;
                
            }
            file.close();
        }
        else
            cout<<warning<<endl;
    }
    
    /* DayofYear inner class implementions */

    void DayofYearSet::DayofYear::setDay(int _day){
        day = _day;
    }
    void DayofYearSet::DayofYear::setMonth(int _month){
        month = _month;
    }
    int DayofYearSet::DayofYear::getDay() const 
    {
        return day;
    }
    int DayofYearSet::DayofYear::getMonth() const 
    {
        return month;
    }



}