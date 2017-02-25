#pragma OBJECTS

struct VECTOR{
  double x;
  double y;
  double z;
  VECTOR(double x_temp, double y_temp, double z_temp) : x(x_temp), y(y_temp), z(z_temp) {}
  ~VECTOR() {}
};

struct PHOTON{
  VECTOR k; // k unit vector of the photon
  VECTOR r; // radius vector of the photon
  double E; // energy of the photon in MeV
  bool toDelete;
  bool counted;
  int id;
  int tag;
  PHOTON(int id_temp, VECTOR k_temp, VECTOR r_temp) : k(k_temp), r(r_temp), E(2.0), toDelete(false), counted(false), id(id_temp), tag(0) {}
  ~PHOTON() {}
};
