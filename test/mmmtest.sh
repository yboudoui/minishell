#!/bin/bash

BOLDGREEN="\033[1;32m"
BOLDRED="\033[1;31m"
CYAN="\033[0;36m"
RESET="\033[0m"

function exec_test() {
  # Split the commands and run them separately
  IFS=';' read -ra commands <<< "$1"

  for cmd in "${commands[@]}"; do
    # Run the command with minishell and bash, compare output and exit status
    TEST1=$(./minishell -c "$cmd" 2>/dev/null)
    ES_1=$?
    TEST2=$(bash -c "$cmd" 2>/dev/null)
    ES_2=$?

    if [ "$TEST1" == "$TEST2" ]; then
      printf "Output Match: $BOLDGREEN%s$RESET" "✓ "
    else
      printf "Output Match: $BOLDRED%s$RESET" "✗ "
    fi

    if [ "$ES_1" == "$ES_2" ]; then
      printf "Exit Code Match: $BOLDGREEN%s$RESET" "✓ "
    else
      printf "Exit Code Match: $BOLDRED%s$RESET" "✗ "
    fi

    if [ $valgrind_exit_code -eq 0 ]; then
      printf "Valgrind Test: $BOLDGREEN%s$RESET" "✓ "
    else
      printf "Valgrind Test: $BOLDRED%s$RESET" "✗ "
    fi

    printf "$CYAN \"%s\" $RESET\n" "$cmd"


    # Run the command with minishell and Valgrind
    valgrind_output=$(valgrind --leak-check=full --track-fds=yes --trace-children=yes --errors-for-leak-kinds=definite,possible,indirect -q ./minishell -c "$cmd" 2>&1)
    valgrind_exit_code=$?

    # Check if Valgrind output contains any error
    if [ $valgrind_exit_code -ne 0 ]; then
      echo "Valgrind reported an error:"
      echo "$valgrind_output"
      echo
    fi
  done
}

