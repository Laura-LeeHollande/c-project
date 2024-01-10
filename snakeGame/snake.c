#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int i, j, height = 30, width = 30;
int gameover, score;
int x, y, fruitx, fruity, flag;

/* -------------------------------------------------------------------------- */
/*                            FRUITS POSITION START                           */
/* -------------------------------------------------------------------------- */
void setup()
{
    gameover = 0;

    // Stores height and
    x = height / 2;
    y = width / 2;

label1:
    fruitx = rand() % 20;
    if (fruitx == 0)
    {
        goto label1;
    }

label2:
    fruity = rand() % 20;
    if (fruity == 0)
    {
        goto label2;
    }

    score = 0;
}
/* -------------------------------------------------------------------------- */
/*                             FRUITS POSITION END                            */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                            DRAW BOUNDARIES START                           */
/* -------------------------------------------------------------------------- */
/* --------------------------------- OUTPUT --------------------------------- */
// ##############################
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// #                            #
// ##############################
void draw()
{
    clear();
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                printf("#");
            }
            else
            {
                if (i == x && j == y)
                    printf("0");
                else if (i == fruitx && j == fruity)
                    printf("*");
                else
                    printf(" ");
            }
        }
        printf("\n"); // Déplacez cette ligne à l'extérieur de la boucle interne
    }

    printf("score = %d", score);
    printf("\n");
    printf("Press X to quit the game");
    refresh();
}
/* -------------------------------------------------------------------------- */
/*                             DRAW BOUNDARIES END                            */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                         SET UP KEYBORD INPUT START                         */
/* -------------------------------------------------------------------------- */
void input()
{
    int ch = getch(); // Utilise getch() de ncurses au lieu de getche()

    switch (ch)
    {
    case 'z':
        flag = 1;
        break;
    case 'q':
        flag = 2;
        break;
    case 's':
        flag = 3;
        break;
    case 'd':
        flag = 4;
        break;
    case 'x':
        gameover = x;
        break;
    }
}
/* -------------------------------------------------------------------------- */
/*                          SET UP KEYBORD INPUT END                          */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                         MOVEMENT OF THE SNAKE START                        */
/* -------------------------------------------------------------------------- */
void logic()
{
    usleep(10000);
    switch (flag)
    {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }

    // If the game is
    if (x < 0 || x > height || y < 0 || y > width)
    {
        gameover = 1;
    }

    // If snake reach the fruit
    if (x == fruitx && y == fruity)
    {
    label3:
        fruitx = rand() % 20;
        if (fruitx == 0)
        {
            goto label3;
        }
    label4:
        fruity = rand() % 20;
        if (fruity == 0)
        {
            goto label4;
        }
        score += 10;
    }
}
/* -------------------------------------------------------------------------- */
/*                          MOVEMENT OF THE SNAKE END                         */
/* -------------------------------------------------------------------------- */

// Driver code
int main()
{
    int m, n;

    initscr(); // Initialiser l'environnement ncurses
    clear();   // Effacer l'écran
    noecho();  // Ne pas afficher les caractères saisis
    cbreak();  // Désactiver la mise en mémoire tampon de ligne
    // Generate boundary
    setup();

    // Function call
    while (!gameover)
    {
        draw();
        input();
        logic();
    }

    endwin();

    return 0;
}