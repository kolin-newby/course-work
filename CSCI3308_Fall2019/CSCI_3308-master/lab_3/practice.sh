#!/bin/bash
# Author : Kolin Newby
# Date: 9/19/2019
# Script follows here:
echo "Enter a number: $0"
echo "Enter a second number: $1"
sum=$(($numOne + $numTwo))
echo "The sum is : $sum"
let prod=numOne*numTwo
echo "The product is: $prod"
grep $1 $2
