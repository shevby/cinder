from collections import defaultdict
import json
import os
import pygame
import sys
import urllib.request


URL = "http://localhost:6789"
PORTRAIT_SIZE = (100, 100)
TILE_SIZE = (2*PORTRAIT_SIZE[0], 2*PORTRAIT_SIZE[1])
INTERVAL_BETWEEN_TILES = 20


display = pygame.display.set_mode()


portraits_cache = {}
def get_image(name):
    if name in portraits_cache:
        return portraits_cache[name]

    image = pygame.image.load(os.path.dirname(os.path.realpath(__file__)) + "/pics/" + name).convert_alpha()
    image = pygame.transform.smoothscale(image, PORTRAIT_SIZE)

    portraits_cache[name] = image
    return image


json_content = '{"tiles": [[]]}'
while(True):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

    try:
        with urllib.request.urlopen(URL) as f:
            json_content = f.read().decode('utf-8')
    except:
        pass

    display.fill((145, 132, 34))

    location = json.loads(json_content)

    for i in range(len(location['tiles'])):
        for j in range(len(location['tiles'][i])):
            creatures = location['tiles'][i][j][0]['creatures']
            for k, creature in enumerate(creatures):
                base_x = i * (TILE_SIZE[0] + INTERVAL_BETWEEN_TILES)
                base_y = j * (TILE_SIZE[1] + INTERVAL_BETWEEN_TILES)
                pygame.draw.rect(display, (77, 3, 204), ((base_x, base_y), (2*PORTRAIT_SIZE[0], 2*PORTRAIT_SIZE[1])))
                if k == 0:
                    display.blit(get_image(creature['type'] + '.png'), (base_x, base_y))
                elif k == 1:
                    display.blit(get_image(creature['type'] + '.png'), (base_x + PORTRAIT_SIZE[0], base_y))
                elif k == 2:
                    display.blit(get_image(creature['type'] + '.png'), (base_x, base_y + PORTRAIT_SIZE[1]))
                elif k == 3:
                    display.blit(get_image(creature['type'] + '.png'), (base_x + PORTRAIT_SIZE[0], base_y + PORTRAIT_SIZE[1]))


    pygame.display.update()
    pygame.time.delay(100)

