#include "ants.h"

// The following is an example program displaying a basic ai that
// tries all possible directions and then moves in whichever one
// is not blocked by water (% characters).
//
// To see all the information contained in struct game_state and
// struct game_info check ants.h. There is also a distance function
// provided in bot.c

void get_dirs(int possibleDirs[], char obj_north, char obj_east, char obj_south, char obj_west);
void init_possible_dirs(int possibleDirs[]);

void do_turn(struct game_state *Game, struct game_info *Info) {
	
    // defining things just so we can do less writing
    // UP and DOWN move up and down rows while LEFT and RIGHT
    // move side to side. The map is just one big array.
	
#define UP -Info->cols
#define DOWN Info->cols
#define LEFT -1
#define RIGHT 1
	
    int i;
	int possibleDirs[kDirectionCount];
	
    for (i = 0; i < Game->my_count; ++i) {
		init_possible_dirs(possibleDirs);
		
        // the location within the map array where our ant is currently
		
        int offset = Game->my_ants[i].row*Info->cols + Game->my_ants[i].col;
		
        // defining things to do less writing again
		
#define ROW Game->my_ants[i].row
#define COL Game->my_ants[i].col
#define ID Game->my_ants[i].id
		
        // Now here is the tricky part. We have to account for
        // the fact that the map wraps (when you go off one edge
        // you end up on the side of the map opposite that edge).
        // This is done by checking to see if we are on the last
        // row or column and if the direction we are taking would
        // take us off the side of the map.
        //
        // For example, you can see here the West direction checks
        // to see if we are in the first column, in which case "West"
        // is a character a full row minus one from our location.
		
        char obj_north, obj_east, obj_south, obj_west;
		
        if (COL != 0)
            obj_west = Info->map[offset + LEFT];
        else
            obj_west = Info->map[offset + Info->cols - 1];
		
        if (COL != Info->cols - 1)
            obj_east = Info->map[offset + RIGHT];
        else
            obj_east = Info->map[offset - Info->cols - 1];
		
        if (ROW != 0)
            obj_north = Info->map[offset + UP];
        else
            obj_north = Info->map[offset + (Info->rows - 1)*Info->cols];
		
        if (ROW != Info->rows - 1)
            obj_south = Info->map[offset + DOWN];
        else
            obj_south = Info->map[offset - (Info->rows - 1)*Info->cols];
		
        char dir = -1;
		
        // cycle through the directions, pick one that works
		get_dirs(possibleDirs, obj_north, obj_east, obj_south, obj_west);
		
        // Now we do our move
		move(i, possibleDirs, Game, Info);
    }
	
    // There are many ways to make this program better.
    // For starters, try to avoid collisions between your
    // own ants and make a conscious effort to gather food
    // instead of walking around at random.
    //
    // Good luck!
}

void get_dirs(int possibleDirs[], char obj_north, char obj_east, char obj_south, char obj_west)
{
	
	if( obj_north == '%' )
		possibleDirs[0] = '0';
	
	if( obj_east == '%' )
		possibleDirs[1] = '0';
	
	if( obj_south == '%' )
		possibleDirs[2] = '0';
	
	if( obj_west == '%' )
		possibleDirs[3] = '0';
}

void init_possible_dirs(int possibleDirs[])
{
	possibleDirs[0] = 'N';
	possibleDirs[1] = 'E';
	possibleDirs[2] = 'S';
	possibleDirs[3] = 'W';
}
