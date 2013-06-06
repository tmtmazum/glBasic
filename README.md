glBasic
=======

A very simple &amp; basic wrapper for OpenGL 3D

=== Non-Essential Modules ===

* DEBUG.h : provides function { DEBUG }
  - A very minimalistic debugging class printing to std::cerr

=== Tier 1 Modules ===

* Angle.{h,cpp} : provides classes { anglePI , angleRAD , angleDEG , angleTAU }
  - Always use the proper constructor when specifying an angle
  - Auto-Casting routines from each of the angle classes provided
  
* Color.{h,cpp} : provides class { ColorRGBA } and namespace { Colors }
  - Provides basic preset colors for use
  - To use one of the colors from the 'Colors' namespace use:
    Colors::Red.get();
  - To define new colors, make a new namespace, add your colors
    as 'const static' variables and append to the end of Color.h

=== Tier 2 Modules ===

^ Inherits from Tier 1 modules ^ 

* Pos.{h,cpp} : provides { PosXY , PosRP , PosXYZ , PosRPT }
  - Use PosXY, PosRP to represent 2D Co-ordinates or two-dimensional vectors
  - Use PosXYZ, PosRPT to represent 3D Co-ordinates
  
  
=== Tier 3 Modules === 

^ Inherits from Tier 1 & 2 modules ^

* GEOMETRY.{h,cpp} : provides { GEOMETRY_OBJECT , GO_CUBE , GO_SPHERE , etc. }
  - Provides skeletons for defining various geometry structures
  - Only holds data describing dimensions of objects 
  
* Material.{h,cpp} : provides class { Material } and namespace { Materials }
  - Provides preset materials for use
  - Enables defining of custom materials for use

* transform.{h,cpp} : provides namespace { transform }
  - Provides simple transformations ( translation, rotation, scale ) for 2D/3D

=== Tier 4 Modules ===

^ Inherits from Tier 1,2 & 3 modules ^

* PosManager.{h,cpp} : provides { PosManager }
  - Provides a simple interface for creating long sets of lines or points
  - Not recommended for use (Deprecated) for draw polygons or other shapes
  
=== Tier 5 Modules ===

^ Inherits from all previous modules ^

* Draw.{h,cpp} : provides namespace { Draw }
(IMPORTANT)
  - Provides routines for drawing different structures

* CameraCEU.{h} : provides class { CameraCEU }
(IMPORTANT)
  - Provides an interface for setting up the camera viewport in opengl
  - Handles GL_PROJECTION and GL_MODELVIEW
  - Provides translate, rotate and scale operations
