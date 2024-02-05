#include <iostream>
#include <valarray>
#include <fstream>
#include "vector"

using namespace std;
double sigma=2.951,epsilon=5.29;
struct ZG_Points {
    int atomic_number;
    double x, y, z;
};
ZG_Points operator-(const ZG_Points& a, const ZG_Points& b) {
    return ZG_Points{a.atomic_number, a.x - b.x, a.y - b.y, a.z - b.z};
}
ZG_Points operator+(const ZG_Points& a, const ZG_Points& b) {
    return ZG_Points{a.atomic_number, a.x + b.x, a.y + b.y, a.z + b.z};
}
ZG_Points operator/(const ZG_Points& a, double b) {
    return ZG_Points{a.atomic_number, a.x / b, a.y / b, a.z / b};
}
ZG_Points operator*(double a, const ZG_Points& b) {
    return ZG_Points{b.atomic_number, a * b.x, a * b.y, a * b.z};
}

void print_point(const vector<ZG_Points>&point){
    for(auto & i : point){
        cout<<"x = "<<i.x<<endl;
        cout<<"y = "<<i.y<<endl;
        cout<<"z = "<<i.z<<endl;
    }
}

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

vector<ZG_Points> CalculateGradient(const vector<ZG_Points>& points,double sgm, double eps){
    vector<ZG_Points> gradient(points.size());
    auto n = points.size();
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            double distance = dis_Cal(points[i], points[j]);
            // Calculating the derivative of the Lennard-Jones potential energy
            double d_LJE = LJE(distance, eps, sgm);
            // Calculate the direction vector
            ZG_Points direction = (points[j] - points[i]) / distance;
            // Calculating the gradient
            gradient[i] = gradient[i] + d_LJE * direction;
            gradient[j] = gradient[j] - d_LJE * direction;
        }
    }
    return gradient;
}


vector<ZG_Points> Min(vector<ZG_Points> &point, double eps, double sgm,const double& con=1e-3, double step = 0.001,int max_seps=1000){
    double energy = energyrecal(point, eps, sgm);
    vector<ZG_Points> gradient = CalculateGradient(point,sgm,eps);
    double delta_energy = INFINITY;
    int steps = 0;
    while (abs(delta_energy) > con) {
        print_point(gradient);
        // one-dimensional search
        vector<ZG_Points> line_search_coords = point;
        for (size_t i = 0; i < point.size(); ++i) {
            // Move in the direction of the gradient
            line_search_coords[i] = line_search_coords[i] - step * gradient[i];
        }
        double line_search_energy = energyrecal(line_search_coords,eps,sgm);// Calculating new energy
        cout<<"line_search_energy = "<<line_search_energy<<endl;
        cout<<"energy = "<<energy<<endl;
        // If the energy decreases, the new coordinates are accepted
        if (line_search_energy < energy) {
            delta_energy = line_search_energy - energy;  // Calculating energy changes
            energy = line_search_energy;  // Renewal of energy
            point = line_search_coords;  // Update coordinates
            gradient = CalculateGradient(point,sgm,eps);  // Update Gradient
            cout<<"优化了"<<endl;
        } else {
            // If the energy increases, decrease the step size
            step *= 0.5;

        }
        steps += 1;
        if(steps >1000){
            break;
        }
        cout<<delta_energy<<endl;
    }
    cout<<abs(delta_energy)<<endl;
    // Return optimized coordinates
    return point;
}


int main(){
    vector<ZG_Points> point = readAtomsFromFile("D:\\CPPSTU\\Min\\1.txt");
    point = Min(point,epsilon,sigma);
    print_point(point);
    return 0;
}