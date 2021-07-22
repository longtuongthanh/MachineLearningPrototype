#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <stdio.h>
#define forx(a,b,c) for(int a = b ; a <= c ; a ++)
/**
possible computation process:
AND (a,b), OR (a,b), NOT(a,-1), SHL(a,-1), SHR(a,-1)
error code:
5  - attempted delete at non-existent position
6  - attempted change at non-existent position
7  - attempted add after non-existent position
8  - invalid variable reference
9  - student bot does nothing
10 - invalid student command
bot files:
    list of command to perform
    always perform calculations left to right.
    line 2x   refers to the 2 variable, -1 refers to a, -2 refers to b
    line 2x+1 refers to calculations    -1 refers to new line.
    The previous calculations will be packaged into a new variable referred to as 0..n
    maximum of 500 pair.
    last line is the final answer.
tester:
    maximum score: 1000
*/
using namespace std;
const int bot_size=1001;
const int min_size=4;
const int bot_pop=200;
const int test_num=100;
const int no_bit=10;
const double max_mult=1.3;
int iter_no=0;
long a,b,c,temp;
double score[bot_pop];
vector <int> mem;
bool elim[bot_pop];

struct bot_data
{
    int m;
    int a[bot_size+2];
    void push_back(int x)
    {
        a[m]=x;
        m++;
    }
/*    bot_data operator = (bot_data b)
    {
        bot_data c;
        c.m=b.m;
        forx(i,0,bot_size+1)
            c.a[i]=b.a[i];
        return c;
    }*/
    void insert_pair(int x,int y,int pos)
    {
        pos=pos*2+1;
        for (int i=m-1;i>=pos;i--)
            a[i+2]=a[i];
        a[pos]=x;
        a[pos+1]=y;
    }
    void delete_pair(int pos)
    {
        pos=pos*2+1;
        forx(i,pos,m-1)
            a[i]=a[i+2];
        a[m-2]=0;
        a[m-1]=0;
        m-=2;
    }
    int chr_no()
    {
        int ans=1;
        for (int i=1;i<m;i+=2)
            if (a[i]==-1)
                ans++;
        return ans;
    }
}bot[bot_pop],new_bot;

struct test_set
{
    int a;
    int b;
    int c;
}test[test_num];

int bsort()
{
    // order-preserved
    forx(i,0,bot_pop-2)
        for (int j=bot_pop-1;j>i;j--)
            if (score[i]<score[j])
            {
                swap(score[i],score[j]);
                swap(bot[i],bot[j]);
            }
    return 0;
}

unsigned int super_secret_formula(unsigned int a,unsigned int b)
{
    return (a&b)|(~(a|b));
}

long computer(long a,long b,int command)
{
    switch (command)
    {
        case 0: return (a | b);break;
        case 1: return (a & b);break;
        case 2: return (~a);break;
        case 3: return (a << 1);break;
        case 4: return (a >> 1);break;
    }
    exit(10);
}

int scorer(int a, int b)
{
    int score=no_bit;
    forx(i,1,no_bit)
    {
        if (a%2!=b%2)
            score--;
        b=b/2;
        a=a/2;
    }
    return score;
}

int refer(int x)
{
    if (x==-1) return a;
    if (x==-2) return b;
    if (x>=int(mem.size()))exit(8);
    return mem[x];
}

void tester()
{
    cout << "Test batch no." << iter_no/1000 << (iter_no%1000)/100 << (iter_no%100)/10 << iter_no%10;
    forx(i,0,bot_pop/2-1)
    {
        if (bot[i].m==0)
            exit(9);
        int cur=refer(bot[i].a[0]);
        score[i]=0;
        /**test the bot with each test*/
        forx(j,0,test_num-1)
        {
            a=test[j].a;
            b=test[j].b;
            c=test[j].c;
            for (int k=1;k<int(bot[i].m-1);k+=2)
            {
                if (bot[i].a[k]>=0)
                    cur=computer(cur,refer(bot[i].a[k+1]),bot[i].a[k])%(1<<no_bit);
                else
                {
                    mem.push_back(cur);
                    cur=refer(bot[i].a[k+1]);
                }
            }
            score[i]+=scorer(c,cur);
        }
        /**redundancy reduction*/
        score[i]=score[i]*(max_mult-float(bot[i].m)/bot_size*(max_mult-1));
    }
}

int eliminate()
{
    forx(i,0,bot_pop-1)
        if (elim[i])
        {
            score[i]=0;
            bot[i].m=0;
        }
    return 0;
}

int number_of_var(bot_data bot)
/**
return the number of -1 at operator position (2x+1)
*/
{
    int ans=0;
    forx(i,0,bot.m/2-1)
        if (bot.a[2*i+1]==-1)
            ans++;
    return ans;
}

const int prob_add=2;
const int prob_dup=1;
const int prob_del=3;
const int prob_chg=2;
const int prob_chr=1;
const int prob_space=prob_add+prob_chg+prob_chr+prob_del+prob_dup;

