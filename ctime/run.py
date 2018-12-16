import glob, os
from shutil import copyfile
import subprocess
import filecmp
import sys
import time

print ("-- How to use this tool:")
print ("-- execute this app \"run\" from your working directory")
print ("-- please put your .cpp, I.x and O.x files in the same directory")


# look for the main cpp <project_name>.cpp and find project name

for file in glob.glob("*.cpp"):
    
    break

print(file)

if file is None or not os.path.isfile(file):
    print("Error - no *.cpp in current dir. Are you in your working dir?")
    sys.exit()

project = file[:-4] # get the section before ".cpp"
print ("Detected project name: "+project)


# test the existence of the executable (same as project name)
if os.path.isfile(project):
    print ("INFO - found executable file")
else:
    print ("ERROR - could not find the executable file. Have you built it?")


# Return: 
# Test result: true/false

def oneround(projectName, testNo):
    inFile = "I."+str(testNo)
    resultFile = "O."+str(testNo)
    exeFile = "./"+projectName
    testInFile = projectName+".in"
    testOutFile = projectName + ".out"
    
    # copy <testName>.in as <projectName>.in
    copyfile(inFile, testInFile)

    # run it
    print subprocess.check_output([exeFile])

    # check the existence of output file
    if not os.path.isfile(testOutFile):
        print ("ERROR - could not find "+ testOutFile +" .check whether your app generates the output file")
        return False

    # compare <project_name>.out with m.out

    
    return filecmp.cmp(testOutFile, resultFile, shallow=False)
    



# repeat the following for I.1, I.2....I.x


tot = 0
for infile in glob.glob("I.*"):
    # skip interim test file in this count
    if infile==project+".in":
        continue
    tot += 1

print ("INFO - found total "+ str(tot) + " test cases")

suc = 0


for i in range(1, tot+1):
    
    print ("INFO - start test round: " + str(i))
    # check existence of the output file
    if not os.path.isfile("O."+str(i)):
        print ("ERROR - could not find O."+ str(i) )
        break

    # proceed with test

    start = time.time()
    if oneround(project, i):
        stop = time.time()
        print ("OK - passed test round: "+ str(i))
        print("Time: " + str(stop - start))
    else:
        stop = time.time();
        print ("ERROR - failed test round: " + str(i))
        print("Time: " + str(stop - start))
        break

    suc += 1

if suc == tot:
    print ("OK. Congratulations!! All passed!!")
else:
    print ("ERROR - Passed "+ str(suc)+ " out of "+ str(tot) + " . keep working on it")


