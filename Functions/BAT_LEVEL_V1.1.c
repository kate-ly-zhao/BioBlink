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



function BAT_LEVEL()   //Returns battery voltage in mV

    dim RAW   //raw 12bit ADC reading
    dim x     //Counter variable

    DO
        x = x + 1 
        RAW = GPIOREAD(BAT_ADC) + RAW   // Accumulate 15 12bit samples

    DOWHILE x < 15

    RAW = RAW/15  //Average the samples

    // 1/4 ADC scaling, 0.6V reference -> RAW = Vin * (Scaling/Reference) * 2^N
    dim V_BAT 
    V_BAT = (RAW) / (4096*(0.25/0.6)) * 1000

    PRINT "\n V_BAT=";V_BAT
    
endfunc V_BAT