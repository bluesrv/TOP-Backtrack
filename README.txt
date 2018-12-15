Name: Sebastian Ignacio Ramirez Vidal
Rol: 201473525-1
Technique: BackTrack with GBJ // Just BackTrack because of problem natural conditions

Code usage:
    - To compile run 'make' in root project directory
    - To remove all compilation files run 'make clean'
    - To run program run './topbacktrack' in 'build/bin' relative directory
    - To print parameters of instance being executed use the argument '--params'
    - To print local bests founds during runtime use the argument '--locals'

Work to do:
    - Fix recursion in order to find actual global bests in all test cases
    - Optimize execution time of candidate fix solution to last point

Execution example:
````
    sebastian@sebastian-HP-Pavilion-Power-Laptop-15-cb0xx:~/Documents/IA$ make
    Creating directories
    make[1]: Entering directory '/home/sebastian/Documents/IA'
    Compiling: src/main.cpp -> build/main.o
    g++  -std=c++11 -Wall -Wextra -g -I include/ -I /usr/local/include -MP -MMD -c src/main.cpp -o build/main.o
    Compiling: src/TOPBacktrack.cpp -> build/TOPBacktrack.o
    g++  -std=c++11 -Wall -Wextra -g -I include/ -I /usr/local/include -MP -MMD -c src/TOPBacktrack.cpp -o build/TOPBacktrack.o
    Compiling: src/Vertex.cpp -> build/Vertex.o
    g++  -std=c++11 -Wall -Wextra -g -I include/ -I /usr/local/include -MP -MMD -c src/Vertex.cpp -o build/Vertex.o
    Linking: build/bin/topbacktrack
    g++ build/main.o build/TOPBacktrack.o build/Vertex.o -o build/bin/topbacktrack
    Making symlink: topbacktrack -> build/bin/topbacktrack
    make[1]: Leaving directory '/home/sebastian/Documents/IA'
    sebastian@sebastian-HP-Pavilion-Power-Laptop-15-cb0xx:~/Documents/IA$ cd build/bin/
    sebastian@sebastian-HP-Pavilion-Power-Laptop-15-cb0xx:~/Documents/IA/build/bin$ ./topbacktrack --params --locals < ../../input.dat 
    6
    2
    17
    24
    16.7016  1 2 4 5 6
    7.40957  1 3 6
    24
    16.7016  1 2 4 5 6
    7.40957  1 3 6
    sebastian@sebastian-HP-Pavilion-Power-Laptop-15-cb0xx:~/Documents/IA/build/bin$ cd ../..
    sebastian@sebastian-HP-Pavilion-Power-Laptop-15-cb0xx:~/Documents/IA$ make clean
    Deleting topbacktrack symlink
    Deleting directories
    
````