#ifndef GTUSET_H
#define GTUSET_H
#include"Iterable.h"
using namespace std;

namespace SavitchIterable{

    template<class T>
    class GTUSet : public Iterable<T>
    {
        public:
            GTUSet( );
            GTUSet(int size_);
            GTUSet(const GTUSet<T>&Obj);
            GTUSet(GTUSet<T>&& other )noexcept; //Move constructor
            GTUSet& operator=(GTUSet<T>&& other)noexcept;//Move assignment operator.
            
            ~GTUSet( );
            bool empty( ) const override ;//Test whether container is empty
            int size( ) const override; //Return container size        
            void add(T element ) ; //Add an element at the end position of container
                          //Increment size

            void erase(const T* iterator) override; //Erase element pointed by the given iterator, and reduces the container size
            void clear( )override ; // Clear all the content in container
            T* begin( ) const override ; //Return iterator to beginning  
            T* end( ) const override ; //Return iterator to end
            T* find(T element) const; // Find the addres of element and return 
            T& operator[](int index); 
            
            const T* cbegin( ) const override ; //Return constant iterator to beginnig
            const T* cend( ) const override; //Return constant iterator to end
            void intersect(T* first_begin,T* first_end, T *second_begin, T*second_end); //Making an intersection
            void union_set(T* first_begin, T* first_end, T *second_begin, T*second_end);
            
            GTUSet<T>& operator=(const GTUSet<T>&Obj); //Assignment operator  
            

        private:
            shared_ptr<T[]> Set;
            int capacity;
            int used = 0;

    };
}

#endif