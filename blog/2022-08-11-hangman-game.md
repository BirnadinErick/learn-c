# A Simple Hangman Game

## Overview

When I first started, making of HANGMAN GAME was the first challenge I put on to me. It was fun and
taught me many things I wanted to know and better ace it. Hope it does the same.

We will simply create a game that ressembles good-old Hangman's core-concept. At the end of this
tutorial/assignment you would be able to:

    1. Display text to the stdout
    2. Take input from stdin
    3. Compare characters
    4. Take decesions using conditionals
    5. Allocate(De-) memory in heap
    6. Modularity via functions

:::danger Not so good
This implementation of the HANGMAN Game won't be the efficient implementation
in C you can get. My sole goal was to show you some C features, so this
implementation includes as much variety of C core-features as possible.
This might made the implementation *clumsy* and *memory-hog*!
:::

:::info Adoption
Following implementation is adopted from [saroj22322's-hangman](https://gist.github.com/saroj22322/aa2f0849f33736395544c2d341ab3722)
you can find in the GitHub and few techniques from my first hangman implementation.
:::
<!-- truncate -->

## Building Blocks

Let's build the game step-by-step. Create a skeleton C file like this.
Later we will discuss what each one is, but for now headthrough!

:::tip Verbose Comments
Feel free to remove comments, they are here for your clarrification! I will be bit verbose
via comments to guide you within the programs. So feel free to remove them!
:::

```c title=hangman.c
/*
    to get rid of warning during compilation on Windows platform.
    Bound-check functions are not supported in GNU C, thus for
    portability this is defined! Feel free to ignore this
*/
#define _CRT_SECURE_NO_WARNINGS 1

/* this defines no of mistakes/health of the gamer! */
#define HEALTH 6

/* entry point for our game */
int main(void)
{
    /*
        from stdlib.h, tells OS exit state is OK.
        You can also return 0 to indicate OK state,
        but this is much schemantically pretty :)

        Any non-zero value will indicate OS exit state is failure
    */
    return EXIT_SUCCESS;
}
```

### Output to Stdout

First off, let's display a welcome banner to the gamer 🎮. C already provide us some
convienient. We just need to use include them in our source text and use them.

Let's include `stdio.h` which will provide neccessary functions from the `libc`.

Add line `#include <stdio.h>` after first *include*-statement. This is will include
`printf` definitions and some other into our source text during preprocessing time.

Then after `{` of `main` add line `printf("Welcome to The Hangman Game!\n")`.
This line tells our CPU to display the message we provided to stdout of current runtime.

At this point, your source file should look something like this...

```c hangman-game.c
#include <stdlib.h>

/* provide some functions for IO ops */
#include <stdio.h>

int main(void)
{
    /* output welcome banner to gamer */
    printf("Welcome to The Hangman Game!\n");

    return EXIT_SUCCESS;
}
```

### Input from stdin

Next, let's grab our gamer's name and print a *hello*-message back to the gamer.

First define a buffer(simply an array) `char gamer[25]` to hold the name.
We will limit the name of the gamer to 25 characters(hope this is enough✌). Then
using [`scanf`](https://www.tutorialspoint.com/c_standard_library/c_function_scanf.htm)
provided by `libc`, we will read stdin into out buffer. At this point your source file
would look like this...

```c hangman-game.c
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    printf("Welcome to The Hangman Game!\n");

    /* get name of the gamer */
    
    printf("Please input your name, within 25 characters without any spaces: ");

    /*
        this array will act as a buffer for the gamer's name
        when OS flushes stdin to our program. The length is specified to
        mitigate an attack vector called `buffer overflow`. You can give
        any length but limit exists as par platforms.
     */
    char gamer[25];

    /*
        this line actually does the job we wanted. this will save any content
        of stdin to the given buffers.

        params:-
            "%24s": is a control string/format string
            gamer: buffer we specified

     */
    scanf("%24s", gamer);

    /* outputs what we got to stdout */
    printf("Hello, %s!\n", gamer);

    return EXIT_SUCCESS;
}
```

:::danger Buffer Overflow/Overrun
If we don't add `24` in between `%` and `s` in the first argument, then any extra
characters may be read and may lead to Buffer Overflow/Overrun. This is a
old-but-gold vulnerability you may find in amatuer programs. So, we specify `24`
to just read 24 characters and leave the rest.
:::

:::tip Why 24?
Find out why `24` not `25` characters to be read! For head start, search how
***`c-string`*** works.
:::

:::info Bound-checked functions
Microsoft wrote some extensions to ISO C std, and submitted a standardization
request to C Committe, it is published as
[TR 24731](https://stackoverflow.com/questions/372980/do-you-use-the-tr-24731-safe-functions?noredirect=1&lq=1)
*but* GNU C won't implement it(yet). So, these safety functions are available in
Windows environments and not that much portable
:::

### Comparing two characters

Another thing we would want to do in our game is compare two character and verify
gamer guessed correctly. Let's just compare two characters.

```c title=compare-two-chars.c
char c = 'c';
char a = 'a';

if (c == a)
{
    printf("%c is equal to %c", c, a);
}
else
{
    printf("%c is not equal to %c", c, a);
}
```

This would print they are not equal. Indeed they are not!

#### Underthehood 🤨

Under the hood, `char` is just an `unsigned int` representing each english
alphabets. The way C knows what value represents what alphabet is by looking up in
the [*ASCII TABLE*](https://www.asciitable.com/) and tell the OS, in this
context, these `unsigned int`s represents alphabets, not the arabic numbers.

So, by comparing the `unsigned int` value, C runtime knows, whether `c` equals to
or not equals to `a`!

### Memory allocatin in heap

> Prerequisites:
>
>   1. [Pointers](https://www.tutorialspoint.com/cprogramming/c_pointers.htm)
>   2. [Heap & Stack](https://www.guru99.com/stack-vs-heap.html)

Normally when you declare a variable/constant in C, you allocate a piece of memory
large enough to hold the data is allocated in the *stack/heap*.

> e.g. int i;

`i` , here, is initialized to a garbage data but in the *stack* living. Allocation
in *stack* is ideal and actually recommended for small amounts of data, as retireval
from the *stack* is much faster than from the *heap*.

But allocation in *heap* is recommended for large amount of data
(e.g. strings, arrays with huge elements etc.) as OS allocates more *heap* space
than *stack* size for a *user-land* mode.

In C, *heap* allocation is done via [`malloc`](https://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm)
or [`calloc`](https://www.tutorialspoint.com/c_standard_library/c_function_calloc.htm).
Since *heap* is not
cleaned after function *epilogue/prologue*(assembly jargon!), we need to free the
memory piece we requested when it is appropriate. Failure to do so, is known as
`Memory Leak` and eventually our program will endavour big chunks of memory as
it requests more memory!

#### Allocation

```c
char* str = malloc(size_needed);
```

`malloc` will return a pointer to the first memory block allocated by the OS with
width as indicated by the type defined and bounds to the `size_needed`.

#### Deallocation

```c
free(str)
```

:::danger
Scope should be considered when using identifiers.
:::

## Stiching together

Alright, enough of building-blocks. Let's get this done with 😎!

Here is our game plan!
    1. Include neccessary libraries we *think* we need
    2. Define some utility functions
    3. Allocate and set neccessary memory space in both *heap* and *stack*
    4. Print welcome banner
    5. Tell gamer about their game status(mistakes, gibbet, to-be-guessed)
    6. Ask for their guess
    7. Check whether the guess was right
    8. Update the game status as neccessary
    9.  Implement the game loop

🥱 quite a handful of tasks, let's go.

### 1. Include neccessary libraries we *think* we need

Make sure you include these libraries at the very top of the
source text file. You can omit the comments,
they are there for your clarification!

```c title=hangman.c
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
```

### 2. Define some utility functions

We will use these sattements in few places exactly as same,
so I decided to extract them away to embose DRY.

`print_str` function takes a pointer to a string and an int
indicating amount of characters from the beggining of the string
we need to print to the *stdout*.

`print_gibbet` function takes str `hangman` and `mistakes`
so far and prints the gibbet given the state of the game.
It utilizes `switch` statement to appoint body parts
to str `hangman` and stimuates hanging animation(🙄).

```c title=hangman.c
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
```

### 3. Allocate neccessary memory space in both *heap* and *stack*

> These statements go inside our `main` function!

```c title=hangman.c
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

```

### 4. Print welcome banner

This is dead simple,
just add `printf("Welcome to Hangman Game!\n");`. Feel free
to customize the message!

### 5. Tell gamer about their game status(mistakes, gibbet, to-be-guessed)

These will print the game status of the gamer at the time of
execution!

```c title=hangman.c
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
print_str(guessed, len);

/* print gibbet */
print_gibbet(hangman, mistakes);
```

### 6. Ask for their guess

```c title=hangman.c
printf("\nguess: ");
do
{
    scanf("%c", &guess);
} while (getchar() != '\n'); /* scan stdin till newline character */
```

### 7. Check whether the guess was right

```c title=hangman.c
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
```

### 8. Update the game status as neccessary

```c title=hangman.c
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
```

### 9.  Implement the game loop

```c title=hangman.c
do {
    /* 
        the game logic we devepoed from step 4. to step 8. 
    */
} while (mistakes < HEALTH && win != NULL);
```

## Finally, with few adjustments and few misselleneous enhancements

```c title=hangman.c
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

/* to check to _ in guessed to determine win status */
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
```

## Compilation and Gameplay

It is recommended to compile with `-std=c17` and source text
is platform independent. Example command to compile with `clang-14` in windows
is as follows:

```bash
clang -std=c17 -o hman.exe .\hangman.c
```

That's it, enjoy the game.

## Homework

We hardcoded the guess target. But try to get the guess from array of names
randomly at the runtime.

### Hints

    1. Use `rand` from `stdlib.h`
    2. Get names from a local text-file

That's it, it's been a long run, see with another assignment! Till then,
this is me the [BE](https://twitter.com/birnadin_e) signing off 👋. 💖 from Jaffna!
