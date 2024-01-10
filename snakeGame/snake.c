#include <stdio.h>
#include <stdlib.h>
int i, j, height = 20, width = 20;
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
    // system("clear");
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("score = %d", score);
    printf("\n");
    printf("Press X to quit the game");
}
/* -------------------------------------------------------------------------- */
/*                             DRAW BOUNDARIES END                            */
/* -------------------------------------------------------------------------- */

// Driver code
int main()
{
    // Generate boundary
    setup();

    // Function call
    while (!gameover)
    {
        draw();
    }
}