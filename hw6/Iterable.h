#ifndef ITERABLE_H
#define ITERABLE_H
#include<iostream>
#include<algorithm> // To test sort, find functions
#include<cstdlib>
#include<string>
#include<cstring>
#include<vector>
#include<memory>

using namespace std;
namespace SavitchIterable{
    template<class T>
    class Iterable{
        
        public:
            Iterable( );
            Iterable(int size);
            //Iterable(const Iterable<T>&Obj);
            //~Iterable( );
            virtual  bool empty( ) const = 0;//Test whether container is empty
            virtual int size( ) const = 0; //Return container size        
            virtual void erase(const T* iterator) = 0; //Erase element pointed by the given iterator, and reduces the container size
            virtual void clear( ) = 0;// Clear all the content in container
            
            virtual T* begin( ) const = 0 ;//Return iterator to beginning  
            virtual T* end( ) const = 0; //Return iterator to end
            
            virtual const T* cbegin( ) const = 0; //Return constant iterator to beginnig
            virtual const T* cend( ) const = 0; //Return constant iterator to end
            Iterable<T>& operator=(const Iterable<T>&Obj); //Assignment operator
            int getCapacity( ) const;
            int getUsed( ) const;
            void modifyUsed(int value);//Modify private variable used by adding an integer number
        
        private:
            int capacity;
            int used;
    
    };

    class CapacityisFullException
    {
        public:
            CapacityisFullException( )
            {
                cerr<<"Error : Exception is caught"<<endl;

            }
            void what( ){
                cerr<<"Capacity of container is full !"<<endl;
            }    

    };

}

#endif