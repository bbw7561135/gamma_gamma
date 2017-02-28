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

#include <chrono>  // for high_resolution_clock

#include "parameters.h"
#include "objects.h"
#include "auxilary.h"
#include "process.h"

void writeToFile(std::vector<struct PHOTON> photons, std::vector<std::vector<int> > grid, int timestep);

int main() {
    srand (time(NULL));
    // ofstream outputData(path + name + ".dat");
    // double L = 1.0;
    // double cdt = 0.0012;
    // double dx = 0.002;
    // int NperStep = 500;

    int N_CELLS = (int)(L / dx);

    /*
    This array contains (a) the number of all particles in the preceding cells + in that cell, (b) the temporary number of particles already tagged in the given cell
    */
    std::vector<std::pair<int, int> > CELLS;
    std::vector<struct PHOTON> photons;

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
        auto startINJ = std::chrono::high_resolution_clock::now();
        inject_photons(NperStep, dx, L, &photons);
        auto finishINJ = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedINJ = finishINJ - startINJ;

        auto startMOV = std::chrono::high_resolution_clock::now();
        move_photons(cdt, dx, L, &photons);
        auto finishMOV = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedMOV = finishMOV - startMOV;

        auto startFILL = std::chrono::high_resolution_clock::now();
        fill_CELLS(L, dx, &CELLS, &photons);
        auto finishFILL = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedFILL = finishFILL - startFILL;

        auto startTAG = std::chrono::high_resolution_clock::now();
        tag_particles(L, dx, &CELLS, &photons);
        auto finishTAG = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTAG = finishTAG - startTAG;

        auto startINT = std::chrono::high_resolution_clock::now();
        interact_photons(sigma, cdt, dx, L, &CELLS, &photons, &grid);
        auto finishINT = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedINT = finishINT - startINT;

        if (i % 10 == 0) {
            std::cout << "step: " << i << " photons: " << photons.size() << std::endl;
            std::cout << "\tinject time: " << elapsedINJ.count() << " s" << std::endl;
            std::cout << "\tmove time: " << elapsedMOV.count() << " s" << std::endl;
            std::cout << "\tfill time: " << elapsedFILL.count() << " s" << std::endl;
            std::cout << "\ttag/sort time: " << elapsedTAG.count() << " s" << std::endl;
            std::cout << "\tinteract time: " << elapsedINT.count() << " s" << std::endl;
        }
        // std::cout << "step: " << i << " | photons in cell: " << CELLS[N_CELLS * (N_CELLS / 2) + (N_CELLS / 2)].first - CELLS[N_CELLS * (N_CELLS / 2) + (N_CELLS / 2) - 1].first << " | pairs in cell: " << grid[N_CELLS / 2][N_CELLS / 2] << std::endl;
        i++;
        if(i % 100 == 0) writeToFile(photons, grid, i);
    }
    // interact_photons(0.2, 1.0, &photons);
    // std::cout << photons[3].E << std::endl;
    return 0;
}

// std::cout << photons[3].r.x << " " << photons[3].r.y << " " << photons[3].r.z << std::endl;
// std::cout << photons[3].k.x << " " << photons[3].k.y << " " << photons[3].k.z << std::endl;


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
