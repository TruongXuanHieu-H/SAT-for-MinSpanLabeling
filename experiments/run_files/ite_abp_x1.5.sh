#!/bin/bash

build_dir="../../build"
dataset_dir="../../benchmarks"
report_dir="../../experiments/results/ite_abp_x1.5"

time_limit="1800"
memory_limit="30000"
general_config="--ladder --verify-result --iterate-bfs -limit-memory $memory_limit -limit-real-time $time_limit -worker-count 8 -symmetry-break highest-degree"

mkdir -p "$report_dir"

$build_dir/mmsl_enc $dataset_dir/A-pores_1.mtx.rnd     -target-value 9      -set-lb 10  -set-ub 45      $general_config >> $report_dir/A-pores_1.txt
$build_dir/mmsl_enc $dataset_dir/B-ibm32.mtx.rnd       -target-value 14     -set-lb 15  -set-ub 48      $general_config >> $report_dir/B-ibm32.txt
$build_dir/mmsl_enc $dataset_dir/C-bcspwr01.mtx.rnd    -target-value 26     -set-lb 27  -set-ub 59      $general_config >> $report_dir/C-bcspwr01.txt
$build_dir/mmsl_enc $dataset_dir/D-bcsstk01.mtx.rnd    -target-value 14     -set-lb 15  -set-ub 72      $general_config >> $report_dir/D-bcsstk01.txt
$build_dir/mmsl_enc $dataset_dir/E-bcspwr02.mtx.rnd    -target-value 32     -set-lb 33  -set-ub 74      $general_config >> $report_dir/E-bcspwr02.txt
$build_dir/mmsl_enc $dataset_dir/F-curtis54.mtx.rnd    -target-value 20     -set-lb 21  -set-ub 81      $general_config >> $report_dir/F-curtis54.txt
$build_dir/mmsl_enc $dataset_dir/G-will57.mtx.rnd      -target-value 20     -set-lb 21  -set-ub 86      $general_config >> $report_dir/G-will57.txt
$build_dir/mmsl_enc $dataset_dir/H-impcol_b.mtx.rnd    -target-value 12     -set-lb 13  -set-ub 89      $general_config >> $report_dir/H-impcol_b.txt
$build_dir/mmsl_enc $dataset_dir/I-ash85.mtx.rnd       -target-value 36     -set-lb 37  -set-ub 128     $general_config >> $report_dir/I-ash85.txt
$build_dir/mmsl_enc $dataset_dir/J-nos4.mtx.rnd        -target-value 53     -set-lb 54  -set-ub 150     $general_config >> $report_dir/J-nos4.txt
$build_dir/mmsl_enc $dataset_dir/K-dwt__234.mtx.rnd    -target-value 77     -set-lb 78  -set-ub 176     $general_config >> $report_dir/K-dwt__234.txt
$build_dir/mmsl_enc $dataset_dir/L-bcspwr03.mtx.rnd    -target-value 59     -set-lb 60  -set-ub 178     $general_config >> $report_dir/L-bcspwr03.txt
$build_dir/mmsl_enc $dataset_dir/M-bcsstk06.mtx.rnd    -target-value 53     -set-lb 54  -set-ub 630     $general_config >> $report_dir/M-bcsstk06.txt
$build_dir/mmsl_enc $dataset_dir/N-bcsstk07.mtx.rnd    -target-value 53     -set-lb 54  -set-ub 630     $general_config >> $report_dir/N-bcsstk07.txt
$build_dir/mmsl_enc $dataset_dir/O-impcol_d.mtx.rnd    -target-value 182    -set-lb 183 -set-ub 638     $general_config >> $report_dir/O-impcol_d.txt
$build_dir/mmsl_enc $dataset_dir/P-can__445.mtx.rnd    -target-value 119    -set-lb 120 -set-ub 668     $general_config >> $report_dir/P-can__445.txt
$build_dir/mmsl_enc $dataset_dir/Q-494_bus.mtx.rnd     -target-value 330    -set-lb 331 -set-ub 741     $general_config >> $report_dir/Q-494_bus.txt
$build_dir/mmsl_enc $dataset_dir/R-dwt__503.mtx.rnd    -target-value 96     -set-lb 97  -set-ub 755     $general_config >> $report_dir/R-dwt__503.txt
$build_dir/mmsl_enc $dataset_dir/S-sherman4.mtx.rnd    -target-value 384    -set-lb 385 -set-ub 819     $general_config >> $report_dir/S-sherman4.txt
$build_dir/mmsl_enc $dataset_dir/T-dwt__592.mtx.rnd    -target-value 156    -set-lb 157 -set-ub 888     $general_config >> $report_dir/T-dwt__592.txt
$build_dir/mmsl_enc $dataset_dir/U-662_bus.mtx.rnd     -target-value 330    -set-lb 331 -set-ub 993     $general_config >> $report_dir/U-662_bus.txt
$build_dir/mmsl_enc $dataset_dir/V-nos6.mtx.rnd        -target-value 489    -set-lb 490 -set-ub 1013    $general_config >> $report_dir/V-nos6.txt
$build_dir/mmsl_enc $dataset_dir/W-685_bus.mtx.rnd     -target-value 204    -set-lb 205 -set-ub 1028    $general_config >> $report_dir/W-685_bus.txt
$build_dir/mmsl_enc $dataset_dir/X-can__715.mtx.rnd    -target-value 170    -set-lb 171 -set-ub 1073    $general_config >> $report_dir/X-can__715.txt