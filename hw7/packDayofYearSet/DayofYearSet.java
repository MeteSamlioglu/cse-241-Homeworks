package packDayofYearSet;
import java.io.FileWriter;
import java.io.IOException; 
import java.util.ArrayList;

public class DayofYearSet
{
 
    public static class DayofYear
    {
        private int month;
        private int day;
        DayofYear( )
        {
            month = 0;
            day = 0;
        }
        
        /**
	    * 
	    * @param int variable to set private int Day of DayofYear inner class
	    */
        public void setDay(int _day)
        {
            day = _day;
        }
        /**
	    * 
	    * @param int variable to set private int month of DayofYear inner class
	    */
        public void setMonth(int _month)
        {
            month = _month;
        }
        /**
	    * 
	    * @return Return private integer month variable
	    */
        public int getMonth( ) 
        {
            return month;
        }
        /**
	    * 
	    * @return Return private integer day variable
	    */
        public int getDay( ) 
        {
            return day;
        }
        
        public final String toString( )
        {
            return String.format("%d.Day %d.Month",getDay( ), getMonth( )); 
        }
    }
    
    private DayofYear[] Set;
    private int capacity;
    private static int totalObjects = 0;
    
    
    public DayofYearSet( )
    {
        capacity = 0;
    }
    
    public DayofYearSet(int size)
    {
        capacity = size;
        Set = new DayofYear[capacity];
        for(int i = 0; i < capacity; i++)
            Set[i] = new DayofYear( );
        
    
    }
    
    public DayofYearSet(int day, int month)
    {
        capacity = 0;
        add(day, month);

    }
    
    /**
	* 
	* @param Constructor takes ArrayList to create another DayofYearSet obj
	*/
    public DayofYearSet(ArrayList<DayofYear> Obj)
    {
        
        capacity = Obj.size( );
        Set = new DayofYear[capacity];
        
        for(int i = 0; i < size(); i++)
            Set[i] = new DayofYear( );

        for(int i = 0; i < size( ); i++)
        {
           
            Set[i].setDay(Obj.get(i).getDay( ) );
            Set[i].setMonth(Obj.get(i).getMonth( ));
        }
    
    }
    /**
	* 
	* @param Constructor takes another DayofYearSet to create a copy DayofYearSet
	*/
    public DayofYearSet(DayofYearSet other) //Copy consturctor
    {
        capacity = other.capacity;
        Set = new DayofYear[capacity];
        for(int i = 0; i < size( ); i++)
            Set[i] = new DayofYear( );

        for(int i = 0; i < size( ); i++)
        {
            Set[i].setDay(other.Set[i].getDay());
            Set[i].setMonth(other.Set[i].getMonth());
        }
    }
    
    
    @Override
    public boolean equals(Object obj) {
            boolean sizeCheck = false, dataControl = false, checkEnd = true;
            // Check if the addreses are the same or not
            if (obj == this) {
                return true;
            }
    
            // Check if object is an instance of Complex 
            if (!(obj instanceof DayofYearSet)) {
                return false;
            }
            
            // Check if their size are the same or not
            DayofYearSet _obj = (DayofYearSet) obj;
            if( _obj.size( ) != size( ))
                return false;
            
            //In the last part we'll compare the elements of DayofYear[] arrays
          
            for(int i = 0; i < size( ); i++)
            {
                dataControl = false;
                for(int j = 0; j < _obj.size( ); j++)
                {
                    if ( (Set[i].getDay( ) == _obj.Set[j].getDay( ) ) && ( Set[i].getMonth( ) == _obj.Set[j].getMonth( ) )){
                        dataControl = true;
                        break;
                    }
                }
                if(dataControl == false)
                {
                    checkEnd = false;
                    break;
                }
            }

            return checkEnd;
    }
    
    public void reset( ) // Reset static variables of Object
    {
        RemoveObject(size( ));
    }

    public int size( ) //Returns size
    {
        return capacity;
    }
    

    public final String toString( )
    {
        return String.format("This set have %d date elements",size( )); 
    }
    
    public final void print( )
    {
        for(int i = 0; i < size( ); i++)
        {
            System.out.println(Set[i]);
        }
    }
    
    /**
	* 
	* @return Return True if given date is valid, False if given date is exist in the set or not valid
	*/
    
