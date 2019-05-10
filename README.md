Small standalone script to calculate both the fake and prompt rates using the tight-to-loose method. The script is divided into different steps.


# Step 1

It is possible to run by hand the script `runNanoFakes.C` on one particular file,

    root -l -b -q 'runNanoFakes.C("2017", "nanoLatino_DYJetsToLL_M-50__part0")'

The normal thing to do is to batch submit several samples at once. The batch submission can be done reading the samples directly from a directory.

    python submitJobs.py -d <full path of the directory>


# Check job status

It is possible to check the status of the jobs by using the command

    condor_q      
    watch -n5 condor_q


# Step 2

An hadd is necessary once all the jobs are done.

    cd results
    hadd hadd_data.root  nanoLatino_*_Run201*.root
    hadd hadd_wjets.root nanoLatino_WJetsToLNu*.root
    hadd hadd_zjets.root nanoLatino_DYJetsToLL*.root

Two different options are then available.


## getFakeRate.C

This is a small script allowing the user to compute both the fake and prompt rates, for both muons and electrons. The output is a set of png histograms.


## getLumiEff.C

This script uses the ZRegion defined in `nanoFakes.C` in order to calculate a basic data/MC ratio within the peak of the Z, to make sure that the results given by `getFakeRate.C` make sense.
