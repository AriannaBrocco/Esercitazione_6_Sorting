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
vector<int> generaVettoreCasuale(unsigned  int dimensione)
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

int main()
{
    int dimensione_piccola;
    int dimensione_elevata;
    int dimensione_ordinato;

    // Chiede all'utente di inserire le dimensioni dei vettori per effetture i test sulla velocità di esecuzione degli algoritmi
    cout <<  "Inserire dimensione piccola: " << endl;
    cin >> dimensione_piccola;
    cout <<  "Inserire dimensione elevata: " << endl;
    cin >> dimensione_elevata;
    cout <<  "Inserire dimensione per un vettore gia' ordinato: " << endl;
    cin >> dimensione_ordinato;

    // Misura del tempo necessario per ordinare vettori di piccole dimensioni con MergeSort
    // Il ciclo si ripete 100 volte per poter avere una media dei tempi e quindi risultati più accurati
    double tempo_mergesort_pic = 0;
    double media_mergesort_pic = 0;
    for(unsigned int i=0; i< 100; i++){
        // Genera un vettore casuale di interi
        vector<int> vettoreInteri_pic = generaVettoreCasuale(dimensione_piccola);
        steady_clock::time_point t_begin = steady_clock::now();
        MergeSort(vettoreInteri_pic);
        steady_clock::time_point t_end = steady_clock::now();
        double tempo_int = duration_cast<microseconds>(t_end - t_begin).count();
        tempo_mergesort_pic = tempo_mergesort_pic + tempo_int;
    }
    media_mergesort_pic = tempo_mergesort_pic/100;

    cout<< "Algoritmo MergeSort: " << endl;
    cout<< "La media dei tempi necessari per ordinare vettori di piccole dimensioni e': " << fixed << setprecision(4) << media_mergesort_pic<< endl;

    // Con vettori di grandi dimensioni
    double tempo_mergesort_el = 0;
    double media_mergesort_el = 0;
    for(unsigned int i=0; i< 100; i++){
        vector<int> vettoreInteri_el = generaVettoreCasuale(dimensione_elevata);
        steady_clock::time_point t_begin = steady_clock::now();
        MergeSort(vettoreInteri_el);
        steady_clock::time_point t_end = steady_clock::now();
        double tempo_int = duration_cast<microseconds>(t_end - t_begin).count();
        tempo_mergesort_el = tempo_mergesort_el + tempo_int;
    }
    media_mergesort_el = tempo_mergesort_el/100;

    cout<< "La media dei tempi necessari per ordinare vettori di grandi dimensioni e': " << fixed << setprecision(4) << media_mergesort_el<< endl;

    // Misura del tempo necessario per ordinare vettori di piccole dimensioni con BubbleSort
    double tempo_bubblesort_pic = 0;
    double media_bubblesort_pic = 0;
    for(unsigned int i=0; i< 100; i++){
        vector<int> vettoreInteri_pic = generaVettoreCasuale(dimensione_piccola);
        steady_clock::time_point t_begin = steady_clock::now();
        BubbleSort(vettoreInteri_pic);
        steady_clock::time_point t_end = steady_clock::now();
        double tempo_int = duration_cast<microseconds>(t_end - t_begin).count();
        tempo_bubblesort_pic = tempo_bubblesort_pic + tempo_int;
    }
    media_bubblesort_pic = tempo_bubblesort_pic/100;

    cout<< "Algoritmo BubbleSort: " << endl;
    cout<< "La media dei tempi necessari per ordinare vettori di piccole dimensioni e: " << fixed << setprecision(4) << media_bubblesort_pic<< endl;

    // Con vettori di grandi dimensioni
    double tempo_bubblesort_el = 0;
    double media_bubblesort_el = 0;
    for(unsigned int i=0; i< 100; i++){
        vector<int> vettoreInteri_el = generaVettoreCasuale(dimensione_elevata);
        steady_clock::time_point t_begin = steady_clock::now();
        BubbleSort(vettoreInteri_el);
        steady_clock::time_point t_end = steady_clock::now();
        double tempo_int = duration_cast<microseconds>(t_end - t_begin).count();
        tempo_bubblesort_el = tempo_bubblesort_el + tempo_int;
    }
    media_bubblesort_el = tempo_bubblesort_el/100;

    cout<< "La media dei tempi necessari per ordinare vettori di grandi dimensioni e': " << fixed << setprecision(4) << media_bubblesort_el<< endl;

    // Caso particolare: vettore già ordinato
    // MergeSort
    double tempo_mergesort_ordinato = 0;
    double media_mergesort_ordinato = 0;
    for(unsigned int i=0; i< 100; i++){
        vector<int> vettoreInteri_ord = generaVettoreCasuale(dimensione_ordinato);
        // Ordino il vettore per poi calcolare il tempo impiegato per ordinare un vettore già ordinato
        MergeSort(vettoreInteri_ord);
        steady_clock::time_point t_begin = steady_clock::now();
        MergeSort(vettoreInteri_ord);
        steady_clock::time_point t_end = steady_clock::now();
        double tempo_int = duration_cast<microseconds>(t_end - t_begin).count();
        tempo_mergesort_ordinato = tempo_mergesort_ordinato + tempo_int;
    }
    media_mergesort_ordinato = tempo_mergesort_ordinato/100;

    cout<< "Con MergeSort, la media dei tempi necessari per ordinare vettori gia' precedentemente ordinati e': " << fixed << setprecision(4) << media_mergesort_ordinato << endl;

    // BubbleSort
    double tempo_bubblesort_ordinato = 0;
    double media_bubblesort_ordinato = 0;
    for(unsigned int i=0; i< 100; i++){
        vector<int> vettoreInteri_ord = generaVettoreCasuale(dimensione_ordinato);
        BubbleSort(vettoreInteri_ord);
        steady_clock::time_point t_begin = steady_clock::now();
        BubbleSort(vettoreInteri_ord);
        steady_clock::time_point t_end = steady_clock::now();
        double tempo_int = duration_cast<microseconds>(t_end - t_begin).count();
        tempo_bubblesort_ordinato = tempo_bubblesort_ordinato + tempo_int;
    }
    media_bubblesort_ordinato = tempo_bubblesort_ordinato/100;

    cout<< "Con BubbleSort, la media dei tempi necessari per ordinare vettori gia' precedentemente ordinati e': " << fixed << setprecision(4) << media_bubblesort_ordinato<< endl;

    // Confronto tra i due algoritmi
    string alg1 = "MergeSort";
    string alg2 = "BubbleSort";
    if (media_mergesort_pic < media_bubblesort_pic)
    {
        cout << alg1 << " e' piu' veloce di " << alg2 << " per vettori di dimensione piccola: " << dimensione_piccola << endl;
    }
    else
    {
        cout << alg2 << " e' piu' veloce di " << alg1 << " per vettori di dimensione piccola: " << dimensione_piccola << endl;
    }

    if (media_mergesort_el < media_bubblesort_el)
    {
        cout << alg1 << " e' piu' veloce di " << alg2 << " per vettori di dimensione grande: " << dimensione_elevata << endl;
    }
    else
    {
        cout << alg2 << " e' piu' veloce di " << alg1 << " per vettori di dimensione grande: " << dimensione_elevata << endl;
    }

    if (media_mergesort_ordinato < media_bubblesort_ordinato)
    {
        cout << alg1 << " e' piu' veloce di " << alg2 << " per vettori gia' precedentemente ordinati di dimensione: " << dimensione_ordinato << endl;
    }
    else
    {
        cout << alg2 << " e' piu' veloce di " << alg1 << " per vettori gia' precedentemente ordinati di dimensione: " << dimensione_ordinato << endl;
    }

    return 0;
}













