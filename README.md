# opengl-cge
OpenGL C++ game engine for educational purposes

# The goal
I'll use this repository to control and share my progress on my understanding of opengl. I'll test my knowledge by building a engine which will only serve as educational purposes.

# Building
I still have to look into that.
The project currently uses Visual Studio 2015 and opengl 4.3

# Features

## Application manager
Easily create a window with the specified title, width and height with a singleton.

#### Constructor
```cpp
app(GLuint _width, GLuint _height);
```
Takes as parameters the window width and the window height

#### Methods

- **open** method
  ```cpp
  void open(int GL_major, int GL_minor, const char * name);
  ```
  The first two parameters specify the major and minor versions of opengl, the third parameter is the new window's name

  Usage example:
  ```cpp
  cge::app app(1250, 900);
  app.open(4, 3, "opengl engine");
  ```

- **shouldClose** method
  ```cpp
  int shouldClose();
  ```
  returns `1` if the current application should close.
  **note**: There is another method wrapping `shouldClose()` that should **always** be used, that is `startLoop()`

  Usage example:
  ```cpp
  cge::app app(1250, 900);
  app.open(4, 3, "opengl engine");
  
  while (!app.shouldClose()) {
    // do something...
  }
  ```

- **startLoop** method
  ```cpp
  int startLoop();
  ```
  prepare the application for the next rendering call. Returns `1` if the current application should close.
  **note**: this method return the result from the `shouldClose()` method

  Usage example:
  ```cpp
  cge::app app(1250, 900);
  app.open(4, 3, "opengl engine");
  
  while (!app.startLoop()) {
    // do something...
  }
  ```

- **endLoop** method
  ```cpp
  void endLoop();
  ```
  Swaps the opengl buffer.
  Internally check if the escape key was pressed to close the application

  Usage example:
  ```cpp
  cge::app app(1250, 900);
  app.open(4, 3, "opengl engine");
  
  while (!app.startLoop()) {
    
    app.endLoop();
  }
  ```

#### Properties

- **keys** property
  ```cpp
  bool keys[1024];
  ```
  can be used to check if a key was pressed between the last loop iteration and the new one. the event key poll is made at the beginning of the loop in the `startLoop()` method.

  ```cpp
  while (!app.startLoop()) {
    if (app.keys[GLFW_KEY_W] == true) {
      std::cout << "W key was pressed\n";
    }

    app.endLoop();
  }
  ```

## Camera system
A virtual 2D camera system

#### Constructor
```cpp
Camera(GLuint width, GLuint height);
```
takes as parameters the viewport' width and height.

#### Methods

- > **updateView** method
  ```cpp
  void updateView();
  ```

  Usage example:
  ```cpp
  cge::app app(1250, 900);
  app.open(4, 3, "opengl engine");
	
  cge::Camera camera(app.width, app.height);

  while (!app.startLoop()) {
    camera.updateView();
		
    app.endLoop();
  }
  ```

#### Methods

- > **runFollow** method
  ```cpp
  void runFollow();
  ```
  make the camera follow the followed vector position stored.

  Usage example:
  ```cpp
  cge::app app(1250, 900);
  app.open(4, 3, "opengl engine");
	
  cge::Camera camera(app.width, app.height);

  while (!app.startLoop()) {
    camera.updateView();
    camera.runFollow();
		
  app.endLoop();
  }
  ```

### Properties

- **followedPosition** property
  ```cpp
  glm::vec2 * followedPosition;
  ```
  Vector pointer to the vector position you want the camera to follow when running the `runFollow()` method.

- **anchor** property
  ```cpp
  glm::vec2 anchor;
  ```
  It is a 2D vector defining the anchor point for the camera's followed position.
  With the vector `[x, y]` when set to `[0.5, 0.5]` the anchor point is set to the center of the viewport.
    - X defines the horizontal position from left to right between 0 and 1.
    - Y defines the vertical position from top to bottom between 0 and 1.

- **followSpeed** property
  ```cpp
  GLfloat followSpeed;
  ```
  this value should be set between 0 and 1. And defines the number of steps required for the camera to get to the followedPosition

## Spritebatch system
Efficient 2D rendering with the spritebatch class

### Constructor
```cpp
SpriteBatch();
```

usage Example:
```cpp
cge::SpriteBatch batch;
```

### Methods

- **begin** method
  ```cpp
  void begin();
  ```
  Set up everything to begin the spritebatch collecting

