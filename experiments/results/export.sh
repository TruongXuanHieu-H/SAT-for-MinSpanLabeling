#!/bin/bash

python3 export_incremental.py   ./abp/incremental               ./abp/incremental/abp-sat-incremental.xlsx
python3 export_iteration.py     ./abp/iteration-bfs-reverse     ./abp/iteration-bfs-reverse/abp-sat-iteration-bfs-reverse.xlsx

python3 export_iteration.py     ./cabp/iteration-bfs-reverse    ./cabp/iteration-bfs-reverse/cabp-sat-iteration-bfs-reverse.xlsx