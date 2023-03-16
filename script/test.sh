#!/bin/zsh

SESSIONNAME="msh_tester"

tmux has-session -t $SESSIONNAME &> /dev/null

if [ $? != 0 ]; then
	echo "error"
fi

tmux	send-keys		-t $SESSIONNAME:0.0		"clear"	ENTER
tmux	send-keys		-t $SESSIONNAME:0.1		"clear"	ENTER
sleep 1

function start_terminals () {
	tmux	send-keys		-t $SESSIONNAME:0.0		"./minishell"	ENTER
	tmux	send-keys		-t $SESSIONNAME:0.1		"bash --posix"	ENTER
}

start_terminals

while IFS= read -r line; do
	tmux	send-keys		-t $SESSIONNAME:0.0		"$line"	ENTER
	tmux	send-keys		-t $SESSIONNAME:0.1		"$line"	ENTER
	if grep -q "exit" <<< "line"; then
		echo $?
		start_terminals
	fi
	printf '%s\n' "$line"
	sleep 1
done < new_input.txt
