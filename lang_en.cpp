#include "lang.h"

const char *lang_en[END_TRANSLATIONS] = {
    // GAME_TITLE,
    "Five digits",
    // BTN_PLAY,
    "Play",
    // BTN_SETTINGS,
    "Settings",
    // BTN_HELP,
    "Help",
    // BTN_QUIT,
    "Quit",

    // PLAY_TEXT,
    "Which mode would you like to play?",
    // BTN_SINGLEPLAYER,
    "Singleplayer",
    // BTN_SINGLEPLAYER_PLUS,
    "Singleplayer plus help",
    // BTN_MULTIPLAYER,
    "Multiplayer",
    // BTN_AI,
    "AI demonstration",

    // SETTINGS_TEXT,
    "Settings only apply after a restart.",
    // SETTING_LANG,
    "Language",
    // SETTING_MUSIC,
    "Music",
    // SETTING_SOUND,
    "Sound",

    // INFO,
    "Welcome to \"Five digits\"!\n"
    "\n"
    "Controls: number keys for the input panel, the mouse otherwise. \n"
    "The DELETE key always goes back to the menu. \n"
    "\n"
    "Singleplayer: the computer will give you a random five digit number, \n"
    "with each digit unique. You then get to make guesses, and will be \n"
    "told how many of the digits you guessed were 'fixed', meaning that \n"
    "they were correct and in the right place, or 'moved', meaning that \n"
    "they were correct, but in the wrong place. The game ends when you've \n"
    "guessed right.\n"
    "\n"
    "Singleplayer with help: Similar, but someone else gets to pick your \n"
    "target for you. Don't look!\n"
    "\n"
    "Multiplayer: Singleplayer with help, but for two people! The blue \n"
    "game panel is the active one, that is currently receiving inputs. \n"
    "\n"
    "AI demonstration: Give the AI a permutation and watch it struggle.\n"
    "\n"
    "\n"
    "Programming by Iacobescu Tudor and Savin Rares. \n",

    // LABEL1,
    "fixed",
    // LABEL2,
    "moved",

    // INPUT_ERR_POPUP,
    "A permutation is not allowed to contain the\n"
    "same digit multiple times. Please try again.\n"
    "\n"
    "Press any key to continue.",

    // SP_WIN_POPUP,
    "Congratulations, you won!\n"
    "Press any key to return to the menu.",
    // MP_TIE_POPUP,
    "The game is a tie!\n"
    "Press any key to return to the menu.",
    // MP_P1_WIN_POPUP,
    "Player 1 wins!\n"
    "Press any key to return to the menu.",
    // MP_P2_WIN_POPUP,
    "Player 2 wins!\n"
    "Press any key to return to the menu."

    // END_TRANSLATIONS
};