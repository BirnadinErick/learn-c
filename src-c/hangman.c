/*
    to get rid of warning during compilation on Windows platform.
    Bound-check functions are not supported in GNU C, thus for
    portability this is defined! Feel free to ignore this
*/
#define _CRT_SECURE_NO_WARNINGS 1

/* this will provide us some variables we need */
#include <stdlib.h>

/* this library will give us scanf and printf and some other */
#include <stdio.h>

/* for string manipulations */
#include <string.h>

/* to have true/false aliases etc. */
#include <stdbool.h>

/* for strchr to check for presence of a character in a str */
#include <mbstring.h>

/* this defines no of mistakes/health of the gamer! */
#define HEALTH 6

/*
    begin::utilis
    some function definitions for modularity and DRY principle
*/
void print_str(char *str, int len);
void print_gibbet(char *hangman, int mistakes);
/* end::utils */

int main(void)
{
    /* this heap-location will be our hangman */
    char *hangman = malloc(HEALTH + 1);
    memset(hangman, ' ', HEALTH + 1);

    /* choose a random target */
    char *target = "birnadin";

    int len = strlen(target);

    /* gamer correctly guessed indicator */
    char *guessed = malloc(len);
    memset(guessed, '_', len);

    /* buffer to hold missed characters */
    char missed[HEALTH];

    char guess;       /* current gamer guess */
    bool found;       /* trigger for misseds update */
    int mistakes = 0; /* no of mistakes */
    char *win;        /* trigger for win status */

    /* flush stdin as soon as interrupt ends */
    setvbuf(stdin, NULL, _IONBF, 0);

    do
    {

/* this will clear the console using appropriate system commands */
#if defined(linux) || defined(__unix__)
        system("clear");
#elif defined(_WIN32) || defined(_WIN64)
        system("cls");
#endif

        printf("Welcome to Hangman Game!\n");

        found = false;

        /* print mistakes and guessed indicators so far in the game */
        printf("Mistakes: ");
        if (mistakes)
        {
            print_str(missed, mistakes);
        }
        else
        {
            printf("None yet!");
        }
        printf("\n");
        print_str(guessed, len);

        printf("\n");

        /* print gibbet */
        print_gibbet(hangman, mistakes);

        printf("\nguess: ");
        do
        {
            scanf("%c", &guess);
        } while (getchar() != '\n'); /* scan stdin till newline character */

        /*
            meat of the program!
            this will iterate via target chosen and checks whether gamer
            guess was correct or not. If correct updates the guesses-indicator
            and updates found trigger.
         */
        for (size_t i = 0; i < len; ++i)
        {
            if (target[i] == guess)
            {
                found = true;
                guessed[i] = guess;
            }
        }

        /*
            if guess was wrong, then updates mistakes count and missed buffer
            for the gamer to have a reference what were wrong!
         */
        if (!found)
        {
            missed[mistakes] = guess;
            mistakes++;
        }

        win = strchr(guessed, '_'); /* CHECKS FOR WIN STATUS */

    } while (mistakes < HEALTH && win != NULL);

    if (win == NULL)
    {
        printf("\nCongrats, You Won!");
    }
    else
    {
        printf("\nOops! try again, better luck next time!");
    }

    /* free the memory allocated on the heap before exit */
    free(hangman);
    free(target);
    free(guessed);

    /* let OS know operation was successful */
    return EXIT_SUCCESS;
}

/* this will print given string to the given length limit */
void print_str(char *str, int len)
{
    for (size_t i = 0; i < len; ++i)
    {
        printf("%c", str[i]);
    }
}

/* this will print the gibbet and its current state */
void print_gibbet(char *hangman, int mistakes)
{
    switch (mistakes)
    {
    case 6:
        hangman[6] = '\\';
        break;
    case 5:
        hangman[5] = '/';
        break;
    case 4:
        hangman[4] = '\\';
        break;
    case 3:
        hangman[3] = '|';
        break;
    case 2:
        hangman[2] = '/';
        break;
    case 1:
        hangman[1] = '}', hangman[0] = '{';
        break;
    default:
        break;
    }

    printf("\t ____\n"
           "\t|    |\n"
           "\t|   %c %c\n"
           "\t|   %c%c%c\n"
           "\t|   %c %c\n"
           "\t|\n"
           "\t|\n"
           "\t----------\n",
           hangman[0], hangman[1],
           hangman[2], hangman[3], hangman[4],
           hangman[5], hangman[6]);
}