#include"GTUArray.h"
using namespace std;


namespace SavitchIterable{

    template<class T>
    GTUArray<T>::GTUArray( )
        :Iterable<T>(50), capacity(50) // initialize with capacity 50
    {
        array.reset(new T[capacity]);
       
    }
    
    template<class T>
    GTUArray<T>::GTUArray(int size_)
        :Iterable<T>(size_), capacity(size_)
    {
        array.reset(new T[capacity]);
    }

    template<class T>
    GTUArray<T>::GTUArray(const GTUArray<T>&Obj)
        :capacity(Obj.capacity), used(Obj.used)
    {

        array.reset(new T[Obj.used]);
         for(int i = 0; i < capacity ; i++)
             array[i] = Obj.array[i];

    }
    template<class T>
    GTUArray<T>::GTUArray(GTUArray<T>&& other )noexcept // Move constructor
        :capacity(0), used(0), array(nullptr)
    {

        capacity = other.capacity;
        used = other.used;
        other.array = nullptr;
        other.capacity = 0;
        other.used = 0;
    }
    template<class T>
    GTUArray<T>& GTUArray<T>::operator=(GTUArray<T>&& other) noexcept //Move Assignment operator
    {
        if(this != &other)
        {
            array.reset( ); //delete data

            used = other.used;
            capacity = other.capacity;

            other.array = nullptr;
            other.capacity = 0;
            other.used = 0;
        }
        return *this;
    } 
    
    template<class T>
    GTUArray<T>::~GTUArray( )
    {
         array.reset( );
         
    }
    
    template<class T>
    GTUArray<T>& GTUArray<T>::operator=(const GTUArray<T> &Obj)
     {
         if(capacity != Obj.capacity){
            array.reset( );
            array.reset(new T[Obj.capacity]);
         }
         capacity = Obj.capacity;
         used = Obj.used;
        
         for(int i = 0; i < capacity; i++)
             array[i] = Obj.array[i];
        
        
         return *this;

    }
    
    template<class T>
    bool GTUArray<T>::empty( ) const
    {
         if( used == capacity) // Container is full
             return false;
         else   // Container is not empty
             return true;
    
    }

    template<class T>
    int GTUArray<T>::size( ) const
    {
         return capacity;
    }
    
    template<class T>
    void GTUArray<T>::insert(T element)
    {   
        if(used == 0){
            array[used] = element;
            used++;
        
        }
        else{
            try{
                if(used == capacity)
                    throw CapacityisFullException( );
                
                shared_ptr<T[]> copy;
                copy.reset(new T[used + 1]);
                for(int i = 0; i < used ; i++)
                    copy[i] = array[i];
                
                copy[used] = element;
                
                array.reset( ); //delete content
                used++; //increment size    
                array.reset(new T[used]);
                
                for(int i = 0; i < used; i++)
                    array[i] = copy[i];
            
                copy.reset( ); // delete copy
            }
            catch(CapacityisFullException& capacityisFullException){
                cout<<"Exception occured "<<endl;
                capacityisFullException.what( );
            }
        
        }

    }
    
    template<class T>
    void GTUArray<T>::erase(const T*iterator)
    {
       int counter = 0;
       int index = 0;
       shared_ptr<T[]> copy;
       copy.reset(new T[used - 1]);
       
       for(auto i = begin( ); i < end( ); i++){
            if(i == iterator)
               break; 
            index++;
       }
        for(int j = 0; j < used; j++)
        {
            if(j != index){
                copy[counter] = array[j];
                counter++;
            }
        }
        array.reset( );
        used--;
        array.reset(new T[used]); 
        for(int i = 0; i < used; i++)
            array[i] = copy[i];

        copy.reset( );
    }
    
    template<class T>
    void GTUArray<T>::clear( )
     {
        used = 0;
        array.reset( );
        array.reset(new T[capacity]);
     
    }
     
     template<class T>
     T& GTUArray<T>::operator[](int index)
    {
        return array[index];
        
    }
    
    template<class T>
    T* GTUArray<T>::begin( ) const //Return the addres of first element
    {
        auto reff = array.get( );

        return reff;
    }
   
    template<class T>
    T* GTUArray<T>::end( ) const //Return the addres of last element
    {
        auto headreff = array.get( );
        int last_index = used;
        auto endreff = headreff + last_index;

        return endreff;
    }
    
    template<class T>
     const T* GTUArray<T>::cbegin( ) const //Return the cons addres of first element
     {

        auto reff = array.get( );
        
        return reff;
     }
    
    template<class T> 
    const T* GTUArray<T>::cend( ) const //Return the addres of const last element
     {
        auto headreff = array.get( );
        int last_index = used;
        auto endreff = headreff + last_index;
        
        return endreff;
     }


}