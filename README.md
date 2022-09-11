# base_gdextension

To start the project go to the folder `native` and create a build folder quer you can execute a cmake command referecing the `code` folder. You may need to update the godot `api.json` file at the `lib/api` folder with the command `godot --dump-extension-api extension_api.json`.

To add any code file just execute the cmake command.

You may need to link your library on the Godot Engine.

For the Auto Register to work you need to use the `Register<BASE_CLASS>` in the place of the godot class of your node. In the class `AutoRegister`, there is one MACRO `REGISTER_CLASS(MAIN_CLASS, BASE_CLASS)`, it replaces `GDCLASS(Name, Base)` and will register the class if the command `AutoRegister::register_initialize_classes();` is called in `initialize_module` for the `register_initializer`.