/*
 *	simple ALU implementation
 *	we have a simple control 'unit'
 *	which performs each instruction depending on opcode
 *
 * */


//the instruction is a simple struct of operand A and B
//And the opcode.
struct ALUd{
	uint8_t A;
	uint8_t B;
	uint8_t opcode;
};

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


void ADD(struct ALUd inst, uint8_t* res);
void SUB(struct ALUd inst, uint8_t* res);
void INC(struct ALUd inst, uint8_t* res);
void DEC(struct ALUd inst, uint8_t* res);
void AND(struct ALUd inst, uint8_t* res);
void OR(struct ALUd inst, uint8_t* res);
void XOR(struct ALUd inst, uint8_t* res);


void ALU_CTR(struct ALUd inst, uint8_t * res)
{
	switch(inst.opcode){
	
		case 1:
			ADD(inst,res);
			break;
		case 2:
			SUB(inst,res);
			break;
		case 3:
			INC(inst,res);
			break;
		case 4:
			DEC(inst,res);
			break;
		case 5:
			AND(inst,res);
			break;
		case 6:
			OR(inst,res);
			break;
		case 7:
			XOR(inst,res);
			break;
	};
}


void ADD(struct ALUd inst, uint8_t* res)
{
	*res = inst.A + inst.B;
}

void SUB(struct ALUd inst, uint8_t* res)
{
	*res = inst.A - inst.B;	
}

void INC(struct ALUd inst, uint8_t* res)
{
	*res = inst.A+1;
}

void DEC(struct ALUd inst, uint8_t* res)
{
	*res = inst.A-1;
}

void AND(struct ALUd inst, uint8_t* res)
{
	*res = inst.A & inst.B;
}

void OR(struct ALUd inst, uint8_t* res)
{
	*res = inst.A | inst.B;
}

void XOR(struct ALUd inst, uint8_t* res)
{
	*res = inst.A ^ inst.B;
}
