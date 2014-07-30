#!/usr/bin/env bash
set -e
make
application_name="gepda.out"
# CPUPROFILE="/tmp/${application_name}.profile" CPUPROFILE_FREQUENCY=1000000 ./${application_name} 100
CPUPROFILE="/tmp/${application_name}.profile" ./${application_name}
# pprof ${application_name} ${CPUPROFILE} > profile."$(hostname -s)".pdf --pdf # --nodefraction=0.002 --edgefraction=0.001
pprof ${application_name} "/tmp/${application_name}.profile" > profile."$(hostname -s)".pdf --pdf # --nodefraction=0.002 --edgefraction=0.001
