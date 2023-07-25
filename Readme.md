# 3D Engine project

An attempt at building a well structured 3D rendering engine.

# Features TODO List

- Mesh
- Mesh loading
- Test mesh + camera
- Materials

- Framebuffers 

# Issues

- less namespaces ! 
- Use mordern opengl: https://github.com/fendevel/Guide-to-Modern-OpenGL-Functions
- Test framework: 
    - build test core files to shared lib
    - Test framework as submodule

# Design improvements ideas

- SpdLog (multithreaded, more functionality ?) + callbacks to display stack trace
- ECS

# Structure

3 stages:

- Culling
- Render (to an emulated command buffer)
- Dispatch to OpenGL

## Culling

For all types of objects

- Meshes
- Lights
- Particles (if ever applicable)

## Command buffer

Make commands stateless: have ALL the information they need to render.

[Can sort draw calls in the buffer layer](https://realtimecollisiondetection.net/blog/?p=86)

Use block allocator, chained together if necessary -> improved data locality

## Dispatch of commands

Even a simulated command buffer accelerates rendering!

Due to better cache utilization, with less back and forth between driver and
engine.


# Models and data

Use FBX or DAE format only (full scene format, more descriptive (materials!))
