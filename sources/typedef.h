#ifndef TYPEDEF_H_
#define TYPEDEF_H_


typedef unsigned char   uint8;
typedef unsigned int    uint16;
typedef unsigned long   uint32;

typedef signed char     sint8;
typedef signed int      sint16;
typedef signed long     sint32;

typedef float           float32;


typedef enum
{
    Flag_SET   = 1u,
    Flag_CLEAR = 2u
} G_Flag_e;


typedef enum
{
    Signal_RELIABLE     = 1u,
    Signal_NOT_RELIABLE = 2u
} G_Qualifier_e;


#endif /* TYPEDEF_H_ */
