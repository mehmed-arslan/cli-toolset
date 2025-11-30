# wc tool

## instructions to build on windows

### change datapath in main to current dir

cd into `build` <br>
`cmake ..` <br>
`cmake --build . --config Release` <br> or <br>
`cmake --build . --config Debug` <br>
executable created in: `build/<build_configuration>/`

## Topics

virtual functions <br>
pure virtual functions <br>
strategy pattern <br>
#pragma once <br>
reinterpret_cast <br>
smart pointers, make unique <br>
### dangling pointer <br>
`std::ifstream file(completeFilePath);`<br>
`input = &file;`<br>
file is a local variable inside the else block. <br>
When you exit the block, file is destroyed.<br>
input now points to a dangling pointer, reading from it later is undefined behavior.<br>