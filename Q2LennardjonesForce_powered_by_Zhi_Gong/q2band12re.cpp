//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <cmath>
//#include <stdexcept>
//#include <string>
//#include <zconf.h>
//#include <cmath>
//#include <sstream>
//
//using namespace std;
//
//// Get its atomic number and x, y, z coordinates. Reference site: https://www.zhihu.com/question/54725226/answer/140852975
//struct ZG_Points {
//    int atomic_number;
//    double x, y, z;
//};
//// Reads the input file. Reference site: https://zhuanlan.zhihu.com/p/352961501
//vector<ZG_Points> readAtomsFromFile(const string& fileName) {
//    ifstream fileStream(fileName);
//    if (fileStream.fail()) {
//        throw logic_error("read file fail");
//    }
//
//    int n;
//    fileStream >> n;
//
//    vector<ZG_Points> atoms(n);
//    for(int i=0; i<n; i++){
//        fileStream >> atoms[i].atomic_number >> atoms[i].x >> atoms[i].y >> atoms[i].z;
//    }
//
//    fileStream.close();
//    return atoms;
//}
//
//// Calculates the distance between two atoms.
//double dis_Cal(const ZG_Points& a, const ZG_Points& b) {
//    return sqrt((a.x - b.x) * (a.x - b.x) +
//                (a.y - b.y) * (a.y - b.y) +
//                (a.z - b.z) * (a.z - b.z));
//}
//
//// Calculates the Lennard-Jones potential energy between two atoms.
//double LJE(double distance, double epsilon, double sigma) {
//    double rates = sigma / distance;
//    double thelater = pow(rates, 6);
//    double theformer = thelater * thelater;
//    return epsilon * (theformer - 2*thelater);
//}
//
//double proeng(const vector<ZG_Points>& a, double epsilon, double sigma) {
//    double total_energy = 0;
//    auto n = a.size();
//    for(int i=0; i<n-1; i++){
//        for(int j=i+1; j<n; j++){
//            double distance = dis_Cal(a[i], a[j]);
//            total_energy += LJE(distance, epsilon, sigma);
//        }
//    }
//    return total_energy;
//}
//
//// Calculate the analytical forces and central/forward force on all atoms based on the Lennard-Jones potential.
//int anaforce(vector<ZG_Points> a){
//    auto n = a.size();
//    cout<<"F_LJ_analytical"<<endl;
//    double sigma=2.951,epsilon=5.29;
//    vector<vector<double>> directions(n, vector<double>(3, 0));
//    for(int i=0;i<n;i++){
//        for(int j=0;j<n;j++){
//            if(i==j) continue;
//            double r=pow(pow(a[i].x-a[j].x,2)+pow(a[i].y-a[j].y,2)+pow(a[i].z-a[j].z,2),0.5);
//            double fctt=epsilon*(12*pow((sigma/r),12)/r-2*6*pow((sigma/r),6)/r);
//            directions[i][0]+=fctt*(a[i].x-a[j].x)/r;
//            directions[i][1]+=fctt*(a[i].y-a[j].y)/r;
//            directions[i][2]+=fctt*(a[i].z-a[j].z)/r;
//        }
//    }
//    for(int i=0;i<3;i++){
//        for(int j=0;j<n;j++){
//            cout<<directions[j][i]<<'	';
//        }
//        cout<<endl;
//    }
//    return 0;
//}
//
////int approximationforce(vector<ZG_Points>& a, double epsilon, double sigma, double step){
////    cout<<"Stepsize for finite difference:"<<step<<endl;
////    cout<<"F_LJ_forward_difference"<<endl;
////    int n = a.size();
////    for(int i=0;i<3;i++){
////        for(int j=0;j<n;j++){
////            double eng=0;
////            if(i==0) a[j].x+=step;
////            else if(i==1) a[j].y+=step;
////            else a[j].z+=step;
////            eng = proeng(a, epsilon, sigma);
////            if(i==0) a[j].x-=step;
////            else if(i==1) a[j].y-=step;
////            else a[j].z-=step;
////            cout<<-(eng-0)/step<<'	';
////        }
////        cout<<endl;
////    }
////    cout<<"F_LJ_central_difference"<<endl;
////    for(int i=0;i<3;i++){
////        for(int j=0;j<n;j++){
////            double eng1=0,eng2=0;
////            if(i==0) a[j].x+=step;
////            else if(i==1) a[j].y+=step;
////            else a[j].z+=step;
////            eng1 = proeng(a, epsilon, sigma);
////            if(i==0) a[j].x-=2*step;
////            else if(i==1) a[j].y-=2*step;
////            else a[j].z-=2*step;
////            eng2 = proeng(a, epsilon, sigma);
////            if(i==0) a[j].x+=step;
////            else if(i==1) a[j].y+=step;
////            else a[j].z+=step;
////            cout<<-(eng1-eng2)/step/2<<'	';
////        }
////        cout<<endl;
////    }
////    return 0;
////}
//int calforce(vector<ZG_Points>& a,double eng0, double epsilon, double sigma, double step){
//    cout<<"Stepsize for finite difference:"<<step<<endl;
//    cout<<"F_LJ_forward_difference"<<endl;
//    auto n = a.size();
//
//    for(int i=0;i<3;i++){
//        for(int j=0;j<n;j++){
//            if(i==0) a[j].x+=step;
//            else if(i==1) a[j].y+=step;
//            else a[j].z+=step;
//            double eng = proeng(a, epsilon, sigma);
//            if(i==0) a[j].x-=step;
//            else if(i==1) a[j].y-=step;
//            else a[j].z-=step;
//            cout<<-(eng-eng0)/step<<'	';
//        }
//        cout<<endl;
//    }
//    cout<<"F_LJ_central_difference"<<endl;
//    for(int i=0;i<3;i++){
//        for(int j=0;j<n;j++){
//            double eng1=0,eng2=0;
//            if(i==0) a[j].x+=step;
//            else if(i==1) a[j].y+=step;
//            else a[j].z+=step;
//            eng1 = proeng(a, epsilon, sigma);
//            if(i==0) a[j].x-=2*step;
//            else if(i==1) a[j].y-=2*step;
//            else a[j].z-=2*step;
//            eng2 = proeng(a, epsilon, sigma);
//            if(i==0) a[j].x+=step;
//            else if(i==1) a[j].y+=step;
//            else a[j].z+=step;
//            cout<<-(eng1-eng2)/step/2<<'	';
//        }
//        cout<<endl;
//    }
//    return 0;
//}
//
//// Main function to drive the program.
//int main() {
//    const double sigma = 2.951; // Parameter for gold atoms (in Angstroms)
//    const double epsilon = 5.29; // Parameter for gold atoms (in kcal/mol)
//    const string input_filename = R"(D:\CPPSTU\HW1\1.txt)";
//    const string output_filename = R"(D:\CPPSTU\HW1\output.txt)";
//    ofstream output_file(output_filename);
//    if (!output_file) {
//        cerr << "Error: Cannot open output file." << '\n';
//        return 1;
//    }
//    try {
//        vector<ZG_Points> atoms = readAtomsFromFile(input_filename);
//        double eng0 =  proeng(atoms,epsilon,sigma);
//        cout<<"E_LJ = "<<eng0<<endl;
//        anaforce(atoms);
//        calforce(atoms,eng0,epsilon,sigma,0.1);
//        calforce(atoms,eng0,epsilon,sigma,0.01);
//        calforce(atoms,eng0,epsilon,sigma,0.001);
//        calforce(atoms,eng0,epsilon,sigma,0.0001);
//    } catch (const runtime_error& e) {
//        cerr << "Error: " << e.what() << '\n';
//        output_file << "Error: " << e.what() << '\n'; // Write the error to the output file as well
//        return 1;
//    }
//    output_file.close();
//    return 0;
//}
//
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>
#include <zconf.h>
#include <cmath>
#include <sstream>

