
#ifndef _GOLD_HPP_
#define _GOLD_HPP_

#include <string>
#include "fib.hpp"

// PARAMETERS

#ifndef HEIGHT_M
    #define HEIGHT_M 0.1
#endif
#ifndef WIDTH_M
    #define WIDTH_M 0.5
#endif
#ifndef INITIAL_ENERGY_J
    #define INITIAL_ENERGY_J 25000
#endif
#ifndef MAX_VOLUME_M3
    #define MAX_VOLUME_M3 100
#endif
#ifndef MAX_MASS_KG
    #define MAX_MASS_KG 193000
#endif


// CONSTANTS
//
const std::string rocket = 
    "          !\n"
    "          !\n"
    "          ^\n"
    "         / \\\n"
    "        /___\\\n"
    "       |=   =|\n"
    "       |     |\n"
    "       |     |\n"
    "       |     |\n"
    "       |     |\n"
    "       |     |\n"
    "       |     |\n"
    "       |     |\n"
    "       |     |\n"
    "       |     |\n"
    "      /|##!##|\\\n"
    "     / |##!##| \\\n"
    "    /  |##!##|  \\\n"
    "   |  / ^ | ^ \\  |\n"
    "   | /  ( | )  \\ |\n"
    "   |/   ( | )   \\|\n"
    "       ((   ))\n"
    "      ((  :  ))\n"
    "      ((  :  ))\n"
    "       ((   ))\n"
    "        (( ))\n"
    "         ( )\n"
    "          .\n"
    "          .\n"
    "          .\n";

const double eps = 1e-8;
const int gold_rho_KG_M3 = 19300;
const int room_temp_K = 282;
const int space_temp_K = 4;
const int melting_temp_K = 1337;
const int melting_energy_J_KG = 64000;
const int gold_capacity_J_KGK = 128;                                                          /// have to pre-heat the gold by 300K
const int rotate_energy_J = 20;
const int turn_energy_J = 20;
const int put_energy_J = 10;
const int accept_energy_J = 10;
const int drop_bad_energy_J = 20;
const int drop_good_energy_J = 20;
const int cut_energy_J = 20;
const int fly_energy_J = 1000;
const double delta_rho = 600;
const int mod = 1250;
const int max_size_M = 6;


double avaliable_energy();
void print_delta_energy(double delta, bool change=true);
int fly();
void print_no_energy(const std::string& operation, double needed);
double available_energy();
int land();
int put();
int rotate();
int turn();
int drop_good();
int drop_bad();
int cut();
double heating_energy(double mass);
double cooling_energy(double mass);
double rec_delta_energy(double mass);
int accept();
double max_ever_cut();
double max_now_cut();
bool transfer_energy(double amount);
void add_nugget();
bool space_left();
void start_stealing();
void separator(int len=40);
int check_space(double, double, double, double);

// GLOBALS

Fib rnd(mod);
double cut_len = -1;
double A_M = 0;
double B_M = 0;
double C_M = 0;
double rho_KG_M3 = 0;
double mass_KG = 0;
double volume_M3 = 0;
double current_energy_J = INITIAL_ENERGY_J;
double current_rec_energy_J = 0;
double current_volume_M3 = 0;
double current_mass_KG = 0;
#endif
