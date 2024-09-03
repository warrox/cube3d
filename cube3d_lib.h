#include <math.h>
#ifndef CUBE3D_LIB_h
#define CUBE3D_LIB_h
#define PI 3.14159265359
#define MAP_WIDTH 6
#define MAP_HEIGHT 5
#define NUM_RAYS 100
#define g_value 10;
#define w_value 10;

typedef struct s_player
{
	int fov;
	int distance;
	int angle;
	int radians;
}t_player;

typedef struct s_data
{
	t_player player;
	int wall;
	int ground;
}t_data;



/******Raycasting func**********/
#endif // !DEBUG
