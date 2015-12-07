#ifndef COLOR_H_
#define COLOR_H_

#include <SDL.h>

typedef struct s_caracteristics t_caracteristics;
struct s_caracteristics {
	int posX, posY, width, height, surface, ratio, gravity, rotation;
};

typedef struct s_seg_computing t_seg_computing;
struct s_seg_computing {
	int posX1, posY1, posX2, posY2, width, height, surface, gravCenterX, gravCenterY;
	float ratio; 
};

int *bin_mat(SDL_Surface *img);
void print_mat(int *mat, int w, int h);
int abs(int a);
int min(int a, int b, int c);
int maxi(int a, int b, int c);
int *labeling(SDL_Surface *img);
void neighbours(int *bin_mat, int* labeled_mat, int w, int h, int i, int j, int label);
int get_nb_regions(SDL_Surface *img);
int *separate_regions(SDL_Surface *img);
void segment_positions(SDL_Surface *img, t_seg_computing *seg_pos);
void compute_dimension(SDL_Surface *img, t_seg_computing *seg_pos);
void compute_on_image(SDL_Surface *img, t_seg_computing *seg_pos);
void draw_square(SDL_Surface *img, int x1, int y1, int width, int height, Uint32 color);
void gravity_center(SDL_Surface *img, t_seg_computing *seg_pos);
void face_detection(char *path);

#endif
