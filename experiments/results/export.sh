#!/bin/bash

# python3 export_incremental.py   ./abp/incremental           ./abp/incremental/abp-sat-incremental.xlsx
# python3 export_iteration.py     ./abp/iteration-bfs         ./abp/iteration-bfs/abp-sat-iteration-bfs.xlsx
# python3 export_iteration.py     ./abp/iteration-from-ub     ./abp/iteration-from-ub/abp-sat-iteration-from-ub.xlsx

python3 export_iteration.py     ./cabp/iteration-bfs        ./cabp/iteration-bfs/cabp-sat-iteration-bfs.xlsx
python3 export_iteration.py     ./cabp/iteration-from-ub    ./cabp/iteration-from-ub/cabp-sat-iteration-from-ub.xlsx