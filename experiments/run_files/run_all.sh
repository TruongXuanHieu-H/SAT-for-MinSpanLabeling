#!/bin/bash

chmod +x *.sh

for script in *.sh; do
    [ "$script" = "$(basename "$0")" ] && continue

    echo "======================================"
    echo "Running $script"
    echo "Started at $(date)"

    ./"$script"

    echo "Finished at $(date)"
    echo "======================================"
done