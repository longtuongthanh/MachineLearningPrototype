#ifndef __BOT_ECOLOGY_H_INCLUDED
#define __BOT_ECOLOGY_H_INCLUDED

#include <algorithm>
#include "constlib.h"
#include "bit_computation.h"
#include "bot_data.h"
#include "test.h"
#include "bot_manip.h"

struct bot_ecology
{
    bot_data bot[bot_no];
    test_set tester;
    elim_pattern elim;
    bool tested;
    long iter_no;

    bot_ecology()
    {
        for (int i=0;i<bot_no/2;i++)
            bot[i]=bot_data(rand()%max_chromosome+1);
        for (int i=bot_no/2+1;i<bot_no;i++)
            bot[i]=bot_data();
        tester=test_set();
        elim=elim_pattern();
        tested=false;
    }

    void qsort(long l,long r)
    {
        long i=l;
        long j=r;
        bot_data x;
        x=bot[(l+r)/2];
        bot_data temp;
        while (i<=j)
        {
            while ((x<bot[i])&&(i<r)) i++;
            while ((bot[j]<x)&&(l<j)) j--;
            if (i<=j)
            {
                temp=bot[i];
                bot[i]=bot[j];
                bot[j]=temp;
                i++;
                j--;
            }
        }
        if (l<j) qsort(l,j);
        if (i<r) qsort(i,r);
    }

    void next_gen()
    {
        iter_no++;
        if (!tested)
            gen_performance();
        /*for (int i=0;i<bot_no-1;i++)
            for (int j=i+1;j<bot_no;j++)
                if (bot[i]<bot[j])
                {
                    bot_data temp;
                    temp=bot[i];
                    bot[i]=bot[j];
                    bot[j]=temp;
                }*/
        qsort(0,bot_no-1);
        int k=0;
        for (int i=0;i<bot_no-1;i++)
        {
            if (i!=k) bot[k]=bot[i];
            if (!(bot[i]==bot[i+1]))
                k++;
        }
        bot[k]=bot[bot_no-1];
        for (;k<bot_no;k++)
            bot[k]=bot_data();
        for (int i=0;i<bot_no;i++)
            if (elim[i])
                bot[i]=bot_data();
        int n=bot_no-1;
        for (int i=bot_no-1;i>=0;i--)
            if ((bot[i].score!=0))
            {
                bot[n]=bot[i];
                n--;
            }
        n++;
        int j=n;
        for (int i=0;i<bot_no/2;i++)
        {
            bot[i]=bot[j];
            tinichange(bot[i]);
            j++;
            if (j>=bot_no) j=n;
        }
        //elim.renew();
        tested=false;
    }

    double gen_performance()
    {
        double ans=0;
        for (int i=0;i<bot_no;i++)
        {
            if (bot[i].size==0) continue;
            double temp=tester.test_report(bot[i]);
            if (temp<bot[i].score)bot[i].score=(temp+2*bot[i].score)/4;
            else bot[i].score=(temp+bot[i].score)/4;
            if (ans<temp) ans=temp;
        }
        tested=true;
        return ans;
    }

    long raw_performance()
    {
        long ans=0;
        for (int i=0;i<bot_no;i++)
        {
            if (bot[i].size==0) continue;
            long temp=tester.raw_test_report(bot[i]);
            bot[i].raw_score=temp;
            if (ans<temp) ans=temp;
        }
        return ans;
    }
};

#endif // __BOT_ECOLOGY_H_INCLUDED
