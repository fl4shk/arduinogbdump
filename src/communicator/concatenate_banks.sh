#!/bin/bash

cat ${1}_bank_[[:digit:]].bin ${1}_bank_[[:digit:]][[:digit:]].bin ${1}_bank_[[:digit:]][[:digit:]][[:digit:]].bin >> ${1}.gb 
#rm ${1}_bank*
