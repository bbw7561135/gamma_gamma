#include <iostream>
#include <vector>

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "objects.h"
#include "process.h"

void writeToFile(std::vector<struct PHOTON> photons, std::vector<std::vector<int> > grid, int timestep);

int main() {
  srand (time(NULL));
  // ofstream outputData(path + name + ".dat");
  double L = 1.0;
  double cdt = 0.008;
  double dx = 0.01;
  int NperStep = 1000;

  int nmax = (int)(L / dx);

  // std::vector<int> CELLS;
  // for (int i = 0; i < nmax; i ++) {
  //   CELLS.push_back(0);
  // }

  std::vector<std::vector<int> > grid;
  for (int i = 0; i < nmax; i ++) {
    std::vector<int> temp;
    for (int j = 0; j < nmax; j ++) {
      temp.push_back(0);
    }
    grid.push_back(temp);
  }

  std::vector<struct PHOTON> photons;
  int i = 0;
  while(i < 10000) {
    inject_photons(NperStep, dx, L, &photons);
    move_photons(cdt, dx, L, &photons);
    interact_photons(cdt, dx, L, &photons, &grid);
    std::cout << "step: " << i << " photons: " << photons.size() << std::endl;
    i++;
    if(i % 50 == 0) writeToFile(photons, grid, i);
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
