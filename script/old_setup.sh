#!/bin/zsh

SESSIONNAME="msh_tester"

tmux has-session -t $SESSIONNAME &> /dev/null

if [ $? = 0 ]; then
	tmux attach -t $SESSIONNAME
	exit(0)
fi

tmux	new-session		-s $SESSIONNAME									\;	\
		split-window	-t $SESSIONNAME:0 -v -l 80% -b					\;	\
		split-window	-t $SESSIONNAME:0 -h							\;	\

#		split-window	-t $SESSIONNAME:0 -b -l 90%		\;	\

#	tmux	send-keys -t $SESSIONNAME:0 "$line" ENTER
#while IFS= read -r line; do
#	tmux	send-keys -t $SESSIONNAME:0 "$line" ENTER
#	printf '%s\n' "$line"
#	sleep 1
#done < input.txt
