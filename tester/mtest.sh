RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"
# Execute the commands and check their exit status
if make -C ../ > /dev/null; then
    echo "make -C ../ command executed successfully"
else
    echo "make -C ../ command failed"
    exit 1
fi

if cp ../minishell .; then
    echo "cp ../minishell . command executed successfully"
else
    echo "cp ../minishell . command failed"
    exit 1
fi

if chmod 755 minishell; then
    echo "chmod 755 minishell command executed successfully"
else
    echo "chmod 755 minishell command failed"
    exit 1
fi



function exec_test()
{
	TEST1=$(./minishell -c "echo $@")
	ES_1=$?
	TEST2=$(bash --posix -c "echo $@")
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	sleep 0.1
}

# Echo
exec_test 'echo test tout'
exec_test 'echo test      tout'
exec_test 'echo -n test tout'
exec_test 'echo -n -n -n test tout'

# MultiCMD
exec_test 'cat /dev/random | head -c 100 | wc -c'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'

# ENV EXPANSIONS + ESCAPE
exec_test 'echo test     /    test'
exec_test 'echo test'
exec_test 'echo $TEST'
exec_test 'echo "$TEST"'
exec_test "echo '$TEST'"
exec_test 'echo "$TEST$TEST$TEST"'
exec_test 'echo "$TEST$TEST=lol$TEST"'
exec_test 'echo "   $TEST lol $TEST"'
exec_test 'echo $TEST$TEST$TEST'
exec_test 'echo $TEST$TEST=lol$TEST""lol'
exec_test 'echo    $TEST lol $TEST'
exec_test 'echo test "" test "" test'
exec_test 'echo $TEST'
exec_test 'echo "$=TEST"'
exec_test 'echo "$"'
exec_test 'echo "$?TEST"'
exec_test 'echo $TEST $TEST'
exec_test 'echo "$1TEST"'
exec_test 'echo "$T1TEST"'

# REDIRECTIONS
exec_test 'echo test > ls | cat ls'
exec_test 'echo test > ls >> ls >> ls | echo test >> ls| cat ls'
exec_test '> lol echo test lol| cat lol'
exec_test '>lol echo > test>lol>test>>lol>test mdr >lol test >test| cat test'
exec_test 'cat < ls'
exec_test 'cat < ls > ls'

# MULTI TESTS
# exec_test 'echo testing multi | echo "test 1 | x | and 2" | cat tests/lorem.txt | grep Lorem'