- **end** method
  ```cpp
  void end();
  ```
  Set up everything for the batch.render() method

- **render** method
  ```cpp
  void render();
  ```
  uses all the data collected between the `begin` and `end` methods to render to the screen the glyphes

  Usage example:
  ```cpp
  cge::app app(1250, 900);
  app.open(4, 3, "opengl engine");
	
  cge::Camera camera(app.width, app.height);
  cge::SpriteBatch batch;

  while (!app.startLoop()) {
    batch.begin();

    // rendering calls

    batch.end();
    batch.rener();

    app.endLoop();
  }
  ```

## Textures
Load 2D textures with ResourceManager

### Constructor
```cpp
Texture2D();
```

usage Example:
```cpp
cge::Texture2D texture_circle = cge::ResourceManager::LoadTexture("assets/circle.png", GL_TRUE, "circle");
```

### Methods
> No methods that should be manually called

## Collision classes
You can use the `cge::hitbox` class to instanciate the hitbox of a 2D sprite.

### Constructor
```cpp
Hitbox(glm::vec2 customSize, glm::vec2 customPosition);
```

### Methods

- **intersects** method
  ```cpp
  bool Hitbox::intersects(Hitbox * obj, glm::vec2 & obj1_position, glm::vec2 obj2_position)
  ```

  return `true` if this hitbox and the supplied hitbox intersects. As an hitbox can be linked to many elements in a 1 hitbox to many elements relation. The object 1's hitbox and the object 2's hitbox must be passed in the parameters. The object 1 is the one linked to this hitbox, the object 2 is the one linked to the supplied hitbox pointer.
  **note**: this method should not be called manually, it is called internally by the `Sprite` class in the `Sprite::intersects` method.

- **resolve** method
  ```cpp
  void Hitbox::resolve(Hitbox * obj, glm::vec2 & obj1_position, glm::vec2 obj2_position)
  ```

  Move the two objects so that they don't intersect anymore.
  **note**: this mothoud should not be called manually, it is called internally by the `Sprite` class in the `Sprite::intersects` method.


## Helper
A singleton that provides many helper methods such as FPS count, delta between frames...

### Constructor
```cpp
helper();
```

### Methods

- **getDelta** method
  ```cpp
  GLfloat getDelta();
  ```
  return the value of the delta-time between the current frame and the last one. Useful to get framerate independant velocity, camera movement and all.

  Usage example:
  ```cpp
  cge::app app(1250, 900);
  app.open(4, 3, "opengl engine");

  cge::helper helper;

  GLfloat delta = helper.getDelta();
  while (!app.startLoop()) {

    delta = helper.getDelta();

    app.endLoop();

  }
  ```

- **coutFramerate()** method
  ```cpp
  void coutFramerate();
  ```
  std::cout the framerate

  Usage example:
  ```cpp
  cge::app app(1250, 900);
  app.open(4, 3, "opengl engine");

  cge::helper helper;

  GLfloat delta = helper.getDelta();
  while (!app.startLoop()) {

    delta = helper.getDelta();
    helper.coutFramerate();

    app.endLoop();

  }
  ```

## Texture rendering
Allows the rendering of 2D fixed textures.

### Constructor
```cpp
Sprite();

Sprite(glm::vec2 pos, glm::vec2 size, cge::Texture2D * _texture);
```

### Methods

- **batchDraw** method
  ```cpp
  virtual void batchDraw(cge::SpriteBatch & spriteBatch);
  ```

  Usage example
  ```cpp
  cge::app app(1250, 900);
  app.open(4, 3, "opengl engine");

  cge::Camera camera(app.width, app.height);
  cge::SpriteBatch batch;

  cge::Texture2D texture_tile = cge::ResourceManager::LoadTexture("assets/tile.png", GL_TRUE, "tile");

  cge::Hitbox tileBox(glm::vec2(100.0f, 100.0f), glm::vec2(0.0f, 0.0f));

  cge::Sprite obstacle(glm::vec2(525.0f, 525.0f), glm::vec2(100.0f, 100.0f), &texture_tile);
  obstacle.addBox(&tileBox);

  while (!app.startLoop()) {
    batch.begin();

    obstacle.batchDraw(batch);

    batch.end();
    batch.rener();

    app.endLoop();
  }
  ```

