#ifndef SRC_GDEXTENSION_REGISTER_HPP_
#define SRC_GDEXTENSION_REGISTER_HPP_

#include "AutoRegister.hpp"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/string.hpp>
#include <string>

template<typename G>
class Register: public G {
//	REGISTER_CLASS(B, G);
	private:
	protected:

		template<class C>
		C* _instanciate_node(godot::String name) {
			C *c = (C*) this->get_node_or_null(name);
			if (c == nullptr) {
				c = memnew(C);
				c->set_name(name);
				this->add_child(c);
				c->set_owner(this);
			}
			return c;
		}

		template<class C>
		C* _instanciate_node_in_node(godot::Node *n, godot::String name) {
			C *c = (C*) n->get_node_or_null(name);
			if (c == nullptr) {
				c = memnew(C);
				c->set_name(name);
				n->add_child(c);
				c->set_owner(this);
			}
			return c;
		}

	public:

		static void _initialize_module() {
		}

		static void _uninitialize_module() {
		}

};

#endif /* SRC_GDEXTENSION_REGISTER_HPP_ */
