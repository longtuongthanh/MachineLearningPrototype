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
  int difficulty = 10;
  int stagnate = 0;
  int score = 0;
    while (stagnate < stagnate_to_print)
    {
        temp=bots.gen_performance();
        /*
        try
        {
            if (iter_no==0) throw 1;
            if (20000/iter_no==0) throw 1;
            if (iter_no%(20000/iter_no)==0)
            {
                bots.elim.renew();
                bots.tester.renew(difficulty);
            }
        }
        catch(int x)
        {//*/
            bots.elim.renew();
            bots.tester.renew(difficulty);
        //}//*/
        //if (temp>max_score) {max_score=temp;if (max_score>500+pos_mutate*100) pos_mutate++;}
        int prevscore = score;
        score = bots.raw_performance();
        if (bots.raw_performance() >= test_num * 9.8 && difficulty < 1e9)
        {

                difficulty*=2;
                bots.elim.renew();
                bots.tester.renew(difficulty);

        }
        if (difficulty > 1e9 && prevscore == score)
        {
            stagnate++;
        }
        else stagnate = 0;
        last_ans=temp;
        cout<<iter_no<<" ("<<difficulty<<") : "<<score << "  " <<last_ans<<'\n';
        bots.next_gen();
        iter_no++;
    }
    bots.printBestBot();
    return 0;
}
