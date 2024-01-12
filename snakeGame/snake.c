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
    int score;
} Snake;

typedef struct
{
    Point position;
} Food;

/* --------------------------- FUNCTION PROTOTYPE --------------------------- */
int foodCollidesWithSnake(Food *food, Snake *snake);
void generateFoodPosition(Food *food, Snake *snake);
void initGame(Snake *snake, Food *food);
void drawBorder();
void draw(Snake *snake, Food *food);
void getInput(Snake *snake);
void moveSnake(Snake *snake, Food *food);
int checkCollision(Snake *snake);

int main()
{
    int replay = 1;

    while (replay)
    {
        Snake snake;
        Food food;

        initscr();
        raw();
        keypad(stdscr, TRUE);
        noecho();
        curs_set(0);

        mvprintw(height / 2, width / 2 - 10, "Press SPACE BAR to start");

        int ch;
        while ((ch = getch()) != ' ')
        {
            // Wait for the space bar to be pressed
        }

        clear();

        initGame(&snake, &food);

        while (1)
        {
            getInput(&snake);
            moveSnake(&snake, &food);
            if (checkCollision(&snake))
            {
                endwin();
                mvprintw(height / 2, width / 2 - 5, "Game Over!");
                mvprintw(height / 2 + 1, width / 2 - 10, "Press 'R' to replay or 'Q' to quit");

                int choice;
                while (1)
                {
                    choice = getch();
                    if (choice == 'R' || choice == 'r')
                    {
                        replay = 1;
                        break;
                    }
                    else if (choice == 'Q' || choice == 'q')
                    {
                        replay = 0;
                        break;
                    }
                }

                if (!replay)
                {
                    break; // Exit the game loop
                }

                clear();
                initGame(&snake, &food);
            }

            draw(&snake, &food);
            usleep(100000); // 100 milliseconds delay
        }
    }

    endwin(); // Close ncurses

    return 0;
}

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
    snake->score = 0;

    // Initialize food
    srand(time(NULL));
    generateFoodPosition(food, snake);
}
/* -------------------------------------------------------------------------- */
/*                             GAME INITIATION END                            */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                        GENERATE FOOD POSITION START                        */
/* -------------------------------------------------------------------------- */
void generateFoodPosition(Food *food, Snake *snake)
{
    do
    {
        food->position.x = 1 + rand() % (width - 1);
        food->position.y = 1 + rand() % (height - 1);
    } while (foodCollidesWithSnake(food, snake));
}

int(foodCollidesWithSnake(Food *food, Snake *snake))
{
    // Check if the fruits position collides with the snake
    for (int i = 0; i < snake->length; ++i)
    {
        if (food->position.x == snake->body[i].x && food->position.y == snake->body[i].y)
        {
            return 1;
        }
    }
    return 0;
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
void drawBorder()
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
/*                             DRAW GAME AREA END                             */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                         DRAW SNAKE AND FRUITS START                        */
/* -------------------------------------------------------------------------- */
    void
    draw(Snake *snake, Food *food)
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
    mvprintw(height + 2, 2, "Score %d", snake->score);

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
        snake-> score += 10;
        generateFoodPosition(food, snake);
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
