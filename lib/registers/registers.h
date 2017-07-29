//Fast I/O Direction

#ifndef FIO1DIR2
#define FIO1DIR2 (*(volatile unsigned char *) (0x2009C022))
#endif

#ifndef FIO1DIR3
#define FIO1DIR3 (*(volatile unsigned char *) (0x2009C023))
#endif

#ifndef FIO2DIR0
#define FIO2DIR0 (*(volatile unsigned char *) (0x2009C040))
#endif

//Fast I/O Pin
#ifndef FIO1PIN2
#define FIO1PIN2 (*(volatile unsigned char *) (0x2009C036))
#endif

#ifndef FIO2PIN0
#define FIO2PIN0 (*(volatile unsigned char *) (0x2009C054))
#endif

//Fast I/O Mask

#ifndef FIO2MASK0
#define FIO2MASK0 (*(volatile unsigned char *) (0x2009C050))
#endif

//A/D Control
#ifndef AD0CR
#define AD0CR (*(volatile unsigned long *) (0x40034000))
#endif

//A/D Global Data Register
#ifndef AD0GDR
#define AD0GDR (*(volatile unsigned long *) (0x40034004))
#endif

//Power Control for Peripheral
#ifndef PCONP
#define PCONP (*(volatile unsigned long *) (0x400FC0C4))
#endif

//Pin Select
#ifndef PINSEL1
#define PINSEL1 (*(volatile unsigned long *) (0x4002C004))
#endif

#ifndef PINSEL3
#define PINSEL3 (*(volatile unsigned long *) (0x4002C00C))
#endif
