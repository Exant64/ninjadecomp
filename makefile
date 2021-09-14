all: 	src\Binary\exe\Binary.lib \
		src\Chunk\exe\Chunk.lib \
		src\Collision\exe\Collision.lib \
		src\Draw\exe\Draw.lib \
		src\Effects\exe\Effects.lib \
		src\kamui\exe\kamui.lib \
		src\Light\exe\Light.lib \
		src\Math\exe\Math.lib \
		src\Motion\exe\Motion.lib \
		src\Particle\exe\Particle.lib \
		src\System\exe\System.lib \
		src\Texture\exe\Texture.lib \
		src\View\exe\View.lib 
src\Binary\exe\Binary.lib:
	$(MAKE) -C src\\Binary
src\Chunk\exe\Chunk.lib:
	$(MAKE) -C src\\Chunk\\Easy
	$(MAKE) -C src\\Chunk\\Simple
	$(MAKE) -C src\\Chunk
src\Collision\exe\Collision.lib:
	$(MAKE) -C src\\Collision
src\Draw\exe\Draw.lib:
	$(MAKE) -C src\\Draw
src\Effects\exe\Effects.lib:
	$(MAKE) -C src\\Effects
src\kamui\exe\kamui.lib:
	$(MAKE) -C src\\kamui
src\Light\exe\Light.lib:
	$(MAKE) -C src\\Light
src\Math\exe\Math.lib:
	$(MAKE) -C src\\Math
src\Motion\exe\Motion.lib:
	$(MAKE) -C src\\Motion
src\Particle\exe\Particle.lib:
	$(MAKE) -C src\\Particle
src\System\exe\System.lib:
	$(MAKE) -C src\\System
src\Texture\exe\Texture.lib:
	$(MAKE) -C src\\Texture
src\View\exe\View.lib:
	$(MAKE) -C src\\View
	
PROJECT =	ninja

PROJECT_LIBS = \
		src\Binary\exe\Binary\
		src\Chunk\exe\Chunk\
		src\Collision\exe\Collision\
		src\Draw\exe\Draw\
		src\Effects\exe\Effects\
		src\kamui\exe\kamui\
		src\Light\exe\Light\
		src\Math\exe\Math\
		src\Motion\exe\Motion\
		src\Particle\exe\Particle\
		src\System\exe\System\
		src\Texture\exe\Texture\
		src\View\exe\View

OPTIMIZE =	1

COMPILER =	SHC
GFXLIB =	
OUTPUT =	LIB

DEBUG  =	FALSE
LIST   =	FALSE


include dc.inc
