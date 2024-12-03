#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

void print_vector(vector<int> &v){
    for (int i = 0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

bool is_safe(vector<int> &v){
    bool valid = true;
    bool est_croissant = (v[0]<=v[1]);
    for (int i=0; (i+1)<v.size() && valid; i++){
        valid = valid && ( ( (est_croissant && (v[i] <= v[i+1])) || (!est_croissant && (v[i] >= v[i+1])) )
                            && (1 <= abs(v[i]-v[i+1])) && (abs(v[i]-v[i+1]) <= 3) );
    }
    //cout << valid << endl;
    return valid;
}

bool is_approx_safe(vector<int> &v){
    bool valid = is_safe(v);
    for (int rm = 0; !valid && rm<v.size(); rm++){
        vector<int> u;
        for (int i = 0; i<v.size(); i++){
            if (i!=rm) u.push_back(v[i]);
        }
        valid = (valid || is_safe(u));
    }
    return valid;
}

int exo1(vector< vector<int> > &lines){
    int safe_lines = 0;
    for (auto e : lines){
        if (is_safe(e)) safe_lines++;
    }
    return safe_lines;
}

int exo2(vector< vector<int> > &lines){
    int safe_lines = 0;
    for (auto e : lines){
        if (is_approx_safe(e)) safe_lines++;
    }
    return safe_lines;
}

vector< vector<int> > readFile(string const fname){
    ifstream input(fname.c_str());
    vector< vector<int> > lines;
    int i = 0;
    string line;
    for (int nb; getline(input, line) ; i++){
        vector<int> v;
        stringstream linestream(line); // On transforme la ligne en input.
        linestream >> nb;
        while (linestream){
            v.push_back(int(nb));
            linestream >> nb;
        }
        lines.push_back(v);
    }
    return lines;
}

int main()
{
    auto lines = readFile("../Inputs/input2.txt");
    cout << exo1(lines) << endl;
    cout << exo2(lines) << endl;
    return 0;
}
