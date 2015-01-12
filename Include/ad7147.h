#ifndef _AD7147_H_
#define _AD7147_H_

unsigned short int GetReg(unsigned short int Addr);
void SetReg (unsigned short int Addr, unsigned short int Data);
unsigned short int SPISend(unsigned short int Comm_Wrd, unsigned short int Data_Wrd);



#endif

