#include"Iterable.h"
using namespace std;


namespace SavitchIterable{

    template<class T>
    Iterable<T>::Iterable( )
        :capacity(50), used(0)
    {
        //deliberatelty empty
    }
    template<class T>
    Iterable<T>::Iterable(int size_)
        :capacity(size_), used(0)
    {
        //deliberatelty empty
    
    }
  
    template<class T>
    int Iterable<T>::getCapacity( ) const{
        return capacity;
    }
    template<class T>
    int Iterable<T>::getUsed( ) const{
        return used;
    }

    template<class T>
    void Iterable<T>::modifyUsed(int value)
    {
        used+=value;
    }


}