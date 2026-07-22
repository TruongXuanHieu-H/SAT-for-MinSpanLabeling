#!/bin/bash

export TZ='Asia/Ho_Chi_Minh'

scripts=(
    "abp/incremental/incre_abp_x0.5-10.sh"
    "abp/incremental/incre_abp_x0.75-10.sh"
    "abp/incremental/ite_abp_x1.5.sh"
    "abp/incremental/ite_abp_x1.25.sh"
    "abp/incremental/ite_abp_x1.sh"

    "abp/iteration-bfs-reverse/ite_abp_x0.5-10.sh"
    "abp/iteration-bfs-reverse/ite_abp_x0.75-10.sh"
    "abp/iteration-bfs-reverse/ite_abp_x1.5.sh"
    "abp/iteration-bfs-reverse/ite_abp_x1.25.sh"
    "abp/iteration-bfs-reverse/ite_abp_x1.sh"

    "abp/iteration-bfs/ite_abp_x0.5-10.sh"
    "abp/iteration-bfs/ite_abp_x0.75-10.sh"
    "abp/iteration-bfs/ite_abp_x1.5.sh"
    "abp/iteration-bfs/ite_abp_x1.25.sh"
    "abp/iteration-bfs/ite_abp_x1.sh"

    "abp/iteration-from-ub/ite_abp_x0.5-10.sh"
    "abp/iteration-from-ub/ite_abp_x0.75-10.sh"
    "abp/iteration-from-ub/ite_abp_x1.5.sh"
    "abp/iteration-from-ub/ite_abp_x1.25.sh"
    "abp/iteration-from-ub/ite_abp_x1.sh"

    "cabp/iteration-bfs/ite_cabp_x0.5-10.sh"
    "cabp/iteration-bfs/ite_cabp_x0.75-10.sh"
    "cabp/iteration-bfs/ite_cabp_x1.5.sh"
    "cabp/iteration-bfs/ite_cabp_x1.25.sh"
    "cabp/iteration-bfs/ite_cabp_x1.sh"

    "cabp/iteration-from-ub/ite_cabp_x0.5-10.sh"
    "cabp/iteration-from-ub/ite_cabp_x0.75-10.sh"
    "cabp/iteration-from-ub/ite_cabp_x1.5.sh"
    "cabp/iteration-from-ub/ite_cabp_x1.25.sh"
    "cabp/iteration-from-ub/ite_cabp_x1.sh"

    "cabp/iteration-bfs-reverse/ite_cabp_x0.5-10.sh"
    "cabp/iteration-bfs-reverse/ite_cabp_x0.75-10.sh"
    "cabp/iteration-bfs-reverse/ite_cabp_x1.5.sh"
    "cabp/iteration-bfs-reverse/ite_cabp_x1.25.sh"
    "cabp/iteration-bfs-reverse/ite_cabp_x1.sh"
)

chmod +x "${scripts[@]}"

for script in "${scripts[@]}"; do
    if [ ! -f "$script" ]; then
        echo "Warning: $script not found"
        continue
    fi

    echo "======================================"
    echo "Running $script"
    echo "Started at $(date '+%Y-%m-%d %H:%M:%S %Z')"

    ./"$script"

    echo "Finished at $(date '+%Y-%m-%d %H:%M:%S %Z')"
    echo "======================================"
done