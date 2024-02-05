#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>

using namespace std;

// Get its atomic number and x, y, z coordinates. Reference site: https://www.zhihu.com/question/54725226/answer/140852975
struct ZG_Points {
    int atomic_number;
    double x, y, z;
};

// Reads the input file. Reference site: https://zhuanlan.zhihu.com/p/352961501
vector<ZG_Points> read_atoms_from_file(const string& file_name) {
    vector<ZG_Points> atoms;
    ifstream fin(file_name);
    
    if (!fin) {
        throw runtime_error("Cannot open file: " + file_name);
    }

    int total_numbers_of_atoms;
    fin >> total_numbers_of_atoms; // Read the first line to get the number of atoms

    ZG_Points atom;
    for (int i = 0; i < total_numbers_of_atoms; ++i) {
        fin >> atom.atomic_number >> atom.x >> atom.y >> atom.z;
        if (atom.atomic_number != 79) { // Check if the atom is gold
            throw runtime_error("WARNING: This atom is not gold.");
        }
        atoms.push_back(atom); // Add atom to the vector to contin
    }

    return atoms;
}

// Calculates the distance between two atoms.
double dis_Cal(const ZG_Points& a, const ZG_Points& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) +
                (a.y - b.y) * (a.y - b.y) +
                (a.z - b.z) * (a.z - b.z));
}

// Calculates the Lennard-Jones potential energy between two atoms.
double LJE(double distance, double epsilon, double sigma) {
    double rates = sigma / distance;
    
    double thelater = pow(rates, 6);
    double theformer = thelater * thelater;
    return epsilon * (theformer - 2*thelater);


}

// Main function to drive the program.
int main() {
    const double sigma = 2.951; // Parameter for gold atoms (in Angstroms)
    const double epsilon = 5.29; // Parameter for gold atoms (in kcal/mol)
    const string input_filename = "3.txt"; 
    // Dearest Xiao, here is the file name of input one, which is okay to CHANGED to test the samples.
    
    const string output_filename = "output4.txt"; 

    ofstream output_file(output_filename);
    if (!output_file) {
        cerr << "Error: Cannot open output file." << '\n';
        return 1;
    }

    try {
        vector<ZG_Points> atoms = read_atoms_from_file(input_filename);

        // Echo the input to the output
        for (const ZG_Points& atom : atoms) {
            output_file << atom.atomic_number
                        << "(" << atom.x << ", " << atom.y << ", " << atom.z << ")\n";
        }

        double calculatedtotal = 0.0; // Initialize total Lennard-Jones potential energy

        // Compute the total Lennard-Jones potential energy of the cluster
        for (size_t i = 0; i < atoms.size(); ++i) {
            for (size_t j = i + 1; j < atoms.size(); ++j) {
                double distance = dis_Cal(atoms[i], atoms[j]);
                calculatedtotal += LJE(distance, epsilon, sigma);
            }
        }

        // Output the total energy to the output file
        output_file << "E_LJ = "
                    << calculatedtotal << "\n";
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << '\n';
        output_file << "Error: " << e.what() << '\n'; // Write the error to the output file as well
        return 1;
    }

    output_file.close();

    return 0;
}
