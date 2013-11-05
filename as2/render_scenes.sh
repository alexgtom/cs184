#!/bin/bash

time  ./main -f testscenes/scene1.test
time  ./main -f testscenes/scene2.test
time  ./main -f testscenes/scene3.test
time  ./main -f testscenes/scene4-emission.test
time  ./main -f testscenes/scene4-specular.test
#time  ./main -f testscenes/scene5.test # this test has a million spheres.
time  ./main -f testscenes/scene6.test
