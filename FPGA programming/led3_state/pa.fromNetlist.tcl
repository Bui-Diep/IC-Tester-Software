
# PlanAhead Launch Script for Post-Synthesis pin planning, created by Project Navigator

create_project -name led3_state -dir "D:/Git new/IC-Tester-Software/FPGA programming/led3_state/planAhead_run_2" -part xc6slx9tqg144-3
set_property design_mode GateLvl [get_property srcset [current_run -impl]]
set_property edif_top_file "D:/Git new/IC-Tester-Software/FPGA programming/led3_state/led3_state.ngc" [ get_property srcset [ current_run ] ]
add_files -norecurse { {D:/Git new/IC-Tester-Software/FPGA programming/led3_state} }
set_param project.pinAheadLayout  yes
set_property target_constrs_file "led3_state.ucf" [current_fileset -constrset]
add_files [list {led3_state.ucf}] -fileset [get_property constrset [current_run]]
link_design
