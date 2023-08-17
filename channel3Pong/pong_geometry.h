#ifndef _PONG_GEOMETRY_H
#define _PONG_GEOMETRY_H

// Assume x,y,z
int16_t cubeVerts[] = {
	0,0,0,
	0,256,0,
	0,0,-256,
	0,256,-256,

	256,0,0,
	256,256,0,
	256,0,-256,
	256,256,-256,
};
uint16_t cubeIndices[] = {
	0,3, 0,6, 0,12, 
	3,9, 3,15,
	6,9, 6,18,
	9,21,
	12,15, 12,18,
	15,21,
	18,21
};

int16_t dodecahedronVerts[] = {	0, 0, 274, 
	182, 0, 204, 
	-91, 158, 204, 
	-91, -158, 204, 
	204, 158, 91, 
	204, -158, 91, 
	-239, 97, 91, 
	34, 256, 91, 
	34, -256, 91, 
	-239, -97, 91, 
	239, 97, -91, 
	239, -97, -91, 
	-204, 158, -91, 
	-34, 256, -91, 
	-34, -256, -91, 
	-204, -158, -91, 
	91, 158, -204, 
	91, -158, -204, 
	-182, 0, -204, 
	0, 0, -274, 
};
uint16_t dodecahedronIndices[] = {	0, 3, 
	0, 6, 
	0, 9, 
	3, 12, 
	3, 15, 
	6, 18, 
	6, 21, 
	9, 24, 
	9, 27, 
	12, 21, 
	12, 30, 
	15, 24, 
	15, 33, 
	18, 27, 
	18, 36, 
	21, 39, 
	24, 42, 
	27, 45, 
	30, 33, 
	30, 48, 
	33, 51, 
	36, 39, 
	36, 54, 
	39, 48, 
	42, 45, 
	42, 51, 
	45, 54, 
	48, 57, 
	51, 57, 
	54, 57, 
};


#define PADDLE_X 46
#define PADDLE_Y 200
#define PADDLE_Z 200
#define PADDLE_CENTER_X(X) (X-(PADDLE_X/2))
#define PADDLE_CENTER_Y(Y) (Y-(PADDLE_Y/2))
#define PADDLE_CENTER_Z(Z) (Z-(PADDLE_Z/2))

#define BALL_X 100
#define BALL_Y 100
#define BALL_Z 100
#define BALL_CENTER_X(X) (X-(BALL_X/2))
#define BALL_CENTER_Y(Y) (Y-(BALL_Y/2))
#define BALL_CENTER_Z(Z) (Z-(BALL_Z/2))

#define BALL_X_POS_MIN -95
#define BALL_X_POS_MAX 95
#define BALL_X_POS_PADDLE_MIN -83
#define BALL_X_POS_PADDLE_MAX 83
#define BALL_Y_POS_MIN -80
#define BALL_Y_POS_MAX 80

#define PADDLE_RADIUS 20


#endif
