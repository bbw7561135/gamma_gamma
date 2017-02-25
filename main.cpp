#include <iostream>
#include <vector>

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "objects.h"
#include "auxilary.h"
#include "process.h"

void writeToFile(std::vector<struct PHOTON> photons, std::vector<std::vector<int> > grid, int timestep);

int main() {
  srand (time(NULL));
  // ofstream outputData(path + name + ".dat");
  double L = 1.0;
  double cdt = 0.003;
  double dx = 0.005;
  int NperStep = 2000;

  int N_CELLS = (int)(L / dx);

  /*
    This array contains (a) the number of all particles in the preceding cells + in that cell, (b) the temporary number of particles already tagged in the given cell
  */
  std::vector<std::pair<int, int> > CELLS;
  std::vector<struct PHOTON> photons;

  // inject_photons(NperStep, dx, L, &photons);
  // move_photons(cdt, dx, L, &photons);
  // move_photons(cdt, dx, L, &photons);
  // move_photons(cdt, dx, L, &photons);
  // move_photons(cdt, dx, L, &photons);
  // move_photons(cdt, dx, L, &photons);
  // fill_CELLS(L, dx, &CELLS, &photons);
  // tag_particles(L, dx, &CELLS, &photons);
  // checkSorting(&photons);
  // fill_CELLS(L, dx, &CELLS, &photons);
  // return 0;

  /*
    This grid keeps the number of pairs produced
  */
  std::vector<std::vector<int> > grid;
  for (int i = 0; i < N_CELLS; i ++) {
    std::vector<int> temp;
    for (int j = 0; j < N_CELLS; j ++) {
      temp.push_back(0);
    }
    grid.push_back(temp);
  }

  int i = 0;
  while(i < 100000) {
    inject_photons(NperStep, dx, L, &photons);
    move_photons(cdt, dx, L, &photons);
    fill_CELLS(L, dx, &CELLS, &photons);
    tag_particles(L, dx, &CELLS, &photons);
    interact_photons(cdt, dx, L, &CELLS, &photons, &grid);
    std::cout << "step: " << i << " photons: " << photons.size() << std::endl;
    i++;
    if(i % 1000 == 0) writeToFile(photons, grid, i);
  }
  // interact_photons(0.2, 1.0, &photons);
  // std::cout << photons[3].E << std::endl;
  return 0;
}

// std::cout << photons[3].r.x << " " << photons[3].r.y << " " << photons[3].r.z << std::endl;
// std::cout << photons[3].k.x << " " << photons[3].k.y << " " << photons[3].k.z << std::endl;


void writeToFile(std::vector<struct PHOTON> photons, std::vector<std::vector<int> > grid, int timestep) {
  std::string path = "dats/";

  struct stat st = {0};
  if (stat(path.c_str(), &st) == -1) {
      mkdir(path.c_str(), 0700);
  }

  std::string filename = std::to_string(timestep);

  // std::stringstream ss;
  // ss << std::setw(4) << std::setfill('0') << timestep;
  // std::string filename = ss.str();

  std::ofstream outputData(path + "time_" + filename + ".dat");
  for (int i = 0; i < grid.size(); i ++) {
    for (int j = 0; j < grid[i].size(); j++) {
      outputData << i << " " << j << " " << grid[i][j] << std::endl;
    }
  }
  // for (auto& photon : photons) {
  //   outputData << photon.r.x << " " << photon.r.y << " " << photon.r.z << std::endl;
  // }
  outputData.close();
}
