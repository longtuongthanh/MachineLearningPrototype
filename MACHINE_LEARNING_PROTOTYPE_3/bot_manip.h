#ifndef __BOT_MANIP_H_INCLUDED
#define __BOT_MANIP_H_INCLUDED

#include "bot_data.h"
#include <cmath>

#ifndef __FUNCTION_POINTER2_INCLUDED
#define __FUNCTION_POINTER2_INCLUDED

typedef bool (*function_pointer2) (bot_data&);

#endif // __FUNCTION_POINTER_INCLUDED

bool add_chr(bot_data &bot)
{
    if (bot.size>=max_chromosome-1) return false;
    chromosome x;
    x=chromosome(rand()%max_pair,bot.size+1);
    ;
    bot.insert(x);
    return true;
}

bool del_chr(bot_data &bot)
{
    if (bot.size<=1) return false;
    long trgt=rand()%bot.size;
    for (int i=trgt;i<bot.size-1;i++)
    {
        bot.chr[i]=bot.chr[i+1];
        if (bot.chr[i].begin>trgt+2)
            bot.chr[i].begin--;
        else if (bot.chr[i].begin==trgt+2)
            bot.chr[i].begin--;
        for (int j=0;j<bot.chr[i].size;j++)
            if (bot.chr[i].command[j].second>trgt+2)
                bot.chr[i].command[j].second--;
            else if (bot.chr[i].command[j].second==trgt+2)
                bot.chr[i].command[j].second=rand()%(i+2);
    }
    bot.size--;
    return true;
}

bool dup_chr(bot_data &bot)
{
    if (bot.size>=max_chromosome-1) return false;
    long trgt=rand()%bot.size;
    long mapp[max_chromosome];
    for (int i=0;i<trgt+2;i++)
        mapp[i]=rand()%(bot.size+1);
    chromosome x;
    x=bot.chr[trgt];
    for (int i=0;i<x.size;i++)
        x.command[i].second=mapp[x.command[i].second];
    x.begin=mapp[x.begin];
    bot.chr[bot.size]=x;
    bot.size++;
    return true;
}

bool add_pair(bot_data &bot)
{
    long trgt=rand()%bot.size;
    if (bot.chr[trgt].size>=max_pair) return false;
    bot.chr[trgt].insert(std::make_pair(rand()%5,rand()%(trgt+2)));
    return true;
}

bool del_pair(bot_data &bot)
{
    long trgt=rand()%bot.size;
    if (bot.chr[trgt].size<=1) return false;
    long trgt2=rand()%bot.chr[trgt].size;
    for (int i=trgt2;i<bot.chr[trgt].size-1;i++)
        bot.chr[trgt].command[i]=bot.chr[trgt].command[i+1];
    bot.chr[trgt].size--;
    return true;
}

bool chg_pair(bot_data &bot)
{
    long trgt=rand()%bot.size;
    if (bot.chr[trgt].size==0) return false;
    long trgt2=rand()%bot.chr[trgt].size;
    bot.chr[trgt].command[trgt2]=std::make_pair(rand()%5,rand()%(trgt+2));
    return true;
}

bool dup_seg(bot_data &bot)
{
    long trgt=rand()%bot.size;
    if (bot.chr[trgt].size==0) return false;
    if (bot.chr[trgt].size==max_pair) return false;
    long trgt2=rand()%(bot.chr[trgt].size);
    long len=rand()%(std::min(bot.chr[trgt].size-trgt2,max_pair-bot.chr[trgt].size));
    for(int i=bot.chr[trgt].size-1;i>=trgt;i--)
    {
        bot.chr[trgt].command[i+len]=bot.chr[trgt].command[i];
    }
    bot.chr[trgt].size+=len;
    return true;
}

bool del_seg(bot_data &bot)
{
    long trgt=rand()%bot.size;
    if (bot.chr[trgt].size<=1) return false;
    long trgt2=rand()%bot.chr[trgt].size;
    long trgt3=rand()%bot.chr[trgt].size;
    if (trgt2>trgt3) std::swap(trgt2,trgt3);
    if ((trgt2==0)&&(trgt3==bot.chr[trgt].size-1)) return false;
    for (int i=trgt2;i+trgt3-trgt2+1<bot.chr[trgt].size;i++)
        bot.chr[trgt].command[i]=bot.chr[trgt].command[i+trgt3-trgt2+1];
    bot.chr[trgt].size-=trgt3-trgt2+1;
    return true;
}
//bool swp_seg(bot_data &bot);

function_pointer2 bot_edit[pos_chnge]=
{
    add_chr,
    del_chr,
    dup_chr,
    add_pair,
    del_pair,
    chg_pair,
    dup_seg,
    del_seg
};

long default_mutation_rate()
{
    long ans=1;
    while (rand()%2==0)ans++;
    return ans;
}

long mutation_rate();

void tinichange(bot_data &bot)
{
    long done=mutation_rate();
    while (done>0)
    {
        int temp=rand()%prob_space;
        for(int i=0;i<pos_chnge;i++)
            if ((temp>=prob[i])&&(temp<prob[i+1]))
                if (bot_edit[i](bot)) done--;
    }
}

#endif // __BOT_MANIP_H_INCLUDED
