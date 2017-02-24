#pragma PROCESS

void inject_photons(int number, double dx, double L, std::vector<struct PHOTON> *photons);
void move_photons(double cdt, double dx, double L, std::vector<struct PHOTON> *photons);
void interact_photons(double cdt, double dx, double L, std::vector<struct PHOTON> *photons, std::vector<std::vector <int> > *grid);
