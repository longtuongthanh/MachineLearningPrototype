#ifndef __CONSTLIB_INCLUDED
#define __CONSTLIB_INCLUDED

#include <cmath>

extern const long bot_no=300;
extern const long pos_func=5;
extern const long pos_chnge=8;

extern const long bit_size=10;
extern const long test_num=1000;
extern const double max_mult=1.06;

extern const long max_pair=20;
extern const long max_chromosome=20;
extern const long max_size=max_pair*max_chromosome;

    extern const long prob_space=80;
    extern const long prob[pos_chnge+1]={0,10,20,35,45,55,65,75,80};

extern const long bot_catcher_raw_score=1000;
extern const long bot_catcher_score=1000;

extern const long new_old_threshhold=10;

long super_secret_formula(long a,long b)
{
    return a xor b;
}

/*
long mutation_coefficent(long a)
{
    double ans=1;
    while (rand()%2==0) ans+=a;
    return floor(ans);
}*/
#define CATCH_CONDITION (score>=bot_catcher_score)&&(raw_score()>=bot_catcher_raw_score)
#endif // constlib_included
