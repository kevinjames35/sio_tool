
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <math.h>
#include <dlfcn.h>

#define int8_t  		char
#define int16_t 		short
#define int32_t 		int
#define int64_t  		long long
#define uint8_t  		unsigned char
#define uint16_t 		unsigned short
#define uint32_t 		unsigned int
#define uint64_t 		unsigned long long


#define SIO_CFGINDEX	0x2E
#define SIO_CFGDATA	0x2F

void __sio_unlock(void);
void __sio_lock(void);
void __sio_logic_device(char num);






/********************************************************************/
/***** SuperIO access functions *************************************/
void __sio_unlock(void)
{
	ioperm(SIO_CFGINDEX, 2, 1);
	outb(0x77 , SIO_CFGINDEX);
	outb(0x77 , SIO_CFGINDEX);
}
/***********/
void __sio_lock(void)
{
	outb(0xaa , SIO_CFGINDEX);
	ioperm(SIO_CFGINDEX, 2, 0);
}
/***********/
void __sio_logic_device(char num)
{
	outb(0x7 , SIO_CFGINDEX);
	outb(num , SIO_CFGDATA);
}
/************/
uint8_t read_sio_reg(uint8_t LDN, uint8_t reg)
{
        outb(0x07, SIO_CFGINDEX); //LDN register
        outb(LDN, SIO_CFGDATA);
        outb(reg , SIO_CFGINDEX);
        return inb(SIO_CFGDATA);
}
/************/
uint8_t write_sio_reg(uint8_t LDN, uint8_t reg, uint8_t value)
{	
        outb(0x07, SIO_CFGINDEX); //LDN register
        outb(LDN, SIO_CFGDATA);
        outb(reg, SIO_CFGINDEX);
        outb(value, SIO_CFGDATA);
        return 0;
}
/****************/
int main( int argc, char** argv )
{
uint16_t wAddr =0, xData=0;
	
	__sio_unlock();
	__sio_logic_device(0x00);

for(int xi=0;xi<=255;xi++)
{
	outb(xi, SIO_CFGINDEX);
	xData=(uint16_t)inb(SIO_CFGDATA);
printf("0x%X = 0x%X\n",xi,xData);
}

	__sio_lock();
	
	return 0;
	
}

