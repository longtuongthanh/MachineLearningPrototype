#ifndef __BIT_COMPUTATION_H_INCLUDED
#define __BIT_COMPUTATION_H_INCLUDED

#include "constlib.h"

#ifndef __FUNCTION_POINTER_INCLUDED
#define __FUNCTION_POINTER_INCLUDED

typedef long (*function_pointer) (long a,long b);

#endif // __FUNCTION_POINTER_INCLUDED

long _and(long a,long b){return (a&b)%(1<<bit_size);}
long _or (long a,long b){return (a|b)%(1<<bit_size);}
long _not(long a,long b){return (((~a)<<1)>>1)%(1<<bit_size);}
long _shl(long a,long b){return (a<<1)%(1<<bit_size);}
long _shr(long a,long b){return (a>>1)%(1<<bit_size);}

function_pointer functions[5]=
{
    _and,
    _or,
    _not,
    _shl,
    _shr
};

long scorer (long scr,long ans)
{
    long s=0;
    if (scr<0) scr=(scr<<1)>>1;
    if (ans<0) ans=(ans<<1)>>1;
    for (int i=0;i<bit_size;i++)
    {
        if (ans%2==scr%2)
            s++;
        ans=ans>>1;
        scr=scr>>1;
    }
    return s;
}
#endif // __BIT_COMPUTATION_H_INCLUDED
