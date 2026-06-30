#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../../../.." && pwd)"

build_dir="$ROOT_DIR/build"
dataset_dir="$ROOT_DIR/benchmarks"
report_dir="$ROOT_DIR/experiments/results/incremental/extended_bound/incre_abp_x1.5"

time_limit="1800"
memory_limit="30000"
general_config="--ladder --has-hole --verify-result --incremental-from-ub -limit-memory $memory_limit -limit-real-time $time_limit -symmetry-break highest-degree"

mkdir -p "$report_dir"

$build_dir/mmsl_enc $dataset_dir/A-pores_1.mtx.rnd     -target-value 9   -set-lb 10  -set-ub 45   $general_config > $report_dir/A-pores_1.txt
$build_dir/mmsl_enc $dataset_dir/B-ibm32.mtx.rnd       -target-value 13  -set-lb 14  -set-ub 48   $general_config > $report_dir/B-ibm32.txt
$build_dir/mmsl_enc $dataset_dir/C-bcspwr01.mtx.rnd    -target-value 25  -set-lb 26  -set-ub 59   $general_config > $report_dir/C-bcspwr01.txt
$build_dir/mmsl_enc $dataset_dir/D-bcsstk01.mtx.rnd    -target-value 13  -set-lb 14  -set-ub 72   $general_config > $report_dir/D-bcsstk01.txt
$build_dir/mmsl_enc $dataset_dir/E-bcspwr02.mtx.rnd    -target-value 31  -set-lb 32  -set-ub 74   $general_config > $report_dir/E-bcspwr02.txt
$build_dir/mmsl_enc $dataset_dir/F-curtis54.mtx.rnd    -target-value 19  -set-lb 20  -set-ub 81   $general_config > $report_dir/F-curtis54.txt
$build_dir/mmsl_enc $dataset_dir/G-will57.mtx.rnd      -target-value 19  -set-lb 20  -set-ub 86   $general_config > $report_dir/G-will57.txt
$build_dir/mmsl_enc $dataset_dir/H-impcol_b.mtx.rnd    -target-value 12  -set-lb 13  -set-ub 89   $general_config > $report_dir/H-impcol_b.txt
$build_dir/mmsl_enc $dataset_dir/I-ash85.mtx.rnd       -target-value 34  -set-lb 35  -set-ub 128  $general_config > $report_dir/I-ash85.txt
$build_dir/mmsl_enc $dataset_dir/J-nos4.mtx.rnd        -target-value 52  -set-lb 53  -set-ub 150  $general_config > $report_dir/J-nos4.txt
$build_dir/mmsl_enc $dataset_dir/K-dwt__234.mtx.rnd    -target-value 76  -set-lb 77  -set-ub 176  $general_config > $report_dir/K-dwt__234.txt
$build_dir/mmsl_enc $dataset_dir/L-bcspwr03.mtx.rnd    -target-value 58  -set-lb 59  -set-ub 178  $general_config > $report_dir/L-bcspwr03.txt
$build_dir/mmsl_enc $dataset_dir/M-bcsstk06.mtx.rnd    -target-value 51  -set-lb 52  -set-ub 630  $general_config > $report_dir/M-bcsstk06.txt
$build_dir/mmsl_enc $dataset_dir/N-bcsstk07.mtx.rnd    -target-value 51  -set-lb 52  -set-ub 630  $general_config > $report_dir/N-bcsstk07.txt
$build_dir/mmsl_enc $dataset_dir/O-impcol_d.mtx.rnd    -target-value 180 -set-lb 181 -set-ub 638  $general_config > $report_dir/O-impcol_d.txt
$build_dir/mmsl_enc $dataset_dir/P-can__445.mtx.rnd    -target-value 135 -set-lb 136 -set-ub 668  $general_config > $report_dir/P-can__445.txt
$build_dir/mmsl_enc $dataset_dir/Q-494_bus.mtx.rnd     -target-value 340 -set-lb 341 -set-ub 741  $general_config > $report_dir/Q-494_bus.txt
$build_dir/mmsl_enc $dataset_dir/R-dwt__503.mtx.rnd    -target-value 94  -set-lb 95  -set-ub 755  $general_config > $report_dir/R-dwt__503.txt
$build_dir/mmsl_enc $dataset_dir/S-sherman4.mtx.rnd    -target-value 391 -set-lb 392 -set-ub 819  $general_config > $report_dir/S-sherman4.txt
$build_dir/mmsl_enc $dataset_dir/T-dwt__592.mtx.rnd    -target-value 169 -set-lb 170 -set-ub 888  $general_config > $report_dir/T-dwt__592.txt
$build_dir/mmsl_enc $dataset_dir/U-662_bus.mtx.rnd     -target-value 330 -set-lb 331 -set-ub 993  $general_config > $report_dir/U-662_bus.txt
$build_dir/mmsl_enc $dataset_dir/V-nos6.mtx.rnd        -target-value 493 -set-lb 494 -set-ub 1013 $general_config > $report_dir/V-nos6.txt
$build_dir/mmsl_enc $dataset_dir/W-685_bus.mtx.rnd     -target-value 204 -set-lb 205 -set-ub 1028 $general_config > $report_dir/W-685_bus.txt
$build_dir/mmsl_enc $dataset_dir/X-can__715.mtx.rnd    -target-value 174 -set-lb 175 -set-ub 1073 $general_config > $report_dir/X-can__715.txt