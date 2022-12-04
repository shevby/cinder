from collections import defaultdict
import json
import math
import os
import pygame
import sys
import time
import urllib.request


URL = "http://localhost:6789"
PORTRAIT_SIZE = (100, 100)
TILE_SIZE = (2*PORTRAIT_SIZE[0], 2*PORTRAIT_SIZE[1])
INTERVAL_BETWEEN_TILES = 20
DISPLAY_SCROLL_SPEED = 15
GAME_STATE_REFRESH_INTERVAL_MS = 200


class FpsMeter:
    def __init__(self):
        self.current_second = math.floor(time.time())
        self.fps_previous_second = 0
        self.fps_this_second = 0

    def tick(self):
        current_second = math.floor(time.time())
        if current_second == self.current_second:
            self.fps_this_second += 1
        else:
            self.fps_previous_second = self.fps_this_second
            self.fps_this_second = 1
            self.current_second = current_second

    def fps(self):
        return self.fps_previous_second


pygame.font.init()

display = pygame.display.set_mode()
display_offset = [0, 0]
display_speed_direction = [0, 0]

portraits_cache = {}


def get_image(name):
    if name in portraits_cache:
        return portraits_cache[name]

    image = pygame.image.load(os.path.dirname(os.path.realpath(__file__)) + "/pics/" + name).convert_alpha()
    image = pygame.transform.smoothscale(image, PORTRAIT_SIZE)

    portraits_cache[name] = image
    return image


previous_request_time = 0
json_content = '{"tiles": [[]]}'
location = json.loads(json_content)
fps_meter = FpsMeter()
while(True):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            if event.key in [pygame.K_LEFT, ord('A'), ord('a')]:
                display_speed_direction[0] -= 1
            elif event.key in [pygame.K_RIGHT, ord('D'), ord('d')]:
                display_speed_direction[0] += 1
            elif event.key in [pygame.K_UP, ord('W'), ord('w')]:
                display_speed_direction[1] -= 1
            elif event.key in [pygame.K_DOWN, ord('S'), ord('s')]:
                display_speed_direction[1] += 1
            elif event.key in [ord('Q'), ord('q')]:
                sys.exit()
        elif event.type == pygame.KEYUP:
            if event.key in [pygame.K_LEFT, ord('A'), ord('a')]:
                display_speed_direction[0] += 1
            elif event.key in [pygame.K_RIGHT, ord('D'), ord('d')]:
                display_speed_direction[0] -= 1
            elif event.key in [pygame.K_UP, ord('W'), ord('w')]:
                display_speed_direction[1] += 1
            elif event.key in [pygame.K_DOWN, ord('S'), ord('s')]:
                display_speed_direction[1] -= 1

    display_offset[0] += display_speed_direction[0] * DISPLAY_SCROLL_SPEED
    display_offset[1] += display_speed_direction[1] * DISPLAY_SCROLL_SPEED

    if time.time() >= previous_request_time + 0.001 * GAME_STATE_REFRESH_INTERVAL_MS:
        try:
            with urllib.request.urlopen(URL) as f:
                json_content = f.read().decode('utf-8')
        except:
            pass

        location = json.loads(json_content)

    display.fill((145, 132, 34))

    for i in range(len(location['tiles'])):
        for j in range(len(location['tiles'][i])):
            base_x = i * (TILE_SIZE[0] + INTERVAL_BETWEEN_TILES) + display_offset[0]
            base_y = j * (TILE_SIZE[1] + INTERVAL_BETWEEN_TILES) + display_offset[1]
            pygame.draw.rect(display, (77, 3, 204), ((base_x, base_y), (2*PORTRAIT_SIZE[0], 2*PORTRAIT_SIZE[1])))

            creatures = location['tiles'][i][j][0]['creatures']
            for k, creature in enumerate(creatures):
                if k == 0:
                    display.blit(get_image(creature['type'] + '.png'), (base_x, base_y))
                elif k == 1:
                    display.blit(get_image(creature['type'] + '.png'), (base_x + PORTRAIT_SIZE[0], base_y))
                elif k == 2:
                    display.blit(get_image(creature['type'] + '.png'), (base_x, base_y + PORTRAIT_SIZE[1]))
                elif k == 3:
                    display.blit(get_image(creature['type'] + '.png'), (base_x + PORTRAIT_SIZE[0], base_y + PORTRAIT_SIZE[1]))

    font = pygame.font.SysFont(pygame.font.get_default_font(), 40)
    caption = font.render(f"FPS: {fps_meter.fps()}", True, (255, 0, 0))
    display.blit(caption, (100, 0))

    pygame.display.update()
    pygame.time.delay(20)

    fps_meter.tick()
