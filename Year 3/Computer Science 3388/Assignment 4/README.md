# Assignment 4

## Description
This assignment consists of the writing of a simple non-recursive ray-tracing program using OpenGL and C/C++ that creates an image of a scene containing a number of simple generic objects.

We intend to build a ray tracer application where the scene will contain at least three spheres of different sizes and colours on a plane. There will be ambient, diffuse and specular lights in the scene. The light will have specular reflection effect on the surface of the sphere(s). Also, the spheres will cast shadows on the floor and on each other’s surface (depending on the light position). Finally, the spheres (or balls) will bounce on the floor.

## Implementation
1. Define three generic spheres with different radius and simple color at- tributes.
2. Place a synthetic camera at a convenient distance from the spheres so that all the spheres are clearly visible.
3. Code and test the ray casting algorithm (cast the rays and compute in- tersection points, and normal vectors). Without shading, the ray tracer should render what would look like three circles of different colours within the rendering window.
4. Once this is working, add a white light source, and implement the diffuse lighting component. The 3D shape of the sphere should become visible, however no specular reflection will show on the sphere.
5. Place a plane to create a ground surface, and render it. At this point the scene should start to look more or less realistic.
6. Implement specular reflection and see that you get a bright spot on the sphere consonant with the position of the light.
7. At this point, the spheres do not cast shadow on the ground plane and on each other’s surface. Implement shadow ray casting to create that effect. Place the spheres at convenient distance from each other so that the shadow on their surface is clearly visible. However, the shadow area will appear completely black. You can use the ambient part of the lighting model to resolve this problem (there will be some marks for aesthetic part of the rendering).
8. Animate the scene by bouncing the balls on the plane. The shadows should change accordingly.