#EXEC
exec_test "gdagadgag"
exec_test "ls -Z"
exec_test "cd gdhahahad"
exec_test "ls -la | wtf"
exec_test "echo hola | cat | cat | cat | cat | cat | grep hola"
exec_test 'echo'
exec_test 'echo -n'
exec_test 'echo Hola'
exec_test 'echoHola'
exec_test 'echo-nHola'
exec_test 'echo -n Hola'
exec_test 'echo "-n" Hola'
exec_test 'echo -nHola'
exec_test 'echo Hola -n'
exec_test 'echo Hola Que Tal'
exec_test 'echo         Hola'
exec_test 'echo    Hola     Que    Tal'
exec_test 'echo      \n hola'
exec_test 'echo "         " | cat -e'
exec_test 'echo           | cat -e'
exec_test '""''echo hola""'''' que""'' tal""'''
exec_test 'echo -n -n'
exec_test 'echo -n -n Hola Que'
exec_test 'echo -p'
exec_test 'echo -nnnnn'
exec_test 'echo -n -nnn -nnnn'
exec_test 'echo -n-nnn -nnnn'
exec_test 'echo -n -nnn hola -nnnn'
exec_test 'echo -n -nnn-nnnn'
exec_test 'echo --------n'
exec_test 'echo -nnn --------n'
exec_test 'echo -nnn -----nn---nnnn'
exec_test 'echo -nnn --------nnnn'
exec_test 'echo $'
exec_test 'echo 0'
exec_test 'echo 0$'
exec_test 'echo 0 | echo 0 | echo 0'
exec_test 'echo $:$= | cat -e'
exec_test 'echo " $ " | cat -e'
exec_test 'echo ' $ ' | cat -e'
exec_test 'echo /mnt/nfs/homes/kdhrif'
exec_test 'echo $HOME'
exec_test 'echo my shit terminal is [screen-256color]'
exec_test 'echo my shit terminal is ['
exec_test 'echo my shit terminal is []'
exec_test 'echo 101778'
exec_test 'echo'
exec_test 'echo HOME'
exec_test 'echo /mnt/nfs/homes/kdhrif%'
exec_test 'echo 101778/mnt/nfs/homes/kdhrif'
exec_test 'echo Le path de mon HOME est /mnt/nfs/homes/kdhrif'
exec_test 'echo kdhrif$USERkdhrif$USERtestkdhrif'
exec_test 'echo *'
exec_test 'echo -nnnn'
exec_test 'echo > <'
exec_test 'echo | |'
exec_test 'EechoE'
exec_test '.echo.'
exec_test '>echo>'
exec_test '<echo<'
exec_test '>>echo>>'
exec_test '|echo|'
exec_test '|echo -n hola'
exec_test 'echo $""'
exec_test 'echo "$"""'
exec_test 'echo '$''''
exec_test 'echo $"HOME"'
exec_test 'echo $''HOME'
exec_test 'echo $""HOME'
exec_test 'echo ""ME'
exec_test 'echo ''ME'
exec_test 'echo """ME"'
exec_test 'echo '''ME''
exec_test 'echo "'''ME'"'
exec_test 'echo ""/mnt/nfs/homes/kdhrif'
exec_test 'echo "" /mnt/nfs/homes/kdhrif'
exec_test 'echo ''/mnt/nfs/homes/kdhrif'
exec_test 'echo '' /mnt/nfs/homes/kdhrif'
exec_test 'echo $"HO""ME"'
exec_test 'echo $'HO''ME''
exec_test 'echo $'HOME''
exec_test 'echo "$"HOME'
exec_test 'echo $=HOME'
exec_test 'echo $"HOLA"'
exec_test 'echo $'HOLA''
exec_test 'echo  Hola'
exec_test 'echo "hola"'
exec_test 'echo 'hola''
exec_test 'echo ''hola'''
exec_test 'echo ''h'o'la'''
exec_test 'echo "''h'o'la''"'
exec_test 'echo "'"h'o'la"'"'
exec_test 'echo"'hola'"'
exec_test 'echo "'hola'"'
exec_test 'echo '"hola"''
exec_test 'echo '''ho"''''l"a''''
exec_test 'echo hola""""""""""""'
exec_test 'echo hola"''''''''''"'
exec_test 'echo hola'''''''''''''
exec_test 'echo hola'""""""""""''
exec_test 'e"cho hola"'
exec_test 'e'cho hola''
exec_test 'echo "hola     " | cat -e'
exec_test 'echo ""hola'
exec_test 'echo "" hola'
exec_test 'echo ""             hola'
exec_test 'echo ""hola'
exec_test 'echo "" hola'
exec_test 'echo hola""bonjour'
exec_test '"e"'c'ho 'b'"o"nj"o"'u'r'
exec_test '""e"'c'ho 'b'"o"nj"o"'u'r"'
exec_test 'echo ""Makefile'
exec_test 'echo """Makefile"'
exec_test 'echo "" "Makefile"'

# SYNTAX ERROR
exec_test '| test'
exec_test 'echo > <'
exec_test 'echo | |'
exec_test '<'
exec_test ':'
exec_test '!'
exec_test '>'
exec_test '<'
exec_test '>>'
exec_test '<<'
exec_test '<>'
exec_test '>>>>>'
exec_test '>>>>>>>>>>>>>>>'
exec_test '<<<<<'
exec_test '<<<<<<<<<<<<<<<<'
exec_test '> > > >'
exec_test '>> >> >> >>'
exec_test '>>>> >> >> >>'
exec_test '/'
exec_test '//'
exec_test '/.'
exec_test '/./../../../../..'
exec_test '///////'
exec_test '$> \$> \\\$> -'
exec_test '|'
exec_test '| hola'
exec_test '| | |'
exec_test '||'
exec_test '|||||'
exec_test '|||||||||||||'
exec_test '>>|><'
exec_test 'echo hola <<<< bonjour'
exec_test 'echo hola <<<<< bonjour'

