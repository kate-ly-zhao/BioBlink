//Pinout Definitions--------SIO#-------PIN#--------------------------------
#define HAPTIC			    //1  	// 13, IO, out. Formally HAPTIC_PWM. ACTIVE LOW
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

#define DIGITAL_IN       1
#define DIGITAL_OUT      2
#define ANALOG_IN        3
#define LOW              0
#define HIGH             1
#define PWM              2
#define FREQ             3



sub OPTICAL_TX(BYVAL CURRENT_SET_DC AS INTEGER)  //Starts optical TX. Input 0 to turn off. 

    dim TX_LIMIT
    TX_LIMIT = 50  //HARDCODE TO MAXIMUM EXPERIMENTAL PWM DUTYCYCLE THAT GIVES MAX ALLOWED CURRENT

    if (CURRENT_SET_DC <= TX_LIMIT)&(CURRENT_SET_DC != 0) then

        GPIOWRITE(CURR_SET_PWM,CURRENT_SET_DC)
        GPIOWRITE(TX_EN,HIGH)  //enable FE TX opamps + oscilator
        PRINT "\n TX ENABLED, DC SET: "; CURRENT_SET_DC

    elseif (CURRENT_SET_DC > TX_LIMIT)&(CURRENT_SET_DC != 0) then

        GPIOWRITE(CURR_SET_PWM,TX_LIMIT)
        GPIOWRITE(TX_EN,HIGH)  //enable FE TX opamps + oscilator
        PRINT "\n TX_LIMIT DC EXCEDED, set to max: "; TX_LIMIT

    elseif CURRENT_SET_DC == 0 then         //turn TX off

        GPIOWRITE(CURR_SET_PWM,0)
        GPIOWRITE(TX_EN,LOW)  //disable FE TX opamps + oscilator
        PRINT "\n TX SHUTDOWN"

    endif

endsub