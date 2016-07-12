How to build:
=============
Use the very osx only makefile, cmake is only used by my IDE for autocompletion.

Dependencies:
=============
1. sdl2 (`brew install sdl2`)
2. stb_image (`already in the repository`)

Implemented:
============
1. Materials: _Lambertian (matte), Metal, Dielectric (glass, water etc...)_
2. Primitives: _sphere, rectangle, axis-aligned box, triangle_
3. Textures: _checker, normal debug, bitmap texture_

Todo:
=====
1. Materials: _physically based materials (cook-torrance ?)_
2. Primitive: _plane, torus, open cylinder, cubic primitives_
3. Textures: _perlin_
4. Acceleration structure: _BVH (AABB)_
5. Complex mesh: _fractals ? 4 degree primitives ? triangulated meshes_
6. Rendering techniques: _ambient occlusion, depth of field, camera eye_