using namespace std;

// Get its atomic number and x, y, z coordinates. Reference site: https://www.zhihu.com/question/54725226/answer/140852975
struct ZG_Points {
    int atomic_number;
    double x, y, z;
};
// Reads the input file. Reference site: https://zhuanlan.zhihu.com/p/352961501
vector<ZG_Points> readAtomsFromFile(const string& fileName) {
    ifstream fileStream(fileName);
    if (fileStream.fail()) {
        throw logic_error("read file fail");
    }

    int n;
    fileStream >> n;

    vector<ZG_Points> atoms(n);
    for(int i=0; i<n; i++){
        fileStream >> atoms[i].atomic_number >> atoms[i].x >> atoms[i].y >> atoms[i].z;
    }

    fileStream.close();
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

double energyrecal(const vector<ZG_Points>& a, double epsilon, double sigma) {
    double total_energy = 0;
    auto n = a.size();
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            double distance = dis_Cal(a[i], a[j]);
            total_energy += LJE(distance, epsilon, sigma);
        }
    }
    return total_energy;
}

// Calculate the analytical forces and central/forward force on all atoms based on the Lennard-Jones potential.
int analyticalforcecal(vector<ZG_Points> a){
    auto n = a.size();
    cout<<"F_LJ_analytical"<<endl;
    double sigma=2.951,epsilon=5.29;
    vector<vector<double>> directions(n, vector<double>(3, 0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) continue;
            double r=pow(pow(a[i].x-a[j].x,2)+pow(a[i].y-a[j].y,2)+pow(a[i].z-a[j].z,2),0.5);
            double fctt=epsilon*(12*pow((sigma/r),12)/r-2*6*pow((sigma/r),6)/r);
            directions[i][0]+=fctt*(a[i].x-a[j].x)/r;
            directions[i][1]+=fctt*(a[i].y-a[j].y)/r;
            directions[i][2]+=fctt*(a[i].z-a[j].z)/r;
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<n;j++){
            cout<<directions[j][i]<<'	';
        }
        cout<<endl;
    }
    return 0;
}

