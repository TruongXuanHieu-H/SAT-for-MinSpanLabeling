#!/bin/bash

# python3 export_incremental.py   ./incremental/extended_bound    ./incremental/extended_bound/sat-incremental-extended-bound.xlsx
# python3 export_incremental.py   ./incremental/reduced_bound     ./incremental/reduced_bound/sat-incremental-reduced-bound.xlsx
# python3 export_incremental.py   ./incremental/standard_bound    ./incremental/standard_bound/sat-incremental-standard-bound.xlsx

python3 export_incremental.py   ./incremental-split-clause/reduced_bound    ./incremental-split-clause/reduced_bound/sat-incremental-reduced-bound-split-clause.xlsx

# python3 export_iteration.py     ./iteration/extended_bound      ./iteration/extended_bound/sat-iteration-extended-bound.xlsx
# python3 export_iteration.py     ./iteration/reduced_bound       ./iteration/reduced_bound/sat-iteration-reduced-bound.xlsx
# python3 export_iteration.py     ./iteration/standard_bound      ./iteration/standard_bound/sat-iteration-standard-bound.xlsx

python3 export_iteration.py   ./iteration-bfs-split-clause/reduced_bound    ./iteration-bfs-split-clause/reduced_bound/sat-iteration-bfs-reduced-bound-split-clause.xlsx

# python3 export_iteration.py     ./iteration-from-ub/extended_bound      ./iteration-from-ub/extended_bound/sat-iteration-extended-bound.xlsx
# python3 export_iteration.py     ./iteration-from-ub/reduced_bound       ./iteration-from-ub/reduced_bound/sat-iteration-reduced-bound.xlsx
# python3 export_iteration.py     ./iteration-from-ub/standard_bound      ./iteration-from-ub/standard_bound/sat-iteration-standard-bound.xlsx

python3 export_iteration.py   ./iteration-from-ub-split-clause/reduced_bound    ./iteration-from-ub-split-clause/reduced_bound/sat-iteration-from-ub-reduced-bound-split-clause.xlsx