Small standalone script to calculate both the fake and prompt rates using a general tight to loose method. The script is divided into several different steps:

# Step 1

It is either possible to run by hand the script runNanoFakes.C on one particular file, or to batch submit several samples at once (from a txt file), using the following command

      python submit-jobs.py -i <samples.txt>

It is possible to checkthe status of the jobs by using the command 

      condor_q      
      watch -n5 condor_q

The <samples.txt> file should only contain one sample per line, and should include the prefix "nanoLatino_" but NOT the complete path, which is defined in runNanoFakes.C
Watch out that an empty directory called "results" should be present before hand in your working directory to keep the output of the jobs sent.

# Step 2

Once all the jobs are done, two different options are available:

## getFakeRate.C

This is a small script allowing the user to compute both the fake and prompt rates, for both muons and electrons. The output is a direct set of png histograms.

## getLumiEff.C

This script uses the ZRegion defined in nanoFakes.C in order to calculate a basic data/MC ratio within the peak of the Z, to make sure that the results given by getFakeRate.C make sense.

More detailed instructions coming soon!
