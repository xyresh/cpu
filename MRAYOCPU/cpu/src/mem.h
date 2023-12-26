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

#define SL 100


typedef uint8_t RegFByte;

struct Instruction *text_init(int size)
{
    return malloc(size*sizeof(struct Instruction));
}
//returns base pointer.
uint8_t *stackinit()
{
	return (uint8_t*)malloc(SL);
}
