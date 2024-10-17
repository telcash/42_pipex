#!/bin/bash

# Color definitions
RED="\e[31m"
GR="\e[32m"
YW="\e[33m"
BL="\e[34m"
MG="\e[35m"
CY="\e[36m"
RES="\e[0m"

printf "Test 1a: Zero arguments: ./pipex\n" 
printf "Expected:\nBad arguments. Try: ./pipex infile cmd1 cmd2 outfile\nResult:\n"
./pipex
printf "**************************************\n"
printf "Test 1b: One argument: ./pipex ./input/infile.txt\n" 
printf "Expected:\nBad arguments. Try: ./pipex infile cmd1 cmd2 outfile\nResult:\n"
./pipex ./input/infile.txt
printf "**************************************\n"
printf "Test 1c: Two arguments: ./pipex ./input/infile.txt \"grep a\"\n" 
printf "Expected:\nBad arguments. Try: ./pipex infile cmd1 cmd2 outfile\nResult:\n"
./pipex ./input/infile.txt "grep a"
printf "**************************************\n"
printf "Test 1d: Six arguments./pipex ./input/infile.txt \"df -m\" \"grep dev\" \"grep -v boot\" \"wc -l\" outfile.txt \n" 
printf "Expected:\nBad arguments. Try: ./pipex infile cmd1 cmd2 outfile\nResult:\n"
./pipex ./input/infile.txt "grep dev" "grep -v boot" "wc -l" outfile.txt
printf "**************************************\n"
printf "Test 2a: Basic case: ./pipex ./input/infile.txt \"grep hola\" \"wc -l\" ./output/outfile2a.txt\n"
printf "Expected in output file: 3\n"
./pipex ./input/infile.txt "grep hola" "wc -l" ./output/outfile2a.txt
printf "Command: <./input/infile.txt grep hola | wc -l >./output/outfile2a-c.txt\n"
<./input/infile.txt grep hola | wc -l >./output/outfile2a-c.txt
diff=$(diff ./output/outfile2a.txt ./output/outfile2a-c.txt)
printf "Diff: %s\n" ${#diff}
printf "**************************************\n"
printf "Test 2b: Basic case (2a) with infile protected: ./pipex ./input/protected-infile.txt \"grep hola\" \"wc -l\" ./output/outfile2b.txt\n"
printf "Expected:\nError: Permission denied\nResult:\n"
./pipex ./input/protected-infile.txt "grep hola" "wc -l" ./output/outfile2b.txt
printf "Command: <./input/protected-infile.txt grep hola | wc -l >./output/outfile2b-c.txt\n"
<./input/protected-infile.txt grep hola | wc -l >./output/outfile2b-c.txt
printf "**************************************\n"
printf "Test 2c: Basic case (2a) but infile doesn't exist: ./pipex ./input/not-infile.txt \"grep hola\" \"wc -l\" ./output/outfile2c.txt\n"
printf "Expected:\nError: No such file or directory\nResult:\n"
./pipex ./input/not-infile.txt "grep hola" "wc -l" ./output/outfile2c.txt
printf "Command: <./input/not-infile.txt grep hola | wc -l >./output/outfile2c-c.txt\n"
<./input/not-infile.txt grep hola | wc -l >./output/outfile2c-c.txt
printf "**************************************\n"
printf "Test 2d: Basic case (2a) but infile is empty: ./pipex ./input/empty-infile.txt \"grep hola\" \"wc -l\" ./output/outfile2d.txt\n"
printf "Expected in output file:\n0\n"
./pipex ./input/empty-infile.txt "grep hola" "wc -l" ./output/outfile2d.txt
printf "Command: <./input/empty-infile.txt grep hola | wc -l >./output/outfile2d-c.txt\n"
<./input/empty-infile.txt grep hola | wc -l >./output/outfile2d-c.txt
diff=$(diff ./output/outfile2d.txt ./output/outfile2d-c.txt)
printf "Diff: %s\n" ${#diff}
printf "**************************************\n"
printf "Test 2e Basic case (2a) but outfile exist and has content: ./pipex ./input/infile.txt \"grep hola\" \"wc -l\" ./output/outfile2e.txt\n"
printf "Expected in output file:\n3\n"
./pipex ./input/infile.txt "grep hola" "wc -l" ./output/outfile2e.txt
printf "Command: <./input/infile.txt grep hola | wc -l >./output/outfile2e-c.txt\n"
<./input/infile.txt grep hola | wc -l >./output/outfile2e-c.txt
diff=$(diff ./output/outfile2e.txt ./output/outfile2e-c.txt)
printf "Diff: %s\n" ${#diff}
printf "**************************************\n"
printf "Test 2f: Basic case (2a) with outfile protected: ./pipex ./input/infile.txt \"grep hola\" \"wc -l\" ./output/protected-outfile.txt\n"
printf "Expected:\nError: Permission denied\nResult:\n"
./pipex ./input/infile.txt "grep hola" "wc -l" ./output/protected-outfile.txt
printf "Command: <./input/infile.txt grep hola | wc -l >./output/protected-outfile.txt\n"
<./input/infile.txt grep hola | wc -l >./output/protected-outfile.txt
printf "**************************************\n"
printf "Test 3a: Command#1 doesn't exist: ./pipex ./input/infile.txt \"wrongcommand\" \"wc -l\" ./output/outfile3a.txt\n"
printf "Expected:\nError: not found\nResult:\n"
./pipex ./input/infile.txt "wrongcommand" "wc -l" ./output/outfile3a.txt
printf "Command: <./input/infile.txt wrongcommand | wc -l >./output/outfile3a-c.txt\n"
<./input/infile.txt wrongcommand | wc -l >./output/outfile3a-c.txt
printf "**************************************\n"
printf "Test 3b: Command#2 doesn't exist: ./pipex ./input/infile.txt \"grep hola\" \"wrongcommand\" ./output/outfile3b.txt\n"
printf "Expected:\nError: not found\nResult:\n"
./pipex ./input/infile.txt "grep hola" "wrongcommand" ./output/outfile3b.txt
printf "Command: <./input/infile.txt grep hola | wrongcommand >./output/outfile3b-c.txt\n"
<./input/infile.txt grep hola | wrongcommand >./output/outfile3a-c.txt
printf "**************************************\n"
printf "Test 3c: Command#1 and Command#2 don't exist: ./pipex ./input/infile.txt \"wrongcommand\" \"wrongcommand\" ./output/outfile3c.txt\n"
printf "Expected:\nError: not found\nResult:\n"
./pipex ./input/infile.txt "wrongcommand" "wrongcommand" ./output/outfile3c.txt
printf "Command: <./input/infile.txt wrongcommand | wrongcommand >./output/outfile3c-c.txt\n"
<./input/infile.txt wrongcommand | wrongcommand >./output/outfile3c-c.txt
printf "**************************************\n"
printf "Test 4a: ./pipex ./input/infile.txt \"ls -l\" \"wc -l\" ./output/outfile4a.txt\n"
./pipex ./input/infile.txt "ls -l" "wc -l" ./output/outfile4a.txt
printf "Command: <./input/infile.txt ls -l | wc -l >./output/outfile4a-c.txt\n"
<./input/infile.txt ls -l | wc -l >./output/outfile4a-c.txt
diff=$(diff ./output/outfile4a.txt ./output/outfile4a-c.txt)
printf "Diff: %s\n" ${#diff}
printf "**************************************\n"
printf "Test 4b: ./pipex ./input/deepthought.txt \"grep Now\" \"head -2\" ./output/outfile4b.txt\n"
./pipex ./input/deepthought.txt "grep Now" "head -2" ./output/outfile4b.txt
echo "${GR}Command: <./input/deepthought.txt grep Now | head -2 >./output/outfile4b-c.txt\n${RES}"
<./input/deepthought.txt grep Now | head -2 >./output/outfile4b-c.txt
diff=$(diff ./output/outfile4b.txt ./output/outfile4b-c.txt)
printf "Diff: %s\n" ${#diff}