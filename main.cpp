//can_read_test
//This code is for a separate board that reads the messages sent by the RTD board.
//This code DOES NOT RUN on the RTD board. It is the code for another board that receives CAN messages.
#include "mbed.h"
#include <cstdint>
#include <cstdio>

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
        CANMessage rx_msg;

        float* rtd0_temperature_addr;
        float* rtd1_temperature_addr;
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

        if(can.read(rx_msg,0) && rx_msg.id == 0x620 && rx_msg.data[4] == 1){
            rtd1_rx_buffer[0] = rx_msg.data[0];
            rtd1_rx_buffer[1] = rx_msg.data[1];
            rtd1_rx_buffer[2] = rx_msg.data[2];
            rtd1_rx_buffer[3] = rx_msg.data[3];
            rtd1_rx_buffer[4] = rx_msg.data[4];
            rtd1_temperature_addr = (float*)rtd1_rx_buffer;
            printf("rtd1 buffer = %.5f\n\n", *rtd1_temperature_addr);
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

        if(can.read(rx_msg,0) && rx_msg.id == 0x620 && rx_msg.data[4] == 1){
            rtd1_rx_buffer[0] = rx_msg.data[0];
            rtd1_rx_buffer[1] = rx_msg.data[1];
            rtd1_rx_buffer[2] = rx_msg.data[2];
            rtd1_rx_buffer[3] = rx_msg.data[3];
            rtd1_rx_buffer[4] = rx_msg.data[4];
            rtd1_temperature_addr = (float*)rtd1_rx_buffer;
            printf("rtd1 buffer = %.5f\n\n", *rtd1_temperature_addr);
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

        if(can.read(rx_msg,0) && rx_msg.id == 0x620 && rx_msg.data[4] == 1){
            rtd1_rx_buffer[0] = rx_msg.data[0];
            rtd1_rx_buffer[1] = rx_msg.data[1];
            rtd1_rx_buffer[2] = rx_msg.data[2];
            rtd1_rx_buffer[3] = rx_msg.data[3];
            rtd1_rx_buffer[4] = rx_msg.data[4];
            rtd1_temperature_addr = (float*)rtd1_rx_buffer;
            printf("rtd1 buffer = %.5f\n\n", *rtd1_temperature_addr);
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
        
        //printf("testing can tx buffer: int value in buffer = %d\n", atoi(can_tx_buffer));
        //ThisThread::sleep_for(250ms);
    }
}

