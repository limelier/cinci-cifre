#include <ctime>
#include <stdlib.h>
#include "base_dependencies.h"

permutation RandomPermutationGenerator()
{
    permutation p;
    int CurrentDigit;
    int firstDigit = rand() % 9+1;
    p.digit_used[firstDigit]++;
    p.digit[0]=firstDigit;
    // cout<<"First digit is "<<firstDigit<<endl;
    int i = 1;
    bool ok = false;
    do{
            // cout<<"Creating the digits \n";
        do{
            ok = false;
            CurrentDigit = rand()%10;
            // cout<<CurrentDigit<<endl;
            if(p.digit_used[CurrentDigit]==0)
                {
                    // cout<<"Found a good digit, moving to the next one \n";
                    p.digit_used[CurrentDigit]++;
                    p.digit[i]=CurrentDigit;
                    ok = true;
                }
            // cout<<CurrentDigit<<" was already used before, retrying... \n";
        } while(not ok);
        i++;
    } while(i<5);
    // cout<<"Found a 5 digit number, printing it... \n";
    // for(int i=0;i<5;i++)
    //     cout<<p.digit[i];
    p.is_valid = 1;
    return p;
}