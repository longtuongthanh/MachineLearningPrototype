#include <vector>
#include <algorithm>
#ifndef __AI_H_INCLUDED
#define __AI_H_INCLUDED


#ifndef __FUNCTION_POINTER_INCLUDED
#define __FUNCTION_POINTER_INCLUDED

typedef long (*function_pointer) (long,long);

#endif // __FUNCTION_POINTER_INCLUDED

template <int bot_size, class input, class output>
class bot_data
{
    public:
    std::vector<long>data;
    double score;
    bot_data()
    {
        data.resize(bot_size);
        for (long i=bot_size;i--;)
            data[i]=rand();
    }
    bot_data(const bot_data &x)
    {
        data.resize(bot_size);
        for (long i=bot_size(x);i--;)
            data[i]=x.data[i];
    }
};

template <int bot_size, class input, class output>
output run (input&,bot_data<bot_size,input,output>&);

template <class output>
double score(output &bot_output, output &correct);

template <int bot_size, class input, class output>
inline double scorer (input &x,output &correct, bot_data<bot_size,input,output> &z)
{
    return score(run(x,z),correct);
}

template <
int bot_size,
int eco_size,
class input,
class output>
class bot_ecology
{
    std::vector<bot_data<bot_size,input,output> > bots;
public:
    bot_ecology()
    {
        bots.resize(eco_size);
    }
    void test()
    {
        for ()
    }
};

#endif // __AI_H_INCLUDED
