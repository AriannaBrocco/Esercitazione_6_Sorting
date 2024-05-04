#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <unistd.h>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include "SortingAlgorithm.hpp"
#include "Eigen/Eigen"

using namespace std;
using namespace chrono;
using namespace SortLibrary;


// Funzione per generare un vettore casuale
vector<int> generaVettoreCasuale(unsigned int dimensione)
{
    unsigned int n = 0;
    vector<int> vettore(dimensione);
    generate(vettore.begin(), vettore.end(), [&n] () {return n++;});

    for(unsigned int i =0; i < dimensione; i++)
    {
        vettore[i] =rand( ) %100;  // dà un numero tra 0 e 100
    }

    return vettore;
}

int main(int argc, char **argv)
{
    int dimensione_piccola = atoi(argv[1]);
    int dimensione_elevata = atoi(argv[2]);
    if (argc!=1)
        cerr << "qualcosa non va" << endl;

    // Genera un vettore casuale di interi
    cout <<  "Inserire dimensione piccola: " << endl;
    cin >> dimensione_piccola;
    cout << "Hai inserito: " << dimensione_piccola << endl;
    cout <<  "Inserire dimensione elevata: " << endl;
    cin >> dimensione_elevata;
    cout << "Hai inserito: " << dimensione_elevata << endl;
    cout << "La dimensione elevata sara' utilizzata anche per il caso particolare" << endl;
    vector<int> vettoreInteri_pic = generaVettoreCasuale(dimensione_piccola);
    vector<int> vettoreInteri_el = generaVettoreCasuale(dimensione_elevata);


    // Misura del tempo per ordinare con mergesort
    // con vettore di piccola dimensione
    double tempo_mergesort_pic = 0;
    double media_mergesort_pic = 0;
    for(unsigned int i=0; i< 100; i++){
        steady_clock::time_point t_begin = steady_clock::now();
        MergeSort(vettoreInteri_pic);
        steady_clock::time_point t_end = steady_clock::now();
        double tempo_int = duration_cast<microseconds>(t_end - t_begin).count();
        tempo_mergesort_pic = tempo_mergesort_pic + tempo_int;
    }
    media_mergesort_pic = tempo_mergesort_pic/100;

    cout<< "Algoritmo MergeSort: " << endl;
    cout<< "La media dei tempi necessari per ordinare vettori di piccole dimensioni e': " << fixed << setprecision(4) << media_mergesort_pic<< endl;

    // con vettore di grandi dimensioni
    double tempo_mergesort_el = 0;
    double media_mergesort_el = 0;
    for(unsigned int i=0; i< 100; i++){
        steady_clock::time_point t_begin = steady_clock::now();
        MergeSort(vettoreInteri_el);
        steady_clock::time_point t_end = steady_clock::now();
        double tempo_int = duration_cast<microseconds>(t_end - t_begin).count();
        tempo_mergesort_el = tempo_mergesort_el + tempo_int;
    }
    media_mergesort_el = tempo_mergesort_el/100;

    cout<< "La media dei tempi necessari per ordinare vettori di grandi dimensioni e': " << fixed << setprecision(4) << media_mergesort_el<< endl;

    // Misura del tempo per ordinare con bubblesort
    // con vettore di piccola dimensione
    double tempo_bubblesort_pic = 0;
    double media_bubblesort_pic = 0;
    for(unsigned int i=0; i< 100; i++){
        steady_clock::time_point t_begin = steady_clock::now();
        BubbleSort(vettoreInteri_pic);
        steady_clock::time_point t_end = steady_clock::now();
        double tempo_int = duration_cast<microseconds>(t_end - t_begin).count();
        tempo_bubblesort_pic = tempo_bubblesort_pic + tempo_int;
    }
    media_bubblesort_pic = tempo_bubblesort_pic/100;
    cout<< "Algoritmo BubbleSort: " << endl;
    cout<< "La media dei tempi necessari per ordinare vettori di piccole dimensioni e: " << fixed << setprecision(4) << media_bubblesort_pic<< endl;

    double tempo_bubblesort_el = 0;
    double media_bubblesort_el = 0;
    for(unsigned int i=0; i< 100; i++){
        steady_clock::time_point t_begin = steady_clock::now();
        BubbleSort(vettoreInteri_el);
        steady_clock::time_point t_end = steady_clock::now();
        double tempo_int = duration_cast<microseconds>(t_end - t_begin).count();
        tempo_bubblesort_el = tempo_bubblesort_el + tempo_int;
    }
    media_bubblesort_el = tempo_bubblesort_el/100;
    cout<< "La media dei tempi necessari per ordinare vettori di grandi dimensioni e': " << fixed << setprecision(4) << media_bubblesort_el<< endl;

    // Caso particolare: vettore già ordinato
    double tempo_mergesort_ordinato = 0;
    double media_mergesort_ordinato = 0;
    for(unsigned int i=0; i< 100; i++){
        // Ordino il vettore per poi calcolare il tempo impiegato per ordinare un vettore già ordinato
        MergeSort(vettoreInteri_el);
        steady_clock::time_point t_begin = steady_clock::now();
        MergeSort(vettoreInteri_el);
        steady_clock::time_point t_end = steady_clock::now();
        double tempo_int = duration_cast<microseconds>(t_end - t_begin).count();
        tempo_mergesort_ordinato = tempo_mergesort_ordinato + tempo_int;
    }
    media_mergesort_ordinato = tempo_mergesort_ordinato/100;

    cout<< "Con MergeSort, la media dei tempi necessari per ordinare vettori gia' precedentemente ordinati e': " << fixed << setprecision(4) << media_mergesort_ordinato << endl;

    // con vettore di grandi dimensioni
    double tempo_bubblesort_ordinato = 0;
    double media_bubblesort_ordinato = 0;
    for(unsigned int i=0; i< 100; i++){
        // Ordino il vettore per poi calcolare il tempo impiegato per ordinare un vettore gia' ordinato
        BubbleSort(vettoreInteri_el);
        steady_clock::time_point t_begin = steady_clock::now();
        BubbleSort(vettoreInteri_el);
        steady_clock::time_point t_end = steady_clock::now();
        double tempo_int = duration_cast<microseconds>(t_end - t_begin).count();
        tempo_bubblesort_ordinato = tempo_bubblesort_ordinato + tempo_int;
    }
    media_bubblesort_ordinato = tempo_bubblesort_ordinato/100;

    cout<< "Con BubbleSort, la media dei tempi necessari per ordinare vettori gia' precedentemente ordinati e': " << fixed << setprecision(4) << media_bubblesort_ordinato<< endl;



    return 0;
}













