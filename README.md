# base_gdnative

To start the project go to the folder `native` and create a build folder quer you can execute a cmake command referecing the `code` folder. You may need to update the godot `api.json` file at the `lib/api` folder with the command `godot --dump-extension-api extension_api.json`.

To add any code file just execute the cmake command.

You may need to link your library on the Godot Engine.

In the class `AutoRegister`, there are 2 MACROS `REGISTER_CLASS(MAIN_CLASS, BASE_CLASS)` and `REGISTER_TOOL(MAIN_CLASS, BASE_CLASS)`, both can replace `GODOT_CLASS(Name, Base)` and will register the class or tool if the command `AutoRegister::register_classes();` is called in `godot_native_script_init`, and the command `AutoRegister::generate_gdns("scripts", "gdnativelibrary");` auto generate gdns files in the `scripts` file linked with the `gdnativelibrary` if called in `godot_native_script_init`.

* [SavariaS](https://github.com/SavariaS)/[GDNativeAutoregister](https://github.com/SavariaS/GDNativeAutoregister) and [SeleDreams](https://github.com/SeleDreams)/[gdnative_class_factory](https://github.com/SeleDreams/gdnative_class_factory), were used as base to create the file `AutoRegister.hpp`.

Wasn't able to test to see if this works:

 * To import any library or CMake project add it at the `lib` folder and execute your cmake command.
