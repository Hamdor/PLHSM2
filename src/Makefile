CC=g++# set your compiler

all: fsm_state_matrix fsm_state_table fsm_gof_pure fsm_gof \
fsm_extern_state_var fsm_guards fsm_nested_switch_case hsm_history \
fsm_orthogonal fsm_unnested_switch_case

fsm_nested_switch_case:
	${CC} fsm_nested_switch_case.cpp -o fsm_nested_switch_case

fsm_unnested_switch_case:
	${CC} fsm_unnested_switch_case.cpp -o fsm_unnested_switch_case

fsm_state_table:
	${CC} fsm_state_table.cpp -o fsm_state_table

fsm_state_matrix:
	${CC} fsm_state_matrix.cpp -o fsm_state_matrix

fsm_gof_pure:
	${CC} fsm_gof_pure.cpp -o fsm_gof_pure

fsm_gof:
	${CC} fsm_gof.cpp -o fsm_gof

fsm_orthogonal:
	${CC} fsm_orthogonal.cpp -o fsm_orthogonal

fsm_extern_state_var:
	${CC} fsm_extern_state_var.cpp -o fsm_extern_state_var

fsm_guards:
	${CC} fsm_guards.cpp -o fsm_guards

hsm_history:
	${CC} hsm_history.cpp -o hsm_history

clean:
	rm fsm_gof fsm_extern_state_var fsm_guards fsm_state_table \
	fsm_state_matrix fsm_gof_pure fsm_nested_switch_case hsm_history \
	fsm_orthogonal fsm_unnested_switch_case
