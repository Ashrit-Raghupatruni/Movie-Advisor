@echo off
echo ========================================
echo Movie Advisor Server - Compile and Run
echo ========================================
echo.

echo Compiling server...
gcc server.c -o server.exe -lws2_32

if %errorlevel% neq 0 (
    echo.
    echo Compilation failed! Make sure you have GCC installed.
    echo.
    pause
    exit /b 1
)

echo.
echo Compilation successful!
echo.
echo Starting server...
echo Open http://localhost:8080/index.html in your browser
echo Press Ctrl+C to stop the server
echo.

server.exe

pause