# Test cases array
test_cases=(
  "export -HOLA=bonjour"
  "export --HOLA=bonjour"
  "export HOLA-=bonjour"
  "export HO-LA=bonjour"
  "export HOL.A=bonjour"

# Echo
 "echo test tout"
 "echo test      tout"
 "echo -n test tout"
 "echo -n -n -n test tout"

 "cat /dev/random | head -c 100 | wc -c"

 "echo test     /    test"
 "echo test"
 "echo $TEST"
 "echo "$TEST""
 "echo "$TEST""
 "echo "$TEST$TEST$TEST""
 "echo "$TEST$TEST=lol$TEST""
 "echo "   $TEST lol $TEST""
 "echo $TEST$TEST$TEST"
 "echo $TEST$TEST=lol$TEST""lol"
 "echo    $TEST lol $TEST"
 "echo test "" test "" test"
 "echo $TEST"
 "echo "$=TEST""
 "echo "$""
 "echo "$?TEST""
 "echo $TEST $TEST"
 "echo "$T1TEST""

 "echo test > ls | cat ls"
 "echo test > ls >> ls >> ls | echo test >> ls| cat ls"
 "> lol echo test lol| cat lol"
 ">lol echo > test>lol>test>>lol>test mdr >lol test >test| cat test"
 "cat < ls"
 "cat < ls > ls"

 'echo testing multi | echo "test 1 | x | and 2" | cat tests/lorem.txt | grep Lorem'

 "gdagadgag"
 "ls -Z"
 "cd gdhahahad"
 "ls -la | wtf"
 "echo hola | cat | cat | cat | cat | cat | grep hola"
 'echo'
 'echo -n'
 'echo Hola'
 'echoHola'
 'echo-nHola'
 'echo -n Hola'
 'echo "-n" Hola'
 'echo -nHola'
 'echo Hola -n'
 'echo Hola Que Tal'
 'echo         Hola'
 'echo    Hola     Que    Tal'
 'echo      \n hola'
 'echo "         " | cat -e'
 'echo           | cat -e'
 '""''echo hola""'''' que""'' tal""'''
 'echo -n -n'
 'echo -n -n Hola Que'
 'echo -p'
 'echo -nnnnn'
 'echo -n -nnn -nnnn'
 'echo -n-nnn -nnnn'
 'echo -n -nnn hola -nnnn'
 'echo -n -nnn-nnnn'
 'echo --------n'
 'echo -nnn --------n'
 'echo -nnn -----nn---nnnn'
 'echo -nnn --------nnnn'
 'echo $'
 'echo 0'
 'echo 0$'
 'echo 0 | echo 0 | echo 0'
 'echo $:$= | cat -e'
 'echo " $ " | cat -e'
 'echo ' $ ' | cat -e'
 'echo /mnt/nfs/homes/kdhrif'
 'echo $HOME'
 'echo my shit terminal is [screen-256color]'
 'echo my shit terminal is ['
 'echo my shit terminal is []'
 'echo 101778'
 'echo'
 'echo HOME'
 'echo /mnt/nfs/homes/kdhrif%'
 'echo 101778/mnt/nfs/homes/kdhrif'
 'echo Le path de mon HOME est /mnt/nfs/homes/kdhrif'
 'echo kdhrif$USERkdhrif$USERtestkdhrif'
 'echo -nnnn'
 'echo > <'
 'echo | |'
 'EechoE'
 '.echo.'
 '>echo>'
 '<echo<'
 '>>echo>>'
 '|echo|'
 '|echo -n hola'
 'echo $""'
 'echo "$"""'
 'echo '$''''
 'echo $"HOME"'
 'echo $''HOME'
 'echo $""HOME'
 'echo ""ME'
 'echo ''ME'
 'echo """ME"'
 'echo '''ME''
 'echo "'''ME'"'
 'echo ""/mnt/nfs/homes/kdhrif'
 'echo "" /mnt/nfs/homes/kdhrif'
 'echo ''/mnt/nfs/homes/kdhrif'
 'echo '' /mnt/nfs/homes/kdhrif'
 'echo $"HO""ME"'
 'echo $'HO''ME''
 'echo $'HOME''
 'echo "$"HOME'
 'echo $=HOME'
 'echo $"HOLA"'
 'echo $'HOLA''
 'echo  Hola'
 'echo "hola"'
 'echo 'hola''
 'echo ''hola'''
 'echo ''h'o'la'''
 'echo "''h'o'la''"'
 'echo "'"h'o'la"'"'
 'echo"'hola'"'
 'echo "'hola'"'
 'echo '"hola"''
 'echo '''ho"''''l"a''''
 'echo hola""""""""""""'
 'echo hola"''''''''''"'
 'echo hola'''''''''''''
 'echo hola'""""""""""''
 'e"cho hola"'
 'e'cho hola''
 'echo "hola     " | cat -e'
 'echo ""hola'
 'echo "" hola'
 'echo ""             hola'
 'echo ""hola'
 'echo "" hola'
 'echo hola""bonjour'
 '"e"'c'ho 'b'"o"nj"o"'u'r'
 '""e"'c'ho 'b'"o"nj"o"'u'r"'
 'echo ""Makefile'
 'echo """Makefile"'
 'echo "" "Makefile"'

 'cat -e bonjour | exit"'
 'exit | cat -e bonjour"'
 'pwd"'
 'env | grep HOLA"'
 'cd /mnt/nfs/homes/kdhrif"'
 '| test'
 'echo > <'
 'echo | |'
 '<'
 ':'
 '!'
 '>'
 '<'
 '>>'
 '<<'
 '<>'
 '>>>>>'
 '>>>>>>>>>>>>>>>'
 '<<<<<'
 '<<<<<<<<<<<<<<<<'
 '> > > >'
 '>> >> >> >>'
 '>>>> >> >> >>'
 '/'
 '//'
 '/.'
 '/./../../../../..'
 '///////'
 '$> \$> \\\$> -'
 '|'
 '| hola'
 '| | |'
 '||'
 '|||||'
 '|||||||||||||'
 '>>|><'
 'echo hola <<<< bonjour'
 'echo hola <<<<< bonjour'

 "exit 42"
 "exit 42 53 68"
 "exit 259"
 "exit 9223372036854775807"
 "exit -9223372036854775808"
 "exit 9223372036854775808"
 "exit -9223372036854775810"
 "exit -4"
 "exit wrong"
 "exit wrong_command"
 'exit'
 'exit exit'
 'exit hola'
 'exit hola que tal'
 'exit 42'
 'exit 000042'
 'exit 666'
 'exit 666 666'
 'exit -666 666'
 'exit hola 666'
 'exit 666 666 666 666'
 'exit 666 hola 666'
 'exit hola 666 666'
 'exit 259'
 'exit -4'
 'exit -42'
 'exit -0000042'
 'exit -259'
 'exit -666'
 'exit +666'
 'exit 0'
 'exit +0'
 'exit -0'
 'exit +42'
 'exit -69 -96'
 'exit --666'
 'exit ++++666'
 'exit ++++++0'
 'exit ------0'
 'exit "666"'
 'exit '666''
 'exit '-666''
 'exit '+666''
 'exit '----666''
 'exit '++++666''
 'exit '6'66'
 'exit '2'66'32''
 'exit "'666'"'
 'exit '"666"''
 'exit '666'"666"666'
 'exit +'666'"666"666'
 'exit -'666'"666"666'

 'export HOL@=bonjour'
 'export HOL~A=bonjour'
 'export -HOLA=bonjour'
 'export --HOLA=bonjour'
 'export HOLA-=bonjour'
 'export HO-LA=bonjour'
 'export HOL.A=bonjour'
 'export HOL}A=bonjour'
 'export HOL{A=bonjour'
 'export HO*LA=bonjour'
 'export HO#LA=bonjour'
 'export HO@LA=bonjour'
 'export HO!LA=bonjour'
 'export HO0LA=bonjour'
 'export +HOLA=bonjour'
 'export HOL+A=bonjour'
 'export 1='

 'unset 9HOLA'
 'unset HOLA9'
 'unset HOL?A'
 'unset HOLA HOL?A'
 'unset HOL?A HOLA'
 'unset HOL?A HOL.A'
 'unset HOLA='
 'unset HOL.A'
 'unset HOL+A'
 'unset HOL=A'
 'unset HOL{A'
 'unset HOL}A'
 'unset HOL-A'
 'unset -HOLA'
 'unset _HOLA'
 'unset HOL_A'
 'unset HOLA_'
 'unset HOL*A'
 'unset HOL#A'
 'unset'
 'unset /mnt/nfs/homes/kdhrif'
 'unset HOL@'
 'unset HOL!A'
 'unset HOL^A'
 'unset HOL0A'
 'unset """" HOLA'
 'unset PATH'
 'unset PATH'
 'unset ='
 'unset ======'
 'unset ++++++'
 'unset _______'
 'unset export'
 'unset echo'
 'unset pwd'
 'unset cd'
 'unset unset'
 'unset sudo'

 'pwd'
 'pwd hola'
 'pwd ./hola'
 'pwd hola que tal'
 'pwd -p'
 'pwd --p'
 'pwd ---p'
 'pwd pwd pwd'
 'pwd ls'
 'pwd ls env'

 'hola que tal'
 'Makefile'
 '0'
 '00'
 '?/mnt/nfs/homes/kdhrif'
 '$'
 '/mnt/nfs/homes/kdhrif'
 ''
 '""'
 ''''
 ''
 '-R'

 'cd'
 'cd .'
 'cd ./'
 'cd ./././.'
 'cd ././././'
 'cd ..'
 'cd ../'
 'cd ../..'
 'cd ../.'
 'cd .././././.'
 'cd srcs'
 'cd srcs objs'
 'cd 'srcs''
 'cd "srcs"'
 'cd '/etc''
 'cd /e'tc''
 'cd /e"tc"'
 'cd sr'
 'cd Makefile'
 'cd ../minishell'
 'cd ../../../../../../..'
 'cd .././../.././../bin/ls'
 'cd /'
 'cd '/''
 'cd ---'
 'cd /mnt/nfs/homes/kdhrif'
 'cd /mnt/nfs/homes/kdhrif /mnt/nfs/homes/kdhrif'
 'cd /mnt/nfs/homes/kdhrif/42_works'
 'cd "/mnt/nfs/homes/kdhrif/srcs"'
 'cd '/mnt/nfs/homes/kdhrif/srcs''

 'export hola | unset hola | echo 0'
 '/bin/echo'
 '/bin/echo Hola Que Tal'
 '/bin/env'
 '/bin/cd Desktop'
 'unset HOME'
 'unset HOME'
 'export HOME='
 'unset HOME'
 'export HOME'
 'cd minishell Docs crashtest.c'
 'cd / | echo 0'
 'env|"wc" -l'
 'env|"wc "-l'
 'expr 1 + 1'
 'expr 0 + 0'
 'cat | cat | cat | ls'
 'ls | exit'
 'ls | exit 42'
 'exit | ls'
 'echo hola > bonjour'
 'echo hola > bonjour'
 'echo | echo'
 'echo hola | echo que tal'
 'pwd | echo hola'
 'env | echo hola'
 'echo oui | cat -e'
 'echo oui | echo non | echo hola | grep oui'
 'echo oui | echo non | echo hola | grep non'
 'echo oui | echo non | echo hola | grep hola'
 'echo hola | cat -e | cat -e | cat -e'
 'cd .. | echo "hola"'
 'cd / | echo "hola"'
 'cd .. | pwd'
 'ifconfig | grep ":"'
 'ifconfig | grep hola'
 'whoami | grep kdhrif'
 'ls | hola'
 'ls | ls hola'
 'ls | ls | hola'
 'ls | hola | ls'
 'ls | ls | hola | rev'
 'ls | ls | echo hola | rev'
 'ls -la | grep "."'
 'ls -la | grep "'.'"'
 'echo hola | cat'
 'echo hola| cat'
 'echo hola |cat'
 'echo hola|cat'
 'echo hola ||| cat'
 'ech|o hola | cat'
 'cat Makefile | cat -e | cat -e'
 'cat Makefile | grep srcs | cat -e'
 'cat Makefile | grep srcs | grep srcs | cat -e'
 'cat Makefile | grep pr | head -n 5 | cd file_not_exist'
 'cat Makefile | grep pr | head -n 5 | hello'
 'export HOLA=bonjour | cat -e | cat -e'
 'unset HOLA | cat -e'
 'export HOLA | echo hola'
 'export | echo hola'
 'cat <pwd'
 'cat <srcs/pwd'
 'cat <../pwd'
 'cat >>'
 'cat >> <<'
 'cat >> > >> << >>'
 'cat < ls'
 'cat < ls > ls'
 'cat <<'
 'cat << prout << lol << koala'
 'prout << lol << cat << koala'
 '<<'
 '<< $"hola"$"b"'
 '<< $""1576101"b"'
 '<< ho$""1576101"b"'
)

# Run all test cases
for test_case in "${test_cases[@]}"; do
  exec_test "$test_case"
done