bot_data add_pair(bot_data bot,int pos)
{
    bot_data a=bot;
    int var_no=2;
    forx(i,0,pos-1)
        if (a.a[i*2+1]==-1)
            var_no++;
    int x=rand()%6-1;
    if (x>1)
        a.insert_pair(x,-1,pos);
    else
    {
        if (x==-1)
            var_no++;
        a.insert_pair(x,rand() % var_no - 2,pos);
    }
    return a;
}

bot_data dup_seg(bot_data bot,int l,int r)
{
    bot_data a=new_bot;
    forx(i,0,r*2)
        a.push_back(bot.a[i]);
    forx(i,l*2+1,bot.m-1)
        a.push_back(bot.a[i]);
    return a;
}

bot_data del_pair(bot_data bot,int pos)
{
    bot_data a=bot;
    a.delete_pair(pos);
    return a;
}

bot_data del_chro(bot_data bot,int chr)
{
    bot_data a=bot;
    int i=1;
    while (chr>0)
    {
        if (a.a[i]==-1)
            chr--;
        i+=2;
    }
    while (a.a[i]!=-1)
        a.delete_pair(i/2);
    i++;
    int var_no=2+chr;
    while (i<=a.m)
    {
        if (a.a[i]>chr)
            a.a[i]--;
        if (a.a[i]==chr)
            a.a[i]=rand()%var_no-2;
        if (a.a[i+1]==-1)
            var_no++;
    }
    return a;
}

bot_data tinichange(bot_data bot)
/**
possible mutation:
add 1 pair          prob: 2/9
duplicate 1 segment prob: 1/9
delete 1 pair       prob: 3/9
change 1 pair       prob: 2/9
delete 1 chromosome prob: 1/9
*/
{
    temp=rand()%prob_space;
    /**add pair*/
    if (temp<prob_add)
    {
        if (bot.m>=bot_size-1) return tinichange(bot);
        return add_pair(bot,rand()%(bot.m/2));
    }
    /**duplicate pair*/
    else if (temp<prob_add+prob_dup)
    {
        int l=rand()%(bot.m/2);
        int r=l+1;
        while ((bot.a[r*2+1]>=0)&&(rand()%2==0))
            r++;
        if (bot.m>=bot_size-1-(r-l)*2) return tinichange(bot);
        return dup_seg(bot,l,r);
    }
    /**delete pair*/
    else if (temp<prob_add+prob_dup+prob_del)
    {
        if (bot.m<=min_size)
            return tinichange(bot);
        return del_pair(bot,rand()%(bot.m/2));
    }
    /**change pair*/
    else if (temp<prob_add+prob_dup+prob_del+prob_chg)
    {
        temp=rand()%(bot.m/2);
        return add_pair(del_pair(bot,temp),temp);
    }
    else
    /**delete chromosome*/
    {
        int chr=number_of_var(bot);
        if (chr<=2) return tinichange(bot);
        temp=rand()%chr;
        return del_chro(bot,temp);
    }
    return bot;
}

void rebuilder()
{
    bsort();
    cout<< "   Max score: " << score[0]<<'\n';
    eliminate();
    int n=0;
    for (int i=bot_pop-1;i>=0;i--)
        if (score[i]>0)
        {
            score[bot_pop-1-n]=score[i];
            bot[bot_pop-1-n]=bot[i];
            score[i]=0;
            n++;
        }
    n--;
    forx(i,0,bot_pop/2-1)
        bot[i]=tinichange(bot[bot_pop-1-n+i%n]);
}

int elimination_pattern_init()
{
    forx(i,0,bot_pop/2-1)
        {
            temp=rand()%200;
            if (i>temp)
                elim[i]=true;
            else
                elim[i]=false;
        }
    forx(i,bot_pop/2,bot_pop-1)
        elim[i]=!elim[i-bot_pop/2];
    return 0;
}

int initializer()
{
    srand(time(0));
    forx(i,0,bot_pop/2-1)
    {
        a=rand()%(1<<(no_bit-1));
        b=rand()%(1<<(no_bit-1));
        c=super_secret_formula(a,b)%1024;
        test[i].a=a;
        test[i].b=b;
        test[i].c=c;
    }
    iter_no=1;
    for (int i=0;i<bot_pop/2;i++)
    {
        temp=rand()%2-2;
        bot[i].push_back(temp);
        int m=rand()%(bot_size);
        int var_no=2;
        for (int j = 0; j < m/2; j++)
        {
            temp = rand() % 6 - 1;
            bot[i].push_back(temp);
            if (temp>1)
                bot[i].push_back(-1);
            else
            {
                if (temp==-1)
                    var_no++;
                temp = rand() % var_no - 2;
                bot[i].push_back(temp);
            }
        }
    }
    elimination_pattern_init();
    return 0;
}

int main()
{
    initializer();
    tester();
    rebuilder();
    tester();
    return 0;
}
