#ifndef SRC_UNUSED_EXAMPLE2_H_
#define SRC_UNUSED_EXAMPLE2_H_

#include <AutoRegister.hpp>

#include <godot_cpp/classes/node.hpp>

namespace godot {
	class ExampleUnused : public Register<Node> {
			REGISTER_CLASS(ExampleUnused, Node)
		public:

			ExampleUnused();
			~ExampleUnused();

			static void _initialize_module();
			static void _uninitialize_module();

		protected:

			static void _bind_methods();
	};
}

#endif /* SRC_UNUSED_EXAMPLE2_H_ */
