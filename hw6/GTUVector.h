#ifndef GTUVECTOR_H
#define GTUVECTOR_H

#include"Iterable.h"
#include"Iterable.cpp"


namespace SavitchIterable{

    template<class T>
    class GTUVector : public Iterable<T>
    {
        public:
            GTUVector( );
            GTUVector(int size);
            GTUVector(const GTUVector<T>&Obj);
            ~GTUVector( );
            GTUVector(GTUVector<T>&& other )noexcept; //Move constructor
            GTUVector& operator=(GTUVector<T>&& other)noexcept;//Move assignment operator.
           
            bool empty( ) const override ;//Test whether container is empty
            int size( ) const override; //Return container size        
            void add(T element ) ; //Add an element at the end position of container
                          //Increment size

            void erase(const T* iterator) override; //Erase element pointed by the given iterator, and reduces the container size
            void clear( )override ; // Clear all the content in container
            T* begin( ) const override ; //Return iterator to beginning  
            T* end( ) const override ; //Return iterator to end
            T& operator[](int index); 
            const T* cbegin( ) const override ; //Return constant iterator to beginnig
            const T* cend( ) const override; //Return constant iterator to end
           
           GTUVector<T>& operator=(const GTUVector<T>&Obj); //Assignment operator  
            

        private:
            shared_ptr<T[]> vect;
            int capacity;
            int used = 0;

    };
}

#endif