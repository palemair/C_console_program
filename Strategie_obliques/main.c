#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <argz.h>
#include <locale.h>
#include <time.h>
#include <wchar.h>

#define MAX 300

/* Print the date + a sentence from brian eno Oblique strategies */


char* getnow (void);

char* getnow (void)
{
    char buffer[100];
    time_t currtime = time (NULL);
    struct tm* timer;

    if (setlocale (LC_ALL, "") == NULL)
    {
        perror ("setlocale");
        return NULL;
    }

    timer = localtime (&currtime);
    strftime (buffer, sizeof (buffer), " %A %2e %B", timer);

    return (strdup (buffer));
}

int main ()
{

    if (setlocale (LC_ALL, "") == NULL)
    {
        perror ("setlocale");
        return EXIT_FAILURE;
    }

    static FILE* fp;
    fp = fopen ("/usr/local/src/C_console_program/Strategie_obliques/strat.txt", "r");
    if (fp == NULL)
    {
        perror ("fopen");
        return (EXIT_FAILURE);
    }

    char** ptr = NULL;

    char* line = NULL;
    size_t n = 0;
    ssize_t read;
    size_t i = 0;
    char* pt = NULL;

    while ((read = getline (&line, &n, fp)) != -1)
    {
        ptr = reallocarray (ptr, i + 2, sizeof (*ptr));
        pt = line;
        while (*pt != '\n') pt++;
        *pt = '\0';
        ptr[i] = strdupa (line);
        if (ptr == NULL)
        {
            perror ("reallocarray");
            free (ptr);
            fclose (fp);
        }
        i++;
    }
    ptr[i] = NULL;
    free (line);

    srand (time (NULL));
    unsigned int alea = rand () % i;

    /* printf("%u\n",alea); */

    char* date = getnow ();
    wchar_t datews[200];
    wchar_t ws[150];

    if (mbstowcs (ws, ptr[alea], 200 - 1) == (size_t) -1)
    {
        perror ("mbstowcs");
        return EXIT_FAILURE;
    }

    if (mbstowcs (datews, date, 200 - 1) == (size_t) -1)
    {
        perror ("mbstowcs");
        return EXIT_FAILURE;
    }
    free (date);

    wcscat (datews, L" : ");
    wcscat (datews, ws);

    for (int x = 0; x < (int) wcslen (datews) + 3; x++) putchar ('~');
    putchar ('\n');
    printf ("|%ls |\n", datews);
    for (int x = 0; x < (int) wcslen (datews) + 3; x++) putchar ('~');
    putchar ('\n');
    free (ptr);
    fclose (fp);

    return (EXIT_SUCCESS);
}
