#include <stdio.h>
 
// Globally declared 2D-array
char board[3][3];
void clear_screen() {
  int x, y;
  for (x = 0; x < 320; x++) {
    for (y = 0; y < 240; y++) {
	  write_pixel(x,y,0);
	}
  }
  for(x=0; x<60; x++)
  {
    write_pixel(x,80,0xffffffff);
    write_pixel(x,120,0xffffffff);
  }
  for(y=0; y<60; y++)
  {
    write_pixel(80,y,0xffffffff);
    write_pixel(120,y,0xffffffff);
  }
}

void write_pixel(int x, int y, short colour) {
  volatile short *vga_addr=(volatile short*)(0x08000000 + (y<<10) + (x<<1));
  *vga_addr=colour;
}
 
// Function to initialize the game board
void initializeBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
    int count = 1;
    printf("\n\n\t  ");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printf("%d", count++);
            if (j < 2)
            {
                printf("  |  ");
            }
        }
        if (i < 2)
        printf("\n\t----------------\n\t  ");
    }
    printf("\n\n\n");
}

void write_char(int x, int y, char c) {
  // VGA character buffer
  volatile char * character_buffer = (char *) (0x09000000 + (y<<7) + x);
  *character_buffer = c;
}
 
// Function shows the game board
void showBoard(int x, int y)
{
    printf("\n\n\t  ");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%c", board[i][j]);
            char* hw = " OX";
            if(board[i][j]=='X')
			{
			hw++;
			hw++;
			}
            else if(board[i][j]=='O')
			{
				hw++;
			}
    
            write_char((15+20*j),(15+20*i), *hw);
            if (j < 2)
            {
                printf("  |  ");
            }
        }
        if (i < 2)
        printf("\n\t----------------\n\t  ");
    }
    printf("\n\n\n");
}
 
// Function to update the game board
int updateBoard(int cell, char playerSign)
{
    int row = (cell - 1) / 3;
    int col = (cell - 1) % 3;
    int isValid = 1;
 
    // accessing already played cell number
    if (board[row][col] != ' ')
    {
        printf("\nInvalid: Cell is already Filled!\n");
        isValid = 0;
    }
 
    // valid cell position
    else
    {
        board[row][col] = playerSign;
    }
    showBoard(row, col);
 
    return isValid;
}
 
// Function to check the winner of the game
int checkWinner(char sg)
{
    // check all rows
    if (board[0][0] == sg && board[0][1] == sg && board[0][2] == sg ||
      board[1][0] == sg && board[1][1] == sg && board[1][2] == sg ||
      board[2][0] == sg && board[2][1] == sg && board[2][2] == sg)
    {
        return 1;
      }
      // check all columns
    else if (board[0][0] == sg && board[1][0] == sg && board[2][0] == sg ||
           board[0][1] == sg && board[1][1] == sg && board[2][1] == sg ||
           board[0][2] == sg && board[1][2] == sg && board[2][2] == sg)
    {
        return 1;
    }
    // check both diagonals
    else if (board[0][0] == sg && board[1][1] == sg && board[2][2] == sg ||
           board[0][2] == sg && board[1][1] == sg && board[2][0] == sg)
    {
        return 1;
    }
 
    // There is no winner
    return 0;
}
 
// Start your game from here
void playTicTacToe()
{
    int gameResult = 0;
    int cell = 0;
    int playCount = 0;
    int updationResult = 1;
 
    char playerSign = ' ';
 
    // start playing the game
    while (!gameResult && playCount < 9)
    {
        if (playCount % 2 == 0)
        {
            // player 1
            printf("\nPlayer 1 [ X ] : ");
            playerSign = 'X';
        }
        else
        {
            // player 2
            printf("\nPlayer 2 [ O ] : ");
            playerSign = 'O';
        }
        scanf("%d", &cell);
        if (cell > 0 && cell < 10)
        {
            updationResult = updateBoard(cell, playerSign);
            // if updation is possible
            if (updationResult)
            {
                gameResult = checkWinner(playerSign);
                // print the winner of the game
                if (gameResult)
                {
                    printf("\t *** Player %d Won!! ***\n", playerSign == 'X' ? 1 : 2);
                    if(playerSign=='X')
                    {
                         char* hw = " Player 1 Won!! ";
                         int x=25;
                         while (*hw) {
                         write_char(x, 10, *hw);
	                     x++;
	                     hw++;
                    }
                    }
                    else
                    {
                         char* hw = " Player 2 Won!! ";
                     int x=25;
                     while (*hw) {
                    write_char(x, 10, *hw);
	                 x++;
	                 hw++;
                    }
                    }
                }
                playCount++;
            }
        }
        else if (cell == -1)
        {
            printf("\n\tGame Terminated\n");
            return;
        }
        else
        {
            printf("\nPlease Enter a valid cell value\n");
        }
    }
 
    // no one won the game
    if (!gameResult && playCount == 9)
    {
        printf("\n\t *** Draw...  ***\n");
           char* hw = "    Draw   ";
     int x=25;
     while (*hw) {
     write_char(x, 10, *hw);
	 x++;
	 hw++;
   }
    }
    printf("\n\t --- Game Over --- \n");
}
 
int main()
{
    clear_screen();
    printf("--------- Tic Tac Toe ----------\n\n");
 
    printf("\n* Instructions \n\n");
    printf("\tPlayer 1 sign = X\n");
    printf("\tPlayer 2 sign = O");
    printf("\n\tTo exit from game, Enter -1\n");
 
    printf("\n\n* Cell Numbers on Board\n");
    initializeBoard();
 
    char start = ' ';
    printf("\n> Press Enter to start...");
 
    scanf("%c", &start);
 
    if (start)
    {
        int userChoice = 1;
        // restart the game
        while (userChoice)
        {
            playTicTacToe();
            printf("\n* Menu\n");
            printf("\nPress 1 to Restart");
            printf("\nPress 0 for Exit");
            printf("\n\nChoice: ");
            scanf("%d", &userChoice);
            if (userChoice)
            {
                initializeBoard();
            }
            printf("\n");
        }
    }
    printf("\n :: Thanks for playing Tic Tac Toe game! :: \n");
    return 0;
}
	
	