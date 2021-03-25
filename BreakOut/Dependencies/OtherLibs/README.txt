1. stb_image.h
- Description: stb_image.h is a very popular single header image loading library by Sean Barrett that is able to load most popular file formats and is easy to integrate in your project(s)
- Link: https://github.com/nothings/stb/blob/master/stb_image.h

2. Shader Class:
- Description: contain shader class which is created once 

3. stb_image:
- Load different types of image

4. Assimp:
- Description: Assimp is able to import dozens of different model file formats (and export to some as well) by loading all the model's data into Assimp's generalized data structures
- The Open-Asset-Importer-Lib: http://assimp.org/
- WaveFront format Link: https://en.wikipedia.org/wiki/Wavefront_.obj_file
  Model formats like the Wavefront.obj only contains model data with minor material information like model colors and diffuse/specular maps
- Collada format Link: https://en.wikipedia.org/wiki/COLLADA
  while model formats like the XML-based Collada file format are extremely extensive and contain models, lights, many types of materials, animation data, cameras, complete scene information, and much more

5. Mesh files:
- One model/scene contains RootNode, Materials and Meshes

- Contains Vertices,
  Normal vectors, 
  Texture coordinates, 
  faces (a Face represents a render primitive of the object (triangles, squares, points), 
  Material index

6. Model class:
- Used to store properties of model into one class:
  https://learnopengl.com/Model-Loading/Assimp
  follow the link to check the Assimp's structure:
  + Scence is the container
  + Scence contains RootNode, Meshes, Materials
  + Node contains children Node and Meshes