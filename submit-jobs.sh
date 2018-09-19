#!/bin/bash

if [ $# -lt 1 ]; then
    echo "  "
    echo "  ./submit-jobs.sh  <samples file>"
    echo "  "
    exit -1
fi


export WORKDIRECTORY=$PWD
export SAMPLES=$1


# Submit jobs to the queues
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
export NJOBS=`grep -c ^ $SAMPLES`
echo "  And... submitting" $NJOBS "jobs"
echo "  "
mkdir -p jobs


# lxplus
#
#    -q 8nm (8 minute)
#    -q 1nh (1 hour)
#    -q 8nh (8 hour)
#    -q 1nd (1 day)
#    -q 2nd (2 day)
#    -q 1nw (1 week)
#    -q 2nw (2 week)
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
cd jobs

bsub -q 8nh -J "settings[1-$NJOBS]" -o $WORKDIRECTORY/jobs $WORKDIRECTORY/settings.lsf WORKDIRECTORY SAMPLES

# gridui
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#qsub -t 1-$NJOBS -v SAMPLES -v SYSTEMATIC settings.sge
