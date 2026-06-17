#!/bin/bash

build_dir="../../build"
dataset_dir="../../benchmarks"
report_dir="../../experiments/results/ite_abp_x1"

time_limit="1800"
memory_limit="30000"
general_config="--ladder --verify-result --iterate-bfs -limit-memory $memory_limit -limit-real-time $time_limit -worker-count 8 -symmetry-break highest-degree"

mkdir -p "$report_dir"

$build_dir/mmsl_enc $dataset_dir/A-pores_1.mtx.rnd     -target-value 6      -set-lb 7   -set-ub 30      $general_config >> $report_dir/A-pores_1.txt
$build_dir/mmsl_enc $dataset_dir/B-ibm32.mtx.rnd       -target-value 9      -set-lb 10  -set-ub 32      $general_config >> $report_dir/B-ibm32.txt
$build_dir/mmsl_enc $dataset_dir/C-bcspwr01.mtx.rnd    -target-value 17     -set-lb 18  -set-ub 39      $general_config >> $report_dir/C-bcspwr01.txt
$build_dir/mmsl_enc $dataset_dir/D-bcsstk01.mtx.rnd    -target-value 9      -set-lb 10  -set-ub 48      $general_config >> $report_dir/D-bcsstk01.txt
$build_dir/mmsl_enc $dataset_dir/E-bcspwr02.mtx.rnd    -target-value 21     -set-lb 22  -set-ub 49      $general_config >> $report_dir/E-bcspwr02.txt
$build_dir/mmsl_enc $dataset_dir/F-curtis54.mtx.rnd    -target-value 13     -set-lb 14  -set-ub 54      $general_config >> $report_dir/F-curtis54.txt
$build_dir/mmsl_enc $dataset_dir/G-will57.mtx.rnd      -target-value 13     -set-lb 14  -set-ub 57      $general_config >> $report_dir/G-will57.txt
$build_dir/mmsl_enc $dataset_dir/H-impcol_b.mtx.rnd    -target-value 8      -set-lb 9   -set-ub 59      $general_config >> $report_dir/H-impcol_b.txt
$build_dir/mmsl_enc $dataset_dir/I-ash85.mtx.rnd       -target-value 24     -set-lb 25  -set-ub 85      $general_config >> $report_dir/I-ash85.txt
$build_dir/mmsl_enc $dataset_dir/J-nos4.mtx.rnd        -target-value 35     -set-lb 36  -set-ub 100     $general_config >> $report_dir/J-nos4.txt
$build_dir/mmsl_enc $dataset_dir/K-dwt__234.mtx.rnd    -target-value 51     -set-lb 52  -set-ub 117     $general_config >> $report_dir/K-dwt__234.txt
$build_dir/mmsl_enc $dataset_dir/L-bcspwr03.mtx.rnd    -target-value 39     -set-lb 40  -set-ub 118     $general_config >> $report_dir/L-bcspwr03.txt
$build_dir/mmsl_enc $dataset_dir/M-bcsstk06.mtx.rnd    -target-value 35     -set-lb 36  -set-ub 420     $general_config >> $report_dir/M-bcsstk06.txt
$build_dir/mmsl_enc $dataset_dir/N-bcsstk07.mtx.rnd    -target-value 35     -set-lb 36  -set-ub 420     $general_config >> $report_dir/N-bcsstk07.txt
$build_dir/mmsl_enc $dataset_dir/O-impcol_d.mtx.rnd    -target-value 121    -set-lb 122 -set-ub 425     $general_config >> $report_dir/O-impcol_d.txt
$build_dir/mmsl_enc $dataset_dir/P-can__445.mtx.rnd    -target-value 79     -set-lb 80  -set-ub 445     $general_config >> $report_dir/P-can__445.txt
$build_dir/mmsl_enc $dataset_dir/Q-494_bus.mtx.rnd     -target-value 220    -set-lb 221 -set-ub 494     $general_config >> $report_dir/Q-494_bus.txt
$build_dir/mmsl_enc $dataset_dir/R-dwt__503.mtx.rnd    -target-value 64     -set-lb 65  -set-ub 503     $general_config >> $report_dir/R-dwt__503.txt
$build_dir/mmsl_enc $dataset_dir/S-sherman4.mtx.rnd    -target-value 256    -set-lb 257 -set-ub 546     $general_config >> $report_dir/S-sherman4.txt
$build_dir/mmsl_enc $dataset_dir/T-dwt__592.mtx.rnd    -target-value 104    -set-lb 105 -set-ub 592     $general_config >> $report_dir/T-dwt__592.txt
$build_dir/mmsl_enc $dataset_dir/U-662_bus.mtx.rnd     -target-value 220    -set-lb 221 -set-ub 662     $general_config >> $report_dir/U-662_bus.txt
$build_dir/mmsl_enc $dataset_dir/V-nos6.mtx.rnd        -target-value 326    -set-lb 327 -set-ub 675     $general_config >> $report_dir/V-nos6.txt
$build_dir/mmsl_enc $dataset_dir/W-685_bus.mtx.rnd     -target-value 136    -set-lb 137 -set-ub 685     $general_config >> $report_dir/W-685_bus.txt
$build_dir/mmsl_enc $dataset_dir/X-can__715.mtx.rnd    -target-value 113    -set-lb 114 -set-ub 715     $general_config >> $report_dir/X-can__715.txt