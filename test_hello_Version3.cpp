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