    public boolean isValidInput(int _day, int _month)
    {
        boolean isValidMonth = false, isValidDay = false, isDateExist = false;
        int counter = 0;
        int months[] = {31,28,31,30,31,30,31,31,30,31,30,31}; 
        
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
                System.out.println("Error: Your input date is not a valid date ! ");
            }
        }
        
        else{
            System.out.println("Error: Your input date is not a valid date !");
            isValidMonth = false;
        }
        
        if(size() > 0){
            for(int i = 0 ; i <size(); i++){
                if(Set[i].getDay()==_day && Set[i].getMonth()==_month){
                    isDateExist = true; /* The given date is exist in our Set */
                    System.out.println("Error: Date is exist in DayofYearSet! ");
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
    
    /**
	* 
	* @param Takes integer day and month value to add date in DayofYear array
	*/
    public void add(int _day, int _month)
    {

        int initial_capacity = size();
        if(isValidInput(_day, _month) == true){
            
            if(initial_capacity==0){ /* For uninitialized array */
                capacity++;
                Set = new DayofYear[capacity];
                Set[0] = new DayofYear( );
                Set[0].setDay(_day);
                Set[0].setMonth(_month);        
            }
            else if(initial_capacity > 0 ){
                DayofYearSet copy = new DayofYearSet(this);    
                initial_capacity = size();
                capacity = initial_capacity + 1;
                Set = new DayofYear[capacity];
                for(int i = 0; i< capacity; i++)
                    Set[i] = new DayofYear( );

                for(int i = 0; i < initial_capacity  ; i++)
                {
                    Set[i].setDay(copy.Set[i].getDay());
                    Set[i].setMonth(copy.Set[i].getMonth());
                }
                    Set[initial_capacity].setDay(_day);
                    Set[initial_capacity].setMonth(_month);
            }
            
            AddNewObject(1);
        }
    }
    /**
	* 
	* @param Function Takes integer index parameter to remove a date from DayofYear array 
	*/
    
    public void remove(int index)
    {
        int initial_capacity = size(), counter = 0;
        
        if(index>=capacity)
            System.out.println("Error! : Given index value is greater than Set's capacity ");
        else{
            DayofYearSet copy = new DayofYearSet(this);
            capacity = initial_capacity - 1;
            Set = new DayofYear[capacity];
            for(int i = 0; i < capacity; i++)
                Set[i] = new DayofYear( );

            for(int i = 0 ; i < initial_capacity ; i++)
            {
                if(index != i){
                    Set[counter].setDay(copy.Set[i].getDay());
                    Set[counter].setMonth(copy.Set[i].getMonth());
                    counter++;
                }
            }
            RemoveObject(1);
        }
    
    }
     
    /**
	* 
	* @return Returns union DayofYearSet 
	*/
    
    public DayofYearSet union(final DayofYearSet Obj){
        
        DayofYearSet union;
        boolean check = false;
        int size_of_union = 0, array_index = 0;
        /* First we need to determine size of union set */
        
        for(int i = 0; i < size( ); i++) 
            size_of_union++;
        
        for(int i = 0; i < Obj.size( ); i++){
            check = false;
            for(int j = 0; j <size( ); j++){
                if(( Set[j].getDay() == Obj.Set[i].getDay() ) && ( Set[j].getMonth() == Obj.Set[i].getMonth() )){
                    check = true;
                    break;
                }
            }
             if(check == false)
                size_of_union++;
        }
        
        union = new DayofYearSet(size_of_union); /* Set the array size accordingly */
        
        for(int i = 0 ; i < size(); i++){
            union.Set[i].setDay(Set[i].getDay( ));
            union.Set[i].setMonth(Set[i].getMonth( )); 
        }
        
        array_index = size();
        for(int i = 0; i < Obj.size(); i++){
            for(int j = 0; j <size(); j++){
                check = false;
                if(( Set[j].getDay( ) == Obj.Set[i].getDay( ) ) && ( Set[j].getMonth( ) == Obj.Set[i].getMonth( ) )){
                    check = true;
                    break;
                }
            }
            if(check == false){
                union.Set[array_index].setDay(Obj.Set[i].getDay());
                union.Set[array_index].setMonth(Obj.Set[i].getMonth()); 
                array_index++;
            }
        }
        
        AddNewObject(union.size( ));
        return union;

    }
    /**
	* 
	* @return  Returns difference DayofYearSet of parameter Obj and calling Object
	*/
    
    public DayofYearSet difference(final DayofYearSet Obj)
    {
        boolean check = false;
        ArrayList<DayofYear> diffSet = new ArrayList<DayofYear>();
        

        for(int i = 0; i < size(); i++){
            check = false ;
            for(int j = 0 ; j < Obj.size(); j++){
                if( (Set[i].getDay()==Obj.Set[j].getDay() ) && (Set[i].getMonth() == Obj.Set[j].getMonth() ) ){
                    check = true;
                    break;
                }
            }
            if(check == false){
                DayofYear diffElement = new DayofYear( );
                diffElement.setDay(Set[i].getDay());
                diffElement.setMonth(Set[i].getMonth());
                diffSet.add(diffElement);
            }
        }

        DayofYearSet difference = new DayofYearSet(diffSet);
        AddNewObject(difference.size( ));
        return difference;
    }
    
    /**
	* 
	* @return  Returns intersection DayofYearSet of parameter Obj and calling Object
	*/
    
    public DayofYearSet intersection(final DayofYearSet Obj)
    {
        ArrayList<DayofYear>intersectSet = new ArrayList<DayofYear>();
       
        boolean check = false;
        for(int i = 0 ; i < size(); i++){
            check = false;
            for(int j = 0 ; j < Obj.size() ; j++ ){
                
                if( (Set[i].getDay() == Obj.Set[j].getDay() ) && (Set[i].getMonth()== Obj.Set[j].getMonth()) ){
                    check = true;
                    
                    break;
                }
            }
            if(check == true){
               
                DayofYear intersectElement = new DayofYear( );
                intersectElement.setDay(Set[i].getDay());
                intersectElement.setMonth(Set[i].getMonth());
                intersectSet.add(intersectElement);
            }
        }
        

        DayofYearSet intersection_set = new DayofYearSet(intersectSet);
        
        AddNewObject(intersection_set.size( ));        

        return intersection_set;
    
    }
     /**
	* 
	* @return  Returns complement DayofYearSet of Object
	*/

    public DayofYearSet complement( )
    {
        boolean check = false;
        ArrayList<DayofYear>complementSet = new ArrayList<DayofYear>();
        int months[] = {31,28,31,30,31,30,31,31,30,31,30,31}; 
        int counter = 0;

        for(int i = 1 ; i <= 12 ; i++){
            for(int k = 1 ; k <= months[ i - 1] ; k++){
                DayofYear complementElement = new DayofYear( );
                complementElement.setDay(k);
                complementElement.setMonth(i);
                complementSet.add(complementElement);
            }
        }
        
        for(var i = complementSet.get(counter); counter < complementSet.size( ); counter++){
            for(int j = 0 ; j < size(); j++){
                if( ( Set[j].getMonth() == i.getMonth()) && ( Set[j].getDay() == i.getDay() )){
                    complementSet.remove(i);
                    counter--;
                    break;
                }
            }
            i = complementSet.get(counter);
        }        
    
        DayofYearSet complement = new DayofYearSet(complementSet);
        AddNewObject(complement.size( ));     
        
        return complement;
    }
    
    
    public void write_to_file( ) // Writes set to file
    {
        try {
            FileWriter writer = new FileWriter("SetDayofYear.txt");
            
            for(int i = 0; i < size( ); i++)
                writer.write(Set[i].getMonth( )+".Month " + Set[i].getDay( )+".Day\n");
            
            writer.close();
            System.out.println("\nSet is written to SetDayofYear.txt");
          } catch (IOException obj) {
            System.out.println("Error!");
            obj.printStackTrace();
          }

    }
    /**
	* 
	* @return Returns the total number of DayOfYear objects alive in all the sets
	*/
  
    public static int NumberofObjects( )
    {
        return totalObjects;
    
    }
    /**
	* 
	* @param Adds a integer value to private static int totalObjects variable
	*/
  
    public static void AddNewObject(int number)
    {
        totalObjects+=number;// Add new objects to total number of active DayofYear object

    }
    /**
	* 
	* @param Removes a integer value to private static int totalObjects variable
	*/

    public static void RemoveObject(int number){ // Remove objects from active DayofYear objects 
        
        totalObjects-= number;
    
    }
  

}