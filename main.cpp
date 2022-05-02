// #include <iostream>
#include "mbed.h"
#include "MAX31865.h"
#include <cstdio>

//Serial pc(SERIAL_TX, SERIAL_RX)
MAX31865_RTD rtd0(MAX31865_RTD::RTD_PT100, D11, D12, D13, A1); //miso = master input slave output (SDI on nucleo), 
//RTD parameters: (ptd_type type,PinName mosi, PinName miso, PinName sclk, PinName nss); nss is chip select, negative logic
// main() runs in its own thread in the OS
MAX31865_RTD rtd1(MAX31865_RTD::RTD_PT100, D11, D12, D13, A0); //miso = master input slave output (SDI on nucleo), 
MAX31865_RTD rtd2(MAX31865_RTD::RTD_PT100, D11, D12, D13, D8); //miso = master input slave output (SDI on nucleo),
MAX31865_RTD rtd3(MAX31865_RTD::RTD_PT100, D11, D12, D13, D9); //miso = master input slave output (SDI on nucleo),
MAX31865_RTD rtd4(MAX31865_RTD::RTD_PT100, D11, D12, D13, A3); //miso = master input slave output (SDI on nucleo),
MAX31865_RTD rtd5(MAX31865_RTD::RTD_PT100, D11, D12, D13, D6); //miso = master input slave output (SDI on nucleo),
MAX31865_RTD rtd6(MAX31865_RTD::RTD_PT100, D11, D12, D13, A6); //miso = master input slave output (SDI on nucleo),
MAX31865_RTD rtd7(MAX31865_RTD::RTD_PT100, D11, D12, D13, D3); //miso = master input slave output (SDI on nucleo),

