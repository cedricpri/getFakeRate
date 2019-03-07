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
    parser.add_option('-d', '--directory', action='store', type=str, dest='inputDir', default='', help='Name of the directory where the samples can be found')
    parser.add_option('-o', '--output', action='store', type=str, dest='outputDir', default='/afs/cern.ch/user/c/cprieels/work/public/Fakes/CMSSW_10_1_0/src/getFakeRate/jobs', help='Output directory')
    parser.add_option('-t', '--test', action='store', type=float, dest='doNotSend', default=0, help='Do not send the jobs to the queue')
    parser.add_option('-y', '--year', action='store', type=str, dest='year', default="", help='Year of the dataset considered (2016, 2017 or 2018)')
    (opts, args) = parser.parse_args()

    #Read the options given
    queue = opts.queue
    inputFile = opts.inputFile
    inputDir = opts.inputDir
    outputDir = opts.outputDir
    doNotSend = opts.doNotSend
    year = opts.year

    if year == "":
        print "BE CAREFUL! You did not introduce any year, so you considering that you are reading 2016 files by default"
        year = "2016"
    elif year != "2016" and year != "2017" and year != "2018":
        print "The year given does not seem to be valid"
        return
        
    if not os.path.exists("jobs"):
        os.makedirs("jobs")

    if not os.path.exists("samples"):
        os.makedirs("samples")

    if not os.path.exists("results"):
        os.makedirs("results")

    if not inputFile:
        if not inputDir:
            print "You have to enter an input file by using the -i option, or a directory using the -d option."
            return
        else:
            inputFile = "samples/samples_to_be_submitted.txt"
            sampleFile = open(inputFile, "w+")
            samples = os.listdir(inputDir)
            for name in samples:
                name = name.replace('.root','')
                if year == "2016" and ("DYJetsToLL_M-50" in name or "WJetsToLNu__" in name or "DoubleMuon" in name or "SingleEle" in name):
                    sampleFile.write(name + "\n")
                if year == "2017" and (("DYJetsToLL_M-" in name and "HT" not in name) or "WJetsToLNu-LO__" in name or "Muon" in name or "Electron" in name):
                    #print name
                    sampleFile.write(name + "\n")
                if year == "2018" and ("DYJetsToLL_M-50" in name or "WJetsToLNu" in name or "DoubleMuon" in name or "DoubleEG" in name):
                    sampleFile.write(name + "\n")
            sampleFile.close()

    if queue not in ['espresso', 'microcentury', 'longlunch', 'workday', 'tomorrow', 'testmatch', 'nextweek']:
        print "Queue not found.... Using tomorrow as default value."
        queue = "tomorrow"

    try:
        finput = open(inputFile, "r")
        #print finput.read()
        print "Input file successfully read, preparing the job(s) submission..."
        
    except:
        print "Input file not found, exiting... \n"
        return

    numberSamples = 0
    outputDir = outputDir+"/"

    jobList = []

    for sample in finput:
        
        if sample == "" or sample == "\n" or ("part" not in sample):
            continue

        numberSamples += 1
            
        #Check the format of the sample names and correct it if necessary
        if "nanoLatino_" not in sample:
            sample = "nanoLatino_"+sample
            
        if ".root" in sample:
            sample = sample[:-5]

        #Remove strange characters from sample name
        sample = sample.strip(' \t\n\r')

        jobFileName = outputDir+sample+".sh"
        subFileName = outputDir+sample+".sub"
        errFileName = outputDir+sample+".err"
        outFileName = outputDir+sample+".out"
        logFileName = outputDir+sample+".log"
        jidFileName = outputDir+sample+".jid"
        
        jobFile = open(jobFileName, "w+")
        jobFile.write("#!/bin/sh \n")
        jobFile.write("cd - \n")
        jobFile.write("cd /afs/cern.ch/user/c/cprieels/work/public/Fakes/CMSSW_10_1_0/src/getFakeRate \n")
        jobFile.write("eval `scramv1 runtime -sh` \n \n")

        jobFile.write("root -l -b -q '/afs/cern.ch/user/c/cprieels/work/public/Fakes/CMSSW_10_1_0/src/getFakeRate/runNanoFakes.C(\"" + year + "\", \"" + sample + "\")' \n \n")
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
        #Submission is not done here for efficiency purposes (send all the jobs at once)
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
        #print JName
        if JName != "" and JName != "\n":
            completeJobFile.write(JName + '\n')
    completeJobFile.write(')\n')
    #completeJobFile.write('queue JName from '+inputFile)
    completeJobFile.close()

    if doNotSend == 0:
        #os.system("rm samples/samples_to_be_submitted.txt")
        print outputDir
        os.system("condor_submit " + outputDir + "all.sub")
        print "Done! "+ str(numberSamples) +" jobs have been submitted. \n"        
    else:
        print "Sample file created but jobs not sent to the queue. \n"

if __name__ == "__main__":
    submit()
