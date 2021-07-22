#ifndef __TEST_H_INCLUDED
#define __TEST_H_INCLUDED

#include "constlib.h"
#include "bit_computation.h"
#include <utility>
#include "bot_data.h"

struct test
{
    long a,b,output;

    test()
    {
        a=rand()%(1<<(bit_size));
        b=rand()%(1<<(bit_size));
        output=super_secret_formula(a,b);
    }

    std::pair <long,long> input()
    {
        return std::make_pair(a,b);
    }
};

struct test_set
{
    test question[test_num];

    long raw_test_report(bot_data &bot)
    {
        long ans=0;
        for(int i=0;i<test_num;i++)
            ans+=scorer(question[i].output,bot.run(question[i].input()));
        return ans;
    }

    double test_report(bot_data bot)
    {
        double ans=raw_test_report(bot);
        ans=ans*(max_mult-(max_mult-1)*bot.memory()/max_size);
        return ans;
    }

    void renew()
    {
        for (int i=0;i<test_num;i++)
            question[i]=test();
    }
};

struct elim_pattern
{
    bool x[bot_no];

    elim_pattern()
    {
        for (int i=0;i<bot_no/2;i++)
            x[i]=(rand()%bot_no)<i;
        for (int i=bot_no/2+1;i<bot_no;i++)
            x[i]=!x[bot_no-i-1];
    }

    void renew()
    {
        for (int i=0;i<bot_no/2;i++)
            x[i]=(rand()%bot_no)<i;
        for (int i=bot_no/2+1;i<bot_no;i++)
            x[i]=!x[bot_no-i-1];
    }
    operator [](int c)
    {
        return x[c];
    }
};

#endif // __TEST_H_INCLUDED

