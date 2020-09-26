#include <bits/stdc++.h>
#include "gold.hpp"
#include ".gold1.hpp"
#include "fib.hpp"

using namespace std;

void print_ascii_art() {
    clog << rocket;
}

void separator(int len) {
    while (len--) {
        clog << '_';
    }
    clog << "\n\n";
}

double avaliable_energy() {
    return current_energy_J - fly_energy_J;
}

void print_delta_energy(double delta, bool change) {
    clog << "\tCurrent energy: " << current_energy_J << " (J)\n";
    clog << "\tDelta: " << delta << " (J)\n";
    clog << "\tResulting energy: " << current_energy_J - delta << " (J)\n";

    if (change)
       current_energy_J -= put_energy_J;

}

int fly() {
    separator();
    clog << "fly() \n";   
    print_delta_energy(fly_energy_J);
    clog << "\tMass = " << current_mass_KG << " (kg)\n";
    clog << "\tVolume = " << current_volume_M3 << " (m^3)\n\n";
    print_ascii_art();
    exit(0);
}

void print_no_energy(const string& operation, double needed) {
    separator();
    clog << operation << "() failed: not enough energy.\n";
    clog << "\tCurrent energy: " << current_energy_J << " (J)\n";
    clog << "\tNeeded energy: " << needed << " (J)\n";
    fly();
}

double available_energy() {
    return current_energy_J - fly_energy_J;
}

int land() {
    separator();
    clog << "land() \n";
    clog << "\tHeight: " << HEIGHT_M << " (m)\n";
    clog << "\tWidth: " << WIDTH_M << " (m) \n";
    clog << "\tCurrent energy: " << INITIAL_ENERGY_J << " (J)\n";
    clog << "\tMax Volume: " << MAX_VOLUME_M3 <<  " (m^3)\n";
    clog << "\tMax Mass: " << MAX_MASS_KG << " (kg)\n";
    return 0;
}

int put() {
    if (available_energy() < put_energy_J) {
        print_no_energy("put", put_energy_J);
        return 1;
    }
    separator();
    clog << "put() \n";
    print_delta_energy(put_energy_J);
    A_M = rnd.next()*0.01;
    B_M = rnd.next()*0.01;
    C_M = rnd.next()*0.01;
    rho_KG_M3 = gold_rho_KG_M3 + rnd.next();
    mass_KG = A_M * B_M * C_M * rho_KG_M3;
    volume_M3 = A_M * B_M * C_M;
    clog << "\tA = " << A_M << " (m)\n";
    clog << "\tB = " << B_M << " (m)\n";
    clog << "\tC = " << C_M << " (m)\n";
    clog << "\trho = " << rho_KG_M3 << " (kg/m^3)\n";
    return 0;
}


int rotate() {
    if (available_energy() < rotate_energy_J) {
        print_no_energy("rotate", rotate_energy_J);
        return 1;
    }
    separator();
    clog << "rotate() \n";
    print_delta_energy(rotate_energy_J);
    swap(A_M, B_M);
    clog << "\tNew A: " << A_M << ' ' << " (m)\n";
    clog << "\tNew B: " << B_M << ' ' << " (m)\n";
    clog << "\tNew C: " << C_M << ' ' << " (m)\n";
    return 0;
}

int turn() {
    if (available_energy() < turn_energy_J) {
        print_no_energy("turn", turn_energy_J);
        return 1;
    }
    separator();
    clog << "turn() \n";
    print_delta_energy(turn_energy_J);
    swap(B_M, C_M);
    clog << "\tNew A: " << A_M << ' ' << " (m)\n";
    clog << "\tNew B: " << B_M << ' ' << " (m)\n";
    clog << "\tNew C: " << C_M << ' ' << " (m)\n";
    return 0;
}

int drop_good() {
    if (avaliable_energy() < drop_good_energy_J) {
        print_no_energy("drop_good", drop_good_energy_J);
        return 1;
    }
    separator();
    clog << "drop_good() \n";
    print_delta_energy(drop_good_energy_J);
    return 0;
}

int drop_bad() {
    if (avaliable_energy() < drop_bad_energy_J) {
        print_no_energy("drop_bad", drop_bad_energy_J);
        return 1;
    }
    separator();
    clog << "drop_bad() \n";
    print_delta_energy(drop_bad_energy_J);
    return 0;
}

