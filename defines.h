#ifndef _DEFINES_H_
#define _DEFINES_H_

#define SETBIT(REG,BIT)      (REG |= (1<<BIT))
#define CLRBIT(REG,BIT)      (REG &= ~(1<<BIT))
#define READBIT(REG,BIT)     ((REG>>BIT)&1)

#define WRITEBYTE(REG,POS,VAL) \
        (REG=((REG&~(0xFF<<(POS)))|((VAL)<<(POS))))

#endif
