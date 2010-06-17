#ifndef AINTERN_PRIM_DIRECTX_H
#define AINTERN_PRIM_DIRECTX_H

struct ALLEGRO_BITMAP;
struct ALLEGRO_VERTEX;

int _al_draw_prim_directx(ALLEGRO_BITMAP* texture, const void* vtxs, const ALLEGRO_VERTEX_DECL* decl, int start, int end, int type);
int _al_draw_prim_indexed_directx(ALLEGRO_BITMAP* texture, const void* vtxs, const ALLEGRO_VERTEX_DECL* decl, const int* indices, int num_vtx, int type);
void _al_set_d3d_decl(ALLEGRO_VERTEX_DECL* ret);

#endif