void cut_log() {
    clog << "cut() \n";
    print_delta_energy(cut_energy_J);
    clog << "\tA: " << A_M << " (m)\n";
    clog << "\tB: " << B_M << " (m)\n";
    clog << "\tC: " << C_M << " (m)\n";
    C_M -= cut_len;
    mass_KG = A_M * B_M * C_M * rho_KG_M3;
    volume_M3 = mass_KG / rho_KG_M3;
    clog << "\tC1 (after cut): " << C_M << " (m)\n";
    clog << "\tMass1: " << mass_KG << " (kg)\n";
    clog << "\tVolume1: " << volume_M3 << " (m^3)\n";
    clog << "\tC2 = " << cut_len << " (m)\n";
    clog << "\tMass2 = " << A_M * B_M * cut_len * rho_KG_M3 << " (kg)\n";
    clog << "\tVolume2 = " << A_M * B_M * cut_len << " (m^3)\n";
}

int cut() {
    if (available_energy() < cut_energy_J) {
        print_no_energy("cut", cut_energy_J);
        fly();
        return 1;
    }

    separator();

    if (cut_len > C_M) {
        clog << "cut() failed: invalid parameter.\n";
        clog << "\tParameter: " << cut_len << "\n";
        clog << "\tC: " << C_M << "\n";
        fly();
        return 1;
    }

    cut_log();
    return 0;
}

double heating_energy(double mass){
    return mass * (gold_capacity_J_KGK * (melting_temp_K - room_temp_K) + melting_energy_J_KG);
}

double cooling_energy(double mass){
    return mass * (gold_capacity_J_KGK * (melting_temp_K - space_temp_K) + melting_energy_J_KG);
}

double rec_delta_energy(double mass){
    return cooling_energy(mass) - heating_energy(mass);
}

int check_space(double v1, double v2, double m1, double m2) {
    if (v1 > MAX_VOLUME_M3 - v2 || m1 > MAX_MASS_KG - m2) {
            separator();
            clog << "accept() failed: ";
            clog << "not enough space\n";
            clog << "\tSpace: " << current_volume_M3 << " (m^3)\n";
            clog << "\tMass: " << current_mass_KG << " (kg)\n";
            clog << "\tNugget volume: " << v1 << " (m^3)\n";
            clog << "\tNugget mass: " << m1 << " (kg)\n";
            fly();
            return 0;
    }
    return 1;
}

double max_ever_cut(){
    double new_mass = 0;
    double new_volume = 0;

    if (MAX_MASS_KG - current_mass_KG >= mass_KG) {
        new_mass = C_M;
    } else {
        double remmass_KG = MAX_MASS_KG - current_mass_KG;
        new_mass = (remmass_KG)/ (rho_KG_M3 * A_M * B_M);
    }

    if (MAX_VOLUME_M3 - current_volume_M3 >= volume_M3) {
      new_volume = C_M;
    } else {
        double remvolume = MAX_VOLUME_M3 - current_volume_M3;
      new_volume = (remvolume) / (A_M * B_M);
    }
    return min(new_mass, new_volume);
}

double max_now_cut(){
    double new_energy = 0;
    double needed_energy_J = heating_energy(mass_KG);
    if (current_rec_energy_J >= needed_energy_J) {
        new_energy = C_M;
    } else {
        double avaliable_energy_J = avaliable_energy() - accept_energy_J;
        if (avaliable_energy_J + current_rec_energy_J >= needed_energy_J) {
            new_energy = C_M;
        } else {
            new_energy = C_M * ((avaliable_energy_J+current_rec_energy_J-cut_energy_J) / needed_energy_J);
        }
    }
    return new_energy;
}

bool transfer_energy(double amount) {
    if (avaliable_energy() >= amount) {
        current_rec_energy_J += amount;
        current_energy_J -= amount;
        return true;
    } else {
        return false;
    }
}

bool space_left() {
    return fabs(current_volume_M3 - MAX_VOLUME_M3) > eps
        && fabs(current_mass_KG - MAX_MASS_KG) > eps;
}

void process_nugget(double a, double b, double c) {
    if (a <= WIDTH_M && b <= HEIGHT_M) {
        add_nugget();
    } else if (a <= HEIGHT_M && b <= WIDTH_M) {
        rotate();
        add_nugget();
    } else if (a <= WIDTH_M && c <= HEIGHT_M) {
        turn();
        add_nugget();
    } else if (a <= HEIGHT_M && c <= WIDTH_M) {
        turn();
        rotate();
        add_nugget();
    } else if (b <= WIDTH_M && c <= HEIGHT_M) {
        rotate();
        turn();
        add_nugget();
    } else if (b <= HEIGHT_M && c <= WIDTH_M) {
        rotate();
        turn();
        rotate();
        add_nugget();
    } else {
        drop_good();
    }
}

void start_stealing() {
    clog << fixed << setprecision(5);
    land();

    while (space_left() && avaliable_energy() > eps){
        if (put())
            break;

        if (fabs(gold_rho_KG_M3 - rho_KG_M3) > delta_rho) {
            drop_bad();
            continue;
        }

        process_nugget(A_M, B_M, C_M);
    }

    fly();
}

