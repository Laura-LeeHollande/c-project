#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#define width 20
#define height 10

typedef struct
{
    int x, y;
} Point;

typedef struct
{
    Point head;
    Point body[width * height];
    int length;
    char direction;
} Snake;

typedef struct
{
    Point position;
} Food;

void generateFoodPosition(Food *food);

/* -------------------------------------------------------------------------- */
/*                            GAME INITIATION START                           */
/* -------------------------------------------------------------------------- */
void initGame(Snake *snake, Food *food)
{
    // Initialize ncurses
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    // Initialize snake
    snake->head.x = width / 2;
    snake->head.y = height / 2;
    snake->length = 1;
    snake->direction = 'R';

    // Initialize food
    srand(time(NULL));
    generateFoodPosition(food);
}
/* -------------------------------------------------------------------------- */
/*                             GAME INITIATION END                            */
/* -------------------------------------------------------------------------- */

    /* -------------------------------------------------------------------------- */
    /*                        GENERATE FOOD POSITION START                        */
    /* -------------------------------------------------------------------------- */
    void
    generateFoodPosition(Food *food)
{
    food->position.x = 1 + rand() % (width - 1);
    food->position.y = 1 + rand() % (height - 1);
}
/* -------------------------------------------------------------------------- */
/*                         GENERATE FOOD POSITION END                         */
/* -------------------------------------------------------------------------- */

    /* -------------------------------------------------------------------------- */
    /*                            DRAW GAME AREA START                            */
    /* -------------------------------------------------------------------------- */
    /* --------------------------------- OUTPUT --------------------------------- */
    // ----------------------
    // |                    |
    // |                    |
    // |                    |
    // |                    |
    // |                    |
    // |                    |
    // |                    |
    // |                    |
    // |                    |
    // |                    |
    // ----------------------
    void
    drawBorder()
{
    // Draw top border
    for (int i = 0; i < width + 2; i++)
    {
        mvprintw(0, i, "-");
    }
    // Draw bottom border
    for (int i = 0; i < width + 2; i++)
    {
        mvprintw(height + 1, i, "-");
    }
    // Draw left and right borders
    for (int i = 1; i <= height; i++)
    {
        mvprintw(i, 0, "|");
        mvprintw(i, width + 1, "|");
    }
}
/* -------------------------------------------------------------------------- */
/*                          DRAW GAME AREA START END                          */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                         DRAW SNAKE AND FRUITS START                        */
/* -------------------------------------------------------------------------- */
void draw(Snake *snake, Food *food)
{
    clear();

    drawBorder();

    // Draw snake
    mvprintw(snake->head.y, snake->head.x, "O");
    for (int i = 0; i < snake->length; ++i)
    {
        mvprintw(snake->body[i].y, snake->body[i].x, "o");
    }

    // Draw food
    mvprintw(food->position.y, food->position.x, "F");

    // Refresh the screen
    refresh();
}
/* -------------------------------------------------------------------------- */
/*                          DRAW SNAKE AND FRUITS END                         */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                       SET UP THE INPUTS KEYBORD START                      */
/* -------------------------------------------------------------------------- */
/* --------------------------------- INPUTS --------------------------------- */
// Move up: up arrow
// Move down: down arrow
// Move right: right arrow
// Move left: left arrow
void getInput(Snake *snake)
{
    int ch = getch();
    switch (ch)
    {
    case KEY_UP:
        if (snake->direction != 'D')
            snake->direction = 'U';
        break;
    case KEY_DOWN:
        if (snake->direction != 'U')
            snake->direction = 'D';
        break;
    case KEY_LEFT:
        if (snake->direction != 'R')
            snake->direction = 'L';
        break;
    case KEY_RIGHT:
        if (snake->direction != 'L')
            snake->direction = 'R';
        break;
    case 'q':
        endwin();
        exit(0);
        break;
    }
}
/* -------------------------------------------------------------------------- */
/*                        SET UP THE INPUTS KEYBORD END                       */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                           SNAKE MOUVEMENTS START                           */
/* -------------------------------------------------------------------------- */
void moveSnake(Snake *snake, Food *food)
{
    // Move the body
    for (int i = snake->length - 1; i > 0; --i)
    {
        snake->body[i] = snake->body[i - 1];
    }

    // Move the head
    snake->body[0] = snake->head;

    switch (snake->direction)
    {
    case 'U':
        snake->head.y--;
        break;
    case 'D':
        snake->head.y++;
        break;
    case 'L':
        snake->head.x--;
        break;
    case 'R':
        snake->head.x++;
        break;
    }

    // Check for collisions with food
    if (snake->head.x == food->position.x && snake->head.y == food->position.y)
    {
        snake->length++;
        generateFoodPosition(food);
    }
}
/* -------------------------------------------------------------------------- */
/*                            SNAKE MOUVEMENTS END                            */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                           CHECK COLLISIONS START                           */
/* -------------------------------------------------------------------------- */
int checkCollision(Snake *snake)
{
    // Check if the snake hits the walls
    if (snake->head.x <= 0 || snake->head.x >= width + 1 || snake->head.y <= 0 || snake->head.y >= height + 1)
    {
        return 1;
    }

    // Check if the snake hits itself
    for (int i = 0; i < snake->length; ++i)
    {
        if (snake->head.x == snake->body[i].x && snake->head.y == snake->body[i].y)
        {
            return 1;
        }
    }

    return 0;
}
/* -------------------------------------------------------------------------- */
/*                            CHECK COLLISIONS END                            */
/* -------------------------------------------------------------------------- */

    int
    main()
{
    Snake snake;
    Food food;

    initGame(&snake, &food);

    while (1)
    {
        getInput(&snake);
        moveSnake(&snake, &food);
        if (checkCollision(&snake))
        {
            endwin();
            printf("Game Over!\n");
            return 0;
        }
        draw(&snake, &food);
        usleep(100000); // 100 milliseconds delay
    }

    return 0;
}
