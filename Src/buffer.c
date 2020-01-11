#include "buffer.h"
#include "Crc_my.h"

double term_buf[BUFFER_SIZE];		/**< fifo buffer for roll data. */
volatile uint8_t tail_t;					/**< index for writing to buffer. */
volatile uint8_t head_t;					/**< index for reading from buffer. */

extern uint8_t buffer[8];

/**
  * @brief  Function adds data to the buffer.
  * @param  double roll value.
  * @retval None.
  */

void InBuffer(double byte)
{
	if(tail_t == BUFFER_SIZE - 1)
		tail_t = 0;
	
    term_buf[tail_t++] = byte;
}

/**
  * @brief  Function returns data from buffer.
  * @param  None.
  * @retval unsigned char current data.
  */
unsigned char OutBufferStr()
{
	if(head_t == BUFFER_SIZE - 1)
		head_t = 0;
	
	unsigned char data;
		data = term_buf[head_t++];
	return data;
}

/**
  * @brief  Function check if new data was received.
  * @param  None.
  * @retval uint8_t result status.
  */
uint8_t IsNewData()
{
	if(head_t == tail_t)
			return 0;
	return 1;
}

uint8_t read_buf()
{
	while(OutBufferStr() != 0xAA)
	{}
		uint8_t ind = 0;
		buffer[ind++] = 2;
		uint8_t length = OutBufferStr();
		buffer[ind++] = length;
		for(uint8_t cnt = 0; cnt < length; cnt++)
		buffer[ind++] = OutBufferStr();
		
		uint16_t crc = crc16(buffer + 2, length);
		buffer[ind++] = crc >> 8;
		buffer[ind++] = crc;
		buffer[ind++] = 3;
		
		return ind;
	}