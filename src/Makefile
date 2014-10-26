
all: fsm_state_matrix fsm_state_table fsm_gof_pure fsm_gof \
fsm_extern_state_var fsm_guards fsm_nested_switch_case

fsm_nested_switch_case:
	g++ fsm_nested_switch_case.cpp -o fsm_nested_switch_case

fsm_state_table:
	g++ fsm_state_table.cpp -o fsm_state_table

fsm_state_matrix:
	g++ fsm_state_matrix.cpp -o fsm_state_matrix

fsm_gof_pure:
	g++ fsm_gof_pure.cpp -o fsm_gof_pure

fsm_gof:
	g++ fsm_gof.cpp -o fsm_gof

fsm_extern_state_var:
	g++ fsm_extern_state_var.cpp -o fsm_extern_state_var

fsm_guards:
	g++ fsm_guards.cpp -o fsm_guards

clean:
	rm fsm_gof fsm_extern_state_var fsm_guards fsm_state_table \
	fsm_state_matrix fsm_gof_pure fsm_nested_switch_case
