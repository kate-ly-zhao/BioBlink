//Pinout Definitions--------SIO#-------PIN#--------------------------------
#define HAPTIC_PWM			//1  	// 13, IO, PWM; out 
#define BUCK_ON				//40	// 17, IO; out - LED 1
#define CURR_SET_PWM		//11	// 19, IO, PWM; out 
#define TX_EN				//25	// 23, IO; out - LED 2
#define MOD				    //14	// 27, IO, FREQ; out 
#define RX_EN				//17	// 28, IO; out - LED 3
#define BLINK				//12	// 29, IO, interrupt; in - Button 1
#define ENV_ADC				//3 	// 10, ADC; in
#define BAT_ADC				//31	// 12, ADC; in
#define PBSTAT				//28	// 36, IO; in
#define CHRG				//30	// 38, IO; in
#define BLK_THRES_PWM		//29	// 39, IO, PWM; out
#define SLOPE_P             //27    // 40, IO, in
#define SLOPE_N             //26    // 45, IO, in
#define DEBUG_LED           //7     // 15, IO, output, high drive, also UART_CTS.

#define DIGITAL_IN       1
#define DIGITAL_OUT      2
#define ANALOG_IN        3
#define LOW              0
#define HIGH             1
#define PWM              2
#define FREQ             3





dim SAMPLE_RATE : SAMPLE_RATE = 500   //ADC sample rate in Hz



sub HP_MODE_ROUTINE(BYVAL CURRENT_SET_DC AS INTEGER)  
	CANCEL_ALL_TIMERS()
//	TimerStart (3,Battery_Check_Interval,1)
	OUTPUT_STATE(MODE_HP)
	print "\n HP_MODE state start \n"
    OPTICAL_TX(CURRENT_SET_DC) //start TX with desired current
	print "\n OPTICAL_TX  FINISH \n"

    dim START_TIME   //current tick value for delay (ms)
    dim END_TIME     //final tick value for delay   (ms)
    dim ADC_RAW      //latest raw adc sample
    dim PREV_BLINK : PREV_BLINK = 0   //tick time of the previously detected blink (ms), first blink is 0.
    dim CURR_BLINK : CURR_BLINK = 0   //tick time of the current blink (ms), if there is one.
    

  //  do  //main loop
		//print "\n adc sample loop start \n"
        ADC_RAW = GPIOREAD(ENV_ADC)  //Get one sample
        //convert current ADC_RAW sample to mV and add to array or circular buffer?
        //BLE transmit??
        START_TIME = GETTICKCOUNT()  //Get initial tick in ms
        END_TIME = START_TIME + 2//((1/ SAMPLE_RATE)*1000)   //Calculate end time based on the sample rate (ms)
       // print "\n start time: "; START_TIME
		//print "\n end time: "; END_TIME
        TimerStart(4,END_TIME,1)

        WHILE GETTICKCOUNT() < END_TIME           
			//print "\n \n delay loop start \n"
            if PREV_BLINK == 0 then      //Only runs on first detected blink.
				
                if GPIOREAD(SLOPE_P) == 0 then     //Sets first blink to previous if SLOPE_P comparator high
                    PREV_BLINK = GETTICKCOUNT()
                    PRINT "\n Init Blink time: ";PREV_BLINK;"ms \n"
                endif

            else                         //All consecutive blinks
				if GETTICKCOUNT() - PREV_BLINK >= TARGET_BLINK_INTERVAL then // if interval time exceeded, use haptics 
					PRINT "\n Interval time exceeed, haptics used \n"
					PREV_BLINK = GETTICKCOUNT()
				ENDIF
                if (GPIOREAD(SLOPE_P) == 0)&((GETTICKCOUNT()- PREV_BLINK) > MIN_TIME_BTWN_BLINKS) then  //if SLOPE_P high AND the time since the previous blink is greater than 200ms
                    CURR_BLINK = GETTICKCOUNT()
                    //Store current blink time data?
                    //BLE transmit blink time data?

                   // PRINT "\n PREV_BLINK @ ";PREV_BLINK;"ms \n"
                    PRINT "\n CURR_BLINK @ ";CURR_BLINK;"ms \n"
                    PREV_BLINK = CURR_BLINK
				else
					
                endif

            endif


        ENDWHILE 

 //   dowhile GPIOREAD(PBSTAT) == 1    //run loop until switch is pressed once
//	OPTICAL_TX(0)
//	print "\n exiting HP Mode \n"

endsub
