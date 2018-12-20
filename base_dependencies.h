#pragma once
// makes sure this header is included only once along the header tree (?)

using namespace std;

const int PERM_LEN = 5;
const int GUESSLIST_LEN = 10;

struct permutation {
    unsigned short digit[PERM_LEN];
    bool digit_used[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    bool is_valid = 0;
};

struct result {
    unsigned short fixed = 0;
    unsigned short moved = 0;
};

struct guessnode {
    permutation perm;
    result res;
    guessnode *next = nullptr;
    guessnode *prev = nullptr;
};

struct guesslist {
    guessnode *first = nullptr;
    guessnode *last = nullptr;
    unsigned int num = 0;
};

struct game {
    permutation base_perm;
    guesslist list;
    bool has_been_won = 0;
};

result comparePermutations(permutation target, permutation compared) {
    result comp_result;

    if (target.is_valid == false || compared.is_valid == false)
        throw "Received invalid permutation(s), cannot compare.";

    for (int i = 0; i <= 9; i++) {
        if (target.digit_used[i] == true && compared.digit_used[i] == true)
            comp_result.moved++;
    }

    for (int i = 0; i < 5; i++) {
        if (target.digit[i] == compared.digit[i]) {
            comp_result.moved--;
            comp_result.fixed++;
        }
    }

    return comp_result;
}