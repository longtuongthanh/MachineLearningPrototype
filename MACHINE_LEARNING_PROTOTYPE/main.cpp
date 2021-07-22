#include <iostream>
#include <time.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#define forx(a,b,c) for(int a = b ; a <= c ; a ++)

using namespace std;
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
const int bot_size=100;
const int max_iter=1e6/bot_size;
int change_tendancy;
struct bot_data
{
    int n;
    int m;
    int a[bot_size+2];
    void push_back(int x)
    {
        a[m]=x;
        m++;
    }
}bot[200];
struct test_set
{
    int a;
    int b;
    int c;
}test[100];
int iter_no,temp,n;
unsigned int a,b,c,score[200];
vector <int> mem;
bool elim[200];
const int base_newbot=2;

int bsort()
// order-preserved
{
    forx(i,0,198)
        for (int j=199;j>i;j--)
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
    int score=10;
    forx(i,1,10)
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

int tester()
{
    cout << "Test batch no." << iter_no/100 << (iter_no%100)/10 << iter_no%10;
    forx(i,0,99)
    {
/** load bot i*/
        if (bot[i].m==0) exit(9);
        int cur=refer(bot[i].a[0]);
        score[i]=0;
        forx(j,0,99)
        {
            a=test[j].a;
            b=test[j].b;
            c=test[j].c;
            for (int k=1;k<int(bot[i].m-1);k+=2)
            {
                if (bot[i].a[k]>=0)
                    cur=computer(cur,refer(bot[i].a[k+1]),bot[i].a[k])%1024;
                else
                {
                    mem.push_back(cur);
                    cur=refer(bot[i].a[k+1]);
                }
            }
            score[i]+=scorer(c,cur);
        }
    }
    return 0;
}

int eliminate()
{
    forx(i,0,199)
        if (elim[i])
        {
            score[i]=0;
            bot[i].n=0;
            bot[i].m=0;
        }
    return 0;
}

int number_of_var(bot_data bot,int n)
/**
return the number of -1 at operator position (2x+1)
*/
{
    int ans=0;
    if (int(bot.m)<2*n+1)
        exit(7);
    forx(i,0,n-1)
        if (bot.a[2*i+1]==-1)
            ans++;
    return ans;
}

bot_data tinichange(bot_data bot)
/**
possible mutation:
add 1 pair      prob:   iter_no/(max_iter*1.5)
delete 1 pair   prob:   (max_iter-iter_no)/(max_iter*1.5)
change 1 pair   prob:   1/3
*/
{
  while (rand()%(iter_no*10)!=0)
  {
    temp=rand()%(max_iter*6/5);
    if (temp<max_iter-iter_no)
    {
        if (bot.n<2) continue;
        temp=rand()%bot.n+1;
        if (temp*2>int(bot.m)) exit(5);
        forx(i,temp*2-1,int(bot.m)-3)
            bot.a[i]=bot.a[i+2];
        bot.m--;
        bot.m--;
        bot.n--;
    }
    else if (temp<max_iter)
    {
        if (bot.n>24) continue;
        int pos=rand()%bot.n;
        if (pos*2+1>int(bot.m))
            exit(7);
        int var_no=number_of_var(bot,pos)+2;
        temp=rand()%6-1;
        bot.m++;
        bot.m++;
        for (int i=int(bot.m)-3;i>=pos*2+1;i--)
            bot.a[i+2]=bot.a[i];
        bot.a[pos*2+2]=temp;
        if (temp>1)
            bot.a[pos*2+2]=-1;
        else
        {
            if (temp==-1)
                var_no++;
            temp = rand() % var_no - 2;
            bot.a[pos*2+2]=temp;
        }
        bot.n++;
    }
    else
    {
        int pos=rand()%bot.n+1;
        if (pos*2>int(bot.m))
            exit(6);
        int var_no=number_of_var(bot,pos)+2;
        temp=rand()%6-1;
        bot.a[pos*2-1]=temp;
        if (temp>1)
            bot.a[pos*2]=-1;
        else
        {
            if (temp==-1)
                var_no++;
            temp = rand() % var_no - 2;
            bot.a[pos*2]=temp;
        }
    }
  }
  return bot;
}

int rebuilder()
{
    bsort();
    cout<< "   Max score: " << score[0]<<'\n';
    eliminate();
    n=0;
    for (int i=199;i>=0;i--)
        if (score[i]>0)
        {
            score[199-n]=score[i];
            bot[199-n]=bot[i];
            score[i]=0;
            n++;
        }
    n--;
    forx(i,0,99-base_newbot)
        bot[i]=tinichange(bot[199-n+i%n]);
    forx(i,99-base_newbot,99)
    {
        bot[i].m=0;
        temp=rand()%2-2;
        bot[i].m++;
        bot[i].a[bot[i].m-1]=temp;
        int n=rand()%(bot_size/2)+1;
        bot[i].n=n;
        int var_no=2;
        for (int j = 0; j < n; j++)
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
    return 0;
}

int elimination_pattern_init()
{
    bool check=true;
    int x=0;
    forx(i,0,199)
        {
            temp=rand()%200;
            if (i>temp)
                elim[i]=true;
            else
                elim[i]=false;
        }
    while (check)
    {
        x=0;
        forx(i,0,199)
            if (elim[i])
                x++;
        if (x>100)
            check=false;
        else
            elim[rand()%200]=true;
    }
    return 0;
}

int initializer()
{
    srand(time(0));
    forx(i,0,99)
    {
        a=rand()%512;
        b=rand()%512;
        c=super_secret_formula(a,b)%1024;
        test[i].a=a;
        test[i].b=b;
        test[i].c=c;
    }
    iter_no=1;
    for (int i=0;i<100;i++)
    {
        temp=rand()%2-2;
        bot[i].push_back(temp);
        int n=rand()%(bot_size/2)+1;
        bot[i].n=n;
        int var_no=2;
        for (int j = 0; j < n; j++)
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
    while (true)
    {
        tester();
        rebuilder();
        iter_no++;
    }
    return 0;
}
