import os, sys, optparse

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def submit():

    print bcolors.HEADER
    print '#######################################################################'
    print '                  Starting job(s) submission...                        '
    print '#######################################################################' + bcolors.ENDC

    parser = optparse.OptionParser(usage='usage: %prog [opts] FilenameWithSamples', version='%prog 1.0')
    parser.add_option('-q', '--queue', action='store', type=str, dest='queue', default='tomorrow', help='Name of the queue to be used')
    parser.add_option('-i', '--input', action='store', type=str, dest='inputFile', default='', help='Name of the txt input file with the samples')
    parser.add_option('-o', '--output', action='store', type=str, dest='outputDir', default='/afs/cern.ch/user/c/cprieels/work/public/Fakes/CMSSW_10_1_0/src/getFakeRate/jobs', help='Output directory')
    (opts, args) = parser.parse_args()

    #Read the options given
    inputFile = opts.inputFile
    queue = opts.queue
    outputDir = opts.outputDir

    if not inputFile:
        print "You have to enter an input file by using the -i option."
        return

    if queue not in ['espresso', 'microcentury', 'longlunch', 'workday', 'tomorrow', 'testmatch', 'nextweek']:
        print "Queue not found.... Using tomorrow as default value."
        queue = "tomorrow"

    try:
        input = open(inputFile, "r")
        print "Input file successfully read, preparing the job(s) submission..."
        
    except:
        print "Input file not found, exiting... \n"
        return

    numberSamples = 0
    outputDir = outputDir+"/"

    jobList = []

    for sample in input:
            
        numberSamples += 1

        #Check the format of the sample names and correct it if necessary
        if "nanoLatino_" not in sample:
            sample += sample
            
        if ".root" in sample:
            sample = sample[:-5]

        #Remove strange characters from sample name
        sample = sample.strip(' \t\n\r')

        jobFileName = outputDir+sample+".sh"
        subFileName = outputDir+sample+".sub"
        errFileName = outputDir+sample+".err"
        outFileName = outputDir+sample+".out"
        logFileName = outputDir+sample+".log"
        #jidFileName = outputDir+sample+".jid"
        
        jobFile = open(jobFileName, "w+")
        jobFile.write("#!/bin/sh \n")
        jobFile.write("cd - \n")
        jobFile.write("cd /afs/cern.ch/user/c/cprieels/work/public/Fakes/CMSSW_10_1_0/src/getFakeRate \n")
        jobFile.write("eval `scramv1 runtime -sh` \n \n")

        jobFile.write("root -l -b -q '/afs/cern.ch/user/c/cprieels/work/public/Fakes/CMSSW_10_1_0/src/getFakeRate/runNanoFakes.C(\"" + sample + "\")' \n \n")
        jobFile.close()
        
        subFile = open(subFileName, "w+")
        subFile.write('executable = '+jobFileName+'\n')
        subFile.write('universe = vanilla\n')
        subFile.write('output = '+ outFileName +'\n')
        subFile.write('error = '+ errFileName +'\n')
        subFile.write('log = '+ logFileName +'\n')
        subFile.write('+JobFlavour  = '+ queue +'\n')
        subFile.write('queue \n')
        subFile.close()
        
        if not sample in jobList:
            jobList.append(sample)

        #Submission is done for efficiency purposes (send all the jobs at once)
        #os.system('condor_submit '+subFileName+' > ' +jidFileName)
        #print "-> File " + sample + " submitted to queue"

    completeJobFile = open(outputDir+"all.sub", "w+")    
    completeJobFile.write('executable = '+outputDir+'$(JName).sh \n')
    completeJobFile.write('universe = vanilla \n')
    completeJobFile.write('output = '+outputDir+'$(JName).out \n')
    completeJobFile.write('error = '+outputDir+'$(JName).err \n')
    completeJobFile.write('log = '+outputDir+'$(JName).log \n')
    completeJobFile.write('+JobFlavour  = '+ queue +'\n')
    completeJobFile.write('queue JName in (\n')
    for JName in jobList:
        print JName
        completeJobFile.write(JName + '\n')
    completeJobFile.write(')\n')
    
    os.system('condor_submit' + outputdir + "all.sub")
    print "Done! "+ str(numberSamples) +" jobs have been submitted. \n"        

if __name__ == "__main__":
    submit()
