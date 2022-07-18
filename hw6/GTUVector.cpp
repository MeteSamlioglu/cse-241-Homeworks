#include"GTUVector.h"
using namespace std;

namespace SavitchIterable{

    template<class T>
    GTUVector<T>::GTUVector( )
        :Iterable<T>(0), capacity(1)
    {
        vect.reset(new T[capacity]);
       
    }
    template<class T>
    GTUVector<T>::GTUVector(int size_)
        :Iterable<T>(size_), capacity(size_)
    {
      
        vect.reset(new T[capacity]);

    }
    template<class T>
    GTUVector<T>::GTUVector(const GTUVector<T>&Obj)
        :capacity(Obj.capacity), used(Obj.used)
    {

        vect.reset(new T[Obj.used]);
         for(int i = 0; i < used ; i++)
             vect[i] = Obj.vect[i];

    }
     template<class T>
     GTUVector<T>::~GTUVector( )
     {
         vect.reset( );
         
     }
     
    template<class T>
    GTUVector<T>::GTUVector(GTUVector<T>&&other)noexcept // Move constructor
        :capacity(0), used(0), vect(nullptr)
    {

        capacity = other.capacity;
        used = other.used;
        other.vect = nullptr;
        other.capacity = 0;
        other.used = 0;
    }
    template<class T>
    GTUVector<T>& GTUVector<T>::operator=(GTUVector<T>&& other) noexcept //Move Assignment operator
    {
        if(this != &other)
        {
            vect.reset( ); //delete data

            used = other.used;
            capacity = other.capacity;

            other.vect = nullptr;
            other.capacity = 0;
            other.used = 0;
        }
        return *this;
    }  
     
     
     template<class T>
     GTUVector<T>& GTUVector<T>::operator=(const GTUVector<T> &Obj)
     {
         if(used != Obj.used){
            vect.reset( );
            vect.reset(new T[Obj.used]);
         }
         capacity = Obj.capacity;
         used = Obj.used;
        
         for(int i = 0; i < used; i++)
             vect[i] = Obj.vect[i];
        
        
         return *this;

    }
    
    template<class T>
     bool GTUVector<T>::empty( ) const
    {
         if(used == 0) // Container is empty
             return true;
         else   // Container is not empty
             return false;
    
    }
    
    template<class T>
    int GTUVector<T>::size( ) const
    {
         int size_ = used;
         return size_;
    }
    
    template<class T>
    void GTUVector<T>::add(T element)
    {
        
        if(used == 0){
            vect[used] = element;
            used++;
        
        }
        else{
            
            shared_ptr<T[]> copy;
            copy.reset(new T[used + 1]);
            for(int i = 0; i < used ; i++)
                copy[i] = vect[i];
            
            copy[used] = element;
            
            vect.reset( ); //delete content
            used++; //increment size    
            vect.reset(new T[used]);
            
            for(int i = 0; i < used; i++)
                vect[i] = copy[i];
        
            copy.reset( ); // delete copy
        }
    }
    
    template<class T>
    void GTUVector<T>::erase(const T*iterator)
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
                copy[counter] = vect[j];
                counter++;
            }
        }
        vect.reset( );
        used--;
        vect.reset(new T[used]); 
        for(int i = 0; i < used; i++)
            vect[i] = copy[i];

        copy.reset( );

    }

    template<class T>
    void GTUVector<T>::clear( )
     {
        used = 0;
        capacity = 1;
        vect.reset( );
        vect.reset(new T[capacity]);
     
    }

     template<class T>
     T& GTUVector<T>::operator[](int index)
    {
        return vect[index];
        
    }
    
    template<class T>
    T* GTUVector<T>::begin( ) const //Return the addres of first element
    {
        auto reff = vect.get( );

        return reff;
    }
   
    template<class T>
    T* GTUVector<T>::end( ) const //Return the addres of last element
    {
        auto headreff = vect.get( );
        int last_index = used;
        auto endreff = headreff + used;

        return endreff;
    }
    
    template<class T>
     const T* GTUVector<T>::cbegin( ) const //Return the cons addres of first element
     {

        auto reff = vect.get( );
        
        return reff;
     }
    
    template<class T> 
    const T* GTUVector<T>::cend( ) const //Return the addres of const last element
     {
        auto headreff = vect.get( );
        int last_index = used;
        auto endreff = headreff + last_index;
        
        return endreff;
     
     }

}