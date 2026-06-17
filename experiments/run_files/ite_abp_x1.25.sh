#!/bin/bash

build_dir="../../build"
dataset_dir="../../benchmarks"
report_dir="../../experiments/results/ite_abp_x1.25"

time_limit="1800"
memory_limit="30000"
general_config="--ladder --verify-result --iterate-bfs -limit-memory $memory_limit -limit-real-time $time_limit -worker-count 8 -symmetry-break highest-degree"

mkdir -p "$report_dir"

$build_dir/mmsl_enc $dataset_dir/A-pores_1.mtx.rnd     -target-value 8      -set-lb 9   -set-ub 38      $general_config >> $report_dir/A-pores_1.txt
$build_dir/mmsl_enc $dataset_dir/B-ibm32.mtx.rnd       -target-value 11     -set-lb 12  -set-ub 40      $general_config >> $report_dir/B-ibm32.txt
$build_dir/mmsl_enc $dataset_dir/C-bcspwr01.mtx.rnd    -target-value 21     -set-lb 22  -set-ub 49      $general_config >> $report_dir/C-bcspwr01.txt
$build_dir/mmsl_enc $dataset_dir/D-bcsstk01.mtx.rnd    -target-value 11     -set-lb 12  -set-ub 60      $general_config >> $report_dir/D-bcsstk01.txt
$build_dir/mmsl_enc $dataset_dir/E-bcspwr02.mtx.rnd    -target-value 26     -set-lb 27  -set-ub 62      $general_config >> $report_dir/E-bcspwr02.txt
$build_dir/mmsl_enc $dataset_dir/F-curtis54.mtx.rnd    -target-value 16     -set-lb 17  -set-ub 68      $general_config >> $report_dir/F-curtis54.txt
$build_dir/mmsl_enc $dataset_dir/G-will57.mtx.rnd      -target-value 16     -set-lb 17  -set-ub 72      $general_config >> $report_dir/G-will57.txt
$build_dir/mmsl_enc $dataset_dir/H-impcol_b.mtx.rnd    -target-value 10     -set-lb 11  -set-ub 74      $general_config >> $report_dir/H-impcol_b.txt
$build_dir/mmsl_enc $dataset_dir/I-ash85.mtx.rnd       -target-value 30     -set-lb 31  -set-ub 107     $general_config >> $report_dir/I-ash85.txt
$build_dir/mmsl_enc $dataset_dir/J-nos4.mtx.rnd        -target-value 44     -set-lb 45  -set-ub 125     $general_config >> $report_dir/J-nos4.txt
$build_dir/mmsl_enc $dataset_dir/K-dwt__234.mtx.rnd    -target-value 64     -set-lb 65  -set-ub 147     $general_config >> $report_dir/K-dwt__234.txt
$build_dir/mmsl_enc $dataset_dir/L-bcspwr03.mtx.rnd    -target-value 49     -set-lb 50  -set-ub 148     $general_config >> $report_dir/L-bcspwr03.txt
$build_dir/mmsl_enc $dataset_dir/M-bcsstk06.mtx.rnd    -target-value 44     -set-lb 45  -set-ub 525     $general_config >> $report_dir/M-bcsstk06.txt
$build_dir/mmsl_enc $dataset_dir/N-bcsstk07.mtx.rnd    -target-value 44     -set-lb 45  -set-ub 525     $general_config >> $report_dir/N-bcsstk07.txt
$build_dir/mmsl_enc $dataset_dir/O-impcol_d.mtx.rnd    -target-value 151    -set-lb 152 -set-ub 531     $general_config >> $report_dir/O-impcol_d.txt
$build_dir/mmsl_enc $dataset_dir/P-can__445.mtx.rnd    -target-value 99     -set-lb 100 -set-ub 557     $general_config >> $report_dir/P-can__445.txt
$build_dir/mmsl_enc $dataset_dir/Q-494_bus.mtx.rnd     -target-value 275    -set-lb 276 -set-ub 618     $general_config >> $report_dir/Q-494_bus.txt
$build_dir/mmsl_enc $dataset_dir/R-dwt__503.mtx.rnd    -target-value 80     -set-lb 81  -set-ub 629     $general_config >> $report_dir/R-dwt__503.txt
$build_dir/mmsl_enc $dataset_dir/S-sherman4.mtx.rnd    -target-value 320    -set-lb 321 -set-ub 683     $general_config >> $report_dir/S-sherman4.txt
$build_dir/mmsl_enc $dataset_dir/T-dwt__592.mtx.rnd    -target-value 130    -set-lb 131 -set-ub 740     $general_config >> $report_dir/T-dwt__592.txt
$build_dir/mmsl_enc $dataset_dir/U-662_bus.mtx.rnd     -target-value 275    -set-lb 276 -set-ub 828     $general_config >> $report_dir/U-662_bus.txt
$build_dir/mmsl_enc $dataset_dir/V-nos6.mtx.rnd        -target-value 408    -set-lb 409 -set-ub 844     $general_config >> $report_dir/V-nos6.txt
$build_dir/mmsl_enc $dataset_dir/W-685_bus.mtx.rnd     -target-value 170    -set-lb 171 -set-ub 857     $general_config >> $report_dir/W-685_bus.txt
$build_dir/mmsl_enc $dataset_dir/X-can__715.mtx.rnd    -target-value 141    -set-lb 142 -set-ub 894     $general_config >> $report_dir/X-can__715.txt