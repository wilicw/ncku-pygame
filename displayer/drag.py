import socket
import sys
import pygame

from env import *


def get_client_socket():
    client = None
    try:
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect((HOST, PORT))
        clientMessage = str("OK")
        client.sendall(clientMessage.encode())

    except socket.error as msg:
        print(msg)
        client.close()
        quit()
    return client


if __name__ == '__main__':
    pygame.init()
    clock = pygame.time.Clock()
    screen = pygame.display.set_mode(SIZE)
    pygame.font.init()
    font = pygame.font.SysFont("Consolas", 50)
    all_spots = []
    rect_pos = [10, 10]
    drag = False
    # client = get_client_socket()
    # bias_x, bias_y = 0, 0
    # grid_x = 1
    while 1:
        # Receive data from server
        # received_data = str(client.recv(1024), encoding='utf-8')
        # print('Server:', received_data)
        # spot.value_x, spot.value_y, p1.value_y, p2.value_y, p1_score, p2_score = received_data.split(
        #     ",")

        # Process data to be a spot
        # try:
        #     value = float(received_data)
        #     spot = Spot(counter, value)
        #     all_spots.append(spot)
        # except ValueError as msg:
        #     print(msg)
        #     value = 0

        # adjust bias of x-axis
        # if counter < 200:
        #     bias_x = 0
        # else:
        #     bias_x = counter - 200

        # Draw spot
        screen.fill(BLACK)
        # spot.value_x += acc[0]
        # spot.value_y += acc[1]
        # if spot.value_x <= 0 or spot.value_x >= WIDTH:
        #     acc[0] *= -1
        #     FPS += 10
        # if spot.value_y <= 0 or spot.value_y >= HEIGHT:
        #     acc[1] *= -1
        # for sp in all_spots:
        #     pygame.draw.circle(screen, WHITE, sp.get_pos(bias_x=bias_x, bias_y=bias_y, grid_x=grid_x),
        #                        sp.radius)
        # pygame.draw.circle(screen, WHITE, spot.get_pos(), spot.radius)
        # pygame.draw.rect(screen, WHITE, pygame.Rect(0, p1.get_pos(), 5, 100))
        # pygame.draw.rect(screen, WHITE, pygame.Rect(
        #     WIDTH-5, p2.get_pos(), 5, 100))
        # text = font.render(f"{p1_score} {p2_score}", True, WHITE)
        # text_rect = text.get_rect()
        # screen.blit(text, (80, 0))

        # Send ack data to server
        # clientMessage = str("OK")
        # for loop counter
        # counter += 1
        # Key and mouse event
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                drag = True
            if event.type == pygame.MOUSEBUTTONUP:
                drag = False
            if event.type == pygame.MOUSEMOTION:
                mouse_pos = pygame.mouse.get_pos()
                if drag:
                    rect_pos[0] = mouse_pos[0]
                    rect_pos[1] = mouse_pos[1]

            pygame.draw.rect(screen, WHITE, pygame.Rect(
                rect_pos[0], rect_pos[1], 100, 50))
            pygame.display.flip()
            # keys_pressed = pygame.key.get_pressed()
            # if keys_pressed[pygame.K_UP]:
            #     client.sendall("pu".encode())
            #     _ = client.recv(1024)
            # elif keys_pressed[pygame.K_DOWN]:
            #     client.sendall("pd".encode())
            #     _ = client.recv(1024)
            # client.sendall("OK".encode())
        clock.tick(FPS)
