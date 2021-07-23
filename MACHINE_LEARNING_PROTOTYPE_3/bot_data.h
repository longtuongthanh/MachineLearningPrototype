#ifndef __BOT_DATA_H_INCLUDED
#define __BOT_DATA_H_INCLUDED

#include <utility>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include "bit_computation.h"
#include "constlib.h"
#include "bot_catcher.h"

typedef std::pair <long,long> instruction;
typedef std::vector <instruction> instruction_set;
using std::cout;
using std::endl;

long refer[max_chromosome+2];

struct chromosome
{
    long begin;
    instruction command[max_pair];
    long size;

    long run()
    {
        long ans=refer[begin];
        for(int i=0;i<size;i++)
            ans=functions[command[i].first](ans,refer[command[i].second]);
        return ans;
    }

    void insert(instruction x)
    {
        command[size]=x;
        size++;
    }

    chromosome()
    {
        begin=0;
        size=0;
        for(int i=0;i<max_pair;i++)
            command[i]=instruction();
    }

    chromosome(int x,int y)
    {
        begin=rand()%y;
        size=x;
        for (int i=0;i<x;i++)
            command[i]=std::make_pair(rand()%5,rand()%y);
    }

    chromosome(const chromosome &x)
    {
        begin=x.begin;
        size=x.size;
        for(int i=0;i<size;i++)
            command[i]=x.command[i];
    }

    void operator = (chromosome x)
    {
        size=x.size;
        begin=x.begin;
        for(int i=0;i<size;i++)
            command[i]=x.command[i];
    }

    bool operator == (chromosome x)
    {
        if (size!=x.size) return false;
        if (begin!=x.begin) return false;
        for(int i=0;i<size;i++)
            if (command[i]!=x.command[i])
                return false;
        return true;
    }

    void printData()
    {
        cout<<'\t'<<begin<<endl;
        for (int i=0; i<size; i++)
            cout<<'\t'<<command[i].first<<' '<<command[i].second<<endl;
    }
};

struct bot_data
{
    long size;
    chromosome chr[max_chromosome];
    double score;
    long raw_score;

    long run(std::pair <long,long> input)
    {
        for(int i=0;i<max_chromosome;i++)
            refer[i]=0;
        refer[0]=input.first;
        refer[1]=input.second;
        for(int i=0;i<size;i++)
            refer[i+2]=chr[i].run();
        return refer[size+1];
    }

    void insert(chromosome x)
    {
        chr[size]=x;
        size++;
    }

    long memory()
    {
        int ans=0;
        for(int i=0;i<size;i++)
            ans+=chr[i].size;
        return ans;
    }

    bot_data()
    {
        size=0;
        score=0;
        raw_score=0;
        for(int i=0;i<max_chromosome;i++)
            chr[i]=chromosome();
    }

    bot_data(int x)
    {
        size=x;
        for(int i=0;i<x;i++)
            chr[i]=chromosome(rand()%max_pair+1,i+2);
        score=0;
        raw_score=0;
    }

    bot_data(const bot_data &x)
    {
        size=x.size;
        for(int i=0;i<size;i++)
            chr[i]=x.chr[i];
        score=x.score;
        raw_score=x.raw_score;
    }

    void operator = (const bot_data &x)
    {
        size=x.size;
        for(int i=0;i<size;i++)
            chr[i]=x.chr[i];
        score=x.score;
        raw_score=x.raw_score;
    }

    bool operator < (bot_data &x)
    {
        return (score<x.score);
    }

    bool operator ==(bot_data &x)
    {
        if (size!=x.size) return false;
        for (int i=0;i<size;i++)
            if (chr[i]==x.chr[i])
                return false;
        return true;
    }
    void printData()
    {
        for (int i = 0; i<size; i++)
        {
            cout<<"Reg "<<i<<":\n";

            chr[i].printData();
        }
    }
};

#endif // __BOT_DATA_H_INCLUDED
