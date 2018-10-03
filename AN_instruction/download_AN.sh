svn co -N svn+ssh://svn.cern.ch/reps/tdr2 AN-17-142
cd AN-17-142 
svn update utils
svn update -N notes
svn update notes/AN-17-142
eval `./notes/tdr runtime -sh` 
cd notes/AN-17-142/trunk
tdr --style=an b AN-17-142

