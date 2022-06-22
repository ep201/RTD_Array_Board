// This code is for a CAN receiver to test the signals that the RTD board sends.
// This code DOES NOT go on the RTD board.
// 
#include "mbed.h"
#include <cstdint>
#include <cstdio>
//
// main() runs in its own thread in the OS
static Ticker ticker;
static bool sampleFlag = false;

void tick(void) {
    sampleFlag = true;
}

int main()
{
    ticker.attach(&tick, 1ms);
    CAN can(D10, D2);
    while (true) {
        

        // float int_test = 110.34;
        // char* int_to_char = (char*)&int_test;
        // uint8_t int_to_char_copy [4];
        // for(int i = 0; i < 4; i++){
        //     int_to_char_copy[i] = int_to_char[i];
        // }
        // float* numAddress = (float*)int_to_char_copy;
        //fixed %f by going into rtd_can_test -> mbed_os ->target -> targets.json, change minimal-printf to std
        //first, if project folder has it, edit mbed_app.json
        //printf("number should be 110.34. Number is : %.2f\n", *numAddress);
        
        char can_tx_buffer [6];
        char rtd0_rx_buffer [5];
        char rtd1_rx_buffer [5];
        char rtd2_rx_buffer [5];
        char rtd3_rx_buffer [5];
        char rtd4_rx_buffer [5];
        char rtd5_rx_buffer [5];
        char rtd6_rx_buffer [5];
        char rtd7_rx_buffer [5];
        char rtd_error_buffer [1];
        
        CANMessage rx_msg;

        float* rtd0_temperature_addr;
        float* rtd1_temperature_addr;
        float* rtd2_temperature_addr;
        float* rtd3_temperature_addr;
        float* rtd4_temperature_addr;
        float* rtd5_temperature_addr;
        float* rtd6_temperature_addr;
        float* rtd7_temperature_addr;
        int* rtd_stauts_addr;
        //*rtd0_temperature_addr = 102.1;
        //set up test rx buffer to send message
        // for(int i = 0; i < 5; i++){
        //     can_tx_buffer[i] = '1';
        // }
        // can_tx_buffer[5] = 0;
        // can_tx_buffer[0] = 0x00;
        // can_tx_buffer[1] = 0x00;
        // can_tx_buffer[2] = 0xAC;
        // can_tx_buffer[3] = 0x41;
        // rtd0_temperature_addr = (float*)can_tx_buffer;
        //rtd0_temperature_addr = (float*)can_tx_buffer;
        //can.write(CANMessage(0x620, rtd0_can_buffer, 5));

        if(can.read(rx_msg,0) && rx_msg.id == 0x633){
            rtd_error_buffer[0] = rx_msg.data[0];
            rtd_stauts_addr = (int*)rtd_error_buffer;
            printf("error = %d\n", *rtd_stauts_addr);
        }
        // need to make this supercede the normal temperature transmits

        if(can.read(rx_msg,0) && rx_msg.id == 0x620 && rx_msg.data[4] == 0){
            rtd0_rx_buffer[0] = rx_msg.data[0];
            rtd0_rx_buffer[1] = rx_msg.data[1];
            rtd0_rx_buffer[2] = rx_msg.data[2];
            rtd0_rx_buffer[3] = rx_msg.data[3];
            rtd0_rx_buffer[4] = rx_msg.data[4];
            rtd0_temperature_addr = (float*)rtd0_rx_buffer;
            printf("rtd0 buffer = %.5f\n", *rtd0_temperature_addr);
        }

        if(can.read(rx_msg,0) && rx_msg.id == 0x620 && rx_msg.data[4] == 1){
            rtd1_rx_buffer[0] = rx_msg.data[0];
            rtd1_rx_buffer[1] = rx_msg.data[1];
            rtd1_rx_buffer[2] = rx_msg.data[2];
            rtd1_rx_buffer[3] = rx_msg.data[3];
            rtd1_rx_buffer[4] = rx_msg.data[4];
            rtd1_temperature_addr = (float*)rtd1_rx_buffer;
            printf("rtd1 buffer = %.5f\n\n", *rtd1_temperature_addr);
        }

        if(can.read(rx_msg,0) && rx_msg.id == 0x620 && rx_msg.data[4] == 2){
            rtd2_rx_buffer[0] = rx_msg.data[0];
            rtd2_rx_buffer[1] = rx_msg.data[1];
            rtd2_rx_buffer[2] = rx_msg.data[2];
            rtd2_rx_buffer[3] = rx_msg.data[3];
            rtd2_rx_buffer[4] = rx_msg.data[4];
            rtd2_temperature_addr = (float*)rtd2_rx_buffer;
            printf("rtd2 buffer = %.5f\n\n", *rtd2_temperature_addr);
        }

        if(can.read(rx_msg,0) && rx_msg.id == 0x620 && rx_msg.data[4] == 3){
            rtd3_rx_buffer[0] = rx_msg.data[0];
            rtd3_rx_buffer[1] = rx_msg.data[1];
            rtd3_rx_buffer[2] = rx_msg.data[2];
            rtd3_rx_buffer[3] = rx_msg.data[3];
            rtd3_rx_buffer[4] = rx_msg.data[4];
            rtd3_temperature_addr = (float*)rtd3_rx_buffer;
            printf("rtd3 buffer = %.5f\n\n", *rtd3_temperature_addr);
        }

        if(can.read(rx_msg,0) && rx_msg.id == 0x620 && rx_msg.data[4] == 4){
            rtd4_rx_buffer[0] = rx_msg.data[0];
            rtd4_rx_buffer[1] = rx_msg.data[1];
            rtd4_rx_buffer[2] = rx_msg.data[2];
            rtd4_rx_buffer[3] = rx_msg.data[3];
            rtd4_rx_buffer[4] = rx_msg.data[4];
            rtd4_temperature_addr = (float*)rtd4_rx_buffer;
            printf("rtd4 buffer = %.5f\n\n", *rtd4_temperature_addr);
        }

        if(can.read(rx_msg,0) && rx_msg.id == 0x620 && rx_msg.data[4] == 5){
            rtd5_rx_buffer[0] = rx_msg.data[0];
            rtd5_rx_buffer[1] = rx_msg.data[1];
            rtd5_rx_buffer[2] = rx_msg.data[2];
            rtd5_rx_buffer[3] = rx_msg.data[3];
            rtd5_rx_buffer[4] = rx_msg.data[4];
            rtd5_temperature_addr = (float*)rtd5_rx_buffer;
            printf("rtd5 buffer = %.5f\n\n", *rtd5_temperature_addr);
        }

        if(can.read(rx_msg,0) && rx_msg.id == 0x620 && rx_msg.data[4] == 6){
            rtd6_rx_buffer[0] = rx_msg.data[0];
            rtd6_rx_buffer[1] = rx_msg.data[1];
            rtd6_rx_buffer[2] = rx_msg.data[2];
            rtd6_rx_buffer[3] = rx_msg.data[3];
            rtd6_rx_buffer[4] = rx_msg.data[4];
            rtd6_temperature_addr = (float*)rtd6_rx_buffer;
            printf("rtd6 buffer = %.5f\n\n", *rtd6_temperature_addr);
        }

        if(can.read(rx_msg,0) && rx_msg.id == 0x620 && rx_msg.data[4] == 7){
            rtd7_rx_buffer[0] = rx_msg.data[0];
            rtd7_rx_buffer[1] = rx_msg.data[1];
            rtd7_rx_buffer[2] = rx_msg.data[2];
            rtd7_rx_buffer[3] = rx_msg.data[3];
            rtd7_rx_buffer[4] = rx_msg.data[4];
            rtd7_temperature_addr = (float*)rtd7_rx_buffer;
            printf("rtd7 buffer = %.5f\n\n", *rtd7_temperature_addr);
        }
        
        //printf("testing can tx buffer: int value in buffer = %d\n", atoi(can_tx_buffer));
        //ThisThread::sleep_for(250ms);
    }
}

