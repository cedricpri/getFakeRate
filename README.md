Small standalone script to calculate both the fake and prompt rates using the tight-to-loose method. The script is divided into different steps.

# Step 1

It is possible to run by hand the script `runNanoFakes.C` on one particular file,

    root -l -b -q 'runNanoFakes.C("2017", "nanoLatino_DYJetsToLL_M-50__part0")

The normal thing to do is to batch submit several samples at once. The batch submission can be done reading the samples directly from a directory.

    python submit-jobs.py -d <full path of the directory>

The batch submission can also be done reading the samples from a txt file

    python submit-jobs.py -o $PWD/jobs -y 2017 -d /eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Fall2017_nAOD_v1_Full2017v2/MCl1loose2017v2__MCCorr2017__btagPerEvent/
    python submit-jobs.py -o $PWD/jobs -y 2017 -d /eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2017_nAOD_v1_Full2017v2/DATAl1loose2017v2__DATACorr2017/

The <samples.txt> file should only contain one sample per line, and should include the prefix "nanoLatino_" but NOT the complete path, which is defined in `runNanoFakes.C`. Watch out that an empty directory called "results" should be present beforehand in your working directory to keep the output of the jobs sent.


# Check job status

It is possible to check the status of the jobs by using the command

    condor_q      
    watch -n5 condor_q


# Step 2

Once all the jobs are done, two different options are available.

## getFakeRate.C

This is a small script allowing the user to compute both the fake and prompt rates, for both muons and electrons. The output is a set of png histograms.

## getLumiEff.C

This script uses the ZRegion defined in `nanoFakes.C` in order to calculate a basic data/MC ratio within the peak of the Z, to make sure that the results given by `getFakeRate.C` make sense.

