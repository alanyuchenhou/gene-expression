gepda
=====

This project is a multi-thread simulator built upon Charlebois' earlier work on stochastic simulation algorithm (SSA) of gene expression(including translation(DNA producing mRNA), transcription(mRNA producing protein), mRNA decay and protein decay) in a cell colony. Gillespie formulated the SSA in 1977 as an exact procedure for numerically simulating the evolution of a chemical system. Since then SSA has evolved and become a popular method for chemical kinetics. There are efforts exploiting data level parallelism in the simulation to improve simulation performance. For example, Komarov demonstrated how to improve the performance with GPU implementation. There are also research in performance gain through thread level parallelism from Sanft.

system requirement
----
* this project is designed for Linux based OS

usage
----
* install gperftools

`sudo <package_manager> install gperftools`

where `<package_magager>` is aptitude, apt-get, yum, etc, depending on your Linux distribution;

* specify thread count

edit file `run` to specify how many threads the program requests from the OS;

* run the simulation and check the result

`./run`

* profile the simulation to optimize the simulation

`./profile`