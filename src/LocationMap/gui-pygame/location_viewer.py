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
MAX_LOCATION_MAP_SIZE = 100000


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


class NetworkLatencyMeter:
    def __init__(self):
        self.current_second = math.floor(time.time())
        self.sum_of_all_latencies_previous_second = 0
        self.number_of_requests_previous_second = 0
        self.previous_second_average_latency = "N/A"

    def add(self, latency):
        current_second = math.floor(time.time())
        if current_second == self.current_second:
            self.sum_of_all_latencies_previous_second += latency
            self.number_of_requests_previous_second += 1
        else:
            self.current_second = current_second
            if self.number_of_requests_previous_second == 0:
                self.previous_second_average_latency = "N/A"
            else:
                self.previous_second_average_latency = self.sum_of_all_latencies_previous_second / self.number_of_requests_previous_second

    def get_average_latency(self):
        return self.previous_second_average_latency


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


class Creature:
    def __init__(self, _type):
        self._type = _type


class Tile:
    def __init__(self):
        self.creatures = []

    def update(self, updates_dict):
        creatures = updates_dict.get('creatures', [])
        self.creatues = []
        for creature in creatures:
            self.creatures.append(Creature(creature['type']))


class Map:
    def __init__(self):
        self.width = 0
        self.height = 0
        self.tick = 0
        self.tiles = []

    def get_tile(self, row, column):
        if row >= len(self.tiles):
            return Tile()
        if column >= len(self.tiles[row]):
            return Tile()

        return self.tiles[row][column]

    def update(self, updates_dict):
        if 'height' in updates_dict:
            self.height = updates_dict['height']

        if 'width' in updates_dict:
            self.height = updates_dict['width']

        if 'tick_id' in updates_dict:
            self.height = updates_dict['tick_id']

        tiles_updates = updates_dict.get('tiles', [])
        for tile_update in tiles_updates:
            if 'row' not in tile_update or 'column' not in tile_update:
                continue

            row = tile_update['row']
            column = tile_update['column']

            if row < 0 or row > MAX_LOCATION_MAP_SIZE or column < 0 or column > MAX_LOCATION_MAP_SIZE:
                continue

            while row >= len(self.tiles):
                self.tiles.append([])

            while column >= len(self.tiles[row]):
                self.tiles[row].append(Tile())

            self.tiles[row][column].update(tile_update)


location_map = Map()
previous_request_time = 0
json_content = '{"tiles": []}'
location = json.loads(json_content)
fps_meter = FpsMeter()
network_latency_meter = NetworkLatencyMeter()
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
            request_begin = time.time()
            content = ""
            with urllib.request.urlopen(URL) as f:
                content = f.read()
            request_end = time.time()
            network_latency_meter.add(1000 * (request_end-request_begin))
            json_content = content.decode('utf-8')
        except Exception as e:
            print(e)

        location = json.loads(json_content)
        location_map.update(location)

    display.fill((145, 132, 34))

    for i in range(len(location_map.tiles)):
        for j in range(len(location_map.tiles[i])):
            base_x = i * (TILE_SIZE[0] + INTERVAL_BETWEEN_TILES) + display_offset[0]
            base_y = j * (TILE_SIZE[1] + INTERVAL_BETWEEN_TILES) + display_offset[1]
            pygame.draw.rect(display, (77, 3, 204), ((base_x, base_y), (2*PORTRAIT_SIZE[0], 2*PORTRAIT_SIZE[1])))

            creatures = location_map.get_tile(i, j).creatures
            for k, creature in enumerate(creatures):
                if k == 0:
                    display.blit(get_image(creature._type + '.png'), (base_x, base_y))
                elif k == 1:
                    display.blit(get_image(creature._type + '.png'), (base_x + PORTRAIT_SIZE[0], base_y))
                elif k == 2:
                    display.blit(get_image(creature._type + '.png'), (base_x, base_y + PORTRAIT_SIZE[1]))
                elif k == 3:
                    display.blit(get_image(creature._type + '.png'), (base_x + PORTRAIT_SIZE[0], base_y + PORTRAIT_SIZE[1]))

    font = pygame.font.SysFont(pygame.font.get_default_font(), 40)
    caption = font.render(f"FPS: {fps_meter.fps()}", True, (255, 0, 0))
    display.blit(caption, (100, 0))

    latency = network_latency_meter.get_average_latency()
    if latency != "N/A":
        latency = round(latency, 2)
    caption = font.render(f"Network latency: {latency} ms", True, (255, 0, 0))
    display.blit(caption, (100, 70))

    pygame.display.update()
    pygame.time.delay(20)

    fps_meter.tick()
