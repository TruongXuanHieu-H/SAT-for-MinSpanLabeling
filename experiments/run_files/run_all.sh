#!/bin/bash

export TZ='Asia/Ho_Chi_Minh'

scripts=(
    # "incremental/extended_bound/ite_abp_x1.5.sh"
    # "incremental/extended_bound/ite_abp_x1.25.sh"

    # "incremental/reduced_bound/ite_abp_x0.5.sh"
    # "incremental/reduced_bound/ite_abp_x0.75.sh"

    # "incremental/standard_bound/ite_abp_x0.5.sh"
    # "incremental/standard_bound/ite_abp_x0.75.sh"
    # "incremental/standard_bound/ite_abp_x1.sh"



    # "incremental-split-clause/reduced_bound/incre_abp_x0.75-0.sh"
    # "incremental-split-clause/reduced_bound/incre_abp_x0.75-5.sh"
    # "incremental-split-clause/reduced_bound/incre_abp_x0.75-10.sh"



    # "iteration-bfs/extended_bound/ite_abp_x1.5.sh"
    # "iteration-bfs/extended_bound/ite_abp_x1.25.sh"

    # "iteration-bfs/reduced_bound/ite_abp_x0.5.sh"
    # "iteration-bfs/reduced_bound/ite_abp_x0.75.sh"

    # "iteration-bfs/standard_bound/ite_abp_x0.5.sh"
    # "iteration-bfs/standard_bound/ite_abp_x0.75.sh"
    # "iteration-bfs/standard_bound/ite_abp_x1.sh"



    # "iteration-from-ub/extended_bound/ite_abp_x1.5.sh"
    # "iteration-from-ub/extended_bound/ite_abp_x1.25.sh"
    
    # "iteration-from-ub/reduced_bound/ite_abp_x0.5.sh"
    # "iteration-from-ub/reduced_bound/ite_abp_x0.75.sh"

    # "iteration-from-ub/standard_bound/ite_abp_x0.5.sh"
    # "iteration-from-ub/standard_bound/ite_abp_x0.75.sh"
    # "iteration-from-ub/standard_bound/ite_abp_x1.sh"
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