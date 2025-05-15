# base_gdextension

To start the project go to the folder `code`, and execute `cmake -Bbuild` to start the project. On windows you may need to specify the generator, for example, to use MinGW as your generator, `cmake -B build -G "MinGW Makefiles"`.

Now you can build the project with the `make` comand on the `build` file.

To add any code file just execute the cmake command.

You may need to adjust the library reference on the Godot Engine, on the file `library.gdextension`.
