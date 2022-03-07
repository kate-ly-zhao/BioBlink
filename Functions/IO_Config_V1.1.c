//Pinout Definitions--------SIO#-------PIN#--------------------------------
#define HAPTIC			    //1  	// 13, IO, IO; out. Formally HAPTIC_PWM. ACTIVE LOW
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




sub IO_Config()

    DIM temp 
    temp = GPIOSETFUNC(CURR_SET_PWM,DIGITAL_OUT,PWM)
    temp = GPIOCONFIGPWM(10000,100)                      //10kHz 1:100 resolution current set PWM
    //To set duty cycle -> change TX current: GPIOWRITE(CURR_SET_PWM, 0 to N) where N = 1 to 100 or 10000?  

    temp = GPIOSETFUNC(HAPTIC,DIGITAL_OUT,HIGH)          //HAPTICS will just be on/off not PWM. Active low.
    temp = GPIOSETFUNC(BUCK_ON,DIGITAL_OUT,HIGH)         
    temp = GPIOSETFUNC(TX_EN,DIGITAL_OUT,LOW) 
    temp = GPIOSETFUNC(RX_EN,DIGITAL_OUT,LOW)
    temp = GPIOSETFUNC(MOD,DIGITAL_OUT,LOW)              //unused with FE v2.0, set as low digital output.
    temp = GPIOSETFUNC(BLK_THRES_PWM,DIGITAL_OUT,LOW)    //unused with FE v2.0, set as low digital output.

    temp = GPIOSETFUNC(BLINK,DIGITAL_IN,0)               //unused with FE v2.0, set as digital input.
    temp = GPIOSETFUNC(PBSTAT,DIGITAL_IN,0)
    temp = GPIOSETFUNC(CHRG,DIGITAL_IN,0)
    temp = GPIOSETFUNC(SLOPE_P,DIGITAL_IN,0)           //Add deep sleep wake?
    temp = GPIOSETFUNC(SLOPE_N,DIGITAL_IN,0)           
    
    temp = GPIOSETFUNCEX(ENV_ADC,ANALOG_IN,"\15\0A\0A")          
    temp = GPIOSETFUNCEX(BAT_ADC,ANALOG_IN,"\14\0C\28")

    PRINT "\n IO Configured"
    
    // Set ADC scaling so max analog voltage * Scaling < 0.6V (ADC reference)
    //0x16 1/6 scaling
    //0x15 1/5 scaling
    //0x14 1/4 scaling
    //0x13 1/3 scaling
    //0x12 1/2 scaling
    //0x11 1/1 scaling (Unity)
    //0x21 2/1 scaling
    //0x41 4/1 scaling
    
    //0x08 8-bit ADC resolution
    //0x0A 10-bit ADC resolution
    //0x0C 12-bit ADC resolution

    //0x03 3 microseconds Acquisition time
    //0x05 5 microseconds
    //0x0A 10 microseconds
    //0x0F 15 microseconds
    //0x14 20 microseconds
    //0x28 40 microseconds
    
endsub 