int approximationforce(vector<ZG_Points>& a, double eng0, double epsilon, double sigma, double step){
    cout<<"Stepsize for finite difference:"<<step<<endl;
    cout<<"F_LJ_forward_difference"<<endl;
    auto n = a.size();

    for(int i=0;i<3;i++){
        for(int j=0;j<n;j++){
            if(i==0) a[j].x+=step;
            else if(i==1) a[j].y+=step;
            else a[j].z+=step;
            double eng = energyrecal(a, epsilon, sigma);
            if(i==0) a[j].x-=step;
            else if(i==1) a[j].y-=step;
            else a[j].z-=step;
            cout<<-(eng-eng0)/step<<'	';
        }
        cout<<endl;
    }
    cout<<"F_LJ_central_difference"<<endl;
    for(int i=0;i<3;i++){
        for(int j=0;j<n;j++){
            double eng1=0,eng2=0;
            if(i==0) a[j].x+=step;
            else if(i==1) a[j].y+=step;
            else a[j].z+=step;
            eng1 = energyrecal(a, epsilon, sigma);
            if(i==0) a[j].x-=2*step;
            else if(i==1) a[j].y-=2*step;
            else a[j].z-=2*step;
            eng2 = energyrecal(a, epsilon, sigma);
            if(i==0) a[j].x+=step;
            else if(i==1) a[j].y+=step;
            else a[j].z+=step;
            cout<<-(eng1-eng2)/step/2<<'	';
        }
        cout<<endl;
    }
    return 0;
}



// Main function to drive the program.
int main() {
    const double sigma = 2.951; // Parameter for gold atoms (in Angstroms)
    const double epsilon = 5.29; // Parameter for gold atoms (in kcal/mol)
    const string input_filename = R"(D:\CPPSTU\HW1\1.txt)";
    const string output_filename = R"(D:\CPPSTU\HW1\output.txt)";
    ofstream output_file(output_filename);
    if (!output_file) {
        cerr << "Error: Cannot open output file." << '\n';
        return 1;
    }
    try {
        vector<ZG_Points> atoms = readAtomsFromFile(input_filename);
        double eng0 =  energyrecal(atoms,epsilon,sigma);
        cout<<"E_LJ = "<<eng0<<endl;
        analyticalforcecal(atoms);
        approximationforce(atoms, eng0, epsilon, sigma, 0.1);
        approximationforce(atoms, eng0, epsilon, sigma, 0.01);
        approximationforce(atoms, eng0, epsilon, sigma, 0.001);
        approximationforce(atoms, eng0, epsilon, sigma, 0.0001);
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << '\n';
        output_file << "Error: " << e.what() << '\n'; // Write the error to the output file as well
        return 1;
    }
    output_file.close();
    return 0;
}

