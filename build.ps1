gcc -std=c99 -Wall -Wextra -Iinclude src/*.c test/test_main.c -o test.exe
if ($LASTEXITCODE -eq 0) { .\test.exe }