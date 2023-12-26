#include"defs.h"

typedef uint8_t RegFByte;
typedef uint8_t DataMByte;


//definition of 10 registers.
#define ZERO 0 //ZEROO
#define r1 1 // op a
#define r2 2 // op b
#define r3 3 
#define r4 4
#define r5 5
#define r6 6
#define r7 7
#define r8 8
#define r9 9
#define r10 0

struct Instruction
{
	uint8_t op;
	uint8_t flag;
	uint8_t t;
	uint8_t A;
	uint8_t B;
};
//we define the control unit function, The arguments parsed are the instruction along with the register file
int CU(struct Instruction in, RegFByte RegF[10], uint8_t dataM[])
{
	struct ALUd ali;


	//a temp byte we allocate in memory for the result.
	uint8_t * rer = malloc(sizeof(uint8_t));

	ali.opcode = in.op;
	if (in.flag == 0)
	{
		ali.A = RegF[r1];
		ali.B = RegF[r2];
	}
	else if(in.flag == 1)
	{
		ali.A = RegF[RegF[r1]];
		ali.B = RegF[r2];
	}
	else if(in.flag == 2)
	{
		ali.A = RegF[RegF[r1]];
		ali.B = RegF[RegF[r2]];
	}	


	if(in.op <= 7 && in.op >=1)
	{
		ALU_CTR(ali, rer);
		RegF[in.t] = * rer;
		free(rer);
		return 1;
	}

	switch (in.op)
	{
	case 8:			//MOV
		switch (in.flag)
		{
			case 0:	//case from reg to reg
				RegF[in.t] = RegF[RegF[r1]];
				break;
			case 1:	//case value to register
				RegF[in.t] = RegF[r1];
				break;
			case 2:	//case register to memory!
				dataM[in.t] = RegF[RegF[r1]];	
				break;		
			case 3: //case memory to register
				RegF[in.t] = dataM[r1];
				break;
	
		}
		return 4;
		break;
	case 9:
		printf("\033c");
		if(in.flag==0)
		{
			printf("r%d : %d\n" ,RegF[r1], RegF[RegF[r1]]);	//we have a display register instruction for now.
		}
		else if(in.flag==1)
		{
			printf("0x%d : %d\n" ,RegF[r1], dataM[RegF[r1]]);	//we have a display register instruction for now.
		}
		else if(in.flag==2)//full memory display
		{
		    printf("\ndisplaying all registers: \n");
		    for(int j=0;j<=10;j++)
		    {
		        printf("r%d : %d\n", j ,RegF[j]);
		    }
		}
		else if(in.flag==3)//full data memory display
		{
		    printf("\ndisplaying full memory: \n");
		    for(int j=0;j<= DATAM;j++)
		    {
		        printf("0x%d : %d\n", j ,dataM[j]);
		    }
		}
		free(rer);
		return 2;
	case 10: //JMP
		if(in.flag == 1)
		{
			return 3;
		}
		else
		{
			return 5;
		}
	case 11: //stack push:q
		return 6;
	case 12://stack pop
		return 7;
	case 13:
		return 5;
	case 0:
		free(rer);
		return 0;
	default:
		break;
	}

}
