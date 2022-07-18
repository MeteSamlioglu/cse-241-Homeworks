#ifndef GTUARRAY_H
#define GTUARRAY_H
#include"Iterable.h"
using namespace std;


namespace SavitchIterable{
    template<class T>
    class GTUArray : public Iterable<T>
    
    {
        public:
        GTUArray( );
        GTUArray(int size);
        GTUArray(const GTUArray<T>&Obj);
        ~GTUArray( );
        GTUArray(GTUArray<T>&& other )noexcept; //Move constructor
        GTUArray& operator=(GTUArray<T>&& other)noexcept;//Move assignment operator.
        GTUArray<T>& operator=(const GTUArray<T>&Obj); //Assignment operator    
        
        bool empty( ) const override ;//Test whether container is empty
        int size( ) const override; //Return container size        
        void insert(T element ) ; //Add an element at the end position of array
                          
        void erase(const T* iterator) override; //Erase element pointed by the given iterator, and reduces the container size
        void clear( )override ; // Clear all the content in container
        T* begin( ) const override ; //Return iterator to beginning  
        T* end( ) const override ; //Return iterator to end
        T& operator[](int index); 
        const T* cbegin( ) const override ; //Return constant iterator to beginnig
        const T* cend( ) const override; //Return constant iterator to end
           
         
        private:
            shared_ptr<T[]> array;
            int capacity;
            int used = 0;
    };

}
#endif