#!/bin/zsh

SESSIONNAME="msh_tester"

tmux has-session -t $SESSIONNAME &> /dev/null

if [ $? = 0 ]; then
	tmux attach -t $SESSIONNAME
	exit(0)
fi

mkdir test_bsh test_msh
msh_cmd="make re_valgrind"
bsh_cmd="bash"

tmux	new-session		-s $SESSIONNAME									\;	\
		split-window	-t $SESSIONNAME:0 -h							\;	\
		send-key		-t $SESSIONNAME:0.0			"$msh_cmd"	ENTER	\;	\
		send-key		-t $SESSIONNAME:0.1			"$bsh_cmd"	ENTER	\;	\
		send-key		-t $SESSIONNAME:0.0			"cd test_msh"	ENTER	\;	\
		send-key		-t $SESSIONNAME:0.1			"cd test_bsh"	ENTER	\;	\
		setw			synchronize-panes on							\;	\



#		split-window	-t $SESSIONNAME:0 -b -l 90%		\;	\

#	tmux	send-keys -t $SESSIONNAME:0 "$line" ENTER
#while IFS= read -r line; do
#	tmux	send-keys -t $SESSIONNAME:0 "$line" ENTER
#	printf '%s\n' "$line"
#	sleep 1
#done < input.txt
