#!/bin/bash
for i in {1..2}; do
    for j in {1..3}; do
        ./shared_lib_caller ./library${i}.so function${j};
    done;
done
