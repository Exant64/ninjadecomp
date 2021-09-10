@echo off

cd src

cd Binary
make
cd ..

cd Chunk
cd Easy
make
cd..
cd Simple
make
cd..
make
cd ..

cd Collision
make
cd ..

cd Draw
make
cd ..

cd Effects
make
cd ..

cd kamui
make
cd ..

cd Light
make
cd ..

cd Math
make
cd ..

cd Motion
make
cd ..

cd Particle
make
cd ..

cd System
make
cd ..

cd Texture
make
cd ..

cd View
make
cd ..

cd ..

make
