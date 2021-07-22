#include <iostream>
#include <ctime>
#include <cstdlib>
#include <exception>
//#include "constlib.h"
//#include "bit_computation.h"
//#include "bot_data.h"
//#include "test.h"
#include "bot_ecology.h"
#include <cstdio>

using namespace std;

//constexpr long i(){return 0;}

bot_ecology bots;
long iter_no=1;
double last_ans,temp;
long same_no=0;
long pos_mutate=4;
long max_score=0;

long mutation_rate()
{
    long done=1;
    while (rand()%pos_mutate<(pos_mutate-1))done++;
    return done;
}

int main()
{
    srand(unsigned(time(0)));
  //  freopen("log.txt","w",stdout);
    while (true)
    {
        temp=bots.gen_performance();
        try
        {
            if (iter_no==0) throw 1;
            if (20000/iter_no==0) throw 1;
            if (iter_no%(20000/iter_no)==0)
            {
                bots.elim.renew();
                bots.tester.renew();
            }
        }
        catch(int x)
        {
            bots.elim.renew();
            bots.tester.renew();
        }
        //if (temp>max_score) {max_score=temp;if (max_score>500+pos_mutate*100) pos_mutate++;}
        last_ans=temp;
        cout<<iter_no<<" : "<<bots.raw_performance() << "  " <<last_ans<<'\n';
        bots.next_gen();
        iter_no++;
    }
    return 0;
}
