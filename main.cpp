#include <Windows.h>
#include <iostream>

int main(int argc, char** argv) {
    HWND wesnoth_window = FindWindow(NULL, "The Battle for Wesnoth - 1.14.9");
    if (wesnoth_window == NULL) {
        std::cerr << "Window not found." << std::endl;
        return 1;
    }

    DWORD process_id = 0;
    GetWindowThreadProcessId(wesnoth_window, &process_id);
    if (process_id == 0) {
        std::cerr << "Failed to get process ID." << std::endl;
        return 1;
    }

    HANDLE wesnoth_process = OpenProcess(PROCESS_VM_READ, FALSE, process_id);
    if (wesnoth_process == NULL) {
        std::cerr << "Failed to open process." << std::endl;
        return 1;
    }

    DWORD gold_value = 0;
    SIZE_T bytes_read = 0;
    if (!ReadProcessMemory(wesnoth_process, (LPCVOID)0x017EECB8, &gold_value, sizeof(DWORD), &bytes_read) || bytes_read != sizeof(DWORD)) {
        std::cerr << "Failed to read memory." << std::endl;
        CloseHandle(wesnoth_process);
        return 1;
    }

    std::cout << "Gold value: " << gold_value << std::endl;

    CloseHandle(wesnoth_process);
    return 0;
}
