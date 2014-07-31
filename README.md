gepda
=====

gene expression and population dynamics algorithm

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