- **addBox** method
  ```cpp
  void addBox(Hitbox * _box);
  ```
  set the hitbox

  Usage example:
  ```cpp
  cge::Texture2D texture_tile = cge::ResourceManager::LoadTexture("assets/tile.png", GL_TRUE, "tile");

  cge::Hitbox tileBox(glm::vec2(100.0f, 100.0f), glm::vec2(0.0f, 0.0f));

  cge::Sprite obstacle(glm::vec2(525.0f, 525.0f), glm::vec2(100.0f, 100.0f), &texture_tile);
	obstacle.addBox(&tileBox);
  ```

- **applyAcceleration** method
  ```cpp
  void applyAcceleration(const GLfloat delta);
  ```

  Add the value of this->acceleration to `this->velocity`, then resets the acceleration value. It should be called before `this->applyVelocity()`.

- **applyVelocity** method
  ```cpp
  void applyVelocity(const GLfloat delta);
  ```
  Add the value of `this->velocity` to `this->position`.	It should be called just before `this->drawBatch()`

- **applyFriction** method
  ```cpp
  void applyFriction(const GLfloat factor);
  ```
  multiply the velocity by the factor

## Animated texture rendering
Spritesheets support with the `cge::SpriteSheet` class and the `cge::AnimationsUV` class

### AnimationsUv
The `AnimationsUv` class serves as a storage for animations based on UV coordinates in a spritesheet. You can declare in the spritesheet multiple animations with custom names, custom lengths and durations.

#### Constructor
```cpp
AnimationsUV(int _rows, int _columns);
```

#### Methods

- **setAnimation** method
  ```cpp
  AnimationsUV & setAnimation(std::string & name, int _beginX, int _beginY, int _endX, int _endY, float _timePerCell)
  ```
  add an animation to the registry

  Usage example:
  ```cpp
  cge::AnimationsUV(3, 9).setAnimation(std::string("default"), 0, 0, 6, 0, 1000)
  ```

- **setCurrentAnimation** method
  ```cpp
  bool setCurrentAnimation(std::string & name);
  ```
  this method tries to change to a new animation **only** if a stored animation exists with the same name as the supplied string.

- **time** method
  ```cpp
  void time(float delta);
  ```
  Adds a tick to the counter, automatically changes the current cell if `currentTick >= ticksPerCell`

### SpriteAnimation

#### Constructor
```cpp
SpriteAnimation(glm::vec2 pos, glm::vec2 _size, cge::Texture2D * _texture, AnimationsUV _animationsUV);
```

#### Methods

- **batchDraw** method
  ```cpp
  virtual void batchDraw(cge::SpriteBatch & spriteBatch);
  ```

- **time** method
  ```cpp
  void time(float delta);
  ```

## Text rendering
Offers easy text rendering with 2 classes
 - `cge::TextManager`
 - `cge::Text`

Text rendering should be done by first defining a `TextManager` instance by passing to the init function the windows width and the windows height.

### Text Manager

#### Constructor
```cpp
TextManager();
```

#### Methods

- **init** method
  ```cpp
  bool init(GLuint width, GLuint height);
  ```

  Usage example:
  ```cpp
  cge::app app(1250, 900);
  app.open(4, 3, "opengl app");

  cge::TextManager textManager;
  textManager.init(app.width, app.height);
  ```

- **newText** method
  ```cpp
  Text newText(char* text, GLfloat x = 0, GLfloat y = 0, GLfloat scale = 1, glm::vec3 color = glm::vec3(1, 1, 1));
  ```

  Usage example:
  ```cpp
  cge::app app(1250, 900);
  app.open(4, 3, "opengl app");

  cge::TextManager textManager;
  textManager.init(app.width, app.height);

  cge::Text textObject = textManager.newText("Hello world", 150, 150);
  ```


### Text

#### Constructor
```cpp
Text(char* text, TextManager * manager, GLfloat x = 0, GLfloat y = 0, GLfloat scale = 1, glm::vec3 color = glm::vec3(1, 1, 1));
```

#### Methods
- **setString** method
  ```cpp
  void setString(char * text);
  ```

  Usage example:
  ```cpp
  cge::Text textObject = textManager.newText("Hello world", 150, 150);

  textObject.setString("Custom message");
  ```

- **render** method
  ```cpp
  void render();
  ```

  Usage example:
  ```cpp
  cge::Text textObject = textManager.newText("Hello world", 150, 150);

  textObject.render();
  ```

# Dependencies
- opengl (use the one provided by your operating system)
- [glfw](http://www.glfw.org/)
- [glew](http://glew.sourceforge.net/)
- [SOIL](http://www.lonesock.net/soil.html)
