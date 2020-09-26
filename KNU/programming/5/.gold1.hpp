#ifndef _GOLD_1_HPP
#define _GOLD_1_HPP

#include "gold.hpp"
#include <bits/stdc++.h>
using namespace std;

int accept() {

    double needed_energy_J = accept_energy_J;
    double curC_M = 0;

    if (cut_len == -1) {
        curC_M = C_M;
    } else {
        curC_M = cut_len;
        cut_len = -1;
    }

    double curvolume_M3 = A_M * B_M * curC_M;
    double curmass_KG = curvolume_M3 * rho_KG_M3;
    if (!check_space(curvolume_M3, current_volume_M3, 
                     curmass_KG, current_mass_KG)) {
        return 1;
    }

    double needed_rec_energy_J = heating_energy(curmass_KG);
    double delta_rec_energy_J = 0;

    if (needed_rec_energy_J > current_rec_energy_J)
        delta_rec_energy_J = needed_rec_energy_J - current_rec_energy_J;

    needed_energy_J += delta_rec_energy_J;

    if (avaliable_energy() < needed_energy_J){
        separator();
        clog << "accept() failed: not enough energy\n";
        clog << "\tCurrent energy: " << current_energy_J << " (J)\n";
        clog << "\tNeeded energy: " << needed_energy_J << " (J)\n";
        clog << "\tRec. energy: " << current_rec_energy_J << " (J)\n";
        clog << "\tRec. energy needed: " << needed_rec_energy_J << " (J)\n";
        fly();
        return 1;
    }

    current_energy_J -= accept_energy_J;
    current_energy_J -= delta_rec_energy_J;
    double added_energy = cooling_energy(curmass_KG);

    separator();
    clog << "accept() \n";
    clog << "\tCurrent energy:" << current_energy_J + needed_energy_J << " (J)\n";
    clog << "\tDelta: " << needed_energy_J << " (J)\n";
    clog << "\tResulting energy: " << current_energy_J << " (J)\n";
    clog << "\tRec. energy: " << current_rec_energy_J << " (J)\n";
    clog << "\tRec. delta: " << delta_rec_energy_J + added_energy - needed_rec_energy_J << " (J)\n";
    current_rec_energy_J += delta_rec_energy_J;
    current_rec_energy_J += cooling_energy(curmass_KG);
    current_rec_energy_J -= needed_rec_energy_J;
    clog << "\tResulting rec. energy: " << current_rec_energy_J << " (J)\n";
    clog << "\tMass: " << current_mass_KG << " (kg)\n";
    clog << "\tVolume: " << current_volume_M3 << " (m^3)\n";
    clog << "\tMass delta: " << curmass_KG << " (kg)\n";
    clog << "\tVolume delta: " << curvolume_M3 << " (m^3)\n";
    current_mass_KG += curmass_KG;
    current_volume_M3 += curvolume_M3;
    clog << "\tResulting mass: " << current_mass_KG << " (kg)\n";
    clog << "\tResulting volume: " << current_volume_M3 << " (m^3)\n";
    return 0;
}

void add_nugget() {

    double maxcut = max_ever_cut();

    while (C_M > 0) {

        double curcut = max_now_cut();

        if (curcut >= maxcut) {
            if (maxcut < C_M) {
                cut_len = maxcut;
                cut();
                accept();
                fly();
            } else {
                accept();
                C_M = 0;
            }
        } else {
            double needed_energy_J = accept_energy_J + cut_energy_J;
            double curcutmass_KG = A_M * B_M * curcut * rho_KG_M3;
            double new_rec_energy_J = rec_delta_energy(curcutmass_KG);

            if (needed_energy_J > new_rec_energy_J) {
                if (!transfer_energy(cut_energy_J)) {
                    fly();
                }
            } else {
                cut_len = curcut;
                needed_energy_J = needed_energy_J + 
                    std::max(0.0, heating_energy(curcutmass_KG) - current_rec_energy_J);

                double future_acc_energy_J = current_energy_J - needed_energy_J;
                double future_rec_energy_J = current_rec_energy_J + new_rec_energy_J;
                double future_mass_KG = mass_KG - curcutmass_KG;

                if (future_rec_energy_J >= heating_energy(future_mass_KG) && 
                   future_acc_energy_J >= accept_energy_J + fly_energy_J){
                        cut();
                        accept();
                } else if (future_acc_energy_J >= cut_energy_J + accept_energy_J + fly_energy_J) {
                    cut();
                    accept();
                } else {
                    cut();
                    accept();
                    fly();
                }
            }
         }
    }
}
#endif
