
#include"GTUSet.h"



namespace SavitchIterable{

    template<class T>
    GTUSet<T>::GTUSet( )
    :Iterable<T>(0), capacity(1)
    {
        Set.reset(new T[capacity]);
    }
     template<class T>
    GTUSet<T>::GTUSet(int size_)
    : Iterable<T>(size_), capacity(size_)
    {
        Set.reset(new T[capacity]);
    
    }
    template<class T>
    GTUSet<T>::GTUSet(const GTUSet<T>&Obj)
        :capacity(Obj.capacity), used(Obj.used)
    {

        Set.reset(new T[Obj.used]);
         for(int i = 0; i < used ; i++)
             Set[i] = Obj.Set[i];

    }
    
    template<class T>
    GTUSet<T>::GTUSet(GTUSet<T>&&other) noexcept // Move constructor
        :capacity(0), used(0), Set(nullptr)
    {

        capacity = other.capacity;
        used = other.used;
        other.set = nullptr;
        other.capacity = 0;
        other.used = 0;
    }
    template<class T>
    GTUSet<T>& GTUSet<T>::operator=(GTUSet<T>&& other) noexcept //Move Assignment operator
    {
        if(this != &other)
        {
            Set.reset( ); //delete data

            used = other.used;
            capacity = other.capacity;

            other.Set = nullptr;
            other.capacity = 0;
            other.used = 0;
        }
        return *this;
    }  
    
    template<class T>
    GTUSet<T>::~GTUSet( )
     {
         Set.reset( );
         
     }

     template<class T>
     GTUSet<T>& GTUSet<T>::operator=(const GTUSet<T> &Obj)
     {
         if(used != Obj.used){
            Set.reset( );
            Set.reset(new T[Obj.used]);
         }
         capacity = Obj.capacity;
         used = Obj.used;
        
         for(int i = 0; i < used; i++)
             Set[i] = Obj.Set[i];
        
        
         return *this;

    }
    template<class T>
    bool GTUSet<T>::empty( ) const
    {
        if(used == 0)
            return true;
        else
            return false;
    }
    
    template<class T>
    int GTUSet<T>::size( ) const
    {
         int size_ = used;
         return size_;
    }
    
    template<class T>
    void GTUSet<T>::add(T element)
    {
        
        if(used == 0){
            Set[used] = element;
            used++;
        
        }
        else{   
            shared_ptr<T[]> copy;
            copy.reset(new T[used + 1]);
            for(int i = 0; i < used ; i++)
                copy[i] = Set[i];
            
            copy[used] = element;
            
            Set.reset( ); //delete content
            used++; //increment size    
            Set.reset(new T[used]);
            
            for(int i = 0; i < used; i++)
                Set[i] = copy[i];
        
            copy.reset( ); // delete copy
        }
        sort(begin( ), end( ));
    }
    
    template<class T>
    void GTUSet<T>::erase(const T*iterator)
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
                copy[counter] = Set[j];
                counter++;
            }
        }
        Set.reset( );
        used--;
        Set.reset(new T[used]); 
        for(int i = 0; i < used; i++)
            Set[i] = copy[i];

        copy.reset( );
        sort(begin( ), end( ));
    }
    template<class T>
    void GTUSet<T>::clear( )
     {
        used = 0;
        capacity = 1;
        Set.reset( );
        Set.reset(new T[capacity]);
    }
    template<class T>
     T& GTUSet<T>::operator[](int index)
    {
        return Set[index];
        
    }
    template<class T>
    T* GTUSet<T>::begin( ) const //Return the addres of first element
    {
        auto reff = Set.get( );

        return reff;
    }
    
    template<class T>
    T* GTUSet<T>::end( ) const //Return the addres of last element
    {
        auto headreff = Set.get( );
        int last_index = used;
        auto endreff = headreff + last_index;

        return endreff;
    }
     template<class T>
     const T* GTUSet<T>::cbegin( ) const //Return the cons addres of first element
     {

        auto reff = Set.get( );
        
        return reff;
     }
    
    template<class T> 
    const T* GTUSet<T>::cend( ) const //Return the addres of const last element
    {
        auto headreff = Set.get( );
        int last_index = used;
        auto endreff = headreff + last_index;
        
        return endreff;
     
    }
    template<class T> 
    void GTUSet<T>::intersect(T* first_begin, T* first_end, T *second_begin, T*second_end)
    {
        
        bool check = false;
        clear( );
        for(auto i = first_begin ; i < first_end; i++){
            check = false;
            for(auto j = second_begin ; j < second_end ; j++){
                if( ( *i ) == ( *j ) ){
                    check = true;
                    break;
                }
            }
            if(check == true)
                add(*i);
            
        }
        sort(begin( ), end( ));
    
    }
    template<class T> 
    void GTUSet<T>::union_set(T* first_begin, T* first_end, T *second_begin, T*second_end)
    {   
        clear( );
        GTUSet<T> Setintersect;
        bool check = false;
        Setintersect.intersect(first_begin, first_end, second_begin, second_end);

        for(auto i : Setintersect)
            add(i);

        for(auto i = first_begin; i < first_end; i++)
        {
            check = false;
            for(auto j = Setintersect.begin( ); j < Setintersect.end( ); j++)
                if( ( *i ) == ( *j ) ){
                    check = true;
                    break;
                }
            if(check == false)
                add(*i);
        
        }
        for(auto i = second_begin; i < second_end; i++)
        {
            check = false;
            for(auto j = Setintersect.begin( ); j < Setintersect.end( ); j++)
                if( ( *i ) == ( *j ) ){
                    check = true;
                    break;
                }
            if(check == false)
                add(*i);
        }

        sort(begin( ), end( ));
    }

    template<class T>
    T* GTUSet<T>::find(T element) const
    {
        int counter = 0;
        for(auto i = begin( ); i < end( ); i++)
        {
            if( ( *i ) == element )
                break;
            

            counter++;
        }
        auto reff = begin( ) + counter;

        return reff;
    }


}
