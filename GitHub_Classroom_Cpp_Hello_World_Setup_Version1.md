# Setting Up a C++ Hello World Project in GitHub Classroom with Codespaces and Automated Testing

## 1. Create a Template Repository

Your repository should include the following files:

- `main.cpp` (Hello World program)
- `test_hello.cpp` (test to check output)
- `CMakeLists.txt` (build/test config)
- `.devcontainer/devcontainer.json` (for Codespaces)
- `README.md` (student instructions)

## 2. Configure GitHub Classroom

1. Go to [GitHub Classroom](https://classroom.github.com/).
2. Create a new classroom or use an existing one.
3. Create a new assignment:
   - **Assignment type:** Individual or Group
   - **Repository source:** Use the template repo you created.
   - **Enable autograding:** Use a simple script to check for the correct program output.

## 3. Autograding Setup

GitHub Classroom supports **GitHub Actions** for autograding.  
Example workflow file to add to your repo:

```yaml
name: Autograding

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Install build tools
        run: sudo apt-get update && sudo apt-get install -y cmake g++ make
      - name: Build
        run: cmake -S . -B build && cmake --build build
      - name: Run tests
        run: cd build && ctest --output-on-failure
```

## 4. Template Repository Example Files

**main.cpp**
```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

**test_hello.cpp**
```cpp
#include <cstdlib>
#include <cstdio>
#include <string>

int main() {
    FILE* pipe = popen("./hello_world", "r");
    if (!pipe) return 1;
    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof buffer, pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);

    if (result == "Hello, World!\n") {
        return 0;
    }
    return 1;
}
```

**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 11)

add_executable(hello_world main.cpp)
add_executable(test_hello test_hello.cpp)

add_test(NAME HelloWorldTest COMMAND test_hello)
```

**.devcontainer/devcontainer.json**
```json
{
    "name": "C++ Dev Container",
    "image": "mcr.microsoft.com/devcontainers/cpp:0-ubuntu-22.04",
    "settings": {},
    "postCreateCommand": "cmake -S . -B build && cmake --build build && cd build && ctest"
}
```

**README.md (excerpt)**
```markdown
# Hello World C++ Assignment

Welcome to your first C++ assignment!

## Instructions

1. Accept the assignment link from GitHub Classroom.
2. Open your repository in Codespaces.
3. Edit `main.cpp` as needed.
4. Run the build and tests in the terminal:
   ```
   cmake -S . -B build
   cmake --build build
   cd build
   ctest
   ```
5. Commit and push your changes!

## Automated Testing

Your code will be tested automatically. Make sure your output matches:
Hello, World!
```

## 5. Next Steps

- Create a new repository with these files and mark it as a template.
- Set up the assignment in GitHub Classroom and link your template repo.
- Share the Classroom assignment link with students.