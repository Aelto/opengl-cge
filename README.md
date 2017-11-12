# opengl-cge
OpenGL C++ game engine for educational purposes

# The goal
I'll use this repository to control and share my progress on my understanding of opengl. I'll test my knowledge by building a engine which will only serve as educational purposes.

# Building
I still have to look into that.
The project currently uses Visual Studio 2015 and opengl 4.3

# Features

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

- > **init** method
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

- > **newText** method
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
- > **setString** method
  ```cpp
  void setString(char * text);
  ```

  Usage example:
  ```cpp
  cge::Text textObject = textManager.newText("Hello world", 150, 150);

  textObject.setString("Custom message");
  ```

- > **render** method
  ```cpp
  void render();
  ```

  Usage example:
  ```cpp
  cge::Text textObject = textManager.newText("Hello world", 150, 150);

  textObject.render();
  ```

# Dependencies
- opengl
- glfw
- glew
- SOIL
