## Project Source Directory

Your Runtime++ project source code needs to live in this folder. The src/CMakeLists.txt file shipped with Runtime++ is programmed
to recursively add every source file in this directory, so feel free to structure your project however you so desire.

### Working with Runtime++

As you can see, this directory comes with a default Runtime++ entry point and a state called "NewRuntimeState". You are welcome to change the names or move any files in this directory, but remember that Runtime++ needs a syntactically valid RuntimeEngineState to begin.

Please consult the Runtime++ documentation [here](https://google.com) (Sorry, there is no completed documentation yet, but it will be added soon) for further instruction on how to use this framework.

### Testing Your Runtime++ Application

When you're ready to test your application, follow the instructions below for your platform...

#### macOS and Linux
```bash
# Start a terminal in the root git directory, then...
cd project
sh ./run.sh
```
#### Windows

Instructions to be added when I can test on a Windows machine.