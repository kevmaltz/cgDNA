#ifndef _Vertex_h_
#define _Vertex_h_


typedef struct {
  double x;
  double y;
  double z;
} vertex;


inline void vertexRotate(vertex *d3v, double theta, bool x, bool y, bool z) {                                                                                                                                                                                                                  
  double rm[3][3];
  double cost = cos(theta);
  double sint = sin(theta);

  double v[3] = { d3v->x, d3v->y, d3v->z };

  //x
  if(x) {
  rm[0][0] = 1;
  rm[0][1] = 0.;
  rm[0][2] = 0.;

  rm[1][0] = 0.;
  rm[1][1] =   cost;
  rm[1][2] =  -sint;

  rm[2][0] = 0.;
  rm[2][1] =  sint;
  rm[2][2] =  cost;
  }

  //y
  if(y) {
  rm[0][0] =  cost;
  rm[0][1] = 0.;
  rm[0][2] =  sint;

  rm[1][0] = 0.;
  rm[1][1] = 1;
  rm[1][2] = 0.;

  rm[2][0] =  -sint;
  rm[2][1] = 0.;
  rm[2][2] =   cost;
  }

  //z
  if(z) {
  rm[0][0] =   cost;
  rm[0][1] =  -sint;
  rm[0][2] = 0.;

  rm[1][0] =  sint;
  rm[1][1] =  cost;
  rm[1][2] = 0.;

  rm[2][0] = 0.;
  rm[2][1] = 0.;
  rm[2][2] = 1;
  }

  double vr[3] = { 0., 0., 0. };

  for(int n=0; n < 3; n++)
    for(int m=0; m < 3; m++)
      vr[n] += rm[n][m] * v[m];

  d3v->x = vr[0];
  d3v->y = vr[1];
  d3v->z = vr[2];
}


inline void vertexRotate2(vertex *d3v, double x, double y, double z) {                                                                                                                                                                                                                  
  double rm[3][3];
  double cost = cos(x);
  double sint = sin(x);

  double v[3] = { d3v->x, d3v->y, d3v->z };

  //x
  rm[0][0] = 1;
  rm[0][1] = 0.;
  rm[0][2] = 0.;

  rm[1][0] = 0.;
  rm[1][1] =   cost;
  rm[1][2] =  -sint;

  rm[2][0] = 0.;
  rm[2][1] =  sint;
  rm[2][2] =  cost;

  //y
  cost = cos(y);
  sint = sin(y);
  rm[0][0] +=  cost;
  rm[0][1] += 0.;
  rm[0][2] +=  sint;

  rm[1][0] += 0.;
  rm[1][1] += 1;
  rm[1][2] += 0.;

  rm[2][0] +=  -sint;
  rm[2][1] += 0.;
  rm[2][2] +=   cost;

  //z
  cost = cos(z);
  sint = sin(z);
  rm[0][0] +=   cost;
  rm[0][1] +=  -sint;
  rm[0][2] += 0.;

  rm[1][0] +=  sint;
  rm[1][1] +=  cost;
  rm[1][2] += 0.;

  rm[2][0] += 0.;
  rm[2][1] += 0.;
  rm[2][2] += 1;

  double vr[3] = { 0., 0., 0. };

  for(int n=0; n < 3; n++)
    for(int m=0; m < 3; m++)
      vr[n] += rm[n][m] * v[m];

  d3v->x = vr[0];
  d3v->y = vr[1];
  d3v->z = vr[2];
}

inline void vectorCross(vertex *va, vertex *vb, vertex *vr) {
  double *a = (double*)va;
  double *b = (double*)vb;
  double *r = (double*)vr;
  r[0] = a[1]*b[2]-a[2]*b[1];
  r[1] = a[2]*b[0]-a[0]*b[2];
  r[2] = a[0]*b[1]-a[1]*b[0];
}


#endif
