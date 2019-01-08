#pragma once

#include <ctime>
#include <stdlib.h>
#include "base_dependencies.h"

/*
Citeste!
EasyAI este functia pentru gasirea permutarii intr-un mod 'usor'
A fost facuta cu ideea ca va fi intr-un while loop, deci va putea fi apelata de n ori
Variabilele globale sunt puse pentru a ma ajuta, nu vor fi folosite neaparat in joc.
*/

//Global stuff

void ChangeAllDigits(permutation &p) //Function to switch all digits if answer is 0m 0f
{
    if(p.is_valid == true)
    {
        for(int i = 0; i < 10; i++)
        {
            if(p.digit_used[i] == 0)
                p.digit_used[i] = 1;
            else p.digit_used[i] = 0;
        }
        for(int j = 0; j < 5; j++)
            for(int k = 0; k < 10; k++)
        {
            if(p.digit[j] != k && p.digit_used[k] == 1)
            {   p.digit[j] = k;
                break;
            }
        }
    }
}

permutation Shuffle(permutation &DefaultPermutation) //Shuffle at random
{
    for (int k = 0; k < 5; k++)
    {
        int r = k + rand() % (5 - k);
        swap(DefaultPermutation.digit[k], DefaultPermutation.digit[r]);
    }
    return DefaultPermutation;
}

void EasyAI(game_panel &game)//The main AI function
{
    permutation InputPerm = game.base_perm;

    guessnode *CurrentPermutation;
    permutation DefaultPerm = RandomPermutationGenerator();
    if(game.list.num == 0)//Creeaza primul element din stiva
    {
        CurrentPermutation = makeGuess(InputPerm, DefaultPerm);
        guesslistPush(game.list, CurrentPermutation);
    }
    else
    {
        //Cazuri favorabile
        //Cauta in functie de cel mai recent element din stiva
        if(game.list.first->res.moved + game.list.first->res.fixed == 5)
        {
            CurrentPermutation = makeGuess(Shuffle(DefaultPerm), DefaultPerm);
            guesslistPush(game.list, CurrentPermutation);
        }
        else if(game.list.first->res.moved + game.list.first->res.fixed == 0)
        {
            ChangeAllDigits(DefaultPerm);
            CurrentPermutation = makeGuess(InputPerm, DefaultPerm);
            guesslistPush(game.list, CurrentPermutation);
        }
        //Cazuri nefavorabile
        else
        {
            DefaultPerm = RandomPermutationGenerator();
            CurrentPermutation = makeGuess(InputPerm, DefaultPerm);
            guesslistPush(game.list, CurrentPermutation);
        }
    }
    //Gasirea permutarii
    if(CurrentPermutation->res.fixed == 5)//Conditia de oprire a jocului, modifica cu ce trebuie.
        game.has_been_won = true;
}