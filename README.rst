gene-expression
====

.. contents::

What is gene-expression?
----
gene-expression is a C++ program for biomedical simulation for gene expression and population dynamics in a homogeneous cell colony. It uses parallel computing and stochastic simulation algorithm of gene expression. The biomedical process includs translation(DNA producing mRNA), transcription(mRNA producing protein), mRNA decay and protein decay. The cell colony is in a time invariant homogeneous ideal environment.

Features
----
Here are just a few of the things gene-expression does:

- Object oriented design emphasizing individual cells
- Cell growth model incorporating stochastic simulation for cell age, size and compound levels
- Constant number Monte Calo method for computation and memory load control
- Multi-threaded simulation for individual cell growths taking advantage of paralle computing capability
- Built in performance profiling with pprof to provide information for simulation optimization

Dependencies
----

- C++11
- GNU Make: http://www.gnu.org/software/make/
- gperftools 2.3: https://github.com/gperftools/gperftools

To install required packages, use the following command::

 sudo apt-get install gperftools

Code
----

To get a copy of the source code, clone the git repository using the the following command::

 git clone https://github.com/yuchenhou/gene-expression.git

Usage
----

- edit file `run` to specify how many threads the program shall request from the OS;
- run the simulation and check the result::
 ./run

- edit file `profile` to specify the profiling results file
- profile the simulation to optimize the simulation::
 ./profile

Authors
----
