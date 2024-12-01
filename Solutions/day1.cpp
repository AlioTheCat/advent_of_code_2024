#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void remontee(int* &liste, int elem, int taille){ //La liste est supposée triée.
    int bus = elem;
    for (int i = 0; (i<taille); i++){
        if (liste[i] > bus) {
            int tmp = liste[i];
            liste[i] = bus;
            bus = tmp;
        }
    }
    liste[taille] = bus;
}

int taille_fichier(ifstream& strm){
    int T = 0; 
    for (string foo; getline(strm, foo); T++);
    return T;
}

int exo1(int* &liste_g, int* &liste_d, int taille){
    int somme = 0;
    for (int i = 0; i<taille; i++){
        somme += abs(liste_g[i] - liste_d[i]);
    }
    return somme;
}

int exo2(int* &liste_g, int* &liste_d, int taille){
    int similarite = 0;
    int i = 0; int j = 0; int n = 0;
    while (i<taille && j<taille){
        n = liste_g[i];
        int incr = 0;
        while (liste_d[j]<=n){ // D'abord on avance dans la liste de droite pour trouver le nb de présence à droite.
            if (liste_d[j]==n) incr+=n;
            j++;
        }
        while (liste_g[i]==n){ // Puis on incrémente le compteur pour chaque présence à gauche.
            similarite += incr;
            i++;
        }
    }
    return similarite;
}

int main()
{
    string const nom("../Inputs/input1.txt");
    ifstream input(nom.c_str());
    ifstream copy(nom.c_str());
    int taille = taille_fichier(copy);
    int* liste_g = new int [taille];
    int* liste_d = new int [taille];
    int N = 0;
    string line;
    for (int a, b; getline(input, line) ; N++){
        istringstream linestream(line); // On transforme la ligne en input.
        linestream >> a >> b;
        remontee(liste_g, a, N); remontee(liste_d, b, N); // On trie les listes au fur et à mesure.
    }
    cout << exo1(liste_g, liste_d, taille) << endl;
    cout << exo2(liste_g, liste_d, taille) << endl;
    return 0;
}
