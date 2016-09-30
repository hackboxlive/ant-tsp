import pygame
import sys
from pygame.locals import *
import time
import random
import subprocess
import math

white = (255, 255, 255)
black = (0, 0, 0)
red = (255, 0, 0)
green = (0, 255, 0)
blue = (0, 0, 255)
yellow = (255, 255, 0)


pygame.init()
display = pygame.display.set_mode((800, 800))
pygame.display.set_caption('Ant Colony Optimisation Visualisation')

vertices = []


def run_ants():
	print "call to run ants"
	f = open("input", "w")
	n = len(vertices)
	m = (n * (n - 1)) / 2
	f.write(str(n) + " " + str(m) + "\n")
	for i in range(n):
		for j in range(i + 1, n):
			ux, uy = vertices[i]
			vx, vy = vertices[j]
			if i == j:
				continue
			else:
				dist = (ux - vx) ** 2 + (uy - vy) ** 2
				f.write(str(i + 1) + " " + str(j + 1) + " " + str(dist) + "\n")
	f.close()
	f = open("input", "r")
	of = open("output", "w")
	subprocess.call(["./a.out"], stdin = f, stdout = of)
	of.close()
	of = open("output", "r")
	path = map(int, of.readline().split())
	for i in range(n):
		for j in range(n):
			ux, uy = vertices[i]
			vx, vy = vertices[j]
			pygame.draw.line(display, (255, 255, 255), (ux, uy), (vx, vy), 1)
			time.sleep(0.05)
			pygame.display.update()

	for i in range(len(path) - 1):
		ux, uy = vertices[path[i] - 1]
		vx, vy = vertices[path[i + 1] - 1]
		print "drawing line b/w {}, {} and {}, {}".format(ux, uy, vx, vy)
		pygame.draw.line(display, (255, 0, 0), (ux, uy), (vx, vy), 5)
		time.sleep(0.4)
		pygame.display.update()
	of.close()


while True:
	for event in pygame.event.get():
		pygame.draw.rect(display, (255, 255, 255), (100, 700, 120, 50))
		mf = pygame.font.SysFont("monospace", 20)
		label = mf.render("Run Ants!", 2, black)
		display.blit(label, (105, 715))
		pygame.draw.rect(display, white, (580, 700, 120, 50))
		label = mf.render("Reset!", 2, black)
		display.blit(label, (605, 715))
		if event.type == QUIT:
			pygame.quit()
			sys.exit()
		elif event.type == MOUSEBUTTONDOWN:
			mouse_pos = list(pygame.mouse.get_pos())
			print mouse_pos[0], mouse_pos[1]
			x, y = mouse_pos
			if 100 <= x <= 220 and 700 <= y <= 750:
				run_ants()
			elif 580 <= x <= 700 and 700 <= y <= 750:
				display.fill(black)
				vertices = []
			else:
				pygame.draw.circle(display, (255, 255, 255), (x, y), 10)
				vertices.append(mouse_pos)
		pygame.display.update()