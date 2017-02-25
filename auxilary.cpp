#include <iostream>
#include <vector>
#include <math.h>

#include "objects.h"
#include "auxilary.h"

void clean_things_up(std::vector<struct PHOTON> *photons) {
  for (auto photon = (*photons).begin(); photon != (*photons).end(); ) {
    if ((*photon).toDelete) {
      photon = photons->erase(photon);
    } else {
      ++photon;
    }
  }
}

void fill_CELLS(double L, double dx, std::vector<std::pair<int, int> > *CELLS, std::vector<struct PHOTON> *photons) {
  int N_CELLS = (int)(L / dx);
  if ((*CELLS).size() == 0) {
    for (int i = 0; i < N_CELLS * N_CELLS; i ++) {
      (*CELLS).push_back({0, 0});
    }
  } else {
    for (int i = 0; i < N_CELLS * N_CELLS; i ++) {
      (*CELLS)[i].first = 0;
      (*CELLS)[i].second = 0;
    }
  }

  /*
    calculating the number of particles at each cell
  */
  for(auto& photon : *photons) {
    int cell_x = floor((photon.r.x + L / 2.0) / dx);
    int cell_z = floor((photon.r.z + L / 2.0) / dx);
    int cell_num = cell_x + cell_z * N_CELLS;
    (*CELLS)[cell_num].first ++;
  }
  /*
    calculating the cumulative number of particles
  */
  for(int i = 1; i < N_CELLS * N_CELLS; i ++) {
    (*CELLS)[i].first += (*CELLS)[i - 1].first;
  }
}

void quickSort(std::vector<struct PHOTON> *photons, int left, int right) {
      int i = left, j = right;
      struct PHOTON pivot = (*photons)[(left + right) / 2];

      /* partition */
      while (i <= j) {
            while ((*photons)[i].tag < pivot.tag)
                  i++;
            while ((*photons)[j].tag > pivot.tag)
                  j--;
            if (i <= j) {
                  struct PHOTON tmp = (*photons)[i];
                  (*photons)[i] = (*photons)[j];
                  (*photons)[j] = tmp;
                  i++;
                  j--;
            }
      };

      /* recursion */
      if (left < j)
            quickSort(photons, left, j);
      if (i < right)
            quickSort(photons, i, right);
}


void tag_particles(double L, double dx, std::vector<std::pair<int, int> > *CELLS, std::vector<struct PHOTON> *photons) {
  int N_CELLS = (int)(L / dx);
  /*
    assigning tags to all particles
  */
  for(auto& photon : *photons) {
    int cell_x = floor((photon.r.x + L / 2.0) / dx);
    int cell_z = floor((photon.r.z + L / 2.0) / dx);
    int cell_num = cell_x + cell_z * N_CELLS;
    if (cell_num == 0) {
      photon.tag = (*CELLS)[0].second;
      (*CELLS)[0].second ++;
    } else {
      photon.tag = (*CELLS)[cell_num].second + (*CELLS)[cell_num - 1].first;
      (*CELLS)[cell_num].second ++;
      if (photon.tag >= (*CELLS)[cell_num].first) {
        std::cout << "Photon tagging error 'tag_particles'\n";
        exit (EXIT_FAILURE);
      }
    }
  }
  /*
    sorting particles in the grid according to their tags
  */
  quickSort(photons, 0, (*photons).size() - 1);
}

void checkSorting(std::vector<struct PHOTON> *photons) {
  for (int i = 0; i < (*photons).size(); i ++) {
    if ((*photons)[i].tag != i) {
      std::cout << "Photons sorted incorrectly 'checkSorting'\n";
      exit (EXIT_FAILURE);
    }
  }
  std::cout << "Photons tagged & sorted correctly!\n";
}
