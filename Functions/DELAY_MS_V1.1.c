

sub DELAY_MS(BYVAL DELAY_TIME AS INTEGER)   //delay N milliseconds.

    dim START_TIME 
    START_TIME = GETTICKCOUNT()  //Get initial tick in ms
    dim END_TIME 
    END_TIME = START_TIME + DELAY_TIME      //Add delay to current tick

    WHILE GETTICKCOUNT() < END_TIME            //Waste power until END_TIME reached

    ENDWHILE 

endsub