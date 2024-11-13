#ifndef FORCE_NODE_H
#define FORCE_NODE_H

struct CoordenadasEsfericas
{
  float alfa;
  float beta;
  float ro;
};

struct CoordenadasRectangulares
{
  float x;
  float y;
  float z;
};

CoordenadasEsfericas RectangulareEsfericas(float x, float y, float z, float x_prima = 0, float y_prima = 0,float z_prima = 0);

CoordenadasRectangulares EsfericasRectangulares(float alfa, float z, float x_prima = 0, float y_prima = 0,float z_prima = 0);

float multi_valor(float angulo);

float CalculoFuerza(float x, float y, float z, float x_prima = 0, float y_prima = 0, float z_prima = 0,float direccion = 0);

#endif // FORCE_NODE_H