Micro Game Engine for Saxion Informatics, Game Programming.

The Code::Blocks project is targetted at windows and linus, both debug mode.

It needs 
- Code::Blocks >= 10.05
- GNU GCC compiler (g++ or mingw for windows and GDB for debugging). 
- GLM - latest. Be aware,i had a problem in xubuntu, used the respository version instead
  glm is a header only lib. Iǘe included my own "glm.hpp"  in the project including glm and adding some operator overloaders for printing 
- Glew - enables newest opengl functionality
- OpenGL -> needs proprietary driver for best perfomace ( NVidia driver )
- SFML 2.0 ! 1.6 IS different ! 
- Proprietary video drivers preferred
- 
- Astah Community for the UML schematics

Make sure to choose the right target for your os. libraries can have different names !
Also be aware that linux is case sensitive, windows is not (like #include <sfml/Window.hpp> will not work in linux, must be <SFML/Window.hpp>

Good luck.....