int main()
{
    //when configuring RTDs to test, make sure that ALL RTDs are configured! If not, the default setting of the chip select pins is sitting at 0,
    //which is normally the chip enable signal. When the RTD is configured, the pin idles at high and prevents unwanted data being sent by
    //chips over the SPI bus, as all chips are tied to the same bus. Otherwise, the bus is filled with junk.
    
    //configure( bool v_bias, bool conversion_mode, bool one_shot, bool three_wire, uint8_t fault_cycle, bool fault_clear,
                            //   bool filter_50hz, uint16_t low_threshold, uint16_t high_threshold )

    rtd0.configure( true, true, false, false, MAX31865_FAULT_DETECTION_NONE,
                   true, true, 0x0000, 0x7fff );
    rtd1.configure( true, true, false, false, MAX31865_FAULT_DETECTION_NONE,
                   true, true, 0x0000, 0x7fff );
    //pads for rtd2 ADC are presently fried               
    // rtd2.configure( true, true, false, false, MAX31865_FAULT_DETECTION_NONE,
    //                true, true, 0x0000, 0x7fff );
    rtd3.configure( true, true, false, false, MAX31865_FAULT_DETECTION_NONE,
                   true, true, 0x0000, 0x7fff );
    rtd4.configure( true, true, false, false, MAX31865_FAULT_DETECTION_NONE,
                   true, true, 0x0000, 0x7fff );
   rtd5.configure( true, true, false, false, MAX31865_FAULT_DETECTION_NONE,
                   true, true, 0x0000, 0x7fff );
    rtd6.configure( true, true, false, false, MAX31865_FAULT_DETECTION_NONE,
                   true, true, 0x0000, 0x7fff );
    rtd7.configure( true, true, false, false, MAX31865_FAULT_DETECTION_NONE,
                   true, true, 0x0000, 0x7fff );

    float temp0_buffer = 50; // set buffers to maintain values in case 0 or 400 ohms is read (error)
    float temperature0 = 50; // default value of buffers is 50 C (estimated baseline temp in sunlight)
    float temp1_buffer = 50;
    float temperature1 = 50;
    float temp2_buffer = 50;
    float temperature2 = 50;
    float temp3_buffer = 50;
    float temperature3 = 50;
    float temp4_buffer = 50;
    float temperature4 = 50;
    float temp5_buffer = 50;
    float temperature5 = 50;
    float temp6_buffer = 50;
    float temperature6 = 50;
    float temp7_buffer = 50;
    float temperature7 = 50;
    bool boardEnable = 0;

    int epochtime = 0;
    char epoch_buffer[11];
    int index = 0;
    BufferedSerial pc(USBTX, USBRX,19200);

    //printf("Enter a 10-digit decimal value for epoch time. Press j to enter.");
    //don't uncomment the above line!
    // bool waiting = true;
    // do {
    //     char myChar;
    //     pc.read(&myChar, 1);
    //     pc.write(&myChar, 1);
    //     if (myChar == 'j') waiting = false;
    //     else {
    //         /* Put your character into epoch_buffer... assuming your data is sanitized, punk */
    //         epoch_buffer[index] = myChar;
    //         index++;
    //     }
    // } while (waiting);
    // epochtime = atoi(epoch_buffer);
   
    // set_time(epochtime);
    // osDelay(500);

    //  time_t seconds = time(NULL);
    //  printf("Time as seconds since January 1, 1970 = %d\n", seconds);
    //  printf("Time as a basic string = %s", ctime(&seconds));
    //  char buffer[32];
    //  strftime(buffer, 32, "%I:%M %p\n", localtime(&seconds));
    //  printf(" %s", buffer);
    // osDelay(500);
    
    // static BufferedSerial pc(USBTX, USBRX, 19200);
    // char epochtime[] = "1647099000";
    // int epoch;
    // pc.read(epochtime,11);
    // sscanf(epochtime, "%d", &epoch);
    // printf("%i\n\r",epoch);
    // set_time(epoch);

    //default CAN runs at 100 kHz = 100 000 (see can_api.c)
    CAN can(D10, D2);
    CANMessage rx_msg;

    //RTD0-3 are subarray 1
    //RTD4-7 are subarray 2
    
    while (1) {
        

        // time_t seconds = time(NULL);
        // printf("%s\n\r", ctime(&seconds));
        
        //if( rtd0.status( ) == 0 ) {

            rtd0.read_all( );
            temp0_buffer = (float)rtd0.temperature( );
            if(temp0_buffer > -10.0 && temp0_buffer < 150.0){
                temperature0 = temp0_buffer;
            }
            printf( " T0 = %f deg C \n\r",temperature0);
            float resistance0 = (float)rtd0.resistance();
            printf("Resistance0 is %f \n", resistance0);
 
        // } else
        // {
        //     printf( "RTD fault register: %d :\r\n",rtd0.status( ));
        //     if( rtd0.status( ) & MAX31865_FAULT_HIGH_THRESHOLD ) {
        //         printf( "RTD high threshold exceeded\r\n" );
        //     } else if( rtd0.status( ) & MAX31865_FAULT_LOW_THRESHOLD ) {
        //         printf( "RTD low threshold exceeded\r\n" );
        //     } else if( rtd0.status( ) & MAX31865_FAULT_REFIN ) {
        //         printf( "REFIN- > 0.85 x V_BIAS\r\n" );
        //     } else if( rtd0.status( ) & MAX31865_FAULT_REFIN_FORCE ) {
        //         printf( "REFIN- < 0.85 x V_BIAS, FORCE- open\r\n" );
        //     } else if( rtd0.status( ) & MAX31865_FAULT_RTDIN_FORCE ) {
        //         printf( "RTDIN- < 0.85 x V_BIAS, FORCE- open\r\n" );
        //     } else if( rtd0.status( ) & MAX31865_FAULT_VOLTAGE ) {
        //         printf( "Overvoltage/undervoltage fault\r\n");
        //     } else {
        //         printf( "Unknown fault; check connection\r\n" );
        //     }
        // }
        
        //rtd 1 good
        rtd1.read_all( );
        temp1_buffer = (float)rtd1.temperature( );
        if(temp1_buffer > -10.0 && temp1_buffer < 150.0){
            temperature1 = temp1_buffer;
        }
        printf( " T1 = %f deg C \n\r",temperature1);
        double resistance1 = rtd1.resistance();
        printf("Resistance1 is %f \n", resistance1);

        //need new board
        // rtd2.read_all( );
        // temp2_buffer = rtd2.temperature( );
        // if(temp2_buffer > -10.0 && temp2_buffer < 150.0){
        //   temperature2 = temp2_buffer;
        //}
        // printf( " T2 = %f deg C \n\r",temperature2);
        // double resistance2 = rtd2.resistance();
        // printf("Resistance2 is %f \n", resistance2);

        //rtd3 is good
        // rtd3.read_all( );
        // temp3_buffer = rtd3.temperature( );
        // if(temp3_buffer > -10.0 && temp3_buffer < 150.0){
        //     temperature3 = temp3_buffer;
        // }
        // printf( " T3 = %f deg C \n\r",temperature3);
        // double resistance3 = rtd3.resistance();
        // printf("Resistance3 is %f \n", resistance3);        
        
        
        // rtd4.read_all( );   //rtd4 is good
        // temp4_buffer = rtd4.temperature( );
        // if(temp4_buffer > -10.0 && temp4_buffer < 150.0){
        //     temperature4 = temp4_buffer;
        // }
        // printf( " T4 = %f deg C \n\r",temperature4);
        // double resistance4 = rtd4.resistance();
        // printf("Resistance4 is %f \n", resistance4);

        
        // // rtd5 is good
        // rtd5.read_all( );
        // temp5_buffer = rtd5.temperature( );
        // if(temp5_buffer > -10.0 && temp5_buffer < 150.0){
        //     temperature5 = temp5_buffer;
        // }
        // printf( " T5 = %f deg C \n\r",temperature5);
        // double resistance5 = rtd5.resistance();
        // printf("Resistance5 is %f \n", resistance5);

        // // rtd6 is good
        // rtd6.read_all( );
        // temp6_buffer = rtd6.temperature( );
        // if(temp6_buffer > -10.0 && temp6_buffer < 150.0){
        //     temperature6 = temp6_buffer;
        // }
        // printf( " T6 = %f deg C \n\r",temperature6);
        // double resistance6 = rtd6.resistance();
        // printf("Resistance6 is %f \n", resistance6);

        // // rtd7 is good
        // rtd7.read_all( );
        // temp7_buffer = rtd7.temperature( );
        // if(temp7_buffer > -10.0 && temp7_buffer < 150.0){
        //     temperature7 = temp7_buffer;
        // }
        // printf( " T7 = %f deg C \n\r",temperature7);
        // double resistance7 = rtd7.resistance();
        // printf("Resistance7 is %f \n", resistance7);
        

        printf("\n");
        //CAN transmit code; 40-bit message, [39:32] are RTD ID (0 through 7), [31:0] are 32-bit temp val

        //create CAN message for rtd0
        //try uint8_t

        // initialize
        char* rtd0_temp_array = (char*) &temperature0; //CAN sends by bytes, so cast temp as array of chars (bytes)
        char* rtd1_temp_array = (char*) &temperature1;
        char* rtd2_temp_array = (char*) &temperature2;
        char* rtd3_temp_array = (char*) &temperature3;
        char* rtd4_temp_array = (char*) &temperature4;
        char* rtd5_temp_array = (char*) &temperature5;
        char* rtd6_temp_array = (char*) &temperature6;
        char* rtd7_temp_array = (char*) &temperature7;
        char rtd0_can_buffer [5];   //create buffer because CAN message is concatenation of temp and rtd address
        char rtd1_can_buffer [5];   // set 5th value (bits 39:32) as rtd address
        char rtd2_can_buffer [5];
        char rtd3_can_buffer [5];
        char rtd4_can_buffer [5];
        char rtd5_can_buffer [5];
        char rtd6_can_buffer [5];
        char rtd7_can_buffer [5];
        rtd0_can_buffer[4] = 0;
        rtd1_can_buffer[4] = 1;
        rtd2_can_buffer[4] = 2;
        rtd3_can_buffer[4] = 3;
        rtd4_can_buffer[4] = 4;
        rtd5_can_buffer[4] = 5;
        rtd6_can_buffer[4] = 6;
        rtd7_can_buffer[4] = 7;

        //rtd0
        for(int i = 0; i < 4; i++){
            rtd0_can_buffer[i] = rtd0_temp_array[i];    //populate CAN buffer with temp values
        }

        // printf("buffer[0] = %x\n", rtd0_can_buffer[0]);
        // printf("buffer[1] = %x\n", rtd0_can_buffer[1]);
        // printf("buffer[2] = %x\n", rtd0_can_buffer[2]);
        // printf("buffer[3] = %x\n", rtd0_can_buffer[3]);
        // printf("buffer test: %f\n", *(float*)rtd0_can_buffer);

        //rtd1
        for(int i = 0; i < 4; i++){
            rtd1_can_buffer[i] = rtd1_temp_array[i];
        }

        //rtd2
        // for(int i = 0; i < 4; i++){
        //     rtd2_can_buffer[i] = rtd2_temp_array[i];
        // }

        //rtd3
        // for(int i = 0; i < 4; i++){
        //     rtd3_can_buffer[i] = rtd3_temp_array[i];
        // }

        //rtd4
        // for(int i = 0; i < 4; i++){
        //     rtd4_can_buffer[i] = rtd4_temp_array[i];
        // }

        //rtd5
        // for(int i = 0; i < 4; i++){
        //     rtd5_can_buffer[i] = rtd5_temp_array[i];
        // }

        //rtd6
        // for(int i = 0; i < 4; i++){
        //     rtd6_can_buffer[i] = rtd6_temp_array[i];
        // }

        //rtd7
        // for(int i = 0; i < 4; i++){
        //     rtd7_can_buffer[i] = rtd7_temp_array[i];
        // }

        if(can.read(rx_msg,0) && rx_msg.id == 0x632){
            boardEnable = rx_msg.data[0] - '0';
            // boardEnable = 0: enable reading
            // boardEnable = 1: halt reading
        }
        
        if(!boardEnable){
            can.write(CANMessage(0x620, rtd0_can_buffer, 5));
            can.write(CANMessage(0x620, rtd1_can_buffer, 5));
            //can.write(CANMessage(0x620, rtd2_can_buffer, 5));
            //can.write(CANMessage(0x620, rtd3_can_buffer, 5));
            //can.write(CANMessage(0x620, rtd4_can_buffer, 5));
            //can.write(CANMessage(0x620, rtd5_can_buffer, 5));
            //can.write(CANMessage(0x620, rtd6_can_buffer, 5));
            //can.write(CANMessage(0x620, rtd7_can_buffer, 5));
        }
        osDelay(500);
 
    }
}

