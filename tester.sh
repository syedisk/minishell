#!/bin/bash

MINISHELL=./minishell
PROMPT="minishell$ "  # Adjust if your prompt is different

run_test() {
    COMMAND="$1"
    echo -e "\nRunning: $COMMAND"
    
    # Run in your minishell
    echo "$COMMAND" | $MINISHELL | sed -e "s/^$PROMPT//" -e "1d" > minishell_output.txt
    # Run in bash for comparison
    echo "$COMMAND" | bash > bash_output.txt

    # Compare outputs
    if diff minishell_output.txt bash_output.txt > /dev/null; then
        echo "✅ Test Passed"
    else
        echo "❌ Test Failed"
        echo "Expected:"
        cat bash_output.txt
        echo "Got:"
        cat minishell_output.txt
    fi
}

### List your test cases here ###
run_test "echo Hello World"
run_test "pwd"
run_test "ls | wc -l"
run_test "cat < Makefile > temp.txt"
run_test "cd .. | pwd"

#basic
run_test "echo Hello World"
run_test "pwd"
run_test "ls"
run_test "ls -la"
run_test "/usr/bin/ls"
run_test "usr/bin/ls"
run_test "./ls"
run_test "hello"
run_test "/usr/bin/hello"
run_test "./hello"
run_test ""
run_test "."
run_test ".."
run_test "$"
run_test "./"
run_test "../"
run_test "./existing_dir"
run_test "../fake_dir/"
run_test "./existing_file"
run_test "./nonexistant_file"
run_test "./executable_file"
run_test ".executable_file"
run_test "executable_file"

# Basic commands without environment
run_test "unset PATH; pwd"
run_test "unset PATH; echo hello"
run_test "unset PATH; /usr/bin/ls"
run_test "unset PATH; usr/bin/ls"
run_test "unset PATH; ./ls"
run_test "unset PATH; hello"
run_test "unset PATH; /usr/bin/hello"
run_test "unset PATH; ./hello"
run_test "unset PATH; \"\""
run_test "unset PATH; ."
run_test "unset PATH; .."
run_test "unset PATH; $"
run_test "unset PATH; ./"
run_test "unset PATH; ../"
run_test "unset PATH; ./existing_dir"
run_test "unset PATH; ../fake_dir/"
run_test "unset PATH; ./existing_file"
run_test "unset PATH; ./nonexistant_file"
run_test "unset PATH; ./executable_file"
run_test "unset PATH; .executable_file"
run_test "unset PATH; executable_file"

# Commands with spaces
run_test "\"\""
run_test "\"                        \""
run_test "						     "
run_test "\t\t\t\t\t\t\t\t\t\t      "
run_test "\t\n\r\v\f                "
run_test "       \t    \t\t\t       "
run_test "ls                        "
run_test "           ls             "
run_test "                        ls"
run_test "ls\t\t\t\t\t\t\t\t\t\t\t\t"
run_test "\t\t\t\t\t\tls\t\t\t\t\t\t"
run_test "\t\t\t\t\t\t\t\t\t\t\t\tls"
run_test "\t\t\t\t            \t\tls"
run_test "      ls         -l     -a"
run_test "\t\tls\t\t\t\t-l\t\t\t\t-a"
run_test "\t    ls\t\t  -l -a\t\t   "

# Commands with pipes
run_test "ls -l | wc -l"
run_test "cat valid_infile_1 | grep dream"
run_test "cat valid_infile_1 | grep dream | cat -e"
run_test "cat valid_infile_1 | grep dream | wc -l"
run_test "cat valid_infile_1 | grep dream | wc -l | cd x"
run_test "cat valid_infile_1 | grep dream | wc -l | x"
run_test "x | cat valid_infile_1 | grep dream | wc -l"
run_test "cat valid_infile_1 | x | grep dream | wc -l"
run_test "cat valid_infile_1 | grep dream | x | wc -l"
run_test "cat /dev/random | head -c 100 | wc -c"
run_test "x | x | x | x | x"
run_test "x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x|x"
run_test "ls | ls | ls"
run_test "ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls"

#quotes
run_test "ec""ho test"
run_test "ec''ho test"
run_test """echo test"
run_test "''echo test"
run_test "echo"" test"
run_test "echo'' test"
run_test "echo "" test"
run_test "echo '' test"
run_test "echo "" "" "" test"
run_test "echo '' '' '' test"
run_test "echo """""" test"
run_test "echo '''''' test"
run_test "echo $USE""R"
run_test "echo $USE''R"
run_test "echo ""$USER"
run_test "echo ''$USER"
run_test "echo "$"USER"
run_test "echo '$'USER"
run_test "echo $""USER"
run_test "echo $''USER"
run_test "echo $USER"" ''"
run_test "echo "cat valid_infile_1 | cat > outfile1""
run_test "echo 'cat valid_infile_1 | cat > outfile1'"
run_test "ls """
run_test "ls '" 
run_test "ls "'"
run_test "ls " ""
run_test "ls " ' ""
run_test ""ls""
run_test "l"s""



# Clean up
rm -f minishell_output.txt bash_output.txt temp.txt