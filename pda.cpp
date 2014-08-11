// Daniel Charlebois - 2014
// A prototype of a serial implementation of the Population Dynamics Algorithm
// that was published in 2011 in Communications in Computational Physics.
// Notes: Code has not been optimized or tested extensively against analytic solutions.
// Segmentation fault occurs after ~20k cells.
#include <iostream>
#include <fstream> 
#include <cmath>
#include <cstdlib> 
#include <ctime>   
#include <string>
#include <new>
#include <algorithm>
#include <cassert>
#include <omp.h>
#include "omprng.h"
using namespace std;
class cell
{
public:
  cell ();
  void grow (double checkpoint, cell * daughter, omprng & random_number_generator);
  bool alive;
  double cell_time;
  double time_last_division;
  double volume;
  long DNA_count;
  long mRNA_count;
  long protein_count;
};
int main(int argc, char** argv)
{
  assert (argc == 2);
  int thread_count_requested = atoi(argv[1]);
  omp_set_num_threads( thread_count_requested );
  omprng random_number_generator; // omprng: OpenMP Random Number Generator
  random_number_generator.setNumThreads( thread_count_requested );
  // FILE * stats;
  // stats = fopen ("stats.tsv", "a");
  // ofstream data_file;
  // data_file.open ("data.tsv", ofstream::out | ofstream::app);
  int const cell_count=1000;
  double const simulation_end=10000;
  double const simulation_interval=3300;
  int thread_count_granted;
  cell mother[cell_count]; 
  cell daughter[cell_count];
  cell granddaughter[cell_count];
  for (int i=0; i < cell_count; ++i) // mothers spwaned
    {
      mother[i].alive = true;
    }
  double time0=omp_get_wtime();
  printf ("    thread_count machince_time(s)        cell_time\
       mRNA_level    protein_level\n");
  for (double checkpoint = simulation_interval;
       checkpoint < simulation_end; checkpoint += simulation_interval)
    {				// step through checkpoints to the end of simulation
#pragma omp parallel
      {
#pragma omp for schedule(static)
	for (int i = 0; i < cell_count; ++i)
	  {			// mothers grow to checkpoint
	    mother[i].grow(checkpoint, daughter+i, random_number_generator);
	  }
#pragma omp for schedule(static)
	for (int l = 0; l < cell_count; ++l)
	  {			// dauthers grow to checkpoint
	    if (daughter[l].alive)
	      {
		daughter[l].grow(checkpoint, granddaughter+l, random_number_generator);
	      }
	  }
#pragma omp single
	{
	  thread_count_granted = omp_get_num_threads();
	  for (int l = 0; l < cell_count; ++l)	// constant-number Monte Carlo Method
	    {
	      if (daughter[l].alive) // every daughter replace a mother randomly
		{
		  double r3 = random_number_generator.runif();
		  mother[ int( r3*cell_count ) ] = daughter[l];
		  daughter[l].alive = false;
		}
	    }
	  double time1=omp_get_wtime();
	  double total_mRNA_count = 0;
	  double total_protein_count = 0;
	  for (int i=0; i < cell_count-1; ++i)
	    {
	      total_mRNA_count+= mother[i].mRNA_count;
	      total_protein_count+= mother[i].protein_count;
	    }
	  printf ("%16d %16f %16d %16d %16d \n", thread_count_granted,
		  time1-time0, (int)checkpoint, (int)total_mRNA_count, (int)total_protein_count);
	}
      }
    }
  // double time1=omp_get_wtime();
  // double total_mRNA_count = 0;
  // double total_protein_count = 0;
  // for (int i=0; i < cell_count-1; ++i)
  //   {
  //     total_mRNA_count+= mother[i].mRNA_count;
  //     total_protein_count+= mother[i].protein_count;
  //   }
  // printf ("\nthread_count     machince_time(s) cell_time      mRNA_level       protein_level \n");
  // printf ("%-16d %-16f %-16f %-16d %-16d \n", thread_count_granted,
  // 	  time1-time0, checkpoint, (int)total_mRNA_count, (int)total_protein_count);
  // fprintf (stats, "%-16d %-16f %-16d %-16d \n", thread_count_granted,
  // 	   time1-time0, (int)total_mRNA_count, (int)total_protein_count);
  // fclose (stats);
  // data_file.close();
  return 0;
}
cell::cell () {
  alive = false;
  cell_time = 0;
  time_last_division = 0;
  volume = 1;
  DNA_count = 1;
  mRNA_count = 0;
  protein_count = 0;
}
void cell::grow (double checkpoint, cell * daughter, omprng & random_number_generator)
{
  //Stochastic Simulation Algorithm
  double const volume_initial = 1;
  double const volume_critical = 2;
  double const cell_cycle=3600;
  int i, mu;
  double h[5];
  double tau=0, amu=0;
  double const kM=0.3, kP=0.05, dM=0.05, dP=0.00005;
  assert (checkpoint-cell_time < cell_cycle);
  //initialize rxn propensity array
  h[0]=0; h[1]=0; h[2]=0; h[3]=0; h[4]=0; 
  while (cell_time < checkpoint) {
    //compute reaction propensities
    h[1] = kM*DNA_count; h[2] = kP*mRNA_count; h[3] = dM*mRNA_count; h[4] = dP*protein_count;
    h[0] = h[1] + h[2] + h[3] + h[4];
    assert (h[0] > 0);
    assert (h[1] >= 0);
    assert (h[2] >= 0);
    assert (h[3] >= 0);
    assert (h[4] >= 0);
    //generate random numbers
    double r1 = random_number_generator.runif(); // runif: Random UNIForm
    double r2 = random_number_generator.runif(); // runif: Random UNIForm
    tau = log(1/r1)/h[0];	//calculate time to next reaction
    assert (tau > 0);
    //determine next reaction
    i=1; mu=0; amu=0;
    while (amu < r2*h[0]) {
      mu = mu + 1; amu=amu+h[i];
      i = i + 1;
    }
    // carry out next reaction
    if (mu == 1) {
      mRNA_count = mRNA_count + 1; //translation (mRNA production)
    }
    else if (mu == 2) {
      protein_count = protein_count + 1; //transcription (protein production)
    }
    else if (mu == 3) {
      if (mRNA_count > 1)
      mRNA_count = mRNA_count - 1; //mRNA decay
    }
    else if (mu == 4) {
      if (protein_count > 1)
      protein_count = protein_count - 1; //protein decay
    }
    cell_time += tau;
    assert (cell_time >= 0);
    volume = volume_initial*exp(log(2)*(cell_time-time_last_division)/cell_cycle);
    if (volume > volume_critical) // a cell divides when its volume exceeds critical volume
      {
	time_last_division = cell_time;
	volume /= 2;
	mRNA_count /= 2;
	protein_count /= 2;
	*daughter = *this;
      }
  }
}
