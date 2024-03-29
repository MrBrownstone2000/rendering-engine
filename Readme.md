# 3D Engine project

An attempt at building a well structured 3D rendering engine.

# Controls

- When the viewport is in focus:
    - ZQSD: move the camera position
    - C: Enable / Disable Camera rotation with mouse movements

# Features TODO List

- Mesh loading

- Materials
    - Has shader, and can set SOME shader uniforms (the ones material-related)
- Material instance
    - Has material instance
    - Has uniforms set to a certain value

=> easier sorting

- Unit Tests: Clean way to intercept calls to Check() / engine::Assertion()

- Get locations of all uniforms at shader compile time ?

- Assets storing: Virtual File System
    - minimum: mapping from os (actual path) to internal, abstract path
        - models: store internal representation in file (quicker to load) = baking

    - more advanced: 
        - need (fast) compression (LZ4 ?)
        - ressource compilation:
            - vertices / index in internal representation
            - images: stored in easily decompressed formats (DDS? DXT? TGA? PNG?)
                - wikipedia => texture compression
        - combine multiple assets in one file: 
            - read only (for read write, research actual file systems !!)
            - groups for assets loaded together ?
            - headers of group loaded first, then assets on read
- Frame Graph


# Issues

- Use modern opengl: https://github.com/fendevel/Guide-to-Modern-OpenGL-Functions

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

GLTF (fastgltf)
OBJ (fast-obj)
FBX (ufbx)
Eventually (better materials ?) Blender plugin