# EXIT
exec_test "exit 42"
exec_test "exit 42 53 68"
exec_test "exit 259"
exec_test "exit 9223372036854775807"
exec_test "exit -9223372036854775808"
exec_test "exit 9223372036854775808"
exec_test "exit -9223372036854775810"
exec_test "exit -4"
exec_test "exit wrong"
exec_test "exit wrong_command"
exec_test 'exit'
exec_test 'exit exit'
exec_test 'exit hola'
exec_test 'exit hola que tal'
exec_test 'exit 42'
exec_test 'exit 000042'
exec_test 'exit 666'
exec_test 'exit 666 666'
exec_test 'exit -666 666'
exec_test 'exit hola 666'
exec_test 'exit 666 666 666 666'
exec_test 'exit 666 hola 666'
exec_test 'exit hola 666 666'
exec_test 'exit 259'
exec_test 'exit -4'
exec_test 'exit -42'
exec_test 'exit -0000042'
exec_test 'exit -259'
exec_test 'exit -666'
exec_test 'exit +666'
exec_test 'exit 0'
exec_test 'exit +0'
exec_test 'exit -0'
exec_test 'exit +42'
exec_test 'exit -69 -96'
exec_test 'exit --666'
exec_test 'exit ++++666'
exec_test 'exit ++++++0'
exec_test 'exit ------0'
exec_test 'exit "666"'
exec_test 'exit '666''
exec_test 'exit '-666''
exec_test 'exit '+666''
exec_test 'exit '----666''
exec_test 'exit '++++666''
exec_test 'exit '6'66'
exec_test 'exit '2'66'32''
exec_test 'exit "'666'"'
exec_test 'exit '"666"''
exec_test 'exit '666'"666"666'
exec_test 'exit +'666'"666"666'
exec_test 'exit -'666'"666"666'

#EXPORT
exec_test 'export HOL@=bonjour'
exec_test 'export HOL~A=bonjour'
exec_test 'export -HOLA=bonjour'
exec_test 'export --HOLA=bonjour'
exec_test 'export HOLA-=bonjour'
exec_test 'export HO-LA=bonjour'
exec_test 'export HOL.A=bonjour'
exec_test 'export HOL}A=bonjour'
exec_test 'export HOL{A=bonjour'
exec_test 'export HO*LA=bonjour'
exec_test 'export HO#LA=bonjour'
exec_test 'export HO@LA=bonjour'
exec_test 'export HO!LA=bonjour'
exec_test 'export HO0LA=bonjour'
exec_test 'export +HOLA=bonjour'
exec_test 'export HOL+A=bonjour'

#unset
exec_test 'unset 9HOLA'
exec_test 'unset HOLA9'
exec_test 'unset HOL?A'
exec_test 'unset HOLA HOL?A'
exec_test 'unset HOL?A HOLA'
exec_test 'unset HOL?A HOL.A'
exec_test 'unset HOLA='
exec_test 'unset HOL.A'
exec_test 'unset HOL+A'
exec_test 'unset HOL=A'
exec_test 'unset HOL{A'
exec_test 'unset HOL}A'
exec_test 'unset HOL-A'
exec_test 'unset -HOLA'
exec_test 'unset _HOLA'
exec_test 'unset HOL_A'
exec_test 'unset HOLA_'
exec_test 'unset HOL*A'
exec_test 'unset HOL#A'
exec_test 'unset'
exec_test 'unset /mnt/nfs/homes/kdhrif'
exec_test 'unset HOL@'
exec_test 'unset HOL!A'
exec_test 'unset HOL^A'
exec_test 'unset HOL0A'
exec_test 'unset """" HOLA'
exec_test 'unset PATH'
exec_test 'unset PATH'
exec_test 'unset ='
exec_test 'unset ======'
exec_test 'unset ++++++'
exec_test 'unset _______'
exec_test 'unset export'
exec_test 'unset echo'
exec_test 'unset pwd'
exec_test 'unset cd'
exec_test 'unset unset'
exec_test 'unset sudo'

#ENV
exec_test 'env | grep HOLA"'

#PWD
exec_test 'pwd'
exec_test 'pwd hola'
exec_test 'pwd ./hola'
exec_test 'pwd hola que tal'
exec_test 'pwd -p'
exec_test 'pwd --p'
exec_test 'pwd ---p'
exec_test 'pwd pwd pwd'
exec_test 'pwd ls'
exec_test 'pwd ls env'

