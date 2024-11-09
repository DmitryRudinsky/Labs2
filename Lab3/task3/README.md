1) clang -fsanitize=address -g -o memory_leak_example options.c main.c
2) ./memory_leak_example in_file.txt -a out_file.txt

1) clang -g -o memory_leak_example options.c main.c
2) leaks --atExit --list -- ./memory_leak_example in_file.txt -a out_file.txt