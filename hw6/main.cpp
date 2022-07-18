#include"GTUVector.h"
#include"GTUVector.cpp"
#include"GTUSet.h"
#include"GTUSet.cpp"
#include"GTUArray.h"
#include"GTUArray.cpp"
#include<iostream>

using SavitchIterable::GTUVector;
using SavitchIterable::GTUSet;
using SavitchIterable::GTUArray;


void print(double num) // To test for_each loop
{
    cout<<num<<" ";

}
void print2(int num)
{
    cout<<num<<" ";
}

void testVector( )
{
    GTUVector<double> A;
    GTUVector<double>B;
    A.add(2.5);
    A.add(3.4);
    A.add(4.6);
    A.add(5.4);
    A.add(4.9);
    B.add(3.1);
    B.add(9.2);
    B.add(7.6);
    B.add(9.10);

    cout<<"Vector A elements "<<endl;    
    for(auto i = A.cbegin( ); i < A.cend( ); i++)
        cout<<(*i)<<" ";
    cout<<endl<<"size "<<A.size( );
    cout<<endl<<"-------------"<<endl;
    cout<<"Vector B elements "<<endl;    
    for(auto i : B)
        cout<<i<<" ";
    cout<<endl<<"size "<<A.size( );
    cout<<endl<<"-------------"<<endl;
    cout<<"erase function check delete second element of A"<<endl;
    A.erase(A.begin( ) + 1);
    for(auto i : A)
        cout<<i<<" ";
        cout<<endl<<"size "<<A.size( );
    cout<<endl<<"-------------"<<endl;
    cout<<"std::find function check find element 7.6 in B"<<endl;
    auto reff = find(B.begin( ), B.end( ), 7.6);
    cout<<(*reff)<<" is found";
    cout<<endl<<"-------------"<<endl;
    cout<<"std::sort function check sort vector A"<<endl;
    sort(A.begin( ), A.end( ));
    for(auto i : A)
        cout<<i<<" ";
    cout<<endl<<"-------------"<<endl;
    cout<<"std::for each function check print vector B elements"<<endl;
    for_each(B.begin( ), B.end( ), print);
    cout<<endl<<"-------------"<<endl;
    cout<<"clear( ) and empty( )functions check, delete vector A "<<endl;
    A.clear( );
    for(auto i : A)
        cout<<i<<" ";
    cout<<endl<<"size "<<A.size( )<<endl;
    if(A.empty( ) == true)
        cout<<"Vector is empty"<<endl;
    cout<<endl<<"-------------"<<endl;
    cout<<"Delete first element of B"<<endl<<"Old first element "<<B[0]<<endl;
    B.erase(B.begin( ));
    cout<<"New first element "<<B[0];

    cout<<endl<<"-------------"<<endl;
   
}

void testSet( )
{
    GTUSet<int> A;
    GTUSet<int> B;
    GTUSet<int> C;
    A.add(10);
    A.add(20);
    A.add(30);
    A.add(80);
    B.add(20);
    B.add(30);
    B.add(60);
    B.add(80);
    cout<<"Set A elements"<<endl;
    for(auto i : A)
        cout<<i<<" ";
    cout<<endl<<"size "<<A.size( );
    cout<<endl<<"-------------"<<endl;
    cout<<"Set B elements"<<endl;
    for(auto i : B)
        cout<<i<<" ";
    cout<<endl<<"size "<<B.size( );
    cout<<endl<<"-------------"<<endl;
    cout<<"Intersection Set of Set A and Set B"<<endl;
    C.intersect(A.begin( ), A.end( ), B.begin( ), B.end( ));
    for(auto i : C)
        cout<<i<<" ";
    cout<<endl<<"-------------"<<endl;
    cout<<"Union Set of Set A and Set B"<<endl;
    C.union_set(A.begin( ), A.end( ), B.begin( ), B.end( ));
    for(auto i : C)
        cout<<i<<" ";
    cout<<endl<<"---------------------"<<endl;
    cout<<"find function test : find 30 in Set B and print all the elements after 30 "<<endl;
    auto k = B.find(30);
    for(auto i = k; i < B.end( ); i++)
        cout<<(*i)<<" ";
    cout<<endl<<"---------------------"<<endl;
    //Since it is a Set, there is no need to try std::sort function, elements will be sorted anytime
    cout<<"for_each function test for Union test C"<<endl;
    for_each(C.begin( ), C.end( ), print2);
    cout<<"size "<<C.size( );
    cout<<endl<<"---------------------"<<endl;
    cout<<"test clear function for Union test C"<<endl;
    C.clear( );
    for_each(C.begin( ), C.end( ), print2);
    cout<<"size "<<C.size( )<<endl;
    cout<<"empty function check "<<endl;
    if(C.empty( ) == true)
        cout<<"Set is empty";
    
    cout<<endl<<"---------------------"<<endl;
    cout<<"test clear Erase function for set A, erase first element"<<endl;
    A.erase(A.begin( ));
    for_each(A.begin( ),A.end( ),print2);
    cout<<endl<<"size "<<A.size( );
    cout<<endl<<"---------------------"<<endl;

}

void testArray( )
{
    GTUArray<int> arr(4);
    GTUArray<double> arr2(10);
    cout<<"Exception handling test"<<endl;
    cout<<"-------------"<<endl;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);
    arr.insert(4);
    arr.insert(5); // An exception will occur because array size is 4
    cout<<"-------------"<<endl;
    cout<<"arr1 elements"<<endl;
    for(auto i : arr) /* Print Elements */
        cout<<i<<" ";
    cout<<endl<<"-------------"<<endl;
    arr2.insert(1.5);
    arr2.insert(0.5);
    arr2.insert(8.5);
    arr2.insert(10.5);
    cout<<"arr2 elements"<<endl;
    for(auto i : arr2)
        cout<<i<<" ";
    
    cout<<endl<<"-------------"<<endl;
    cout<<"std::find test "<<endl;
    auto reff = find(arr2.begin( ), arr2.end( ), 0.5);
    cout<<"Element is found "<<(*reff)<<endl;
    cout<<"-------------"<<endl;
    cout<<"for_each Test"<<endl;
    for_each(arr2.begin( ), arr2.end( ), print);
    cout<<endl<<"-------------"<<endl;
    cout<<"Sort function test"<<endl;
    sort(arr2.begin( ), arr2.end( ));
    for(auto i : arr2)
        cout<<i<<" ";
    
    cout<<endl<<"-------------"<<endl;


}



int main()
{
    cout<<"GTUVector derived class Tests"<<endl;
    testVector( );
    
    cout<<"GTUSet derived class Tests"<<endl;
    testSet( );
    
    cout<<"GTUArray derived class Tests"<<endl;
    testArray( );
    
    

    return 0;

}
