#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../../../.." && pwd)"

build_dir="$ROOT_DIR/build"
dataset_dir="$ROOT_DIR/benchmarks"
report_dir="$ROOT_DIR/experiments/results/cabp/iteration-bfs-reverse/ite_cabp_x0.75_no_hole"

time_limit="1800"
memory_limit="45000"
general_config="--cabp --ladder --no-hole --verify-result --iterate-bfs-reverse -limit-memory $memory_limit -limit-real-time $time_limit -worker-count 8 -symmetry-break highest-degree -max-cnf-size 10"

mkdir -p "$report_dir"

$build_dir/mmsl_enc $dataset_dir/A-pores_1.mtx.rnd     -target-value 4      -set-lb 5   -set-ub 22      $general_config > $report_dir/A-pores_1.txt
$build_dir/mmsl_enc $dataset_dir/B-ibm32.mtx.rnd       -target-value 6      -set-lb 7   -set-ub 24      $general_config > $report_dir/B-ibm32.txt
$build_dir/mmsl_enc $dataset_dir/C-bcspwr01.mtx.rnd    -target-value 9      -set-lb 10  -set-ub 29      $general_config > $report_dir/C-bcspwr01.txt
$build_dir/mmsl_enc $dataset_dir/D-bcsstk01.mtx.rnd    -target-value 6      -set-lb 7   -set-ub 36      $general_config > $report_dir/D-bcsstk01.txt
$build_dir/mmsl_enc $dataset_dir/E-bcspwr02.mtx.rnd    -target-value 12     -set-lb 13  -set-ub 36      $general_config > $report_dir/E-bcspwr02.txt
$build_dir/mmsl_enc $dataset_dir/F-curtis54.mtx.rnd    -target-value 7      -set-lb 8   -set-ub 40      $general_config > $report_dir/F-curtis54.txt
$build_dir/mmsl_enc $dataset_dir/G-will57.mtx.rnd      -target-value 8      -set-lb 9   -set-ub 42      $general_config > $report_dir/G-will57.txt
$build_dir/mmsl_enc $dataset_dir/H-impcol_b.mtx.rnd    -target-value 5      -set-lb 6   -set-ub 44      $general_config > $report_dir/H-impcol_b.txt
$build_dir/mmsl_enc $dataset_dir/I-ash85.mtx.rnd       -target-value 15     -set-lb 16  -set-ub 63      $general_config > $report_dir/I-ash85.txt
$build_dir/mmsl_enc $dataset_dir/J-nos4.mtx.rnd        -target-value 24     -set-lb 25  -set-ub 75      $general_config > $report_dir/J-nos4.txt
$build_dir/mmsl_enc $dataset_dir/K-dwt__234.mtx.rnd    -target-value 34     -set-lb 35  -set-ub 87      $general_config > $report_dir/K-dwt__234.txt
$build_dir/mmsl_enc $dataset_dir/L-bcspwr03.mtx.rnd    -target-value 21     -set-lb 22  -set-ub 88      $general_config > $report_dir/L-bcspwr03.txt
$build_dir/mmsl_enc $dataset_dir/M-bcsstk06.mtx.rnd    -target-value 24     -set-lb 25  -set-ub 315     $general_config > $report_dir/M-bcsstk06.txt
$build_dir/mmsl_enc $dataset_dir/N-bcsstk07.mtx.rnd    -target-value 24     -set-lb 25  -set-ub 315     $general_config > $report_dir/N-bcsstk07.txt
$build_dir/mmsl_enc $dataset_dir/O-impcol_d.mtx.rnd    -target-value 78     -set-lb 79  -set-ub 318     $general_config > $report_dir/O-impcol_d.txt
$build_dir/mmsl_enc $dataset_dir/P-can__445.mtx.rnd    -target-value 65     -set-lb 66  -set-ub 333     $general_config > $report_dir/P-can__445.txt
$build_dir/mmsl_enc $dataset_dir/Q-494_bus.mtx.rnd     -target-value 123    -set-lb 124 -set-ub 370     $general_config > $report_dir/Q-494_bus.txt
$build_dir/mmsl_enc $dataset_dir/R-dwt__503.mtx.rnd    -target-value 46     -set-lb 47  -set-ub 377     $general_config > $report_dir/R-dwt__503.txt
$build_dir/mmsl_enc $dataset_dir/S-sherman4.mtx.rnd    -target-value 193    -set-lb 194 -set-ub 409     $general_config > $report_dir/S-sherman4.txt
$build_dir/mmsl_enc $dataset_dir/T-dwt__592.mtx.rnd    -target-value 84     -set-lb 85  -set-ub 444     $general_config > $report_dir/T-dwt__592.txt
$build_dir/mmsl_enc $dataset_dir/U-662_bus.mtx.rnd     -target-value 123    -set-lb 124 -set-ub 496     $general_config > $report_dir/U-662_bus.txt
$build_dir/mmsl_enc $dataset_dir/V-nos6.mtx.rnd        -target-value 246    -set-lb 247 -set-ub 506     $general_config > $report_dir/V-nos6.txt
$build_dir/mmsl_enc $dataset_dir/W-685_bus.mtx.rnd     -target-value 85     -set-lb 86  -set-ub 513     $general_config > $report_dir/W-685_bus.txt
$build_dir/mmsl_enc $dataset_dir/X-can__715.mtx.rnd    -target-value 75     -set-lb 76  -set-ub 536     $general_config > $report_dir/X-can__715.txt