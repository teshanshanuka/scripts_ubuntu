#!/bin/bash

trap 'while [ 1 ]; do echo `date +"%T.%N"` >> /root/test/termsh.t; sleep 1; done' SIGTERM

echo $$
while [ 1 ]; do sleep 1; done
