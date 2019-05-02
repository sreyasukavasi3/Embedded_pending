#include "tm4c123gh6pm.h"
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTE_DATA_BITS_R  ((volatile unsigned long *)0x40024000)
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_IS_R         (*((volatile unsigned long *)0x40024404))
#define GPIO_PORTE_IBE_R        (*((volatile unsigned long *)0x40024408))
#define GPIO_PORTE_IEV_R        (*((volatile unsigned long *)0x4002440C))
#define GPIO_PORTE_IM_R         (*((volatile unsigned long *)0x40024410))
#define GPIO_PORTE_RIS_R        (*((volatile unsigned long *)0x40024414))
#define GPIO_PORTE_MIS_R        (*((volatile unsigned long *)0x40024418))
#define GPIO_PORTE_ICR_R        (*((volatile unsigned long *)0x4002441C))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DR2R_R       (*((volatile unsigned long *)0x40024500))
#define GPIO_PORTE_DR4R_R       (*((volatile unsigned long *)0x40024504))
#define GPIO_PORTE_DR8R_R       (*((volatile unsigned long *)0x40024508))
#define GPIO_PORTE_ODR_R        (*((volatile unsigned long *)0x4002450C))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_PDR_R        (*((volatile unsigned long *)0x40024514))
#define GPIO_PORTE_SLR_R        (*((volatile unsigned long *)0x40024518))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_LOCK_R       (*((volatile unsigned long *)0x40024520))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *)0x40024524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
#define GPIO_PORTE_ADCCTL_R     (*((volatile unsigned long *)0x40024530))
#define GPIO_PORTE_DMACTL_R     (*((volatile unsigned long *)0x40024534))
// 2. Declarations Section
//   Global Variables
unsigned long SW1,SW2;  // input from PF4,PF0
unsigned long Out;      // outputs to PF3,PF2,PF1 (multicolor LED)

//   Function Prototypes
void PORTE_Init(void);
void Delay(void);
void Delay()
{
	unsigned long volatile time;
  time = 150000;  // counter value for delay
  while(time){
		time--;
	}
}
// 3. Subroutines Section
// MAIN: Mandatory for a C Program to be executable
int main(void){    
  PORTE_Init();           
  while(1){
    SW1 = GPIO_PORTE_DATA_R&0x01;     
    if(!SW1){                   
				GPIO_PORTE_DATA_R |= 0x02;       
				Delay();
				GPIO_PORTE_DATA_R &=  ~(0x02);
				Delay();
			
    }
		else {                
				GPIO_PORTE_DATA_R |= 0x02;     
		} 
	}
}

void PORTE_Init(void){ volatile unsigned long d;
  SYSCTL_RCGC2_R |= 0x00000010;     
  d = SYSCTL_RCGC2_R;               //Dummy instruction to wait for clock to stabilize 
  GPIO_PORTE_CR_R |= 0x03;              
  GPIO_PORTE_AMSEL_R &= ~(0x03);       
  GPIO_PORTE_PCTL_R &=  ~(0x03);   
  GPIO_PORTE_DIR_R |= 0x02;            
  GPIO_PORTE_AFSEL_R &=  ~(0x03);           
  GPIO_PORTE_DEN_R |= 0x03;                
}
// Color    LED(s) PORTE
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06
