#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#include"ALU.h"
#include"CU.h"
#include"mem.h"
#include"defs.h"


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

#define MAX_LINE_LENGTH 20

typedef uint8_t RegFByte;
typedef uint8_t DataMByte;


void loadToMem(struct Instruction text[], const char* filename)
{

    FILE *file;
    char line[MAX_LINE_LENGTH];
		struct Instruction inst;

		int i = 0;

	 file = fopen(filename, "r"); // Open the file

   if (file == NULL) {
       perror("Error opening binary");
       return;
   }

		uint32_t hexValue;
		while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
		{
      hexValue = (uint32_t)strtoul(line, NULL, 16); // Convert hexadecimal string to uint32_t and store in the array
			uint8_t byte1, byte2, byte3, byte4;
					
			byte1 = (hexValue >> 24) & 0xFF;
			inst.A = (hexValue >> 16) & 0xFF;
			inst.B = (hexValue >> 8) & 0xFF;
			inst.t = hexValue & 0xFF;
					
			uint8_t opp = (byte1 >> 4) & 0x0F;
			uint8_t flagg = byte1 & 0x0F;
					
			inst.op = opp;
			inst.flag = flagg;
			
			text[i]=inst;

			if (inst.op == 0)
			{
				break;
			}
			i++;
		}	
}



int main(int argc, char * argv[])
{

	//int inCnt = atoi(argv[1]);
	//printf("\n %d \n\n", inCnt);
	//struct Instruction inst;
	int PC = 0;
	char mode;

	uint8_t RegF[10]={0};
	//stack initialization
	uint8_t *BP = stackinit();
	uint8_t *SP = BP; //Stack pointer
	struct Instruction TEXT[MEM]={0};
	uint8_t dataM[DATAM];



	printf("\nMarios CPU emulator\n");
	
	mode = *argv[1];	


	if (mode == 'i')
	{
		printf("\nInterpreter Mode\nEach interpreted Command is entered in HEX machine code\n");

		while (1)
		{
			printf("\n$> ");

				struct Instruction inst;
				//scanf("%d %d %d %d %d",&inst.op,&inst.flag,&inst.A,&inst.B,&inst.t);
				
				
				uint32_t hexValue;
    
				scanf("%x", &hexValue);
				
				uint8_t byte1, byte2, byte3, byte4;
				
				byte1 = (hexValue >> 24) & 0xFF;
				inst.A = (hexValue >> 16) & 0xFF;
				inst.B = (hexValue >> 8) & 0xFF;
				inst.t = hexValue & 0xFF;
				
				uint8_t opp = (byte1 >> 4) & 0x0F;
				uint8_t flagg = byte1 & 0x0F;
				
				inst.op = opp;
				inst.flag = flagg;

				int res;
				

				RegF[r1] = inst.A;
				RegF[r2] = inst.B;
				//printf("%d %d %d \n", inst.op,inst.flag,RegF[r1], RegF[r2]);
				
				res = CU(inst, RegF, dataM);

				//check to see for error codes despite us having a compiler this is also gonna be interpretable :D
				switch (res)
				{
				case 0:
					//printf("\033c");
					printf("\nexit...\n");
					return 0;
				case 1: //any Normal OP except jmp
					//printf("\033c");
					printf("\nres = %d\n", RegF[inst.t]);
					printf("\noperation completed succesfully\n\n");
					break;
				case 4:
					//printf("\033c");
					printf("\nMOV\n");

					printf("\noperation completed succesfully\n\n");
					break;
				case 2:
					printf("\n\n");
					break;
				case 3:
					printf("\njmp\n");
					break;
				case 6:
					printf("\npush\n");
					*SP = RegF[RegF[1]];
					if(SP-BP < SL)
					{
						SP++;
					}
					break;
				case 7:
					printf("\npop\n");
					if(SP>BP)
					{
						SP--;	
					}
					RegF[RegF[1]] = *SP;
					break;
				case 5:
					printf("\nstack pointer value: %d",*(SP-1));
					break;
				default:
					break;
				}

		}

	}
	if(mode == 'r')
	{
    if (argc < 3) {
        printf("Usage: %s r <filename>\n", argv[0]);
        return 1;
    }

		loadToMem(TEXT,argv[2]);

		while (1)
		{
			printf("\nProgram counter: %d",PC);
			struct Instruction inst;

			int res;
			
			inst = TEXT[PC];

			RegF[r1] = inst.A;
			RegF[r2] = inst.B;
			//printf("%d %d \n",RegF[r1], RegF[r2]);
			
			res = CU(inst, RegF, dataM);

			//check to see for error codes despite us having a compiler this is also gonna be interpretable :D
			switch (res)
			{
			case 0:
				printf("\nexiting...\n");
				return 0;
			case 1: //any Normal OP except jmp
				printf("\nres = %d\n", RegF[inst.t]);
				printf("\noperation completed succesfully\n\n");
				PC++;
				break;
			case 4:
				printf("\nMOV\n");
				printf("\noperation completed succesfully\n\n");
				PC++;
				break;
			case 2:
				printf("\n\n");
				PC++;
				break;
			case 3://conditional jump, if r2 is 0, otherwise jump instruction ignored 
				if( RegF[r2] == 0)
				{
					PC = r1;
				}
				break;
			case 5:
				printf("\n\n%d\n\n",PC);
				PC = r1;
				break;
			case 6:
				printf("\npush\n");
				*SP = RegF[RegF[1]];
				if(SP-BP < SL)
				{
					SP++;
				}
				break;
			case 7:
				printf("\npop\n");
				if(SP>BP)
				{
					SP--;	
				}
				RegF[RegF[1]] = *SP;
				break;
	
			default:
				break;
			}
		}
	}



/*
	for(int i=0; i<S; i++) 
	{
		scanf("%d %d %d",&PC->op,&PC->A,&PC->B);
		PC=PC+sizeof(struct Instruction);
	}
	PC = PCN;
*/



	
	
}
