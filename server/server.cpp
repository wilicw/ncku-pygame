#include <future>
#include <stdio.h>
#include <string>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "game.cpp"

#define PORT "8888"
#define BUFFER_LEN 100

static int FPS = 10;

int err;
game g;

SOCKET make_server() {
  WSADATA wsaData;
  err = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (err) {
    printf("Startup failed");
    return 0;
  }

  struct addrinfo *result = nullptr;
  struct addrinfo hints;

  ZeroMemory(&hints, sizeof(hints));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  err = getaddrinfo(nullptr, PORT, &hints, &result);
  if (err) {
    printf("getaddrinfo failed");
    WSACleanup();
    return 0;
  }

  SOCKET ListenSocket = INVALID_SOCKET;
  ListenSocket =
      socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  err = ListenSocket == INVALID_SOCKET;
  if (err) {
    printf("Error at socket(): %ld\n", WSAGetLastError());
    freeaddrinfo(result);
    WSACleanup();
    return 0;
  }

  err = bind(ListenSocket, result->ai_addr, result->ai_addrlen);
  freeaddrinfo(result);
  if (err) {
    printf("bind failed");
    WSACleanup();
    closesocket(ListenSocket);
    return 0;
  }

  if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
    printf("Listen failed with error: %ld\n", WSAGetLastError());
    closesocket(ListenSocket);
    WSACleanup();
    return 0;
  }
  printf("Socket is created successfully. \n");
  return ListenSocket;
}

SOCKET make_client(SOCKET ListenSocket) {
  SOCKET ClientSocket = INVALID_SOCKET;
  ClientSocket = accept(ListenSocket, nullptr, nullptr);
  err = ClientSocket == INVALID_SOCKET;
  if (err) {
    printf("accept failed: %d\n", WSAGetLastError());
    closesocket(ListenSocket);
    WSACleanup();
    return 0;
  }
  return ClientSocket;
}

std::string_view controller(std::string_view buff, int p) {
  if (buff == "pu") {
    if (p == 1) {
      g.p1.push(1);
    } else {
      g.p2.push(1);
    }
  } else if (buff == "pd") {
    if (p == 1) {
      g.p1.push(-1);
    } else {
      g.p2.push(-1);
    }
  }
  return g.get_info();
}

void client_handler(SOCKET ListenSocket, int p) {
  SOCKET ClientSocket = make_client(ListenSocket);

  char recv_buff[BUFFER_LEN] = {0};
  int recv_len = BUFFER_LEN;

  do {
    err = recv(ClientSocket, recv_buff, recv_len, 0);
    if (err > 0) {
      std::string_view response = controller(std::string_view(recv_buff), p);
      send(ClientSocket, response.data(), response.length(), 0);
    } else if (err == 0) {
      printf("Connection closing\n");
      return;
    } else {
      printf("recv failed\n");
      closesocket(ClientSocket);
      WSACleanup();
      return;
    }
  } while (err > 0);
}

// void HAL_TIM_PeriodElapsedCallback(TIM_HandleType *htim){
//   if(htim==&htim6){

//   }

// }

void game_handler() {
  const int frame_rate = 100000 / FPS;
  g.init();
  while (true) {
    g.tick();
    std::this_thread::sleep_for(std::chrono::microseconds(frame_rate));
  }
}

int main() {
  using namespace std;
  SOCKET ListenSocket = make_server();
  vector<future<void>> async_future;
  async_future.push_back(async(launch::async, game_handler));
  for (auto i : {1, 2}) {
    async_future.push_back(
        async(launch::async, client_handler, ListenSocket, i));
  }
  return 0;
}
