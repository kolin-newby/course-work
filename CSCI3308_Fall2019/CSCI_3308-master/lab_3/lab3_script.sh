#!/bin/bash
# Author : Kolin Newby
# Date : 9/19/2019
# Problem 1 Code:

# prompt user for file and regex and take input
#echo "Input file name: "
#read file
#echo "Input RegEx Pattern: "
#read pattern

# Problem 2 Code:

# uses pattern and filename to grep file
#grep $pattern $file

# Problem 3 Code:

# grep -c [0-9][0-9][0-9]-[0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]\$ "regex_practice.txt"

# Problem 4 Code: 

#grep -Ec '([a-z]|[0-9]|.|_|-)*@[a-z]*.(edu|com)' "regex_practice.txt"

#grep -Eo '303-[0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]$' "regex_practice.txt"

#grep -E '^([0-9]|[a-z]|.|_|-)*@geocities.com$' "regex_practice.txt" >> "email_results.txt"

#git add "email_results.txt"

git commit -m "email list results"
