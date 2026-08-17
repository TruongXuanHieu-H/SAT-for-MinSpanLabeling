#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../../../.." && pwd)"

build_dir="$ROOT_DIR/build"
dataset_dir="$ROOT_DIR/benchmarks"
report_dir="$ROOT_DIR/experiments/results/abp/iteration-from-ub/ite_abp_x0.75"

time_limit="1800"
memory_limit="30000"
general_config="--abp --ladder --no-hole --verify-result --iterate-from-ub -limit-memory $memory_limit -limit-real-time $time_limit -worker-count 8 -symmetry-break highest-degree -max-cnf-size 10"

mkdir -p "$report_dir"

$build_dir/mmsl_enc $dataset_dir/A-pores_1.mtx.rnd     -target-value 4      -set-lb 5   -set-ub 22      $general_config > $report_dir/A-pores_1.txt
$build_dir/mmsl_enc $dataset_dir/B-ibm32.mtx.rnd       -target-value 6      -set-lb 7   -set-ub 24      $general_config > $report_dir/B-ibm32.txt
$build_dir/mmsl_enc $dataset_dir/C-bcspwr01.mtx.rnd    -target-value 12     -set-lb 13  -set-ub 29      $general_config > $report_dir/C-bcspwr01.txt
$build_dir/mmsl_enc $dataset_dir/D-bcsstk01.mtx.rnd    -target-value 6      -set-lb 7   -set-ub 36      $general_config > $report_dir/D-bcsstk01.txt
$build_dir/mmsl_enc $dataset_dir/E-bcspwr02.mtx.rnd    -target-value 15     -set-lb 16  -set-ub 36      $general_config > $report_dir/E-bcspwr02.txt
$build_dir/mmsl_enc $dataset_dir/F-curtis54.mtx.rnd    -target-value 9      -set-lb 10  -set-ub 40      $general_config > $report_dir/F-curtis54.txt
$build_dir/mmsl_enc $dataset_dir/G-will57.mtx.rnd      -target-value 9      -set-lb 10  -set-ub 42      $general_config > $report_dir/G-will57.txt
$build_dir/mmsl_enc $dataset_dir/H-impcol_b.mtx.rnd    -target-value 6      -set-lb 7   -set-ub 44      $general_config > $report_dir/H-impcol_b.txt
$build_dir/mmsl_enc $dataset_dir/I-ash85.mtx.rnd       -target-value 17     -set-lb 18  -set-ub 63      $general_config > $report_dir/I-ash85.txt
$build_dir/mmsl_enc $dataset_dir/J-nos4.mtx.rnd        -target-value 26     -set-lb 27  -set-ub 75      $general_config > $report_dir/J-nos4.txt
$build_dir/mmsl_enc $dataset_dir/K-dwt__234.mtx.rnd    -target-value 38     -set-lb 39  -set-ub 87      $general_config > $report_dir/K-dwt__234.txt
$build_dir/mmsl_enc $dataset_dir/L-bcspwr03.mtx.rnd    -target-value 29     -set-lb 30  -set-ub 88      $general_config > $report_dir/L-bcspwr03.txt
$build_dir/mmsl_enc $dataset_dir/M-bcsstk06.mtx.rnd    -target-value 25     -set-lb 26  -set-ub 315     $general_config > $report_dir/M-bcsstk06.txt
$build_dir/mmsl_enc $dataset_dir/N-bcsstk07.mtx.rnd    -target-value 25     -set-lb 26  -set-ub 315     $general_config > $report_dir/N-bcsstk07.txt
$build_dir/mmsl_enc $dataset_dir/O-impcol_d.mtx.rnd    -target-value 90     -set-lb 91  -set-ub 318     $general_config > $report_dir/O-impcol_d.txt
$build_dir/mmsl_enc $dataset_dir/P-can__445.mtx.rnd    -target-value 67     -set-lb 68  -set-ub 333     $general_config > $report_dir/P-can__445.txt
$build_dir/mmsl_enc $dataset_dir/Q-494_bus.mtx.rnd     -target-value 170    -set-lb 171 -set-ub 370     $general_config > $report_dir/Q-494_bus.txt
$build_dir/mmsl_enc $dataset_dir/R-dwt__503.mtx.rnd    -target-value 47     -set-lb 48  -set-ub 377     $general_config > $report_dir/R-dwt__503.txt
$build_dir/mmsl_enc $dataset_dir/S-sherman4.mtx.rnd    -target-value 195    -set-lb 196 -set-ub 409     $general_config > $report_dir/S-sherman4.txt
$build_dir/mmsl_enc $dataset_dir/T-dwt__592.mtx.rnd    -target-value 84     -set-lb 85  -set-ub 444     $general_config > $report_dir/T-dwt__592.txt
$build_dir/mmsl_enc $dataset_dir/U-662_bus.mtx.rnd     -target-value 165    -set-lb 166 -set-ub 496     $general_config > $report_dir/U-662_bus.txt
$build_dir/mmsl_enc $dataset_dir/V-nos6.mtx.rnd        -target-value 246    -set-lb 247 -set-ub 506     $general_config > $report_dir/V-nos6.txt
$build_dir/mmsl_enc $dataset_dir/W-685_bus.mtx.rnd     -target-value 102    -set-lb 103 -set-ub 513     $general_config > $report_dir/W-685_bus.txt
$build_dir/mmsl_enc $dataset_dir/X-can__715.mtx.rnd    -target-value 87     -set-lb 88  -set-ub 536     $general_config > $report_dir/X-can__715.txt