#MISC
exec_test 'hola que tal'
exec_test 'Makefile'
exec_test '0'
exec_test '00'
exec_test '?/mnt/nfs/homes/kdhrif'
exec_test '$'
exec_test '/mnt/nfs/homes/kdhrif'
exec_test ''
exec_test '""'
exec_test ''''
exec_test ''
exec_test '-R'

#CD
exec_test 'cd'
exec_test 'cd .'
exec_test 'cd ./'
exec_test 'cd ./././.'
exec_test 'cd ././././'
exec_test 'cd ..'
exec_test 'cd ../'
exec_test 'cd ../..'
exec_test 'cd ../.'
exec_test 'cd .././././.'
exec_test 'cd srcs'
exec_test 'cd srcs objs'
exec_test 'cd 'srcs''
exec_test 'cd "srcs"'
exec_test 'cd '/etc''
exec_test 'cd /e'tc''
exec_test 'cd /e"tc"'
exec_test 'cd sr'
exec_test 'cd Makefile'
exec_test 'cd ../minishell'
exec_test 'cd ../../../../../../..'
exec_test 'cd .././../.././../bin/ls'
exec_test 'cd /'
exec_test 'cd '/''
exec_test 'cd ---'
exec_test 'cd /mnt/nfs/homes/kdhrif'
exec_test 'cd /mnt/nfs/homes/kdhrif /mnt/nfs/homes/kdhrif'
exec_test 'cd /mnt/nfs/homes/kdhrif/42_works'
exec_test 'cd "/mnt/nfs/homes/kdhrif/srcs"'
exec_test 'cd '/mnt/nfs/homes/kdhrif/srcs''

#More ECHO
exec_test 'export hola | unset hola | echo 0'
exec_test '/bin/echo'
exec_test '/bin/echo Hola Que Tal'
exec_test '/bin/env'
exec_test '/bin/cd Desktop'
exec_test 'unset HOME'
exec_test 'cd /mnt/nfs/homes/kdhrif"'
exec_test 'unset HOME'
exec_test 'export HOME='
exec_test 'unset HOME'
exec_test 'export HOME'
exec_test 'cd minishell Docs crashtest.c'
exec_test 'cd / | echo 0'
exec_test 'pwd"'
exec_test 'env|"wc" -l'
exec_test 'env|"wc "-l'
exec_test 'expr 1 + 1'
exec_test 'expr 0 + 0'
exec_test 'cat | cat | cat | ls'
exec_test 'ls | exit'
exec_test 'ls | exit 42'
exec_test 'exit | ls'
exec_test 'echo hola > bonjour'
exec_test 'exit | cat -e bonjour"'
exec_test 'echo hola > bonjour'
exec_test 'cat -e bonjour | exit"'
exec_test 'echo | echo'
exec_test 'echo hola | echo que tal'
exec_test 'pwd | echo hola'
exec_test 'env | echo hola'
exec_test 'echo oui | cat -e'
exec_test 'echo oui | echo non | echo hola | grep oui'
exec_test 'echo oui | echo non | echo hola | grep non'
exec_test 'echo oui | echo non | echo hola | grep hola'
exec_test 'echo hola | cat -e | cat -e | cat -e'
exec_test 'cd .. | echo "hola"'
exec_test 'cd / | echo "hola"'
exec_test 'cd .. | pwd'
exec_test 'ifconfig | grep ":"'
exec_test 'ifconfig | grep hola'
exec_test 'whoami | grep kdhrif'
exec_test 'ls | hola'
exec_test 'ls | ls hola'
exec_test 'ls | ls | hola'
exec_test 'ls | hola | ls'
exec_test 'ls | ls | hola | rev'
exec_test 'ls | ls | echo hola | rev'
exec_test 'ls -la | grep "."'
exec_test 'ls -la | grep "'.'"'
exec_test 'echo hola | cat'
exec_test 'echo hola| cat'
exec_test 'echo hola |cat'
exec_test 'echo hola|cat'
exec_test 'echo hola ||| cat'
exec_test 'ech|o hola | cat'
exec_test 'cat Makefile | cat -e | cat -e'
exec_test 'cat Makefile | grep srcs | cat -e'
exec_test 'cat Makefile | grep srcs | grep srcs | cat -e'
exec_test 'cat Makefile | grep pr | head -n 5 | cd file_not_exist'
exec_test 'cat Makefile | grep pr | head -n 5 | hello'
exec_test 'export HOLA=bonjour | cat -e | cat -e'
exec_test 'unset HOLA | cat -e'
exec_test 'export HOLA | echo hola'
exec_test 'env | grep PROUT"'
exec_test 'export | echo hola'
exec_test 'sleep 3 | sleep 3'
exec_test 'time sleep 3 | sleep 3'
exec_test 'sleep 3 | exit'
exec_test 'exit | sleep 3'
exec_test 'cat <pwd'
exec_test 'cat <srcs/pwd'
exec_test 'cat <../pwd'
exec_test 'cat >>'
exec_test 'cat >> <<'
exec_test 'cat >> > >> << >>'
exec_test 'cat < ls'
exec_test 'cat < ls > ls'
exec_test '<<hola'
exec_test 'cat <<'
exec_test 'cat << prout << lol << koala'
exec_test 'prout << lol << cat << koala'
exec_test '<<'
exec_test '<< $"hola"$"b"'
exec_test '<< $""1576101"b"'
exec_test '<< ho$""1576101"b"'
