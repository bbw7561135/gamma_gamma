#pragma AUXILARY

void clean_things_up(std::vector<struct PHOTON> *photons);

void fill_CELLS(double L, double dx, std::vector<std::pair<int, int> > *CELLS, std::vector<struct PHOTON> *photons);
void tag_particles(double L, double dx, std::vector<std::pair<int, int> > *CELLS, std::vector<struct PHOTON> *photons);

void checkSorting(std::vector<struct PHOTON> *photons);
