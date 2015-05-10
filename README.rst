gene-expression
====

.. contents::

What is gene-expression?
----

Gene-expression is a C++ program for biomedical simulation for gene expression and population dynamics in a homogeneous cell colony. It uses parallel computing and stochastic simulation algorithm of gene expression. The biomedical process includes translation(DNA producing mRNA), transcription(mRNA producing protein), mRNA decay and protein decay. The cell colony is in a time invariant homogeneous ideal environment. 

Features
----

Here are just a few of the things gene-expression does well:

- Object oriented design emphasizing individual cells
- Cell growth model incorporating stochastic simulation for cell age, size and compound levels
- Constant number Monte Calo method for computation and memory load control
- Multi-threaded simulation for individual cell growths taking advantage of parallel computing capability
- Built in performance profiling with pprof to provide information for simulation optimization

Dependencies
----

The following packages are required:

- C++11
- GNU Make: http://www.gnu.org/software/make/
- gperftools: https://github.com/gperftools/gperftools

To install required packages, use the following command::

 sudo apt-get install gperftools

Code
----

To get a copy of the source code, clone the git repository using the the following command::

 git clone https://github.com/yuchenhou/gene-expression.git

Usage
----

Edit file ``run`` to specify how many threads the program shall request from the OS.

Run the simulation and check the result::

 ./run

Edit file ``profile`` to specify the profiling results file.

Profile the simulation to optimize the simulation::

 ./profile

Background
----

In a cell colony, the population(number) of the cells changes with time, due to cell divisions and deaths. This phenomenon is called population dynamics. On the other hand, the chemical reactions in translation, transcription and compounds decay processes result in related compounds level changes with time. This phenomenon is called gene expression. This program simulates all the above processes and record the population and compound levels during the whole experiments for biomedical research.

Authors
----
