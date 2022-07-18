import packDayofYearSet.DayofYearSet;
public class DayofYearSetMain
{
    
    public static void main(String args[])
    {
        DayofYearSet s1 = new DayofYearSet();
        DayofYearSet s2 = new DayofYearSet();
        System.out.printf("Set s1\n\n");
        s1.add(10,12);
        s1.add(6,1);
        s1.add(6,2);
        s1.add(4,5);
        s1.print( );
        System.out.printf("\nCurrent DayofYear objects count is %d\n",s2.NumberofObjects( ));
        System.out.printf("size : %d\n",s1.size( ));
        System.out.printf("\nSet s2\n");
        s2.add(6,1);
        s2.add(6,2);
        s2.add(10,11);
        s2.add(4,6);
        s2.add(9, 10);
        s2.print( );
        
        System.out.printf("\nsize : %d",s2.size( ));
        System.out.printf("\nCurrent DayofYear objects count is %d\n",s2.NumberofObjects( ));
        System.out.printf("--------------\n");
        System.out.printf("Intersection Set\n\n");
        DayofYearSet s3 = new DayofYearSet();
        s3 = s1.intersection(s2);
        s3.print( );
        System.out.printf("\nsize : %d",s3.size( ));
        System.out.printf("\nCurrent DayofYear objects count is %d\n",s2.NumberofObjects( ));
        System.out.printf("--------------\n");
        System.out.printf("Union Set\n\n");
        s3.reset( ); //We'll assign another DayofYearSet object to s3, Therefore we need to remove its old DayofYear objects count
        s3 = s1.union(s2);
        s3.print( );
        System.out.printf("\nsize : %d",s3.size( ));
        System.out.printf("\nCurrent DayofYear objects count is %d\n",s2.NumberofObjects( ));
        
        System.out.printf("--------------\n");
        System.out.printf("Difference Set A - B \n");
        s3.reset( );
        s3 = s1.difference(s2);
        s3.print( );
        System.out.printf("\nsize : %d",s3.size( ));
        System.out.printf("\nCurrent DayofYear objects count is %d\n",s2.NumberofObjects( ));
        System.out.printf("--------------\n");
        //System.out.printf("Complement set of s1 \n"); // This set have too many elements, printing all these elements make output mess
        //s3.reset( );
        //s3 = s1.complement( );
        //s3.print( );
        //System.out.printf("%d",s3.size( ));
        //System.out.printf("\nsize : %d",s3.size( ));
        //System.out.printf("\nCurrent DayofYear objects count is %d\n",s2.NumberofObjects( ));
       
        System.out.printf("Write DayofYearSet to file");
        DayofYearSet s4 = new DayofYearSet( );
        s4.add(6,5);
        s4.add(7,2);
        s4.add(10,4);
        s4.write_to_file( );
        System.out.printf("\n--------------\n");
        System.out.printf("Remove function check\nSet s4 elements\n");
        s4.print( );
        System.out.printf("\nsize : %d",s4.size( ));
        System.out.printf("\nCurrent DayofYear objects count is %d\n",s4.NumberofObjects( ));
        System.out.printf("\nRemove function is invoked for s4.remove(0) and s4.remove(1)\n");
        s4.remove(0);
        s4.remove(1);
        System.out.printf("\nNew Set s4 elements\n");
        s4.print( );
        System.out.printf("\nnew size : %d",s4.size( ));
        System.out.printf("\nCurrent DayofYear objects count is %d\n",s4.NumberofObjects( )); 
        System.out.printf("\n--------------");
       
        System.out.printf("\nDe Morgan Rule check !(s1 + s2) == !s1 ^ !s2 \n");
        DayofYearSet firstExpression = new DayofYearSet( );
        DayofYearSet secondExpression = new DayofYearSet( );
        s1.reset();
        s2.reset();
        firstExpression = s1.union(s2);
        firstExpression.reset( );
        firstExpression = firstExpression.complement( );
        
        s1 = s1.complement( );
        s2 = s2.complement( );
        secondExpression = s1.intersection(s2);
        
        if(firstExpression.equals(secondExpression))
        {
            System.out.printf("Logical De Morgan equation is correct !\n"); 
        }
        System.out.printf("--------------\n");
        System.out.printf("Invalid input check\nAdding the date of 15.day 14.month  to Set\n"); 
        s4.add(15,14);
        System.out.printf("\n%s\n",s4.toString( ));
        System.out.printf("--------------\n");
        
        if(s4.equals(s2))
            System.out.printf("Set s4 equal set s2\n"); 
        else
            System.out.printf("Set s4 is not equal set s2\n"); 

    }
    // We checked every function at least two times, all of them works as expected!



}